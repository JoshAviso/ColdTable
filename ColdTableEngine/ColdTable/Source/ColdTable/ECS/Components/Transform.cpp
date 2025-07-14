#include "Transform.h"

#include "ColdTable/Math/Quaternion.h"

ColdTable::Mat4 ColdTable::Transform::transformMat() const
{
	return
		position.asTranslationMatrix() *
		rotation.asRotationMatrix() *
		scale.asScaleMatrix()
	;
}
