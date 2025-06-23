#include <string>
#include <ColdTable/Graphics/Camera.h>

#include "GraphicsEngine.h"
#include "ColdTable/Core/Logger.h"

ColdTable::Camera::Camera(const CameraDesc& desc): _cameraBuffer(desc.constantBuffer), _windowRectInfo(desc.windowRectInfo)
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

ColdTable::Ray ColdTable::Camera::RayFromScreenpoint(Vec2 screenpoint, float distance)
{

	float x_ndc = (screenpoint.x / _windowRectInfo.width - 0.5f) * 2.0f;
	float y_ndc = (screenpoint.y / _windowRectInfo.height - 0.5f) * 2.0f;

	Vec4 nearpoint = Vec4(x_ndc, y_ndc, -1.0f, 1.0f);
	Vec4 farpoint = Vec4(x_ndc, y_ndc, 1.0f, 1.0f);

	Mat4 InverseMat = (projectionMat * viewMatrix()).inverse();
	Vec4 nearWorld = InverseMat * nearpoint; nearWorld /= nearWorld.w;
	Vec4 farWorld   = InverseMat * farpoint  ; farWorld /= farWorld.w;

	Vec3 rayDir = Vec3((farWorld - nearWorld).normalize());
	Logger::Log(Logger::LogLevel::Info, (std::to_string(farWorld.x) + ", " + std::to_string(farWorld.y) + ", " + std::to_string(farWorld.z)).c_str());
	return Ray(Vec3(nearWorld), rayDir, distance);
}

void ColdTable::Camera::OnKeyDown(int key)
{
	if (!_isControlling) return;

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
	if (!_isControlling) return;

	if (xRotation + delta.y <= 90 && xRotation + delta.y >= -90)
		xRotation += delta.y;

	yRotation += delta.x;

	localRotation = Quaternion::Identity;
	localRotation.rotateLocal( {-1.0f, 0.0f, 0.0f}, xRotation );
	localRotation.rotate( {0.0f, 1.0f, 0.0f}, yRotation );
}

void ColdTable::Camera::OnLeftMouseDown(Vec2 pos)
{
	Vec2 windowPos = Vec2(pos.x, _windowRectInfo.height - pos.y);
	Ray raycast = RayFromScreenpoint(windowPos, 100);
	RenderablePtr target = GraphicsEngine::Instance->CheckHitObject(raycast);
	if (target != nullptr)
		ColdTable::Logger::Log(Logger::LogLevel::Info, "Target hit");
	else

		ColdTable::Logger::Log(Logger::LogLevel::Info, "No Target hit");
}

void ColdTable::Camera::OnRightMouseDown(Vec2 pos)
{
	_isControlling = true;
}

void ColdTable::Camera::OnRightMouseUp(Vec2 pos)
{
	_isControlling = false;
}
