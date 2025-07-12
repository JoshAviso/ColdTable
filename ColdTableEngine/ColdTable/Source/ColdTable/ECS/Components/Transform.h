#pragma once
#include "ColdTable/Math/Quaternion.h"
#include "ColdTable/Math/Vec3.h"

namespace ColdTable
{
	class Transform
	{
	public:
		Vec3 position	= Vec3::Zero;
		Vec3 scale		= Vec3::Identity;
		Quaternion rotation	= Quaternion::Identity;

		Mat4 transformMat() const;
	};
}

