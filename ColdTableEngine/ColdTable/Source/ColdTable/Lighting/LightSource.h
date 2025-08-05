#pragma once
#include "ColdTable/Math/Vec3.h"

namespace ColdTable
{
	struct alignas(16) LightContent
	{
		Vec3	ambientColor = Vec3::Identity;
		f32		ambientIntensity = 0.1f;
		Vec3	diffuseColor = Vec3::Identity;
		f32		diffuseIntensity = 0.1f;
		Vec3	specColor = Vec3::Identity;
		f32		specIntensity = 0.1f;
		Vec3	direction = Vec3::Zero; // For directional and spot lights
		f32		specPhong = 0.01f;
		Vec3	position = Vec3::Zero; // For point and spot lights
		f32		innerCutoff = 0.0f;	// For spotlights
		f32		outerCutoff = 0.0f;	// For spotlights
		int 	lightType = -1; // 1: Point, 0: Directional, 2: Spot
		Vec3	padding;
	};

	enum ELightType
	{
		Unknown = -1,
		Directional = 0,
		Point = 1,
		Spot = 2
	};

	struct LightSourceDesc
	{
	};

	class LightSource
	{
	public:
		explicit LightSource(const LightSourceDesc& desc);
		virtual LightContent GenerateLightData() = 0;

	public:
		ELightType	lightType = ELightType::Unknown;
		f32			ambientIntensity = 0.1f;
		Vec3		ambientColor = Vec3::Identity;
		f32			diffuseIntensity = 0.1f;
		Vec3		diffuseColor = Vec3::Identity;
		f32			specIntensity = 0.1f;
		Vec3		specColor = Vec3::Identity;
		f32			specPhong = 0.01f;

	};
}

