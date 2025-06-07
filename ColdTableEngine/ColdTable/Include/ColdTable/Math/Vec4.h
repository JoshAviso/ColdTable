#pragma once
#include <ColdTable/Core/Core.h>
#include <ColdTable/Math/Vec3.h>
#include <cmath>

namespace ColdTable
{
	class Vec3;

	class Vec4
	{
	public:
		Vec4() = default;
		Vec4(f32 x, f32 y, f32 z, f32 w) : x(x), y(y), z(z), w(w) {}
		f32 x{}, y{}, z{}, w{};
	public:
		/* CONSTANTS */
		static const Vec4 Zero;

		/* UTILITY */
		static Vec4 lerp(Vec4 initial, Vec4 final, f32 delta)
		{
			return (initial * (1 - delta)) + (final * delta);
		};

		/* CONVERSIONS */
		explicit operator Vec3() const;

		/* COMPONENT OPERATORS */
		bool operator == (const Vec4 vec) const { return (this->x == vec.x && this->y == vec.y && this->z == vec.z && this->w == vec.w); }
		bool operator != (const Vec4 vec) const { return (this->x != vec.x || this->y != vec.y || this->z != vec.z || this->w != vec.w); }

		Vec4 operator + (const Vec4 vec) const { return Vec4(this->x + vec.x, this->y + vec.y, this->z + vec.z, this->w + vec.w); }
		Vec4 operator - (const Vec4 vec) const { return Vec4(this->x - vec.x, this->y - vec.y, this->z - vec.z, this->w - vec.w); }
		Vec4 operator * (const Vec4 vec) const { return Vec4(this->x * vec.x, this->y * vec.y, this->z * vec.z, this->w * vec.w); }
		Vec4 operator * (const f32 scalar) const { return Vec4(this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar); }
		Vec4 operator / (const f32 scalar) const { return Vec4(this->x / scalar, this->y / scalar, this->z / scalar, this->w / scalar); }

		void operator += (const Vec4 vec) { this->x += vec.x; this->y += vec.y; this->z += vec.z; this->w += vec.w; }
		void operator -= (const Vec4 vec) { this->x -= vec.x; this->y -= vec.y; this->z -= vec.z; this->w -= vec.w; }
		void operator *= (const Vec4 vec) { this->x *= vec.x; this->y *= vec.y; this->z *= vec.z; this->w *= vec.w; }
		void operator *= (const f32 scalar) { this->x *= scalar; this->y *= scalar; this->z *= scalar; this->w *= scalar; }
		void operator /= (const f32 scalar) { this->x /= scalar; this->y /= scalar; this->z /= scalar; this->w /= scalar; }

		/* VECTOR OPERATIOSN */
		f32 dot(const Vec4 vec) const { return this->x * vec.x + this->y * vec.y + this->z * vec.z + this->w * vec.w; }
		f32 scalarProduct(const Vec4 vec) const { return this->dot(vec); }

		Vec4 normalize() const { return *this / this->magnitude(); }
		Vec4 direction() const { return this->normalize(); }

		f32 magnitudeSqrd() const { return this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w; }
		f32 magnitude() const { return std::sqrt(this->magnitudeSqrd()); }
		f32 distSqrdFrom(const Vec4 vec) const { return (*this - vec).magnitudeSqrd(); }
		f32 distFrom(const Vec4 vec) const { return (*this - vec).magnitude(); }
	};
}
