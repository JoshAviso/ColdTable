#pragma once
#include <d3d11.h>
#include <ColdTable/Core/Base.h>
#include <ColdTable/Core/Common.h>
#include <ColdTable/Graphics/GraphicsLogUtil.h>

namespace ColdTable
{
	struct IndexBufferDesc
	{
		const BaseDesc& base;
		const GraphicsDevicePtr& sourceDevice;
	};


	class IndexBuffer : public Base
	{
	public:
		explicit IndexBuffer(const IndexBufferDesc& desc);
		virtual ~IndexBuffer() override;

		void LoadIndices(const void* list, UINT listSize);
	private:
		UINT GetListSize();
		UINT _listSize;

	private:

		ID3D11Buffer* _buffer;
		GraphicsDevicePtr _sourceDevice;

	private:
		friend class DeviceContext;
		friend class Renderable;
	};
}
