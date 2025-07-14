#include "Transform.h"

#include "ColdTable/Math/Quaternion.h"

ColdTable::Mat4 ColdTable::Transform::transformMat() const
{
	return
		position.asTranslationMatrix() *
		Quaternion(Vec3::Forward, rotation.z).asMat() *
		Quaternion(Vec3::Up, rotation.y).asMat() *
		Quaternion(Vec3::Right, rotation.x).asMat() *
		scale.asScaleMatrix()
	;
}
