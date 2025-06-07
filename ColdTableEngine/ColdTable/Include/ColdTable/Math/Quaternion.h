#pragma once
#include <ColdTable/Math/Vec4.h>
#include <ColdTable/Math/Mat4.h>
#include <iostream>

#include <cmath>
#define M_PIf 3.14159265358979323846f
#define M_PI 3.14159265358979323846

namespace ColdTable
{
	class Quaternion : Vec4
	{
	public:
		/* CONSTANTS */
		static const Quaternion Identity;
		static const Quaternion Zero;

	public:
		Quaternion() = default;
		Quaternion(const Vec4& vec) : Vec4(vec) {}
		Quaternion(const Vec3& axis, const f32 angle): Vec4(axis.normalize()){
			f32 sin = std::sin(angle * M_PIf / 360.0f);
			*this *= sin;
			w = cos(angle * M_PIf / 360.0f);
		}
		Quaternion(const Quaternion& q) = default;
		Quaternion& operator = (const Quaternion& q) { this->x = q.x; this->y = q.y; this->z = q.z; this->w = q.w; return *this; }

		explicit operator Mat4() const;

		bool operator == (const Quaternion& q) const { return Vec4(*this) == Vec4(q); }
		bool operator != (const Quaternion& q) const { return Vec4(*this) != Vec4(q); }

		Quaternion operator * (const Quaternion& q) const
		{
			return Vec4(
				w * q.x + x * q.w + y * q.z - z * q.y,
				w * q.y - x * q.z + y * q.w + z * q.x,
				w * q.z + x * q.y - y * q.x + z * q.w,
				w * q.w - x * q.x - y * q.y - z * q.z
			);
		}

		void rotate(const Quaternion& q)
		{
			if (q == Quaternion::Zero) return;
			*this = q * *this;
		}
		void rotate(const Vec3& axis, const f32 angle) { rotate(Quaternion(axis.normalize(), angle)); }
	};
}
