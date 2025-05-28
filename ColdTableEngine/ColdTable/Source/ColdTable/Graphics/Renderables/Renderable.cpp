#include <ColdTable/Graphics/Renderables/Renderable.h>

#include <ColdTable/Graphics/Shader.h>
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
	_vertexBuffer->LoadVertices(vertexList, sizeof(Vertex), listSize, _shader);
}

void ColdTable::Renderable::SetShader(ShaderPtr shader)
{
	_shader = shader;
}
