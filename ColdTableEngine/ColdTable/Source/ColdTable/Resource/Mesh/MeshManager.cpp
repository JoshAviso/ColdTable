#include <ColdTable/Resource/Mesh/MeshManager.h>

ColdTable::MeshManager::MeshManager(): ResourceManager()
{
}

ColdTable::MeshManager::~MeshManager()
{
}

ColdTable::MeshPtr ColdTable::MeshManager::CreateMeshFromFile(GraphicsDevicePtr sourceDevice, const wchar_t* filepath, MaterialPtr material)
{
	_material = material;
	return std::static_pointer_cast<Mesh>(CreateResourceFromFile(sourceDevice, filepath));
}

ColdTable::Resource* ColdTable::MeshManager::CreateResourceFromFileConcrete(GraphicsDevicePtr sourceDevice,
	const wchar_t* filepath)
{

	Mesh* mesh = nullptr;
	try
	{
		mesh = new Mesh(sourceDevice, filepath, _material);
	}
	catch (...) {}

	return mesh;
}
