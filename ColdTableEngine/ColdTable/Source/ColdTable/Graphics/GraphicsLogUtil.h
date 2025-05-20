#pragma once
#include <ColdTable/Core/Logger.h>


namespace ColdTable
{
#define ColdTableGraphicsLogThrowOnFail(hr, message)\
	{\
		auto res = (hr);\
		if (FAILED(res))\
		{\
			ColdTableLogErrorAndThrow(message);\
		}\
	}\

}