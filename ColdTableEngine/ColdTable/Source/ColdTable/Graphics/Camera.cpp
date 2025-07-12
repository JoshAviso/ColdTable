#include <string>
#include <ColdTable/Graphics/Camera.h>
#include <math.h>

#include "GraphicsEngine.h"
#include "ShaderLibrary.h"
#include "ColdTable/Core/Logger.h"
#include "ColdTable/ECS/GameObjects/GameObject.h"
#include "ColdTable/ECS/GameObjects/GameObjectManager.h"
#include "Renderables/Cube.h"

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
	return Ray(Vec3(nearWorld), rayDir, distance);
}

	//Logger::Log(Logger::LogLevel::Info, (std::to_string(farWorld.x) + ", " + std::to_string(farWorld.y) + ", " + std::to_string(farWorld.z)).c_str());
void ColdTable::Camera::OnKeyDown(int key)
{

	if (key == EKeyCode::SPACEBAR)
	{
		CubePtr cube = std::make_shared<Cube>(GraphicsEngine::Instance->CreateIndexBuffer(), ShaderLibrary::GetShader("BlankShader"));
		GameObjectPtr cubeObject = GameObjectManager::CreateGameObject("Cube (" + std::to_string(cubeIndex++) + ")");
		cubeObject->renderable = cube;
		cubeObject->transform->position = this->localPosition;

	}
	_shiftHeldDown = InputSystem::Instance->IsKeyDown(EKeyCode::SHIFT);
	if (_shiftHeldDown && !_isControlling)
	{
		float rotSpeed = 10.0f;
		if (key == 'W') RotateHeld(Vec3::Right, -rotSpeed);
		if (key == 'S') RotateHeld(Vec3::Right, rotSpeed);
		if (key == 'E') RotateHeld(Vec3::Forward, rotSpeed);
		if (key == 'Q') RotateHeld(Vec3::Forward, -rotSpeed);
		if (key == 'D') RotateHeld(Vec3::Up, -rotSpeed);
		if (key == 'A') RotateHeld(Vec3::Up, rotSpeed);
	}


	if (!_isControlling) return;

	f32 moveSpeed = _camMoveSpeed;
	if (_shiftHeldDown)
		moveSpeed *= 2.0f;

	if (key == 'W')
		localPosition += localRotation.rotate({0, 0, moveSpeed});
	if (key == 'S')
		localPosition += localRotation.rotate({0, 0, -moveSpeed});
	if (key == 'E')
		localPosition += localRotation.rotate({0, moveSpeed, 0});
	if (key == 'Q')
		localPosition += localRotation.rotate({0, -moveSpeed, 0});
	if (key == 'D')
		localPosition += localRotation.rotate({moveSpeed, 0, 0});
	if (key == 'A')
		localPosition += localRotation.rotate({-moveSpeed, 0, 0});
}

