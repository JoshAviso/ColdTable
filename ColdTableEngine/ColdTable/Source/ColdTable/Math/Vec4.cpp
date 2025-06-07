
#include <ColdTable/Math/Vec4.h>

const ColdTable::Vec4 ColdTable::Vec4::Zero = { 0.0, 0.0, 0.0 , 0.0 };

ColdTable::Vec4::operator ColdTable::Vec3() const { return Vec3(this->x, this->y, this->z); }
