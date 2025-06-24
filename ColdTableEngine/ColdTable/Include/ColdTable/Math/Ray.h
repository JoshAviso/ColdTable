#pragma once
#include <ColdTable/Math/Vec3.h>

namespace ColdTable
{
class Ray
{
public:
	Ray(const Vec3& origin, const Vec3& direction, float maxDist);

	bool TestIntersection(const RenderablePtr& testTarget, float& intersection_dist);

public:
	Vec3 _origin;
	Vec3 _direction;
	float _maxDist;
};
	
}

