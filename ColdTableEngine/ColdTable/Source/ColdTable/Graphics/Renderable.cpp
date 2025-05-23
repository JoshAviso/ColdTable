#include <ColdTable/Graphics/Renderable.h>

#include "Shader.h"
#include "VertexBuffer.h"

ColdTable::Renderable::Renderable(const RenderableDesc& desc) : Base(desc.base), _shader(desc.shader), _drawMode(desc.drawMode)
{
	VertexBufferDesc bufferDesc{ {_logger} };
	_vertexBuffer = std::make_shared<VertexBuffer>(bufferDesc);
	LoadVertices(desc.vertexList, desc.vertexCount);
}

ColdTable::Renderable::~Renderable()
{

}

void ColdTable::Renderable::LoadVertices(const Vertex* vertexList, UINT listSize)
{
	_vertexBuffer->LoadVertices(vertexList, sizeof(Vertex), listSize, _shader);
}

void ColdTable::Renderable::SetShader(ShaderPtr shader)
{
	_shader = shader;
}
