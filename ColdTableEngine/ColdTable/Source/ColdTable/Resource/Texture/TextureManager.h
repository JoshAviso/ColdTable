#pragma once
#include <ColdTable/Resource/ResourceManager.h>
#include <ColdTable/Resource/Texture/Texture.h>

namespace ColdTable
{
class TextureManager: public ResourceManager
{
public:
	TextureManager();
	~TextureManager() override;

	TexturePtr CreateTextureFromFile(GraphicsDevicePtr sourceDevice, const wchar_t* filepath);
protected:
	Resource* CreateResourceFromFileConcrete(GraphicsDevicePtr sourceDevice, const wchar_t* filepath) override;
};
}

