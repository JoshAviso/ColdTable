#pragma once
#include "VertexObject.h"
#include "ColdTable/Editor/IEditorPickable.h"
#include "ColdTable/Math/Vertex.h"

namespace ColdTable
{
	class FaceObject;
	class EdgeObject : public IEditorPickable
	{
	public:
		EdgeObject(VertexObjectPtr vert1, VertexObjectPtr vert2);
		void RecalcAabb();
		void Translate(Vec3 translation) override;
		void Rotate(Vec3 axis, float degree) override;
		void Scale(Vec3 scale) override;

		Vec3 aabb_min{};
		Vec3 aabb_max{};

		VertexObjectPtr _vert1;
		VertexObjectPtr _vert2;

		Transform originalTransform;
		Transform transform;

		void AddFace(FaceObject* face );
		std::vector<FaceObject*> _owningFaces{};

	};
	using EdgeObjectPtr = std::shared_ptr<EdgeObject>;
}

