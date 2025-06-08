
#include <ColdTable/Math/Vec3.h>

const ColdTable::Vec3 ColdTable::Vec3::Zero = { 0.0, 0.0, 0.0 };
const ColdTable::Vec3 ColdTable::Vec3::Identity = { 1.0, 1.0, 1.0 };

ColdTable::Vec3::Vec3() = default;

ColdTable::Vec3::Vec3(f32 val): Vec3(val, val, val)
{}

ColdTable::Vec3::Vec3(f32 x, f32 y, f32 z): x(x), y(y), z(z)
{}

ColdTable::Vec3 ColdTable::Vec3::lerp(Vec3 initial, Vec3 final, f32 delta)
{
	return (initial * (1 - delta)) + (final * delta);
}

bool ColdTable::Vec3::operator==(const Vec3 vec) const
{ return (this->x == vec.x && this->y == vec.y && this->z == vec.z); }

bool ColdTable::Vec3::operator!=(const Vec3 vec) const
{ return (this->x != vec.x || this->y != vec.y || this->z != vec.z); }

ColdTable::Vec3 ColdTable::Vec3::operator+(const Vec3 vec) const
{ return Vec3(this->x + vec.x, this->y + vec.y, this->z + vec.z); }

ColdTable::Vec3 ColdTable::Vec3::operator-(const Vec3 vec) const
{ return Vec3(this->x - vec.x, this->y - vec.y, this->z - vec.z); }

ColdTable::Vec3 ColdTable::Vec3::operator*(const Vec3 vec) const
{ return Vec3(this->x * vec.x, this->y * vec.y, this->z * vec.z); }

ColdTable::Vec3 ColdTable::Vec3::operator*(const f32 scalar) const
{ return Vec3(this->x * scalar, this->y * scalar, this->z * scalar); }

ColdTable::Vec3 ColdTable::Vec3::operator/(const f32 scalar) const
{ return Vec3(this->x / scalar, this->y / scalar, this->z / scalar); }

void ColdTable::Vec3::operator+=(const Vec3 vec)
{ this->x += vec.x; this->y += vec.y; this->z += vec.z; }

void ColdTable::Vec3::operator-=(const Vec3 vec)
{ this->x -= vec.x; this->y -= vec.y; this->z -= vec.z; }

void ColdTable::Vec3::operator*=(const Vec3 vec)
{ this->x *= vec.x; this->y *= vec.y; this->z *= vec.z; }

void ColdTable::Vec3::operator*=(const f32 scalar)
{ this->x *= scalar; this->y *= scalar; this->z *= scalar; }

void ColdTable::Vec3::operator/=(const f32 scalar)
{ this->x /= scalar; this->y /= scalar; this->z /= scalar; }

ColdTable::f32 ColdTable::Vec3::dot(const Vec3 vec) const
{ return this->x * vec.x + this->y * vec.y + this->z * vec.z; }

ColdTable::f32 ColdTable::Vec3::scalarProduct(const Vec3 vec) const
{ return this->dot(vec); }

ColdTable::Vec3 ColdTable::Vec3::cross(Vec3 vec)
{ return Vec3(this->y * vec.z - vec.y * this->z, this->z * vec.x - vec.z * this->x, this->x * vec.y - vec.x * this->y); }

ColdTable::Vec3 ColdTable::Vec3::vectorProduct(Vec3 vec)
{ return this->cross(vec); }

ColdTable::Vec3 ColdTable::Vec3::normalize() const
{
	f32 mag = this->magnitude();
	if (mag == 0.0f) return *this;
	return *this / mag;
}

ColdTable::Vec3 ColdTable::Vec3::direction() const
{ return this->normalize(); }

ColdTable::f32 ColdTable::Vec3::magnitudeSqrd() const
{ return this->x * this->x + this->y * this->y + this->z * this->z; }

ColdTable::f32 ColdTable::Vec3::magnitude() const
{ return std::sqrt(this->magnitudeSqrd()); }

ColdTable::f32 ColdTable::Vec3::distSqrdFrom(const Vec3 vec) const
{ return (*this - vec).magnitudeSqrd(); }

ColdTable::f32 ColdTable::Vec3::distFrom(const Vec3 vec) const
{ return (*this - vec).magnitude(); }

ColdTable::Mat4 ColdTable::Vec3::asTranslationMatrix() const
{
	return {
		1.0, 0.0, 0.0, x,
		0.0, 1.0, 0.0, y,
		0.0, 0.0, 1.0, z,
		0.0, 0.0, 0.0, 1.0
	};
}

ColdTable::Mat4 ColdTable::Vec3::asScaleMatrix() const
{
	return {
		x, 0.0, 0.0, 0.0,
		0.0, y, 0.0, 0.0,
		0.0, 0.0, z, 0.0,
		0.0, 0.0, 0.0, 1.0
	};
}

ColdTable::Vec3::operator ColdTable::Vec4() const { return ColdTable::Vec4(this->x, this->y, this->z, 1.0); }
