#include <stdexcept>
#include <string>
#include <ColdTable/Window/Window.h>
#include <Windows.h>

#include "ColdTable/Core/Logger.h"
#include "ColdTable/Input/InputSystem.h"

#include <DearImGUI/imgui.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam);

static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam)) {
		return true;
	}

	switch(msg)
	{
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		break;
	}

	case WM_SETFOCUS:
	{
		ColdTable::Window* window = (ColdTable::Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->OnFocus();
		break;
	}

	case WM_KILLFOCUS:
	{
		ColdTable::Window* window = (ColdTable::Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->OnLoseFocus();
		break;
	}

	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
}

ColdTable::Window::Window(const WindowDesc& desc): Base(desc.base), _size(desc.size)
{
	auto registerWindowClass = []()
		{
			WNDCLASSEX windowClass{};
			windowClass.cbSize = sizeof(WNDCLASSEX);
			windowClass.lpszClassName = L"Dx#DWindow";
			windowClass.lpfnWndProc = &WindowProcedure;

			return RegisterClassEx(&windowClass);
		};

	static const auto windowClassId = std::invoke(registerWindowClass);

	if (!windowClassId)
	{
		ColdTableLogErrorAndThrow("RegisterClassEx failed.");
	}

	RECT windowRect{0,0,_size.width,_size.height };
	AdjustWindowRect(&windowRect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false);

	_windowHandle = CreateWindowEx(
		NULL,
		MAKEINTATOM(windowClassId),
		L"Cold Table Engine",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		NULL,
		NULL,
		NULL,
		NULL);

	if (!_windowHandle)
	{
		ColdTableLogErrorAndThrow("CreateWindowEx failed.");
	}

	ShowWindow(static_cast<HWND>(_windowHandle), SW_SHOW);
}

ColdTable::Window::~Window()
{
	DestroyWindow(static_cast<HWND>(_windowHandle));
}

void ColdTable::Window::OnFocus()
{
	if (InputSystem::Instance != nullptr)
		InputSystem::Instance->SetWindowFocus(true);
}

void ColdTable::Window::OnLoseFocus()
{
	if (InputSystem::Instance != nullptr)
		InputSystem::Instance->SetWindowFocus(false);
}

ColdTable::Vec2 ColdTable::Window::WindowPosition()
{

	RECT rect, output;
	HWND windowHandle = static_cast<HWND>(_windowHandle);
	GetWindowRect(windowHandle, &rect);

	POINT point;
	point.x = 0;
	point.y = 0;

	ClientToScreen(windowHandle, &point);
	output.left = point.x;
	output.top = point.y;
	output.right = point.x + rect.right;
	output.bottom = point.y + rect.bottom;

	return Vec2(output.left, output.top);
}
