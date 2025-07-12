#pragma once
#include <ColdTable/Math/Vec3.h>

#include "Vertex.h"
#include "ColdTable/Editor/FaceObject.h"

namespace ColdTable
{
class Ray
{
public:
	Ray(const Vec3& origin, const Vec3& direction, float maxDist);

	bool TestIntersection(const GameObjectPtr& testTarget, float& intersectionDist);
	bool TestIntersection(const FaceObjectPtr& testTarget, const Mat4& transform, float& intersectionDist);
	bool TestIntersection(const EdgeObjectPtr& testTarget, const Mat4& transform, float& intersectionDist);
	bool TestIntersection(const VertexObjectPtr& testTarget, const Mat4& transform, float& intersectionDist);

	bool TestIntersection(const RenderablePtr& testTarget, float& intersection_dist);
	bool TestIntersection(const VertexPtr& testTarget, const Mat4& transform, float& intersection_dist);

public:
	Vec3 _origin;
	Vec3 _direction;
	float _maxDist;

private:
	bool TestIntersection(const Mat4& transformMat, const Vec3& aabb_min, const Vec3& aabb_max, float& intersection_dist);
};
	
}

