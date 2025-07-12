#pragma once
#include <vector>

#include "EdgeObject.h"
#include "ColdTable/Editor/IEditorPickable.h"

namespace ColdTable
{
	
	class FaceObject : public IEditorPickable
	{
	public:
		FaceObject(Vec3 normal);
		FaceObject(EdgeObjectPtr edge1, EdgeObjectPtr edge2, EdgeObjectPtr edge3, Vec3 normal);
		FaceObject(EdgeObjectPtr edge1, EdgeObjectPtr edge2, EdgeObjectPtr edge3, EdgeObjectPtr edge4, Vec3 normal);


		void AddEdge(EdgeObjectPtr edge);
		void RecalcAABB();
		void Translate(Vec3 translation) override;
		void Rotate(Vec3 axis, float degree) override;
		void Scale(Vec3 scale) override;

		Vec3 aabb_min{};
		Vec3 aabb_max{};

		std::vector<EdgeObjectPtr> _edges{};

		Mat4 currentTransform();

		Transform originalTransform;
		Transform transform;
	};
	using FaceObjectPtr = std::shared_ptr<FaceObject>;
}

