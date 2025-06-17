#pragma once
#include <ColdTable/Window/Window.h>
#include <ColdTable/Core/Common.h>
#include <ColdTable/Math/Rect.h>

namespace ColdTable{
	class Display final: public Window
	{
	public:
		explicit Display(const DisplayDesc& desc);

		SwapChain& GetSwapChain() noexcept;

	private:
		SwapChainPtr _swapChain{};

		friend class GameLoop;
	};
}

