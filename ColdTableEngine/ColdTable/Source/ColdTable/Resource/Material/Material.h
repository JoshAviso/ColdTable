#pragma once
#include <intsafe.h>
#include <vector>
#include <ColdTable/Core/Core.h>

#include "ColdTable/Math/Vec3.h"

namespace ColdTable
{
	struct MaterialDesc
	{
		const ShaderPtr& shader;
		const ConstantBufferPtr& constantBuffer;
		const DeviceContextPtr& context;
	};

	struct MaterialContent
	{
		
	};

	enum ECULL_MODE
	{
		CULL_MODE_FRONT = 0,
		CULL_MODE_BACK
	};
	
class Material
{
public:
	explicit Material(const MaterialDesc& desc);
	void AddTexture(const TexturePtr& texture);
	void RemoveTexture(unsigned int index);

	void SetData(void* data, UINT size);
	void SetCullMode(ECULL_MODE mode);

public:
	Vec3 tint = Vec3::Identity;
	f32 phong = 1.0f;

private:
	ShaderPtr _shader;
	ConstantBufferPtr _constantBuffer;
	std::vector<TexturePtr> _textures;
	DeviceContextPtr _deviceContext;
	ECULL_MODE _cullmode;

private:
	friend class DeviceContext;
	friend class GraphicsEngine;
	friend class Renderable;
};
}

