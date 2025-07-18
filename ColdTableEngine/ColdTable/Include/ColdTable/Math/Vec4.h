#pragma once
#include <ColdTable/Core/Core.h>
#include <cmath>

namespace ColdTable
{
	class Vec3;

	class Vec4
	{
	public:
		Vec4();
		Vec4(f32 x, f32 y, f32 z, f32 w);
		Vec4(const Vec3& vec3);
		f32 x{}, y{}, z{}, w{};
	public:
		/* CONSTANTS */
		static const Vec4 Zero;

		/* UTILITY */
		static Vec4 lerp(Vec4 initial, Vec4 final, f32 delta);;

		/* CONVERSIONS */
		explicit operator Vec3() const;
		std::string toString() const;

		/* COMPONENT OPERATORS */
		bool operator == (const Vec4 vec) const;
		bool operator != (const Vec4 vec) const;

		Vec4 operator + (const Vec4 vec) const;
		Vec4 operator - (const Vec4 vec) const;
		Vec4 operator * (const Vec4 vec) const;
		Vec4 operator * (const f32 scalar) const;
		Vec4 operator / (const f32 scalar) const;

		void operator += (const Vec4 vec);
		void operator -= (const Vec4 vec);
		void operator *= (const Vec4 vec);
		void operator *= (const f32 scalar);
		void operator /= (const f32 scalar);

		/* VECTOR OPERATIOSN */
		f32 dot(const Vec4 vec) const;
		f32 scalarProduct(const Vec4 vec) const;

		static Vec4 cross(const Vec4& v1, const Vec4& v2, const Vec4& v3);
		static Vec4 vectorProduct(const Vec4& v1, const Vec4& v2, const Vec4& v3);

		Vec4 normalize() const;
		Vec4 direction() const;

		f32 magnitudeSqrd() const;
		f32 magnitude() const;
		f32 distSqrdFrom(const Vec4 vec) const;
		f32 distFrom(const Vec4 vec) const;
	};
}
