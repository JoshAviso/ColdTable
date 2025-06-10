#pragma once
#include <ColdTable/Resource/Resource.h>

#include <DirectXTex.h>
#include <ColdTable/Graphics/GraphicsLogUtil.h>

#include "ColdTable/Core/Core.h"

namespace ColdTable
{
class Texture: public Resource
{
public:
	Texture(GraphicsDevicePtr sourceDevice, const wchar_t* fullpath);
	virtual ~Texture() override;

private:
	ID3D11Resource* _texture;

	ID3D11ShaderResourceView* _resourceView = nullptr;

	friend class DeviceContext;
};
	
}

