#pragma once
#include <ColdTable/Math/Vec3.h>
#include <ColdTable/Math/Mat4.h>
#include <ColdTable/Math/Quaternion.h>

#include "ColdTable/Input/IInputListener.h"

namespace  ColdTable
{
	struct CameraDesc
	{
		const ConstantBufferPtr& constantBuffer;
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

		void OnKeyDown(int key) override;
		void OnMouseMove(Vec2 delta) override;
		void OnRightMouseDown(Vec2 pos) override;
		void OnRightMouseUp(Vec2 pos) override;

	private:
		ConstantBufferPtr _cameraBuffer;
		float yRotation = 0;
		float xRotation = 0;
		bool _isControlling = false;

		friend class GraphicsEngine;
	};
}

