#include <ColdTable/Resource/ResourceManager.h>

#include "ColdTable/All.h"


ColdTable::ResourceManager::ResourceManager()
{
}

ColdTable::ResourceManager::~ResourceManager()
{
}

ColdTable::ResourcePtr ColdTable::ResourceManager::CreateResourceFromFile(GraphicsDevicePtr sourceDevice, const wchar_t* filepath)
{
	LPCWSTR filename = filepath;
	TCHAR fullpathBuff[4096] = TEXT("");
	GetFullPathNameW(filename, 4096, fullpathBuff, NULL);

	std::wstring fullpath = fullpathBuff;

	auto itr = _resources.find(fullpath);
	if (itr != _resources.end())
		return itr->second;

	Resource* rawResource = this->CreateResourceFromFileConcrete(sourceDevice, fullpath.c_str());

	if (rawResource)
	{
		ResourcePtr res(rawResource);
		_resources.insert({fullpath, res});
		return res;
	}

	return nullptr;
}
