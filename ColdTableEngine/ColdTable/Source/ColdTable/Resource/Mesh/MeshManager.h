#pragma once
#include <unordered_map>
#include <ColdTable/Resource/ResourceManager.h>
#include <ColdTable/Resource/Mesh/Mesh.h>

namespace ColdTable
{
	
class MeshManager: public ResourceManager
{
public:
	static MeshManager* Instance;
	static void Initialize();

	static void DrawImportButton();

	MeshPtr GetMesh(String key);
	String FindMeshKey(MeshPtr mesh);
	MeshPtr CreateMeshFromRenderable(String key, RenderablePtr renderable);
	MeshPtr CreateMeshFromList(String key, Vertex* vertexList, UINT vertexCount, UINT* indexList, UINT indexCount);
	MeshPtr CreateMeshFromFile(String key, GraphicsDevicePtr sourceDevice, const wchar_t* filepath, MaterialPtr material);

protected:
	virtual Resource* CreateResourceFromFileConcrete(GraphicsDevicePtr sourceDevice, const wchar_t* filepath) override;

	MaterialPtr _material;
	std::unordered_map<String, MeshPtr> _meshLibrary;
	friend class MeshComponent;

private:
	MeshManager();
	~MeshManager() override;

	void CreateCubeMesh(float side);
	void CreatePlaneMesh(float side, float height);
	void CreateSphereMesh(float radius, UINT sliceCount, UINT stackCount);
	void CreateCylinderMesh(float radius, float height, UINT stackCount, UINT sliceCount);
	void CreateCapsuleMesh(float radius, float height, UINT sliceCount, UINT stackCount);
};
}

