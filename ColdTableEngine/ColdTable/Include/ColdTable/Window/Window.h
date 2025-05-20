#pragma once
#include <ColdTable/Core/Base.h>
#include <ColdTable/Core/Common.h>

namespace ColdTable
{
	class Window : public Base
	{
	public:
		explicit Window(const WindowDesc& desc);
		virtual ~Window() override;

	protected:
		void* _windowHandle;
		Rect _size;
	};
} 

