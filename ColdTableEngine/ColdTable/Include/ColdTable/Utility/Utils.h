#pragma once
#include <stdlib.h>
#include <ctime>
#include <chrono>

namespace ColdTable
{
	class Utils
	{
	public:
		static int Random(int min_inclusive, int max_exclusive);
		static float Random(float min_inclusive, float max_inclusive);
	};
}

