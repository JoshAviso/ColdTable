#include <ColdTable/Input/InputSystem.h>

ColdTable::InputSystem::InputSystem()
{
	POINT currMousePos = {};
	::GetCursorPos(&currMousePos);

	_oldMousePosition.x = static_cast<float>(currMousePos.x);
	_oldMousePosition.y = static_cast<float>(currMousePos.y);
}

ColdTable::InputSystem::~InputSystem()
{
	_listeners.clear();
}

ColdTable::InputSystem::InputSystem(const InputSystem&)
{
}

ColdTable::InputSystem& ColdTable::InputSystem::operator=(const InputSystem&)
{
	return *this;
}

ColdTable::InputSystem* ColdTable::InputSystem::Instance = nullptr;
void ColdTable::InputSystem::Initialize()
{
	if (Instance == nullptr)
		Instance = new InputSystem();
}

void ColdTable::InputSystem::SetWindowFocus(bool value)
{
	_windowInFocus = value;
}

void ColdTable::InputSystem::Update()
{
	if (!_windowInFocus) return;

	// MOUSE
	POINT currMousePos = {};
	::GetCursorPos(&currMousePos);

	// MOUSE MOVE EVENT
	if (currMousePos.x != static_cast<long>(_oldMousePosition.x) || currMousePos.y != static_cast<long>(_oldMousePosition.y))
	{
		for (auto listener : _listeners)
		{
			listener.second->OnMouseMove({
				static_cast<float>(currMousePos.x) - _oldMousePosition.x,
				-(static_cast<float>(currMousePos.y) - _oldMousePosition.y)
			});
		}

		_oldMousePosition.x = static_cast<float>(currMousePos.x);
		_oldMousePosition.y = static_cast<float>(currMousePos.y);
	}

	// KEYBOARD AND MOUSE CLICKS
	if (::GetKeyboardState(_keyboardState))
	{
		for (int i = 0; i < 256; i++)
		{
			// KEY IS DOWN
			if (_keyboardState[i] & 0x80)
			{
				for (auto listenerPair : _listeners)
				{
					if (i == VK_LBUTTON)
					{
						if (_keyboardState[i] != _oldKeyboardState[i])
							listenerPair.second->OnLeftMouseDown({static_cast<float>(currMousePos.x), static_cast<float>(currMousePos.y)});
					}
					else if (i == VK_RBUTTON)
					{
						if (_keyboardState[i] != _oldKeyboardState[i])
							listenerPair.second->OnRightMouseDown({ static_cast<float>(currMousePos.x), static_cast<float>(currMousePos.y) });

					} else
						listenerPair.second->OnKeyDown(i);
				}
			}
			// KEY IS UP
			else
			{
				if (_keyboardState[i] != _oldKeyboardState[i])
				{
					for (auto listenerPair : _listeners)
					{
						if (i == VK_LBUTTON)
							listenerPair.second->OnLeftMouseUp({ static_cast<float>(currMousePos.x), static_cast<float>(currMousePos.y) });
						else if (i == VK_RBUTTON)
							listenerPair.second->OnRightMouseUp({ static_cast<float>(currMousePos.x), static_cast<float>(currMousePos.y) });
						else
							listenerPair.second->OnKeyUp(i);
					}
				}
				
			}
		}

		::memcpy(_oldKeyboardState, _keyboardState, sizeof(unsigned char) * 256);
	}
}

void ColdTable::InputSystem::AddListener(IInputListener* listener)
{
	_listeners.insert({listener, listener});
}

void ColdTable::InputSystem::RemoveListener(IInputListener* listener)
{
	auto itr = _listeners.find(listener);
	if (itr == _listeners.end()) return;

	_listeners.erase(itr);
}


