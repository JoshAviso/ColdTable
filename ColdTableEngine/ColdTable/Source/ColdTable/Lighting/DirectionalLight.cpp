#include "DirectionalLight.h"

#include "ColdTable/Math/Quaternion.h"

ColdTable::DirectionalLight::DirectionalLight(const LightSourceDesc& desc): LightSource(desc)
{
	lightType = ELightType::Directional;
}

ColdTable::LightContent ColdTable::DirectionalLight::GenerateLightData()
{
   LightContent lightContent;
   lightContent.lightType = lightType;
   lightContent.ambientIntensity = ambientIntensity;
   lightContent.ambientColor = ambientColor;
   lightContent.diffuseIntensity = diffuseIntensity;
   lightContent.diffuseColor = diffuseColor;
   lightContent.specIntensity = specIntensity;
   lightContent.specColor = specColor;
   lightContent.specPhong = specPhong;
   lightContent.direction = direction; // For directional and spot light
   return lightContent;
}

void ColdTable::DirectionalLight::Update()
{
	direction = Quaternion(tempRotAxis, tempRotSpeed).rotate(direction);
}
