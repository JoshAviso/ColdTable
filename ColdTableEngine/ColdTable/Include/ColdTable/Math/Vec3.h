#pragma once
#include <ColdTable/Core/Core.h>
#include <cmath>
#include <ColdTable/Math/Mat4.h>

namespace ColdTable
{
	class Vec4;
	class Mat4;

	class Vec3
	{
	public:
		Vec3();
		Vec3(f32 val);
		Vec3(f32 x, f32 y, f32 z);
		f32 x{}, y{}, z{};

	public:
		/* CONSTANTS */
		static const Vec3 Zero;
		static const Vec3 Identity;

		/* UTILITY */
		static Vec3 lerp(Vec3 initial, Vec3 final, f32 delta);;

		/* CONVERSION */
		explicit operator Vec4() const;

		/* COMPONENT OPERATORS */
		bool operator == (const Vec3 vec) const;
		bool operator != (const Vec3 vec) const;

		Vec3 operator + (const Vec3 vec) const;
		Vec3 operator - (const Vec3 vec) const;
		Vec3 operator * (const Vec3 vec) const;
		Vec3 operator * (const f32 scalar) const;
		Vec3 operator / (const f32 scalar) const;

		void operator += (const Vec3 vec);
		void operator -= (const Vec3 vec);
		void operator *= (const Vec3 vec);
		void operator *= (const f32 scalar);
		void operator /= (const f32 scalar);

		/* VECTOR OPERATIOSN */
		f32 dot(const Vec3 vec) const;
		f32 scalarProduct(const Vec3 vec) const;
		Vec3 cross(Vec3 vec);
		Vec3 vectorProduct(Vec3 vec);

		Vec3 normalize() const;
		Vec3 direction() const;

		f32 magnitudeSqrd() const;
		f32 magnitude() const;
		f32 distSqrdFrom(const Vec3 vec) const;
		f32 distFrom(const Vec3 vec) const;

		/* CONVERSIONS */
		Mat4 asTranslationMatrix() const;

		Mat4 asScaleMatrix() const;
	};
}
