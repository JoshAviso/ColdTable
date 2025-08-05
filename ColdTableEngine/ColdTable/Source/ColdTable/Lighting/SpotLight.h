#pragma once
#include "LightSource.h"
#include "ColdTable/Input/IInputListener.h"
#include "ColdTable/Math/Vec3.h"

namespace ColdTable
{
struct SpotLightContent
{
	LightContent data;
	Vec3 position;
	Vec3 direction;
	f32 innerCutoff;
	f32 outerCutoff;
};

class SpotLight: public LightSource, public IInputListener
{

public:
	explicit SpotLight(const LightSourceDesc& desc);
	LightContent GenerateLightData() override;

	void OnLeftMouseDown(Vec2 pos) override;

public:
	Vec3 position = Vec3::Zero;
	Vec3 direction = {0.0, 0.0, 1.0};
	f32 innerCutoff = 0.1f;
	f32 outerCutoff = 0.3f;

	bool tempIsOn = true;
};
}

