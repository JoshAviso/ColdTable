#include <ColdTable/Graphics/Camera.h>

ColdTable::Camera::Camera(const CameraDesc& desc): _cameraBuffer(desc.constantBuffer)
{
}

ColdTable::Mat4 ColdTable::Camera::transformMat() const
{
	Mat4 translateMat = localPosition.asTranslationMatrix();

	return translateMat * static_cast<Mat4>(localRotation);
}

ColdTable::Mat4 ColdTable::Camera::viewMatrix()
{
	return transformMat().inverse();
}

void ColdTable::Camera::OnKeyDown(int key)
{
	if (key == 'W')
		localPosition += localRotation.rotate({0, 0, 0.1});
	if (key == 'S')
		localPosition += localRotation.rotate({0, 0, -0.1});
	if (key == 'E')
		localPosition += localRotation.rotate({0, 0.1, 0});
	if (key == 'Q')
		localPosition += localRotation.rotate({0, -0.1, 0});
	if (key == 'D')
		localPosition += localRotation.rotate({0.1, 0, 0});
	if (key == 'A')
		localPosition += localRotation.rotate({-0.1, 0, 0});
}

void ColdTable::Camera::OnMouseMove(Vec2 delta)
{
	if (xRotation + delta.y <= 90 && xRotation + delta.y >= -90)
		xRotation += delta.y;

	yRotation += delta.x;

	localRotation = Quaternion::Identity;
	localRotation.rotateLocal( {-1.0f, 0.0f, 0.0f}, xRotation );
	localRotation.rotate( {0.0f, 1.0f, 0.0f}, yRotation );
}
