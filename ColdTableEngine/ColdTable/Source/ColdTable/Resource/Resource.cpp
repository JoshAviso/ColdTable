#include <ColdTable/Resource/Resource.h>

ColdTable::Resource::Resource()
{
	_fullpath = L"";
}

ColdTable::Resource::Resource(const wchar_t* fullpath): _fullpath(fullpath)
{
}

ColdTable::Resource::~Resource()
{
}
