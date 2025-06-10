#pragma once
#include "ColdTable/Math/Vec3.h"

namespace ColdTable
{
	struct LightContent
	{
		f32		ambientIntensity = 0.1f;
		Vec3	ambientColor = Vec3::Identity;
		f32		diffuseIntensity = 0.1f;
		Vec3	diffuseColor = Vec3::Identity;
		f32		specIntensity = 0.1f;
		Vec3	specColor = Vec3::Identity;
		f32		specPhong = 0.01f;
	};

	struct LightSourceDesc
	{
	};

	class LightSource
	{
	public:
		explicit LightSource(const LightSourceDesc& desc);

	public:
		LightContent data;

	};
}

