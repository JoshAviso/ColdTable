#pragma once
#include <ColdTable/Math/Vec3.h>
#include <ColdTable/Math/Mat4.h>
#include <ColdTable/Math/Quaternion.h>
#include <ColdTable/Math/Rect.h>

#include "ColdTable/Input/IInputListener.h"
#include "ColdTable/Math/Ray.h"

namespace  ColdTable
{
	struct CameraDesc
	{
		const ConstantBufferPtr& constantBuffer;
		const Rect& windowRectInfo;
	};

	class Camera: public IInputListener
	{
	public:
		explicit Camera(const CameraDesc& desc);
		Vec3 localPosition = Vec3::Zero;
		Quaternion localRotation = Quaternion::Identity;
		Mat4 projectionMat = Mat4::Identity;

		Mat4 transformMat() const;
		Mat4 viewMatrix();
		Ray RayFromScreenpoint(Vec2 screenpoint, float distance);
		float dist;

		void OnKeyDown(int key) override;
		void OnMouseMove(Vec2 delta) override;
		void OnLeftMouseDown(Vec2 pos) override;
		void OnLeftMouseUp(Vec2 pos) override;
		void OnRightMouseDown(Vec2 pos) override;
		void OnRightMouseUp(Vec2 pos) override;
		void OnMouseScroll(f32 delta) override;

		Vec3 GetClosestParallelVec(Vec3 checkVec);
		void RotateHeld(Vec3 rotAxis, float rot);

	private:
		ConstantBufferPtr _cameraBuffer;
		float yRotation = 0;
		float xRotation = 0;
		float _camMoveSpeed = 0.1f;
		float _camSpeedChangeRate = 0.0001f;
		bool _isControlling = false;
		bool _leftMouseDown = false;
		bool _shiftHeldDown = false;

		float accumulatedMoveX = 0.0f;
		float accumulatedMoveY = 0.0f;
		float accumulatedMoveZ = 0.0f;
		float accRotX = 0.0f;
		float accRotY = 0.0f;
		float accRotZ = 0.0f;

		Rect _windowRectInfo;
		IEditorPickablePtr selectedObject;
		int cubeIndex = 0;

		friend class GraphicsEngine;
	};
}

