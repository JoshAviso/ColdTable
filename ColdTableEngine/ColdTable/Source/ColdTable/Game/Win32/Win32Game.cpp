#include <ColdTable/Game/Game.h>
#include <Windows.h>

#include "ColdTable/Game/Display.h"

void ColdTable::Game::Run()
{
	onInternalStartup();

	MSG message{};
	while (_isRunning)
	{
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

