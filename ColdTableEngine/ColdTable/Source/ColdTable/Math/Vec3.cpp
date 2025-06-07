
#include <ColdTable/Math/Vec3.h>

const ColdTable::Vec3 ColdTable::Vec3::Zero = { 0.0, 0.0, 0.0 };
const ColdTable::Vec3 ColdTable::Vec3::Identity = { 1.0, 1.0, 1.0 };

ColdTable::Vec3::operator ColdTable::Vec4() const { return ColdTable::Vec4(this->x, this->y, this->z, 1.0); }