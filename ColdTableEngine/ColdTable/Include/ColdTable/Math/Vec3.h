#pragma once
#include <ColdTable/Core/Core.h>
#include <ColdTable/Math/Vec4.h>
#include <cmath>

namespace ColdTable
{
	class Vec4;

	class Vec3
	{
	public:
		Vec3() = default;
		Vec3(f32 val) : Vec3(val, val, val){}
		Vec3(f32 x, f32 y, f32 z) : x(x), y(y), z(z) {}
		f32 x{}, y{}, z{};

	public:
		/* CONSTANTS */
		static const Vec3 Zero;
		static const Vec3 Identity;

		/* UTILITY */
		static Vec3 lerp(Vec3 initial, Vec3 final, f32 delta)
		{
			return (initial * (1 - delta)) + (final * delta);
		};

		/* CONVERSION */
		explicit operator Vec4() const;

		/* COMPONENT OPERATORS */
		bool operator == (const Vec3 vec) const { return (this->x == vec.x && this->y == vec.y && this->z == vec.z); }
		bool operator != (const Vec3 vec) const { return (this->x != vec.x || this->y != vec.y || this->z != vec.z); }

		Vec3 operator + (const Vec3 vec) const { return Vec3(this->x + vec.x, this->y + vec.y, this->z + vec.z); }
		Vec3 operator - (const Vec3 vec) const { return Vec3(this->x - vec.x, this->y - vec.y, this->z - vec.z); }
		Vec3 operator * (const Vec3 vec) const { return Vec3(this->x * vec.x, this->y * vec.y, this->z * vec.z); }
		Vec3 operator * (const f32 scalar) const { return Vec3(this->x * scalar, this->y * scalar, this->z * scalar); }
		Vec3 operator / (const f32 scalar) const { return Vec3(this->x / scalar, this->y / scalar, this->z / scalar); }

		void operator += (const Vec3 vec) { this->x += vec.x; this->y += vec.y; this->z += vec.z; }
		void operator -= (const Vec3 vec) { this->x -= vec.x; this->y -= vec.y; this->z -= vec.z; }
		void operator *= (const Vec3 vec) { this->x *= vec.x; this->y *= vec.y; this->z *= vec.z; }
		void operator *= (const f32 scalar) { this->x *= scalar; this->y *= scalar; this->z *= scalar; }
		void operator /= (const f32 scalar) { this->x /= scalar; this->y /= scalar; this->z /= scalar; }

		/* VECTOR OPERATIOSN */
		f32 dot(const Vec3 vec) const { return this->x * vec.x + this->y * vec.y + this->z * vec.z; }
		f32 scalarProduct(const Vec3 vec) const { return this->dot(vec); }
		Vec3 cross(Vec3 vec) { return Vec3(this->y * vec.z - vec.y * this->z, this->z * vec.x - vec.z * this->x, this->x * vec.y - vec.x * this->y); }
		Vec3 vectorProduct(Vec3 vec) { return this->cross(vec); }

		Vec3 normalize() const {
			f32 mag = this->magnitude();
			if (mag == 0.0f) return *this;
			return *this / mag;
		}
		Vec3 direction() const { return this->normalize(); }

		f32 magnitudeSqrd() const { return this->x * this->x + this->y * this->y + this->z * this->z; }
		f32 magnitude() const { return std::sqrt(this->magnitudeSqrd()); }
		f32 distSqrdFrom(const Vec3 vec) const { return (*this - vec).magnitudeSqrd(); }
		f32 distFrom(const Vec3 vec) const { return (*this - vec).magnitude(); }
	};
}
