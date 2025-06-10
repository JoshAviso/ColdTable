#include <string>
#include <ColdTable/Graphics/Renderables/Renderable.h>

#include <ColdTable/Graphics/EngineShader.h>
#include <ColdTable/Graphics/VertexBuffer.h>

#include "ColdTable/Resource/Material/Material.h"

ColdTable::Renderable::Renderable(const RenderableDesc& desc) : _shader(0), _drawMode(desc.drawMode), _material(desc.material)
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
	_vertexBuffer->LoadVertices(vertexList, sizeof(Vertex), listSize, _material->_shader);
}

void ColdTable::Renderable::LoadVerticesInIndex(const Vertex* vertexList, UINT listSize, const IndexBufferPtr& indexBuffer)
{
	_indexBuffer = indexBuffer;

	vertexListRef = vertexList;
	_vertexBuffer->LoadVertices(vertexList, sizeof(Vertex), listSize, _material->_shader);
}

void ColdTable::Renderable::Update(const d64 deltaTime)
{

}

void ColdTable::Renderable::SetShader(ShaderPtr shader)
{
	_shader = shader;
}

void ColdTable::Renderable::SetTexture(TexturePtr texture)
{
	_texture = texture;
}

ColdTable::Mat4 ColdTable::Renderable::transformMat() const
{
	Mat4 scaleMat = localScale.asScaleMatrix();
	Mat4 translateMat = localPosition.asTranslationMatrix();

	return translateMat * static_cast<Mat4>(localRotation) * scaleMat;
}

void ColdTable::Renderable::OnKeyDown(int key)
{
	/*
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
	*/
}

void ColdTable::Renderable::OnKeyUp(int key)
{
}

void ColdTable::Renderable::OnMouseMove(Vec2 delta)
{
	/*
	localRotation.rotate({ {-1.0f, 0.0f, 0.0f}, delta.y });
	localRotation.rotate({ {0.0f, -1.0f, 0.0f}, delta.x });*/
}

void ColdTable::Renderable::OnLeftMouseDown(Vec2 pos)
{
	/*
	localScale += {0.1f, 0.1f, 0.1f};
	*/
}

void ColdTable::Renderable::OnRightMouseUp(Vec2 pos)
{
	/*
	localScale -= {0.1f, 0.1f, 0.1f};
	*/
}
