#pragma once
#include "LightSource.h"
#include "ColdTable/Math/Vec3.h"

namespace ColdTable
{
class DirectionalLight: public LightSource
{

public:
	explicit DirectionalLight(const LightSourceDesc& desc);
	LightContent GenerateLightData() override;

public:
	Vec3 direction = {0.0, -1.0, 0.0};

	void Update();

	Vec3 tempRotAxis = Vec3::Zero;
	float tempRotSpeed = 0;
};
}

