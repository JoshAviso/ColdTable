#include "PointLight.h"

#include "ColdTable/Math/Quaternion.h"

ColdTable::PointLight::PointLight(const LightSourceDesc& desc): LightSource(desc)
{
	lightType = ELightType::Point;
}

ColdTable::LightContent ColdTable::PointLight::GenerateLightData()
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
   lightContent.position = position; // For point and spot light  
   return lightContent;  

}