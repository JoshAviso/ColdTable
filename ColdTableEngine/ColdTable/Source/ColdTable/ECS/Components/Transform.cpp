#include "Transform.h"

#include "ColdTable/Math/Quaternion.h"
#include <ColdTable/Math/Mat4.h> 

ColdTable::Mat4 ColdTable::Transform::transformMat() const
{
	return
		scale.asScaleMatrix() *
		position.asTranslationMatrix() *
		rot.asMat();
	;
}

void ColdTable::Transform::setTransfrom(float (&matrix)[16])
{
	position = Vec3(matrix[12], matrix[13], matrix[14]);

	float Sx = Vec3(matrix[0], matrix[1], matrix[2]).magnitude();
	float Sy = Vec3(matrix[4], matrix[5], matrix[6]).magnitude();
	float Sz = Vec3(matrix[8], matrix[9], matrix[10]).magnitude();
	scale = Vec3(Sx, Sy, Sz);

	Vec3 R0 = Vec3(matrix[0] / Sx, matrix[1] / Sx, matrix[2] / Sx);
	Vec3 R1 = Vec3(matrix[4] / Sy, matrix[5] / Sy, matrix[6] / Sy);
	Vec3 R2 = Vec3(matrix[8] / Sz, matrix[9] / Sz, matrix[10] / Sz);

	float sy = sqrt(R0.x * R0.x + R0.y * R0.y);
	bool singular = sy < 1e-6;
	float rotX, rotY, rotZ;
	if (!singular)
	{
		rotX = atan2(R1.z, R2.z);
		rotY = atan2(-R0.z, sy);
		rotZ = atan2(R0.y, R0.x);
	} else
	{
		rotX = atan2(-R2.y, R1.y);
		rotY = atan2(-R0.z, sy);
		rotZ = 0;
	}
	float degX = rotX * 180.0f / M_PIf;
	float degY = rotY * 180.0f / M_PIf;
	float degZ = rotZ * 180.0f / M_PIf;

	rotation = Vec3(degX, degY, degZ);
}
