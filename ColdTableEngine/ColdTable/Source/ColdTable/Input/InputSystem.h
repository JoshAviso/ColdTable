#pragma once

#include <map>
#include <Windows.h>
#include <ColdTable/Input/IInputListener.h>
#include <ColdTable/Math/Vec2.h>

namespace ColdTable
{
	enum EKeyCode;
class InputSystem
{
public:
	InputSystem();
	~InputSystem();
	InputSystem(const InputSystem&);
	InputSystem& operator = (const InputSystem&);

public:
	static InputSystem* Instance;
	static void Initialize();

	void SetScrollWheelDelta(f32 value);
	void SetWindowFocus(bool value);
	void CloseGameCallback();

	void Update();
	void AddListener(IInputListener* listener);
	void RemoveListener(IInputListener* listener);
	bool IsKeyDown(EKeyCode keycode);

	bool GameClosing = false;

private:
	std::map<IInputListener*, IInputListener*> _listeners{};
	unsigned char _keyboardState[256] = {};
	unsigned char _oldKeyboardState[256] = {};
	Vec2 _oldMousePosition;
	bool _windowInFocus = true;
	f32 _scrollDelta;

public:
	Vec2 _windowPos;

};
}

