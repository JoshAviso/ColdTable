#include <ColdTable/Math/Quaternion.h>


const ColdTable::Quaternion ColdTable::Quaternion::Identity = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
const ColdTable::Quaternion ColdTable::Quaternion::Zero = Vec4(0.0f, 0.0f, 0.0f, 0.0f);

ColdTable::Quaternion::Quaternion() = default;

ColdTable::Quaternion::Quaternion(const Vec4& vec): Vec4(vec)
{}

ColdTable::Quaternion::Quaternion(const Vec3& axis, const f32 angle): Vec4(axis.normalize())
{
	f32 sin = std::sin(angle * M_PIf / 360.0f);
	*this *= sin;
	w = cos(angle * M_PIf / 360.0f);
}

ColdTable::Quaternion::Quaternion(const Quaternion& q) = default;

ColdTable::Quaternion& ColdTable::Quaternion::operator=(const Quaternion& q)
{ this->x = q.x; this->y = q.y; this->z = q.z; this->w = q.w; return *this; }

bool ColdTable::Quaternion::operator==(const Quaternion& q) const
{ return Vec4(*this) == Vec4(q); }

bool ColdTable::Quaternion::operator!=(const Quaternion& q) const
{ return Vec4(*this) != Vec4(q); }

ColdTable::Quaternion ColdTable::Quaternion::operator*(const Vec3& vec) const
{
	return *this * Quaternion(Vec4{vec.x, vec.y, vec.z, 0.0f});
}

ColdTable::Quaternion ColdTable::Quaternion::operator*(const Quaternion& q) const
{
	return Vec4(
		w * q.x + x * q.w + y * q.z - z * q.y,
		w * q.y - x * q.z + y * q.w + z * q.x,
		w * q.z + x * q.y - y * q.x + z * q.w,
		w * q.w - x * q.x - y * q.y - z * q.z
	);
}

ColdTable::Vec3 ColdTable::Quaternion::rotate(const Vec3& vec) const
{
	Quaternion res = *this * vec * this->conjugate();
	return { res.x, res.y, res.z };
}

void ColdTable::Quaternion::rotate(const Quaternion& q)
{
	if (q == Quaternion::Zero) return;
	*this = q * *this;
}

void ColdTable::Quaternion::rotate(const Vec3& worldAxis, const f32 angle)
{ rotate(Quaternion(worldAxis.normalize(), angle)); }

void ColdTable::Quaternion::rotateLocal(const Vec3& localAxis, const f32 angle)
{
	*this = *this * Quaternion({ localAxis }, angle);
}

ColdTable::Quaternion::operator ColdTable::Mat4() const
{
	return {
		1.0f - 2.0f * y * y - 2.0f * z * z, 2.0f * x * y - 2.0f * w * z, 2.0f * x * z + 2.0f * w * y, 0.0f,
		2.0f * x * y + 2.0f * w * z, 1.0f - 2.0f * x * x - 2.0f * z * z, 2.0f * y * z - 2.0f * w * x, 0.0f,
		2.0f * x * z - 2.0f * w * y, 2.0f * y * z + 2.0f * w * x, 1.0f - 2.0f * x * x - 2.0f * y * y, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

ColdTable::Mat4 ColdTable::Quaternion::asMat() const
{
	return static_cast<Mat4>(*this);
}

ColdTable::Quaternion ColdTable::Quaternion::conjugate() const
{
	return Vec4(-x, -y, -z, w);
}

ColdTable::Vec3 ColdTable::Quaternion::forward() const
{
	Vec3 vec = { 0.0, 0.0, 1.0 };
	return this->rotate(vec);
}

