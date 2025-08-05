#pragma once
#include <d3d11.h>
#include <ColdTable/Core/Base.h>
#include <ColdTable/Core/Common.h>

#include "ColdTable/Lighting/DirectionalLight.h"
#include "ColdTable/Lighting/PointLight.h"
#include "ColdTable/Lighting/SpotLight.h"

namespace ColdTable
{
	__declspec(align(16))
	struct LightConstantBufferContent
	{
		LightContent lights[32];
	};

	__declspec(align(16))
	struct CameraBufferContent
	{
		Mat4 m_view;
		Mat4 m_projection;
		Vec4 m_cameraPos;
	};

	__declspec(align(16))
	struct PerObjectBufferContent
	{
		Mat4 transformMat;
		Vec3 materialTint;
		bool hasMaterial;
	};

	struct ConstantBufferDesc
	{
		BaseDesc			base;
		GraphicsDevicePtr	graphicsDevice;
		UINT				bufferSize;
	};
	class ConstantBuffer : public Base
	{
	public:
		explicit ConstantBuffer(ConstantBufferDesc desc);
		virtual ~ConstantBuffer() override;
		void Update(DeviceContext* context, void* buffer);

	private:
		void LoadData(void* buffer);
		GraphicsDevicePtr _graphicsDevice{};
		ID3D11Buffer* _buffer;
		UINT _bufferSize;

	private:
		friend class DeviceContext;
		friend class GraphicsEngine;
		friend class Material;
	};
}
