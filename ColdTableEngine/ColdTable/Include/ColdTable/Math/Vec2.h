#pragma once
#include <ColdTable/Core/Core.h>
#include <ColdTable/Math/Vec4.h>
#include <cmath>

namespace ColdTable
{
	//class Vec4;

	class Vec2
	{
	public:
		Vec2() = default;
		Vec2(f32 val) : Vec2(val, val){}
		Vec2(f32 x, f32 y) : x(x), y(y) {}
		f32 x{}, y{};

	public:
		/* CONSTANTS */
		static const Vec2 Zero;
		static const Vec2 Identity;

		/* UTILITY */
		static Vec2 lerp(Vec2 initial, Vec2 final, f32 delta)
		{
			return (initial * (1 - delta)) + (final * delta);
		};

		/* CONVERSION */
		//explicit operator Vec4() const;

		/* COMPONENT OPERATORS */
		Vec2 operator = (const Vec2 vec) { this->x = vec.x; this->y = vec.y; return *this; }

		bool operator == (const Vec2 vec) const { return (this->x == vec.x && this->y == vec.y); }
		bool operator != (const Vec2 vec) const { return (this->x != vec.x || this->y != vec.y); }

		Vec2 operator + (const Vec2 vec) const { return Vec2(this->x + vec.x, this->y + vec.y); }
		Vec2 operator - (const Vec2 vec) const { return Vec2(this->x - vec.x, this->y - vec.y); }
		Vec2 operator * (const Vec2 vec) const { return Vec2(this->x * vec.x, this->y * vec.y); }
		Vec2 operator * (const f32 scalar) const { return Vec2(this->x * scalar, this->y * scalar); }
		Vec2 operator / (const f32 scalar) const { return Vec2(this->x / scalar, this->y / scalar); }

		void operator += (const Vec2 vec) { this->x += vec.x; this->y += vec.y; }
		void operator -= (const Vec2 vec) { this->x -= vec.x; this->y -= vec.y; }
		void operator *= (const Vec2 vec) { this->x *= vec.x; this->y *= vec.y; }
		void operator *= (const f32 scalar) { this->x *= scalar; this->y *= scalar; }
		void operator /= (const f32 scalar) { this->x /= scalar; this->y /= scalar; }

		/* VECTOR OPERATIONS */
		f32 dot(const Vec2 vec) const { return this->x * vec.x + this->y * vec.y; }
		f32 scalarProduct(const Vec2 vec) const { return this->dot(vec); }
		
		Vec2 normalize() const {
			f32 mag = this->magnitude();
			if (mag == 0.0f) return *this;
			return *this / mag;
		}
		Vec2 direction() const { return this->normalize(); }

		f32 magnitudeSqrd() const { return this->x * this->x + this->y * this->y; }
		f32 magnitude() const { return std::sqrt(this->magnitudeSqrd()); }
		f32 distSqrdFrom(const Vec2 vec) const { return (*this - vec).magnitudeSqrd(); }
		f32 distFrom(const Vec2 vec) const { return (*this - vec).magnitude(); }
	};
}
