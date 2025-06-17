#pragma once
#include <ColdTable/Resource/ResourceManager.h>
#include <ColdTable/Resource/Mesh/Mesh.h>

namespace ColdTable
{
	
class MeshManager: public ResourceManager
{
public:
	MeshManager();
	~MeshManager() override;

	MeshPtr CreateMeshFromFile(GraphicsDevicePtr sourceDevice, const wchar_t* filepath, MaterialPtr material);
protected:
	virtual Resource* CreateResourceFromFileConcrete(GraphicsDevicePtr sourceDevice, const wchar_t* filepath) override;

	MaterialPtr _material;
};
}

