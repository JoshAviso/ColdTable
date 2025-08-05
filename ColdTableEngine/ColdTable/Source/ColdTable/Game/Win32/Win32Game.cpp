#include <ColdTable/Game/GameLoop.h>
#include <Windows.h>

#include <ColdTable/Game/EngineTime.h>
#include "ColdTable/Game/Display.h"
#include <ColdTable/Input/InputSystem.h>
#include <ColdTable/ECS/ECSEngine.h>


void ColdTable::GameLoop::Run()
{
	onInternalStartup();
	ECSEngine::GetInstance()->Start();

	MSG message{};
	while (_isRunning)
	{
		InputSystem::Instance->Update();

		EngineTime::LogFrameStart();

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
		;
		Sleep(1);
		ECSEngine::GetInstance()->EarlyUpdate();
		ECSEngine::GetInstance()->Update();
		ECSEngine::GetInstance()->LateUpdate();

		EngineTime::LogFrameEnd();
		ECSEngine::GetInstance()->_doFrameStep = false;

		onInternalCallback();
		if (InputSystem::Instance->GameClosing)
			_isRunning = false;
	}
}

