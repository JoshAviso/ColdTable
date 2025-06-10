#pragma once
#include <string>

namespace ColdTable
{
class Resource
{
public:
	Resource(const wchar_t* fullpath);
	virtual ~Resource();

protected:
	std::wstring _fullpath;
};
}

