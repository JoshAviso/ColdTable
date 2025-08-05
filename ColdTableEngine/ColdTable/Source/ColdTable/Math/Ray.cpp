#include <string>
#include <ColdTable/Math/Ray.h>

#include "ColdTable/ECS/GameObjects/GameObject.h"
#include "ColdTable/Graphics/Renderables/Renderable.h"

ColdTable::Ray::Ray(const Vec3& origin, const Vec3& direction, float maxDist): _origin(origin), _direction(direction), _maxDist(maxDist)
{
}

bool ColdTable::Ray::TestIntersection(const GameObjectPtr& testTarget, float& intersectionDist)
{
	if (testTarget->renderable == nullptr) return false;
	testTarget->renderable->recalcAABB();
	return TestIntersection(testTarget->transform->transformMat(), testTarget->renderable->aabb_min, testTarget->renderable->aabb_max, intersectionDist);
}

bool ColdTable::Ray::TestIntersection(const FaceObjectPtr& testTarget, const Mat4& transform, float& intersectionDist)
{
	testTarget->RecalcAABB();
	return TestIntersection(transform, testTarget->aabb_min, testTarget->aabb_max, intersectionDist);
}

bool ColdTable::Ray::TestIntersection(const EdgeObjectPtr& testTarget, const Mat4& transform, float& intersectionDist)
{
	testTarget->RecalcAabb();
	return TestIntersection(transform, testTarget->aabb_min - Vec3(0.1, 0.1, 0.1), testTarget->aabb_max + Vec3(0.1, 0.1, 0.1), intersectionDist);
}

bool ColdTable::Ray::TestIntersection(const VertexObjectPtr& testTarget, const Mat4& transform, float& intersectionDist)
{
	return TestIntersection(transform, testTarget->getActualPos() - Vec3(0.1f, 0.1f, 0.1f), testTarget->getActualPos() + Vec3(0.1f, 0.1f, 0.1f), intersectionDist);
}

bool ColdTable::Ray::TestIntersection(const RenderablePtr& testTarget, float& intersection_dist)
{
	testTarget->recalcAABB();
	return TestIntersection(testTarget->transformMat(), testTarget->aabb_min, testTarget->aabb_max, intersection_dist);
}

bool ColdTable::Ray::TestIntersection(const VertexPtr& testTarget, const Mat4& transform, float& intersection_dist)
{
	return TestIntersection(((Vec3)(transform * testTarget->position)).asTranslationMatrix(), Vec3(-0.1f, -0.1f, -0.1f), Vec3(0.1f, 0.1f, 0.1f), intersection_dist);
}

bool ColdTable::Ray::TestIntersection(const Mat4& transformMat, const Vec3& aabb_min, const Vec3& aabb_max,
	float& intersection_dist)
{
	float tMin = 0.0f;
	float tMax = 100000.0f;

	Vec3 aabb_min_scaled = aabb_min;
	Vec3 aabb_max_scaled = aabb_max;
	Mat4 modelMat = transformMat;
	Vec3 OBBpositionWorld = Vec3(modelMat.m_mat[0][3], modelMat.m_mat[1][3], modelMat.m_mat[2][3]);

	Vec3 delta = OBBpositionWorld - _origin;

	//Logger::Log(Logger::LogLevel::Info, (std::to_string(e) + ", " + std::to_string(f)).c_str());

	Vec3 xaxis = Vec3(modelMat.m_mat[0][0], modelMat.m_mat[1][0], modelMat.m_mat[2][0]);
	float e = xaxis.dot(delta);
	float f = _direction.dot(xaxis);
	if (abs(f) <= 0.001f)
	{
		if (-e + aabb_min_scaled.x > 0.0f || -e + aabb_max_scaled.x < 0.0f) 
			return false;
	} else
	{
		float t1 = (e + aabb_min_scaled.x) / f;
		float t2 = (e + aabb_max_scaled.x) / f;
		if (t1 > t2) { float w = t1; t1 = t2; t2 = w; }

		if (t2 < tMax) tMax = t2;
		if (t1 > tMin) tMin = t1;
		if (tMax < tMin) return false;
	}
	Vec3 yaxis = Vec3(modelMat.m_mat[0][1], modelMat.m_mat[1][1], modelMat.m_mat[2][1]);
	e = yaxis.dot(delta);
	f = _direction.dot(yaxis);
	if (abs(f) <= 0.001f)
	{
		if (-e + aabb_min_scaled.y > 0.0f || -e + aabb_max_scaled.y < 0.0f)
			return false;
	}
	else
	{
		float t1 = (e + aabb_min_scaled.y) / f;
		float t2 = (e + aabb_max_scaled.y) / f;
		if (t1 > t2) { float w = t1; t1 = t2; t2 = w; }

		if (t2 < tMax) tMax = t2;
		if (t1 > tMin) tMin = t1;
		if (tMax < tMin) return false;
	}
	Vec3 zaxis = Vec3(modelMat.m_mat[0][2], modelMat.m_mat[1][2], modelMat.m_mat[2][2]);
	e = zaxis.dot(delta);
	f = _direction.dot(zaxis);
	if (abs(f) <= 0.001f)
	{
		if (-e + aabb_min_scaled.z > 0.0f || -e + aabb_max_scaled.z < 0.0f)
			return false;
	}
	else
	{
		float t1 = (e + aabb_min_scaled.z) / f;
		float t2 = (e + aabb_max_scaled.z) / f;
		if (t1 > t2) { float w = t1; t1 = t2; t2 = w; }

		if (t2 < tMax) tMax = t2;
		if (t1 > tMin) tMin = t1;
		if (tMax < tMin) return false;
	}

	intersection_dist = tMin;
	return true;
}

