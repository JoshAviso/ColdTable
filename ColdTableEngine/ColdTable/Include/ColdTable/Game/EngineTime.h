#pragma once
#include <chrono>

namespace ColdTable
{
	class EngineTime
	{
	public:
		static void Initialize();
		static double GetDeltaTime();

	private:
		EngineTime();
		~EngineTime();
		EngineTime(const EngineTime&){};
		EngineTime& operator = (const EngineTime&){};

		static EngineTime* sharedInstance;

		std::chrono::system_clock::time_point start;
		std::chrono::system_clock::time_point end;

		double deltaTime = 0.0;

		static void LogFrameStart();
		static void LogFrameEnd();

		friend class GameLoop;
		friend class GraphicsEngine;
	};

} 

