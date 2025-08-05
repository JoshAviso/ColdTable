#pragma once

#include <intsafe.h>
#include <vector>
#include <ColdTable/Core/Base.h>
#include <ColdTable/Core/Common.h>
#include <ColdTable/Math/Vertex.h>
#include <ColdTable/Graphics/GraphicsEnums.h>
#include <ColdTable/Math/Mat4.h>
#include <ColdTable/Math/Quaternion.h>

#include "ColdTable/Editor/FaceObject.h"
#include "ColdTable/Input/IInputListener.h"
#include "ColdTable/Editor/IEditorPickable.h"

namespace ColdTable
{
	struct RenderableDesc
	{
		Vertex* vertexList;
		UINT vertexCount;
		EGeometryDrawmode drawMode;
		MaterialPtr material;
	};

	class Renderable : public std::enable_shared_from_this<Renderable>
	{
	public:
		Renderable(const Renderable& other);
		explicit Renderable(const RenderableDesc& desc);
		explicit Renderable(const RenderableDesc& desc, const ShaderPtr& shader);
		virtual ~Renderable();

		virtual void LoadVertices(const Vertex* vertexList, UINT listSize);
		virtual void LoadVerticesInIndex(const Vertex* vertexList, UINT listSize, const IndexBufferPtr& indexBuffer);
		void ReloadVertices();

	public:
		Vec3 localPosition = Vec3::Zero;
		Vec3 localScale = Vec3::Identity;
		Quaternion localRotation = Quaternion::Identity;
		Mat4 transformMat() const;

	protected:
		VertexBufferPtr		_vertexBuffer;
		IndexBufferPtr		_indexBuffer;
		EGeometryDrawmode	_drawMode;

		MaterialPtr			_material;
		ShaderPtr			_shader;

		const Vertex* vertexListRef;
		std::vector<FaceObjectPtr> _faceObjects{};

	public:
		void recalcAABB();

	public:
		Vec3 aabb_min{0, 0, 0};
		Vec3 aabb_max{0, 0, 0};

	private:
		friend class DeviceContext;
		friend class GraphicsEngine;
		friend class Ray;
		friend class VertexObject;
		friend class EdgeObject;
		friend class FaceObject;
		friend class GameObject;
		friend class Mesh;
	};
}

