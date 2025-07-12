#include <ColdTable/Graphics/VertexBuffer.h>

#include "GraphicsDevice.h"
#include "GraphicsLogUtil.h"

ColdTable::VertexBuffer::VertexBuffer(VertexBufferDesc desc): Base(desc.base), _buffer(0), _layout(0)
{
}

ColdTable::VertexBuffer::~VertexBuffer()
{
	if (_buffer)
	_buffer->Release();
	if (_layout)
	_layout->Release();
}

void ColdTable::VertexBuffer::LoadVertices(const void* list, UINT vertexSize, UINT listSize, ShaderPtr shader)
{
	_shader = shader;
	if (_buffer) _buffer->Release();
	if (_layout) _layout->Release();
	_vertices.clear();

	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = vertexSize * listSize;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData{};
	initData.pSysMem = list;

	_vertexSize = vertexSize;
	_listSize = listSize;

	ColdTableGraphicsLogThrowOnFail(shader->_sourceDevice->_d3dDevice->CreateBuffer(&bufferDesc, &initData, &_buffer),
		"CreateBuffer failed.");


	D3D11_INPUT_ELEMENT_DESC layout[] = 
	{
		{"POSITION",0, DXGI_FORMAT_R32G32B32_FLOAT,0, 0,D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD",0, DXGI_FORMAT_R32G32_FLOAT,0, 12,D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"NORMAL",0, DXGI_FORMAT_R32G32B32_FLOAT,0, 20,D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",0, DXGI_FORMAT_R32G32B32_FLOAT,0, 32,D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//{"COLOR",1, DXGI_FORMAT_R32G32B32_FLOAT,0, 24,D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	UINT layoutSize = ARRAYSIZE(layout);

	ColdTableGraphicsLogThrowOnFail(shader->_sourceDevice->_d3dDevice->CreateInputLayout(layout, layoutSize, shader->_vertexShaderBlob->GetBufferPointer(), shader->_vertexShaderBlob->GetBufferSize(), &_layout),
		"CreateInputLayer failed.")

	const Vertex* vert = static_cast<const Vertex*>(list);
	for (int i = 0; i < listSize; i++)
	{
		VertexPtr vertex = std::make_shared<Vertex>( (vert + i)->position, (vert + i)->texcoord, (vert + i)->normal, (vert + i)->color );
		_vertices.push_back(vertex);
		_stagingVerts.push_back(*vertex);
	}

	// Create staging buffer
	D3D11_BUFFER_DESC stagingDesc{};
	stagingDesc.Usage = D3D11_USAGE_STAGING;
	stagingDesc.ByteWidth = _vertexSize * _listSize;
	stagingDesc.BindFlags = 0;
	stagingDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	stagingDesc.MiscFlags = 0;

	_stagingBuffer = nullptr;
	ColdTableGraphicsLogThrowOnFail(
		shader->_sourceDevice->_d3dDevice->CreateBuffer(&stagingDesc, nullptr, &_stagingBuffer),
		"Create staging buffer fail.");
}

void ColdTable::VertexBuffer::UpdateVertexData()
{
	if (!_canUpdateVertex || !_isDirty || !_stagingBuffer) return;

	// Copy vertex data on GPU to staging buffer
	_shader->_sourceDevice->_d3dContext->CopyResource(_stagingBuffer, _buffer);
	_shader->_sourceDevice->_d3dContext->Flush();

	// Create Mapped Resource
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	// Disable GPU access by mapping resource of staging buffer
	_shader->_sourceDevice->_d3dContext->Map(_stagingBuffer, 0, D3D11_MAP_READ, 0, &mappedResource);

	// Reset staging vertices
	for (int i = 0; i < _vertices.size(); i++)
	{
		//Logger::Log(Logger::LogLevel::Info, ("Staging vert1: " + _stagingVerts[i].position.toString()).c_str());
		_stagingVerts[i] = (*(_vertices[i]));
	}

	// Calculate and Update the vertex buffer
	for (auto vertObj : _vertexObjects)
	{
		for (auto vertIndex : vertObj->_vertexIndices)
		{
			_stagingVerts[vertIndex].position = vertObj->getActualPos();
		}
	}

	Vertex* bufferVertex = reinterpret_cast<Vertex*>(mappedResource.pData);
	for (UINT i = 0; i < _listSize; i++)
	{
		bufferVertex[i] = _stagingVerts[i];
		//Logger::Log(Logger::LogLevel::Info, _stagingVerts[i].position.toString().c_str());
	}
	_shader->_sourceDevice->_d3dContext->UpdateSubresource(_buffer, NULL, NULL, (void*)bufferVertex, NULL, NULL);

	// Re-enable GPU access
	_shader->_sourceDevice->_d3dContext->Unmap(_stagingBuffer, 0);
}

UINT ColdTable::VertexBuffer::GetVertexCount()
{
	return _listSize;
}
