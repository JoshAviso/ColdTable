#include <ColdTable/Resource/Mesh/MeshManager.h>

#include "ColdTable/Graphics/GraphicsEngine.h"
#include "DearImGUI/imgui.h"

ColdTable::MeshManager::MeshManager(): ResourceManager()
{
	// Create some primitive meshes
	CreateCubeMesh(1.0f);
	CreatePlaneMesh(10.0f, 0.01f);
	CreateSphereMesh(0.5f,16,16);
	CreateCylinderMesh(0.5f, 2.0f,1,16);
	CreateCapsuleMesh(0.5f,2.0f,16,16);
}

ColdTable::MeshManager::~MeshManager(){}

ColdTable::MeshManager* ColdTable::MeshManager::Instance = nullptr;
void ColdTable::MeshManager::Initialize()
{
	if (Instance == nullptr)
	{
		Instance = new MeshManager();
	}
	else
	{
		Logger::LogWarning("MeshManager already initialized.");
		return;
	}
}

void ColdTable::MeshManager::DrawImportButton()
{
	
}

ColdTable::MeshPtr ColdTable::MeshManager::GetMesh(String key)
{
	if (_meshLibrary.find(key) != _meshLibrary.end())
		return _meshLibrary[key];

	return nullptr;
}

ColdTable::String ColdTable::MeshManager::FindMeshKey(MeshPtr mesh)
{
	// Iterate over all key-value pairs in the map
	for (const auto& pair : _meshLibrary)  // Replace meshMap with your actual map variable name
	{
		if (pair.second == mesh)  // Compare the MeshPtr values
		{
			return pair.first;    // Return key if value matches
		}
	}

	// Return empty string or some sentinel value if not found
	return ColdTable::String();
}

ColdTable::MeshPtr ColdTable::MeshManager::CreateMeshFromRenderable(String key, RenderablePtr renderable)
{
	if (_meshLibrary.find(key) != _meshLibrary.end())
		return _meshLibrary[key];
	MeshPtr mesh = std::make_shared<Mesh>(renderable);
	if (mesh != nullptr)
	{
		_meshLibrary.insert({ key, mesh });
	}
	return mesh;
}

ColdTable::MeshPtr ColdTable::MeshManager::CreateMeshFromList(String key, Vertex* vertexList, UINT vertexCount, UINT* indexList, UINT indexCount)
{
	if (_meshLibrary.find(key) != _meshLibrary.end())
		return _meshLibrary[key];

	MeshPtr mesh = std::make_shared<Mesh>(GraphicsEngine::Instance->_graphicsDevice, vertexList, vertexCount, indexList, indexCount);
	if (mesh != nullptr)
	{
		_meshLibrary.insert({ key, mesh });
	}

	return mesh;
}

