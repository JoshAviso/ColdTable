#include <iostream>
#include <string>
#include <ColdTable/Game/EngineTime.h>

#include "ColdTable/Core/Logger.h"

ColdTable::EngineTime* ColdTable::EngineTime::sharedInstance = nullptr;

void ColdTable::EngineTime::Initialize()
{
	sharedInstance = new EngineTime();
}

double ColdTable::EngineTime::GetDeltaTime()
{
	return sharedInstance->deltaTime;
}

ColdTable::EngineTime::EngineTime()
{
}

ColdTable::EngineTime::~EngineTime()
{
}

void ColdTable::EngineTime::LogFrameStart()
{
	sharedInstance->start = std::chrono::system_clock::now();
}

void ColdTable::EngineTime::LogFrameEnd()
{
	sharedInstance->end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsedTime = sharedInstance->end - sharedInstance->start;
	sharedInstance->deltaTime = elapsedTime.count();
}
