#pragma once
#include <ColdTable/Core/Core.h>
#include <iostream>
#include <cmath>
#include <ColdTable/Math/Vec4.h>

#define M_PIf 3.14159265358979323846f
#define M_PI 3.14159265358979323846

namespace ColdTable
{
	class Vec3;
	class Mat4;
	
	class Quaternion : public Vec4
	{
	public:
		/* CONSTANTS */
		static const Quaternion Identity;
		static const Quaternion Zero;

	public:
		Quaternion();
		Quaternion(const Vec4& vec);

		Quaternion(const Vec3& axis, const f32 angle);
		Quaternion(const Quaternion& q);
		Quaternion& operator = (const Quaternion& q);

		explicit operator Mat4() const;
		Mat4 asMat() const;
		Quaternion conjugate() const;
		Quaternion inverse() const;
		Vec3 forward() const;

		bool operator == (const Quaternion& q) const;
		bool operator != (const Quaternion& q) const;

		Quaternion operator * (const Vec3& vec) const;
		Quaternion operator * (const Quaternion& q) const;

		Vec3 rotate(const Vec3& vec) const;
		void rotate(const Quaternion& q);
		void rotate(const Vec3& worldAxis, const f32 angle);

		void rotateLocal(const Vec3& localAxis, const f32 angle);
		void rotateWorld(const Vec3& worldAxis, const f32 angle);

		Vec3 toEulerAngles() const;
	};
}