ColdTable::MeshPtr ColdTable::MeshManager::CreateMeshFromFile(String key, GraphicsDevicePtr sourceDevice, const wchar_t* filepath, MaterialPtr material)
{
	_material = material;
	if (_meshLibrary.find(key) != _meshLibrary.end())
		return _meshLibrary[key];

	MeshPtr mesh = std::static_pointer_cast<Mesh>(CreateResourceFromFile(sourceDevice, filepath));
	if (mesh != nullptr)
	{
		_meshLibrary.insert({key, mesh});
		
	}

	return mesh;
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


void ColdTable::MeshManager::CreateCubeMesh(float side)
{
	std::vector<Vertex> vertlist{};
	std::vector<unsigned int> indexList{};

	float half = side / 2.0f;

	// Positions of 8 cube corners
	Vec3 p[8] = {
		{-half, -half,  half}, // 0
		{ half, -half,  half}, // 1
		{ half,  half,  half}, // 2
		{-half,  half,  half}, // 3
		{-half, -half, -half}, // 4
		{ half, -half, -half}, // 5
		{ half,  half, -half}, // 6
		{-half,  half, -half}  // 7
	};

	// Cube faces normals
	Vec3 normals[6] = {
		{ 0,  0,  1},  // Front
		{ 0,  0, -1},  // Back
		{ 1,  0,  0},  // Right
		{-1,  0,  0},  // Left
		{ 0,  1,  0},  // Top
		{ 0, -1,  0}   // Bottom
	};

	// Each face defined by 4 vertex indices from p[]
	int faceIndices[6][4] = {
		{0, 1, 2, 3},  // Front
		{5, 4, 7, 6},  // Back
		{1, 5, 6, 2},  // Right
		{4, 0, 3, 7},  // Left
		{3, 2, 6, 7},  // Top
		{4, 5, 1, 0}   // Bottom
	};

	// UV coords for each face (same for all faces)
	float uvCoords[4][2] = {
		{0.0f, 1.0f}, {1.0f, 1.0f},
		{1.0f, 0.0f}, {0.0f, 0.0f}
	};

	// Build vertices for each face (24 vertices total)
	for (int f = 0; f < 6; ++f) {
		for (int v = 0; v < 4; ++v) {
			vertlist.push_back(Vertex{
				p[faceIndices[f][v]],
				{uvCoords[v][0], uvCoords[v][1]},
				normals[f],
			});
		}
	}

	// Build indices (2 triangles per face)
	for (int f = 0; f < 6; ++f) {
		int start = f * 4;
		indexList.push_back(start + 0);
		indexList.push_back(start + 1);
		indexList.push_back(start + 2);

		indexList.push_back(start + 2);
		indexList.push_back(start + 3);
		indexList.push_back(start + 0);
	}

	CreateMeshFromList("Cube", vertlist.data(), vertlist.size(), indexList.data(), indexList.size());
}

void ColdTable::MeshManager::CreatePlaneMesh(float side, float height)
{
	std::vector<Vertex> vertlist{};
	std::vector<unsigned int> indexList{};

	float half = side / 2.0f;
	float halfHeight = height / 2.0f;

	// Positions of 8 cube corners
	Vec3 p[8] = {
		{-half, -halfHeight,  half}, // 0
		{ half, -halfHeight,  half}, // 1
		{ half,  halfHeight,  half}, // 2
		{-half,  halfHeight,  half}, // 3
		{-half, -halfHeight, -half}, // 4
		{ half, -halfHeight, -half}, // 5
		{ half,  halfHeight, -half}, // 6
		{-half,  halfHeight, -half}  // 7
	};

	// Cube faces normals
	Vec3 normals[6] = {
		{ 0,  0,  1},  // Front
		{ 0,  0, -1},  // Back
		{ 1,  0,  0},  // Right
		{-1,  0,  0},  // Left
		{ 0,  1,  0},  // Top
		{ 0, -1,  0}   // Bottom
	};

	// Each face defined by 4 vertex indices from p[]
	int faceIndices[6][4] = {
		{0, 1, 2, 3},  // Front
		{5, 4, 7, 6},  // Back
		{1, 5, 6, 2},  // Right
		{4, 0, 3, 7},  // Left
		{3, 2, 6, 7},  // Top
		{4, 5, 1, 0}   // Bottom
	};

	// UV coords for each face (same for all faces)
	float uvCoords[4][2] = {
		{0.0f, 1.0f}, {1.0f, 1.0f},
		{1.0f, 0.0f}, {0.0f, 0.0f}
	};

	// Build vertices for each face (24 vertices total)
	for (int f = 0; f < 6; ++f) {
		for (int v = 0; v < 4; ++v) {
			vertlist.push_back(Vertex{
				p[faceIndices[f][v]],
				{uvCoords[v][0], uvCoords[v][1]},
				normals[f],
				});
		}
	}

	// Build indices (2 triangles per face)
	for (int f = 0; f < 6; ++f) {
		int start = f * 4;
		indexList.push_back(start + 0);
		indexList.push_back(start + 1);
		indexList.push_back(start + 2);

		indexList.push_back(start + 2);
		indexList.push_back(start + 3);
		indexList.push_back(start + 0);
	}

	CreateMeshFromList("Plane", vertlist.data(), vertlist.size(), indexList.data(), indexList.size());

}
void ColdTable::MeshManager::CreateSphereMesh(float radius, UINT sliceCount, UINT stackCount)
{
	std::vector<Vertex> vertlist{};
	std::vector<unsigned int> indexList{};


	for (int i = 0; i <= stackCount; ++i) {
		float phi = (float)M_PI * i / stackCount;
		float y = radius * cos(phi);
		float r = radius * sin(phi);

		for (int j = 0; j <= sliceCount; ++j) {
			float theta = 2.0f * (float)M_PI * j / sliceCount;
			float x = r * cos(theta);
			float z = r * sin(theta);

			Vec3 pos = { x, y, z };
			Vec3 n = { x / radius, y / radius, z / radius };

			float u = (float)j / sliceCount;
			float v = (float)i / stackCount;

			vertlist.push_back(Vertex{ pos, { u, v }, n });
		}
	}

	for (int i = 0; i < stackCount; ++i) {
		for (int j = 0; j < sliceCount; ++j) {
			int first = i * (sliceCount + 1) + j;
			int second = first + sliceCount + 1;

			indexList.push_back(first);
			indexList.push_back(first + 1);
			indexList.push_back(second);

			indexList.push_back(second);
			indexList.push_back(first + 1);
			indexList.push_back(second + 1);
		}
	}

	CreateMeshFromList("Sphere", vertlist.data(), vertlist.size(), indexList.data(), indexList.size());
}

void ColdTable::MeshManager::CreateCylinderMesh(float radius, float height, UINT stackCount, UINT sliceCount)
{
	std::vector<Vertex> vertlist{};
	std::vector<unsigned int> indexList{};

	float halfHeight = height * 0.5f;

	// Generate side vertices
	for (int i = 0; i <= stackCount; ++i) {
		float y = -halfHeight + height * ((float)i / stackCount);
		for (int j = 0; j <= sliceCount; ++j) {
			float theta = 2.0f * (float)M_PI * j / sliceCount;
			float x = radius * cos(theta);
			float z = radius * sin(theta);

			Vec3 pos = { x, y, z };
			Vec3 n = { x, 0.0f, z };
			float length = sqrt(n.x * n.x + n.z * n.z);
			n.x /= length; n.z /= length;

			float u = (float)j / sliceCount;
			float v = (float)i / stackCount;

			vertlist.push_back(Vertex{ pos,{ u, v }, n });
		}
	}

	// Create side indices
	for (int i = 0; i < stackCount; ++i) {
		for (int j = 0; j < sliceCount; ++j) {
			int first = i * (sliceCount + 1) + j;
			int second = first + sliceCount + 1;

			indexList.push_back(first);
			indexList.push_back(second);
			indexList.push_back(first + 1);

			indexList.push_back(second);
			indexList.push_back(second + 1);
			indexList.push_back(first + 1);
		}
	}

	// Top cap center vertex
	int topCenterIndex = (int)vertlist.size();
	vertlist.push_back(Vertex{ {0, halfHeight, 0}, {0.5f, 0.5f}, { 0, 1, 0 } });

	// Top cap vertices
	for (int j = 0; j <= sliceCount; ++j) {
		float theta = 2.0f * (float)M_PI * j / sliceCount;
		float x = radius * cos(theta);
		float z = radius * sin(theta);

		Vec3 pos = { x, halfHeight, z };
		Vec3 n = { 0, 1, 0 };
		float u = 0.5f + 0.5f * cos(theta);
		float v = 0.5f + 0.5f * sin(theta);

		vertlist.push_back(Vertex{ pos, {u, v }, n });
	}

	// Top cap indices
	for (int j = 0; j < sliceCount; ++j) {
		indexList.push_back(topCenterIndex);
		indexList.push_back(topCenterIndex + j + 2);
		indexList.push_back(topCenterIndex + j + 1);
	}

	// Bottom cap center vertex
	int bottomCenterIndex = (int)vertlist.size();
	vertlist.push_back(Vertex{ {0, -halfHeight, 0}, {0.5f, 0.5f}, {0, -1, 0} });

	// Bottom cap vertices
	for (int j = 0; j <= sliceCount; ++j) {
		float theta = 2.0f * (float)M_PI * j / sliceCount;
		float x = radius * cos(theta);
		float z = radius * sin(theta);

		Vec3 pos = { x, -halfHeight, z };
		Vec3 n = { 0, -1, 0 };
		float u = 0.5f + 0.5f * cos(theta);
		float v = 0.5f + 0.5f * sin(theta);

		vertlist.push_back(Vertex{ pos, { u, v }, n });
	}

	// Bottom cap indices
	for (int j = 0; j < sliceCount; ++j) {
		indexList.push_back(bottomCenterIndex);
		indexList.push_back(bottomCenterIndex + j + 1);
		indexList.push_back(bottomCenterIndex + j + 2);
	}

	CreateMeshFromList("Cylinder", vertlist.data(), vertlist.size(), indexList.data(), indexList.size());
}

void ColdTable::MeshManager::CreateCapsuleMesh(float radius, float height, UINT sliceCount, UINT stackCount)
{
	std::vector<Vertex> vertlist{};
	std::vector<unsigned int> indexList{};

	float cylinderHeight = height - 2 * radius;
	float halfCylinderHeight = cylinderHeight * 0.5f;

	// Generate side vertices
	for (int i = 0; i <= 1; ++i) {
		float y = -halfCylinderHeight + cylinderHeight * ((float)i / 1);
		for (int j = 0; j <= sliceCount; ++j) {
			float theta = 2.0f * (float)M_PI * j / sliceCount;
			float x = radius * cos(theta);
			float z = radius * sin(theta);

			Vec3 pos = { x, y, z };
			Vec3 n = { x, 0.0f, z };
			float length = sqrt(n.x * n.x + n.z * n.z);
			n.x /= length; n.z /= length;

			float u = (float)j / sliceCount;
			float v = (float)i / 1;

			vertlist.push_back(Vertex{ pos,{ u, v }, n });
		}
	}

	// Create side indices
	for (int i = 0; i < stackCount; ++i) {
		for (int j = 0; j < sliceCount; ++j) {
			int first = i * (sliceCount + 1) + j;
			int second = first + sliceCount + 1;

			indexList.push_back(first);
			indexList.push_back(second);
			indexList.push_back(first + 1);

			indexList.push_back(second);
			indexList.push_back(second + 1);
			indexList.push_back(first + 1);
		}
	}

	int baseIndex = (int)vertlist.size();

	// Generate top hemisphere (stacks from 0 to stacks, phi from 0 to pi/2)
	for (int i = 0; i <= stackCount; ++i) {
		float phi = 0.5f * (float)M_PI * i / stackCount;
		float y = radius * cos(phi) + halfCylinderHeight;
		float r = radius * sin(phi);

		for (int j = 0; j <= sliceCount; ++j) {
			float theta = 2.0f * (float)M_PI * j / sliceCount;
			float x = r * cos(theta);
			float z = r * sin(theta);

			Vec3 pos = { x, y, z };
			Vec3 n = { x / radius, (y - halfCylinderHeight) / radius, z / radius };
			float u = (float)j / sliceCount;
			float v = (float)i / stackCount / 2.0f;  // UV v scaled for hemisphere

			vertlist.push_back(Vertex{ pos,{ u, v }, n});
		}
	}

	// Generate top hemisphere indices
	int topStart = baseIndex;
	int hemiStacks = stackCount;
	int hemiSlices = sliceCount;

	for (int i = 0; i < hemiStacks; ++i) {
		for (int j = 0; j < hemiSlices; ++j) {
			int first = topStart + i * (hemiSlices + 1) + j;
			int second = first + hemiSlices + 1;

			indexList.push_back(first);
			indexList.push_back(first + 1);
			indexList.push_back(second);

			indexList.push_back(second);
			indexList.push_back(first + 1);
			indexList.push_back(second + 1);
		}
	}

	baseIndex = (int)vertlist.size();

	// Generate bottom hemisphere (phi from pi/2 to pi)
	for (int i = 0; i <= stackCount; ++i) {
		float phi = 0.5f * (float)M_PI + 0.5f * (float)M_PI * i / stackCount;
		float y = radius * cos(phi) - halfCylinderHeight;
		float r = radius * sin(phi);

		for (int j = 0; j <= sliceCount; ++j) {
			float theta = 2.0f * (float)M_PI * j / sliceCount;
			float x = r * cos(theta);
			float z = r * sin(theta);

			Vec3 pos = { x, y, z };
			Vec3 n = { x / radius, (y + halfCylinderHeight) / radius, z / radius };
			float u = (float)j / sliceCount;
			float v = 0.5f + (float)i / stackCount / 2.0f;  // UV v adjusted

			vertlist.push_back(Vertex{ pos, { u, v }, n });
		}
	}

	// Generate bottom hemisphere indices
	int bottomStart = baseIndex;

	for (int i = 0; i < hemiStacks; ++i) {
		for (int j = 0; j < hemiSlices; ++j) {
			int first = bottomStart + i * (hemiSlices + 1) + j;
			int second = first + hemiSlices + 1;

			indexList.push_back(first);
			indexList.push_back(first + 1);
			indexList.push_back(second);

			indexList.push_back(second);
			indexList.push_back(first + 1);
			indexList.push_back(second + 1);
		}
	}

	CreateMeshFromList("Capsule", vertlist.data(), vertlist.size(), indexList.data(), indexList.size());
}

/*
void ColdTable::MeshManager::CreateCubeMesh()
{
	Vec3 positionList[] = {
		// FRONT FACE
		{-0.5, -0.5, -0.5},
		{-0.5,  0.5, -0.5},
		{ 0.5,  0.5, -0.5},
		{ 0.5, -0.5, -0.5},
		//// BACK FACE
		{ 0.5, -0.5,  0.5},
		{ 0.5,  0.5,  0.5},
		{-0.5,  0.5,  0.5},
		{-0.5, -0.5,  0.5}
	};
	Vec3 normalList[] = {
		{0.0f, 0.0f, -1.0f},
		{0.0f, 0.0f, 1.0f},
		{0.0f, 1.0f, 0.0f},
		{0.0f, -1.0f, 0.0f},
		{1.0f, 0.0f, 0.0f},
		{-1.0f, 0.0f, 0.0f},
	};
	Vec2 texcoordList[] = {
		{0.0f, 0.0f},
		{0.0f, 1.0f},
		{1.0f, 0.0f},
		{1.0f, 1.0f}
	};
	Vertex vertlist[] = {
		//
		{positionList[0], texcoordList[1], normalList[0], {1.0, 0.0, 0.0}},
		{positionList[1], texcoordList[0], normalList[0], {0.0, 1.0, 0.0}},
		{positionList[2], texcoordList[2], normalList[0], {0.0, 0.0, 1.0}},
		{positionList[3], texcoordList[3], normalList[0], {1.0, 1.0, 0.0}},
		// FRONT
		//
		{positionList[4], texcoordList[1], normalList[1], {1.0, 0.0, 0.0}},
		{positionList[5], texcoordList[0], normalList[1], {0.0, 1.0, 0.0}},
		{positionList[6], texcoordList[2], normalList[1], {0.0, 0.0, 1.0}},
		{positionList[7], texcoordList[3], normalList[1], {1.0, 1.0, 0.0}},
		// BACK
		//
		{positionList[1], texcoordList[1], normalList[2], {1.0, 0.0, 0.0}},
		{positionList[6], texcoordList[0], normalList[2], {0.0, 1.0, 0.0}},
		{positionList[5], texcoordList[2], normalList[2], {0.0, 0.0, 1.0}},
		{positionList[2], texcoordList[3], normalList[2], {1.0, 1.0, 0.0}},
		// TOP
		//
		{positionList[7], texcoordList[1], normalList[3], {1.0, 0.0, 0.0}},
		{positionList[0], texcoordList[0], normalList[3], {0.0, 1.0, 0.0}},
		{positionList[3], texcoordList[2], normalList[3], {0.0, 0.0, 1.0}},
		{positionList[4], texcoordList[3], normalList[3], {1.0, 1.0, 0.0}},
		// BOTTOM
		//
		{positionList[3], texcoordList[1], normalList[4], {1.0, 0.0, 0.0}},
		{positionList[2], texcoordList[0], normalList[4], {0.0, 1.0, 0.0}},
		{positionList[5], texcoordList[2], normalList[4], {0.0, 0.0, 1.0}},
		{positionList[4], texcoordList[3], normalList[4], {1.0, 1.0, 0.0}},
		// RIGHT
		//
		{positionList[7], texcoordList[1], normalList[5], {1.0, 0.0, 0.0}},
		{positionList[6], texcoordList[0], normalList[5], {0.0, 1.0, 0.0}},
		{positionList[1], texcoordList[2], normalList[5], {0.0, 0.0, 1.0}},
		{positionList[0], texcoordList[3], normalList[5], {1.0, 1.0, 0.0}},
		// LEFT
	};

	unsigned int indexList[] = {
		0, 1, 2, 2, 3, 0, // FRONT
		4, 5, 6, 6, 7, 4, // BACK
		8, 9, 10, 10, 11, 8, // TOP
		12, 13, 14, 14, 15, 12, // BOTTOM
		16, 17, 18, 18, 19, 16, // RIGHT
		20, 21, 22, 22, 23, 20, // LEFT
	};

	CreateMeshFromList("Cube", vertlist, ARRAYSIZE(vertlist), indexList, ARRAYSIZE(indexList));
}

void ColdTable::MeshManager::CreatePlaneMesh()
{
	Vec3 positionList[] = {
		// FRONT FACE
		{-5.0, -0.01, -5.0},
		{-5.0,  0.01, -5.0},
		{ 5.0,  0.01, -5.0},
		{ 5.0, -0.01, -5.0},
		//// BACK FACE
		{ 5.0, -0.01,  5.0},
		{ 5.0,  0.01,  5.0},
		{-5.0,  0.01,  5.0},
		{-5.0, -0.01,  5.0}
	};
	Vec3 normalList[] = {
		{0.0f, 0.0f, -1.0f},
		{0.0f, 0.0f, 1.0f},
		{0.0f, 1.0f, 0.0f},
		{0.0f, -1.0f, 0.0f},
		{1.0f, 0.0f, 0.0f},
		{-1.0f, 0.0f, 0.0f},
	};
	Vec2 texcoordList[] = {
		{0.0f, 0.0f},
		{0.0f, 1.0f},
		{1.0f, 0.0f},
		{1.0f, 1.0f}
	};
	Vertex vertlist[] = {
		//
		{positionList[0], texcoordList[1], normalList[0], {1.0, 0.0, 0.0}},
		{positionList[1], texcoordList[0], normalList[0], {0.0, 1.0, 0.0}},
		{positionList[2], texcoordList[2], normalList[0], {0.0, 0.0, 1.0}},
		{positionList[3], texcoordList[3], normalList[0], {1.0, 1.0, 0.0}},
		// FRONT
		//
		{positionList[4], texcoordList[1], normalList[1], {1.0, 0.0, 0.0}},
		{positionList[5], texcoordList[0], normalList[1], {0.0, 1.0, 0.0}},
		{positionList[6], texcoordList[2], normalList[1], {0.0, 0.0, 1.0}},
		{positionList[7], texcoordList[3], normalList[1], {1.0, 1.0, 0.0}},
		// BACK
		//
		{positionList[1], texcoordList[1], normalList[2], {1.0, 0.0, 0.0}},
		{positionList[6], texcoordList[0], normalList[2], {0.0, 1.0, 0.0}},
		{positionList[5], texcoordList[2], normalList[2], {0.0, 0.0, 1.0}},
		{positionList[2], texcoordList[3], normalList[2], {1.0, 1.0, 0.0}},
		// TOP
		//
		{positionList[7], texcoordList[1], normalList[3], {1.0, 0.0, 0.0}},
		{positionList[0], texcoordList[0], normalList[3], {0.0, 1.0, 0.0}},
		{positionList[3], texcoordList[2], normalList[3], {0.0, 0.0, 1.0}},
		{positionList[4], texcoordList[3], normalList[3], {1.0, 1.0, 0.0}},
		// BOTTOM
		//
		{positionList[3], texcoordList[1], normalList[4], {1.0, 0.0, 0.0}},
		{positionList[2], texcoordList[0], normalList[4], {0.0, 1.0, 0.0}},
		{positionList[5], texcoordList[2], normalList[4], {0.0, 0.0, 1.0}},
		{positionList[4], texcoordList[3], normalList[4], {1.0, 1.0, 0.0}},
		// RIGHT
		//
		{positionList[7], texcoordList[1], normalList[5], {1.0, 0.0, 0.0}},
		{positionList[6], texcoordList[0], normalList[5], {0.0, 1.0, 0.0}},
		{positionList[1], texcoordList[2], normalList[5], {0.0, 0.0, 1.0}},
		{positionList[0], texcoordList[3], normalList[5], {1.0, 1.0, 0.0}},
		// LEFT
	};

	unsigned int indexList[] = {
		0, 1, 2, 2, 3, 0, // FRONT
		4, 5, 6, 6, 7, 4, // BACK
		8, 9, 10, 10, 11, 8, // TOP
		12, 13, 14, 14, 15, 12, // BOTTOM
		16, 17, 18, 18, 19, 16, // RIGHT
		20, 21, 22, 22, 23, 20, // LEFT
	};

	CreateMeshFromList("Plane", vertlist, ARRAYSIZE(vertlist), indexList, ARRAYSIZE(indexList));
}
*/