#pragma once
#include <ColdTable/Math/Vec3.h>
#include <ColdTable/Math/Mat4.h>

namespace  ColdTable
{
	struct CameraDesc
	{
		Vec3 position;
		Mat4 rotation;
	};

	class Camera
	{
	public:
		Camera(const CameraDesc& desc);

		Mat4 getViewMatrix();
	};
}

