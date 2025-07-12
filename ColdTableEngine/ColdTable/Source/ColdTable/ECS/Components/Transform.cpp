#include "Transform.h"

#include "ColdTable/Math/Quaternion.h"

ColdTable::Mat4 ColdTable::Transform::transformMat() const
{
	return
		scale.asScaleMatrix() *
		rotation.asMat() *
		position.asTranslationMatrix();
}
