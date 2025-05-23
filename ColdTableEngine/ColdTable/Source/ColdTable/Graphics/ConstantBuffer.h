#pragma once
#include <d3d11.h>
#include <ColdTable/Core/Base.h>
#include <ColdTable/Core/Common.h>

namespace ColdTable
{
	class ConstantBuffer : public Base
	{
	public:
		explicit ConstantBuffer(ConstantBufferDesc desc);
		virtual ~ConstantBuffer() override;
		void LoadData(void* buffer, UINT bufferSize);
		void Update(DeviceContext* context, void* buffer);

	private:
		GraphicsDevicePtr _graphicsDevice{};

		ID3D11Buffer* _buffer;

	private:
		friend class DeviceContext;
	};
}
