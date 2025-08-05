#include <ColdTable/Resource/Material/Material.h>

#include "ColdTable/Graphics/ConstantBuffer.h"
#include "ColdTable/Graphics/DeviceContext.h"

ColdTable::Material::Material(const MaterialDesc& desc) :
	_shader(desc.shader), _deviceContext(desc.context)
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

}

void ColdTable::Material::SetCullMode(ECULL_MODE mode)
{
	_cullmode = mode;
}
