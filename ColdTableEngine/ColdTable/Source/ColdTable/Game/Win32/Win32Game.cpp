#include <ColdTable/Game/GameLoop.h>
#include <Windows.h>

#include "ColdTable/Game/Display.h"

void ColdTable::GameLoop::Run()
{
	onInternalStartup();

	MSG message{};
	while (_isRunning)
	{

		// Input reading, currently funnels to window
		while(PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT)
			{
				_isRunning = false;
				break;
			}

			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		onInternalCallback();
	}
}

