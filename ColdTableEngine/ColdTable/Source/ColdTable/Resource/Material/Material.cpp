#include <ColdTable/Resource/Material/Material.h>

#include "ColdTable/Graphics/ConstantBuffer.h"
#include "ColdTable/Graphics/DeviceContext.h"

ColdTable::Material::Material(const MaterialDesc& desc):
	_shader(desc.shader), _constantBuffer(desc.constantBuffer), _deviceContext(desc.context)
{


}

void ColdTable::Material::AddTexture(const TexturePtr& texture)
{
	_textures.push_back(texture);
}

void ColdTable::Material::RemoveTexture(unsigned int index)
{
	if (index >= _textures.size()) return;

	_textures.erase(_textures.begin() + index);
}

void ColdTable::Material::SetData(void* data, UINT size)
{
	if (!_constantBuffer->_buffer)
		_constantBuffer->LoadData(data, size);
	else
		_constantBuffer->Update(&*_deviceContext, data);
}

void ColdTable::Material::SetCullMode(ECULL_MODE mode)
{
	_cullmode = mode;
}
