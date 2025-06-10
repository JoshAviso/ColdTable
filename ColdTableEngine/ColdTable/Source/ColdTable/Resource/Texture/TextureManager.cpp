#include <ColdTable/Resource/Texture/TextureManager.h>

ColdTable::TextureManager::TextureManager(): ResourceManager()
{
}

ColdTable::TextureManager::~TextureManager()
{
}

ColdTable::TexturePtr ColdTable::TextureManager::CreateTextureFromFile(GraphicsDevicePtr sourceDevice,
	const wchar_t* filepath)
{
	return std::static_pointer_cast<Texture>(CreateResourceFromFile(sourceDevice, filepath));
}

ColdTable::Resource* ColdTable::TextureManager::CreateResourceFromFileConcrete(GraphicsDevicePtr sourceDevice, const wchar_t* filepath)
{
	Texture* tex = nullptr;
	try
	{
		tex = new Texture(sourceDevice, filepath);
	}catch (...){}

	return tex;
}
