#include <ColdTable/Lighting/SpotLight.h>

ColdTable::SpotLight::SpotLight(const LightSourceDesc& desc): LightSource(desc)
{
}

void ColdTable::SpotLight::OnLeftMouseDown(Vec2 pos)
{
	if (tempIsOn)
	{
		tempIsOn = false;
		data.diffuseIntensity = 0;
		data.specIntensity = 0;
		data.ambientIntensity = 0;
	} else
	{
		tempIsOn = true;
		data.diffuseIntensity = 10;
		data.specIntensity = 1;
		data.ambientIntensity = 1;
	}
}
