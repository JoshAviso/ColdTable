#include <ColdTable/Lighting/SpotLight.h>

ColdTable::SpotLight::SpotLight(const LightSourceDesc& desc): LightSource(desc)
{
	lightType = ELightType::Spot;
}

ColdTable::LightContent ColdTable::SpotLight::GenerateLightData()
{
   ColdTable::LightContent lightContent;
   lightContent.lightType = lightType;
   lightContent.ambientIntensity = ambientIntensity;
   lightContent.ambientColor = ambientColor;
   lightContent.diffuseIntensity = diffuseIntensity;
   lightContent.diffuseColor = diffuseColor;
   lightContent.specIntensity = specIntensity;
   lightContent.specColor = specColor;
   lightContent.specPhong = specPhong;
   lightContent.direction = direction; // For directional and spot light
   lightContent.position = position; // For point and spot light
   lightContent.innerCutoff = innerCutoff; // For spotlight
   lightContent.outerCutoff = outerCutoff; // For spotlight
   return lightContent;

}

void ColdTable::SpotLight::OnLeftMouseDown(Vec2 pos)
{
	return;
	if (tempIsOn)
	{
		tempIsOn = false;
		diffuseIntensity = 0;
		specIntensity = 0;
		ambientIntensity = 0;
	} else
	{
		tempIsOn = true;
		diffuseIntensity = 10;
		specIntensity = 1;
		ambientIntensity = 1;
	}
}
