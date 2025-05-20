#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <ColdTable/Core/Base.h>
#include <ColdTable/Core/Common.h>
#include <ColdTable/Graphics/GraphicsLogUtil.h>

namespace ColdTable
{
	struct GraphicsResourceDesc
	{
		BaseDesc base;
		std::shared_ptr<const GraphicsDevice> graphicsDevice;
		ID3D11Device& device;
		IDXGIFactory& factory;
	};

	class GraphicsResource: public Base
	{
	public:
		explicit GraphicsResource(const GraphicsResourceDesc& desc):
			Base(desc.base),
			_graphicsDevice(desc.graphicsDevice),
			_device(desc.device),
			_factory(desc.factory)
		{
			
		}

	protected:
		std::shared_ptr<const GraphicsDevice> _graphicsDevice;
		ID3D11Device& _device;
		IDXGIFactory& _factory;
	};
}
