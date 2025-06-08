#pragma once

#include <map>
#include <memory>
#include <ColdTable/Input/IInputListener.h>
#include <ColdTable/Core/Core.h>
#include <Windows.h>
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

	void Update();
	void AddListener(IInputListener* listener);
	void RemoveListener(IInputListener* listener);

private:
	std::map<IInputListener*, IInputListener*> _listeners{};
	unsigned char _keyboardState[256] = {};
	unsigned char _oldKeyboardState[256] = {};
	Vec2 _oldMousePosition;
	bool _windowInFocus = true;

};
}