void ColdTable::Camera::OnMouseMove(Vec2 delta)
{
 	if (_leftMouseDown && selectedObject != nullptr)
	{
		Vec3 yVec = GetClosestParallelVec(localRotation.rotate(Vec3::Up)) * delta.y * dist * 0.002f;
		Vec3 xVec = GetClosestParallelVec(localRotation.rotate(Vec3::Right)) * delta.x * dist * 0.002f;
		accumulatedMoveZ += yVec.z + xVec.z;
		accumulatedMoveX += yVec.x + xVec.x;
		accumulatedMoveY += yVec.y + xVec.y;

		if (GameObjectManager::Instance == nullptr)
		{
			selectedObject->Translate(Vec3::Up * accumulatedMoveY);
			selectedObject->Translate(Vec3::Right * accumulatedMoveX);
			selectedObject->Translate(Vec3::Forward * accumulatedMoveZ);
			accumulatedMoveX = accumulatedMoveY = accumulatedMoveZ = 0.0f;
		} else
		{
			float gridSnapping = GameObjectManager::Instance->gridSnapping;
			while (abs(accumulatedMoveY) >= gridSnapping)
			{
				if (accumulatedMoveY >= 0)
				{
					accumulatedMoveY -= gridSnapping;
					selectedObject->Translate(Vec3::Up * gridSnapping);
				}
				else
				{
					accumulatedMoveY += gridSnapping;
					selectedObject->Translate(Vec3::Down * gridSnapping);
				}
			}
			while (abs(accumulatedMoveX) >= gridSnapping)
			{
				if (accumulatedMoveX >= 0)
				{
					accumulatedMoveX -= gridSnapping;
					selectedObject->Translate(Vec3::Right * gridSnapping);
				}
				else
				{
					accumulatedMoveX += gridSnapping;
					selectedObject->Translate(Vec3::Left * gridSnapping);
				}
			}
			while (abs(accumulatedMoveZ) >= gridSnapping)
			{
				if (accumulatedMoveZ >= 0)
				{
					accumulatedMoveZ -= gridSnapping;
					selectedObject->Translate(Vec3::Forward * gridSnapping);
				}
				else
				{
					accumulatedMoveZ += gridSnapping;
					selectedObject->Translate(Vec3::Back * gridSnapping);
				}
			}
		}
		
		//selectedObject->Translate(localRotation.rotate({ delta.x * dist * 0.002f, delta.y * dist * 0.0025f, 0}));
	}

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
	_leftMouseDown = true;
	Vec2 windowPos = Vec2(pos.x, _windowRectInfo.height - pos.y);
	Ray raycast = RayFromScreenpoint(windowPos, 100);
	IEditorPickablePtr target = GraphicsEngine::Instance->CheckHitObject(raycast);
	if (target != nullptr)
	{
		ColdTable::Logger::Log(Logger::LogLevel::Info, "Target hit!");
		selectedObject = target;
		dist = GraphicsEngine::Instance->closestDist;
	}
	else
	{
		selectedObject = nullptr;
	}
}

void ColdTable::Camera::OnLeftMouseUp(Vec2 pos)
{
	_leftMouseDown = false;
	accumulatedMoveX = 0.0f;
	accumulatedMoveY = 0.0f;
	accumulatedMoveZ = 0.0f;
}

void ColdTable::Camera::OnRightMouseDown(Vec2 pos)
{
	_isControlling = true;
}

void ColdTable::Camera::OnRightMouseUp(Vec2 pos)
{
	_isControlling = false;
}

void ColdTable::Camera::OnMouseScroll(f32 delta)
{
	if (_isControlling)
	{
		_camMoveSpeed += _camSpeedChangeRate * delta;
		if (_camMoveSpeed < 0) _camMoveSpeed = 0;
		return;
	}
}

ColdTable::Vec3 ColdTable::Camera::GetClosestParallelVec(Vec3 checkVec)
{
	Vec3 closestVec = Vec3::Zero;
	float cosineSim = -2.0f;
	Vec3 vecs[] = {
		Vec3::Up, Vec3::Down, Vec3::Left, Vec3::Right, Vec3::Forward, Vec3::Back
	};

	for (auto vec : vecs)
	{
		float csim = checkVec.dot(vec);
		if (csim >= cosineSim)
		{
			cosineSim = csim;
			closestVec = vec;
		}
	}

	return closestVec;
}

void ColdTable::Camera::RotateHeld(Vec3 rotAxis, float rot)
{
	if (selectedObject != nullptr)
	{
		if (GameObjectManager::Instance == nullptr)
		{

		}
		else
		{
			float gridSnapping = GameObjectManager::Instance->gridSnapping;
			while (abs(accRotY) >= gridSnapping)
			{
				if (accRotY >= 0)
				{
					accRotY -= gridSnapping;
					selectedObject->Rotate(Vec3::Up, gridSnapping);
				}
				else
				{
					accRotY += gridSnapping;
					selectedObject->Rotate(Vec3::Down, gridSnapping);
				}
			}
			while (abs(accRotX) >= gridSnapping)
			{
				if (accRotX >= 0)
				{
					accRotX -= gridSnapping;
					selectedObject->Rotate(Vec3::Right, gridSnapping);
				}
				else
				{
					accRotX += gridSnapping;
					selectedObject->Rotate(Vec3::Left, gridSnapping);
				}
			}
			while (abs(accRotZ) >= gridSnapping)
			{
				if (accRotZ >= 0)
				{
					accRotZ -= gridSnapping;
					selectedObject->Rotate(Vec3::Forward, gridSnapping);
				}
				else
				{
					accRotZ += gridSnapping;
					selectedObject->Rotate(Vec3::Back, gridSnapping);
				}
			}
		}
	}
}
