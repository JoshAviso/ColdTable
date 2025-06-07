#include <ColdTable/Utility/Utils.h>

#include "ColdTable/All.h"

int ColdTable::Utils::Random(int min_inclusive, int max_exclusive)
{
	srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	int val = rand() % (max_exclusive - min_inclusive) + min_inclusive;
	return val;
}

float ColdTable::Utils::Random(float min_inclusive, float max_inclusive)
{
	return static_cast<float>(Random(static_cast<int>(min_inclusive * 100), static_cast<int>((max_inclusive * 100) + 1)))/ 100.0f;
}
