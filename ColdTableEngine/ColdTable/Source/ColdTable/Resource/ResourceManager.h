#pragma once
#include <map>
#include <string>
#include <ColdTable/Core/Core.h>

namespace ColdTable
{
class ResourceManager
{
public:
	ResourceManager();
	virtual ~ResourceManager();

	ResourcePtr CreateResourceFromFile(GraphicsDevicePtr sourceDevice, const wchar_t* filepath);

protected:
	virtual Resource* CreateResourceFromFileConcrete(GraphicsDevicePtr sourceDevice, const wchar_t* filepath) = 0;

private:
	std::map<std::wstring, ResourcePtr> _resources;

};
}

