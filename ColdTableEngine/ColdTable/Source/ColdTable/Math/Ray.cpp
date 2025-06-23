#include <ColdTable/Math/Ray.h>

#include "ColdTable/Graphics/Renderables/Renderable.h"

ColdTable::Ray::Ray(const Vec3& origin, const Vec3& direction, float maxDist): _origin(origin), _direction(direction), _maxDist(maxDist)
{
}

bool ColdTable::Ray::TestIntersection(const RenderablePtr& testTarget, float& intersection_dist)
{
	float tMin = 0.0f;
	float tMax = 100000.0f;

	Vec3 aabb_min = testTarget->aabb_min;
	Vec3 aabb_max = testTarget->aabb_max;
	Mat4 modelMat = testTarget->transformMat();
	Vec3 OBBpositionWorld = Vec3(modelMat.m_mat[3][0], modelMat.m_mat[3][1], modelMat.m_mat[3][2]);

	Vec3 delta = OBBpositionWorld - _origin;

	Vec3 xaxis = Vec3(modelMat.m_mat[0][0], modelMat.m_mat[0][1], modelMat.m_mat[0][2]);
	float e = xaxis.dot(delta);
	float f = _direction.dot(xaxis);
	if (abs(f) < 0.001f)
	{
		if (-e + aabb_min.x > 0.0f || -e + aabb_max.x < 0.0f) 
			return false;
	} else
	{
		float t1 = (e + testTarget->aabb_min.x) / f;
		float t2 = (e + testTarget->aabb_max.x) / f;
		if (t1 > t2) { float w = t1; t1 = t2; t2 = w; }

		if (t2 < tMax) tMax = t2;
		if (t1 > tMin) tMin = t1;
		if (tMax < tMin) return false;
	}
	Vec3 yaxis = Vec3(modelMat.m_mat[1][0], modelMat.m_mat[1][1], modelMat.m_mat[1][2]);
	e = yaxis.dot(delta);
	f = _direction.dot(yaxis);
	if (abs(f) < 0.001f)
	{
		if (-e + aabb_min.y > 0.0f || -e + aabb_max.y < 0.0f)
			return false;
	}
	else
	{
		float t1 = (e + testTarget->aabb_min.y) / f;
		float t2 = (e + testTarget->aabb_max.y) / f;
		if (t1 > t2) { float w = t1; t1 = t2; t2 = w; }

		if (t2 < tMax) tMax = t2;
		if (t1 > tMin) tMin = t1;
		if (tMax < tMin) return false;
	}
	Vec3 zaxis = Vec3(modelMat.m_mat[2][0], modelMat.m_mat[2][1], modelMat.m_mat[2][2]);
	e = zaxis.dot(delta);
	f = _direction.dot(zaxis);
	if (abs(f) < 0.001f)
	{
		if (-e + aabb_min.z > 0.0f || -e + aabb_max.z < 0.0f)
			return false;
	}
	else
	{
		float t1 = (e + testTarget->aabb_min.z) / f;
		float t2 = (e + testTarget->aabb_max.z) / f;
		if (t1 > t2) { float w = t1; t1 = t2; t2 = w; }

		if (t2 < tMax) tMax = t2;
		if (t1 > tMin) tMin = t1;
		if (tMax < tMin) return false;
	}

	intersection_dist = tMin;
	return true;
}

