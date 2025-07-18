
#include <string>
#include <ColdTable/Math/Vec4.h>
#include <ColdTable/Math/Vec3.h>

const ColdTable::Vec4 ColdTable::Vec4::Zero = { 0.0, 0.0, 0.0 , 0.0 };

ColdTable::Vec4::Vec4() = default;

ColdTable::Vec4::Vec4(f32 x, f32 y, f32 z, f32 w): x(x), y(y), z(z), w(w)
{}

ColdTable::Vec4::Vec4(const Vec3& vec3): Vec4(vec3.x, vec3.y, vec3.z, 1.0f)
{
}

ColdTable::Vec4 ColdTable::Vec4::lerp(Vec4 initial, Vec4 final, f32 delta)
{
	return (initial * (1 - delta)) + (final * delta);
}

bool ColdTable::Vec4::operator==(const Vec4 vec) const
{ return (this->x == vec.x && this->y == vec.y && this->z == vec.z && this->w == vec.w); }

bool ColdTable::Vec4::operator!=(const Vec4 vec) const
{ return (this->x != vec.x || this->y != vec.y || this->z != vec.z || this->w != vec.w); }

ColdTable::Vec4 ColdTable::Vec4::operator+(const Vec4 vec) const
{ return Vec4(this->x + vec.x, this->y + vec.y, this->z + vec.z, this->w + vec.w); }

ColdTable::Vec4 ColdTable::Vec4::operator-(const Vec4 vec) const
{ return Vec4(this->x - vec.x, this->y - vec.y, this->z - vec.z, this->w - vec.w); }

ColdTable::Vec4 ColdTable::Vec4::operator*(const Vec4 vec) const
{ return Vec4(this->x * vec.x, this->y * vec.y, this->z * vec.z, this->w * vec.w); }

ColdTable::Vec4 ColdTable::Vec4::operator*(const f32 scalar) const
{ return Vec4(this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar); }

ColdTable::Vec4 ColdTable::Vec4::operator/(const f32 scalar) const
{ return Vec4(this->x / scalar, this->y / scalar, this->z / scalar, this->w / scalar); }

void ColdTable::Vec4::operator+=(const Vec4 vec)
{ this->x += vec.x; this->y += vec.y; this->z += vec.z; this->w += vec.w; }

void ColdTable::Vec4::operator-=(const Vec4 vec)
{ this->x -= vec.x; this->y -= vec.y; this->z -= vec.z; this->w -= vec.w; }

void ColdTable::Vec4::operator*=(const Vec4 vec)
{ this->x *= vec.x; this->y *= vec.y; this->z *= vec.z; this->w *= vec.w; }

void ColdTable::Vec4::operator*=(const f32 scalar)
{ this->x *= scalar; this->y *= scalar; this->z *= scalar; this->w *= scalar; }

void ColdTable::Vec4::operator/=(const f32 scalar)
{ this->x /= scalar; this->y /= scalar; this->z /= scalar; this->w /= scalar; }

ColdTable::f32 ColdTable::Vec4::dot(const Vec4 vec) const
{ return this->x * vec.x + this->y * vec.y + this->z * vec.z + this->w * vec.w; }

ColdTable::f32 ColdTable::Vec4::scalarProduct(const Vec4 vec) const
{ return this->dot(vec); }

ColdTable::Vec4 ColdTable::Vec4::cross(const Vec4& v1, const Vec4& v2, const Vec4& v3)
{
	return{
		v1.y * (v2.z * v3.w - v3.z * v2.w) - v1.z * (v2.y * v3.w - v3.y * v2.w) + v1.w * (v2.y * v3.z - v2.z * v3.y),
		-(v1.x * (v2.z * v3.w - v3.z * v2.w) - v1.z * (v2.x * v3.w - v3.x * v2.w) + v1.w * (v2.x * v3.z - v3.x * v2.z)),
		v1.x * (v2.y * v3.w - v3.y * v2.w) - v1.y * (v2.x * v3.w - v3.x * v2.w) + v1.w * (v2.x * v3.y - v3.x * v2.y),
		-(v1.x * (v2.y * v3.z - v3.y * v2.z) - v1.y * (v2.x * v3.z - v3.x * v2.z) + v1.z * (v2.x * v3.y - v3.x * v2.y))
	};

}

ColdTable::Vec4 ColdTable::Vec4::vectorProduct(const Vec4& v1, const Vec4& v2, const Vec4& v3)
{ return cross(v1, v2, v3); }

ColdTable::Vec4 ColdTable::Vec4::normalize() const
{ return *this / this->magnitude(); }

ColdTable::Vec4 ColdTable::Vec4::direction() const
{ return this->normalize(); }

ColdTable::f32 ColdTable::Vec4::magnitudeSqrd() const
{ return this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w; }

ColdTable::f32 ColdTable::Vec4::magnitude() const
{ return std::sqrt(this->magnitudeSqrd()); }

ColdTable::f32 ColdTable::Vec4::distSqrdFrom(const Vec4 vec) const
{ return (*this - vec).magnitudeSqrd(); }

ColdTable::f32 ColdTable::Vec4::distFrom(const Vec4 vec) const
{ return (*this - vec).magnitude(); }

ColdTable::Vec4::operator ColdTable::Vec3() const { return Vec3(this->x, this->y, this->z); }

std::string ColdTable::Vec4::toString() const
{
	return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w) + ")";
}
