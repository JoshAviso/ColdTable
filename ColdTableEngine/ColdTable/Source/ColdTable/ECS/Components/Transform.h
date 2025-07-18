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
		Quaternion rot = Quaternion::Identity;
		Vec3 rotation	= Vec3::Zero;

		Mat4 transformMat() const;
		void setTransfrom(float (&matrix)[16]);
	};
}

