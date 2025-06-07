#include <ColdTable/Math/Quaternion.h>


const ColdTable::Quaternion ColdTable::Quaternion::Identity = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
const ColdTable::Quaternion ColdTable::Quaternion::Zero = Vec4(0.0f, 0.0f, 0.0f, 0.0f);

ColdTable::Quaternion::operator ColdTable::Mat4() const
{
	return {
		1.0f - 2.0f * y * y - 2.0f * z * z, 2.0f * x * y - 2.0f * w * z, 2.0f * x * z + 2.0f * w * y, 0.0f,
		2.0f * x * y + 2.0f * w * z, 1.0f - 2.0f * x * x - 2.0f * z * z, 2.0f * y * z - 2.0f * w * x, 0.0f,
		2.0f * x * z - 2.0f * w * y, 2.0f * y * z + 2.0f * w * x, 1.0f - 2.0f * x * x - 2.0f * y * y, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

