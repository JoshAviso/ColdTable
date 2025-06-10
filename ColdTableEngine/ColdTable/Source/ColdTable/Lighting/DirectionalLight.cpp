#include "DirectionalLight.h"

#include "ColdTable/Math/Quaternion.h"

ColdTable::DirectionalLight::DirectionalLight(const LightSourceDesc& desc): LightSource(desc)
{
}

void ColdTable::DirectionalLight::Update()
{
	direction = Quaternion(tempRotAxis, tempRotSpeed).rotate(direction);
}
