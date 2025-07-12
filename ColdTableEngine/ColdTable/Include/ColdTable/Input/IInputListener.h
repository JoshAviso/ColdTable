#pragma once

#include <ColdTable/Input/InputSystem.h>
#include <ColdTable/Math/Vec2.h>
#include <WinUser.h>

namespace ColdTable
{
	enum EKeyCode
	{
		SPACEBAR = VK_SPACE,
		DELETE_KEY = VK_DELETE,
		BACKSPACE = VK_BACK,
		ESCAPE_KEY = VK_ESCAPE,
		SHIFT = VK_SHIFT,
		CTRL = VK_CONTROL,
		LCTRL = VK_LCONTROL,
		RCTRL = VK_RCONTROL
	};

class IInputListener
{
public:
	IInputListener();
	virtual ~IInputListener();

	virtual void OnKeyDown(int key);
	virtual void OnKeyUp(int key);

	virtual void OnMouseMove(Vec2 delta);
	virtual void OnLeftMouseDown(Vec2 pos);
	virtual void OnRightMouseDown(Vec2 pos);
	virtual void OnLeftMouseUp(Vec2 pos);
	virtual void OnRightMouseUp(Vec2 pos);
	virtual void OnMouseScroll(f32 delta);
};
	
}

