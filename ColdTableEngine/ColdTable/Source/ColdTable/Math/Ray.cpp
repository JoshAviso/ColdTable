#include <ColdTable/Math/Ray.h>

#include "ColdTable/Graphics/Renderables/Renderable.h"

ColdTable::Ray::Ray(const Vec3& origin, const Vec3& direction, float maxDist): _origin(origin), _direction(direction), _maxDist(maxDist)
{
}

bool ColdTable::Ray::TestIntersection(const RenderablePtr& testTarget, float& intersection_dist)
{
	Mat4 modelMat = testTarget->transformMat();
	Vec3 OBBpositionWorld = Vec3(modelMat.m_mat[3][0], modelMat.m_mat[3][1], modelMat.m_mat[3][2]);

	Vec3 delta = OBBpositionWorld - _origin;

	Vec3 xaxis = Vec3(modelMat.m_mat[0][0], modelMat.m_mat[0][1], modelMat.m_mat[0][2]);
	float e = xaxis.dot(delta);
	float f = _direction.dot(xaxis);

	float t1 = (e + testTarget->aabb_min.x) / f;
	float t2 = (e + testTarget->aabb_max.x) / f;
	if (t1 > t2) { float w = t1; t1 = t2; t2 = w; }

	return false;

}

