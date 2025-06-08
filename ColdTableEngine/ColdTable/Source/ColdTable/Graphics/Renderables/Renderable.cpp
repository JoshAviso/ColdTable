#include <ColdTable/Graphics/Renderables/Renderable.h>

#include <ColdTable/Graphics/EngineShader.h>
#include <ColdTable/Graphics/VertexBuffer.h>

ColdTable::Renderable::Renderable(const RenderableDesc& desc) : _shader(desc.shader), _drawMode(desc.drawMode)
{
	VertexBufferDesc bufferDesc{ {} };
	_vertexBuffer = std::make_shared<VertexBuffer>(bufferDesc);
	if (desc.vertexCount > 0)
		LoadVertices(desc.vertexList, desc.vertexCount);
}

ColdTable::Renderable::~Renderable()
{

}

void ColdTable::Renderable::LoadVertices(const Vertex* vertexList, UINT listSize)
{
	if (_indexBuffer) _indexBuffer = nullptr;

	vertexListRef = vertexList;
	_vertexBuffer->LoadVertices(vertexList, sizeof(Vertex), listSize, _shader);
}

void ColdTable::Renderable::LoadVerticesInIndex(const Vertex* vertexList, UINT listSize, const IndexBufferPtr& indexBuffer)
{
	_indexBuffer = indexBuffer;

	vertexListRef = vertexList;
	_vertexBuffer->LoadVertices(vertexList, sizeof(Vertex), listSize, _shader);
}

void ColdTable::Renderable::Update(const d64 deltaTime)
{

}

void ColdTable::Renderable::SetShader(ShaderPtr shader)
{
	_shader = shader;
}

ColdTable::Mat4 ColdTable::Renderable::transformMat() const
{
	Mat4 scaleMat = {
		localScale.x, 0.0, 0.0, 0.0,
		0.0, localScale.y, 0.0, 0.0,
		0.0, 0.0, localScale.z, 0.0,
		0.0, 0.0, 0.0, 1.0
	};
	Mat4 translateMat = {
		 1.0, 0.0, 0.0, localPosition.x ,
		0.0, 1.0, 0.0, localPosition.y ,
		0.0, 0.0, 1.0, localPosition.z ,
		 0.0, 0.0, 0.0, 1.0 
	};

	//return Mat4::Identity;

	return translateMat * static_cast<Mat4>(localRotation) * scaleMat;
}

void ColdTable::Renderable::OnKeyDown(int key)
{
	if (key == 'W')
	{
		localRotation.rotate({ {1.0f, 0.0f, 0.0f}, 5.0f });
	}

	if (key == 'S')
	{
		localRotation.rotate({ {1.0f, 0.0f, 0.0f}, -5.0f });
	}
	if (key == 'D')
	{
		localRotation.rotate({ {0.0f, 1.0f, 0.0f}, -5.0f });
	}
	if (key == 'A')
	{
		localRotation.rotate({ {0.0f, 1.0f, 0.0f}, 5.0f });
	}
}

void ColdTable::Renderable::OnKeyUp(int key)
{
}

void ColdTable::Renderable::OnMouseMove(Vec2 delta)
{
	localRotation.rotate({ {-1.0f, 0.0f, 0.0f}, delta.y });
	localRotation.rotate({ {0.0f, -1.0f, 0.0f}, delta.x });
}
