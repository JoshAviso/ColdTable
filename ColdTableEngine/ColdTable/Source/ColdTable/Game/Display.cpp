#include <ColdTable/Game/Display.h>

#include "ColdTable/Graphics/GraphicsDevice.h"

ColdTable::Display::Display(const DisplayDesc& desc): Window(desc.window)
{
	_swapChain = desc.graphicsDevice->CreateSwapChain({ desc.base,_windowHandle, _size });
}

ColdTable::SwapChain& ColdTable::Display::GetSwapChain() noexcept
{
	return *_swapChain;
}
