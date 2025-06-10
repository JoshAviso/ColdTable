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
		DirectionalLightContent directionalLight[2];
		PointLightContent pointlight;
		SpotLightContent spotlight;
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
	};

	class ConstantBuffer : public Base
	{
	public:
		explicit ConstantBuffer(ConstantBufferDesc desc);
		virtual ~ConstantBuffer() override;
		void LoadData(void* buffer, UINT bufferSize);
		void Update(DeviceContext* context, void* buffer);
		void Update(ID3D11DeviceContext* context, void* buffer);

	private:
		GraphicsDevicePtr _graphicsDevice{};

		ID3D11Buffer* _buffer;

	private:
		friend class DeviceContext;
		friend class GraphicsEngine;
		friend class Material;
	};
}
