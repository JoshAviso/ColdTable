#include <ColdTable/Graphics/Camera.h>

ColdTable::Camera::Camera(const CameraDesc& desc)
{
}

ColdTable::Mat4 ColdTable::Camera::getViewMatrix()
{
	return Mat4::Identity;
}
