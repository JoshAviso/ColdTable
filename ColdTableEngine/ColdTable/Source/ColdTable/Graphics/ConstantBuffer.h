#pragma once
#include <d3d11.h>
#include <ColdTable/Core/Base.h>
#include <ColdTable/Core/Common.h>

namespace ColdTable
{
	__declspec(align(16))
		struct ConstantBufferContent
	{
		Mat4 m_world;
		Mat4 m_view;
		Mat4 m_projection;
		unsigned int m_time;
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
	};
}
