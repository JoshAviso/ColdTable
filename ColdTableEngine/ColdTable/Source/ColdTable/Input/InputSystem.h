#pragma once

#include <map>
#include <Windows.h>
#include <ColdTable/Input/IInputListener.h>
#include <ColdTable/Math/Vec2.h>

namespace ColdTable
{
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

	void SetWindowFocus(bool value);
	void CloseGameCallback();

	void Update();
	void AddListener(IInputListener* listener);
	void RemoveListener(IInputListener* listener);

	bool GameClosing = false;

private:
	std::map<IInputListener*, IInputListener*> _listeners{};
	unsigned char _keyboardState[256] = {};
	unsigned char _oldKeyboardState[256] = {};
	Vec2 _oldMousePosition;
	bool _windowInFocus = true;

public:
	Vec2 _windowPos;

};
}

