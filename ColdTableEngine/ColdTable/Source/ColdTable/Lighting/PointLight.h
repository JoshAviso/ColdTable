#pragma once
#include "LightSource.h"
#include "ColdTable/Math/Vec3.h"

namespace ColdTable
{
struct PointLightContent
{
	LightContent data;
	Vec3 position;
};

class PointLight : public LightSource
{

public:
	explicit PointLight(const LightSourceDesc& desc);

public:
	Vec3 position = Vec3::Zero;

};
}

