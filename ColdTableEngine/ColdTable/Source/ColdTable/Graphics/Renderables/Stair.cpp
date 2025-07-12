#include <ColdTable/Graphics/Renderables/Stair.h>

#include "ColdTable/Graphics/VertexBuffer.h"

ColdTable::Stair::Stair(StairDesc desc, IndexBufferPtr indexBuffer, ShaderPtr shader): Renderable({
	                                                                                                  0, 0,
	                                                                                                  EGeometryDrawmode::DRAWMODE_TRI,
	                                                                                                  nullptr
                                                                                                  }, shader)
{
	float stepHeight = desc._height / desc._stepCount;
	float stepDepth = desc._length / desc._stepCount;

	Vertex* vertList = new Vertex[(desc._stepCount * 20) + 4];
	unsigned int* indexList = new unsigned int[(desc._stepCount * 30) + 6];
	int vertIndexTracker = 0;
	for (int i = 0; i < desc._stepCount; i++)
	{
		GenerateStep(stepHeight, desc._width, stepDepth, i, i == desc._stepCount - 1, vertList, indexList, &vertIndexTracker);
	}

	// Load the index buffer and vertex buffer
	indexBuffer->LoadIndices(indexList, (desc._stepCount * 30) + 6);
	LoadVerticesInIndex(vertList, (desc._stepCount * 20) + 4, indexBuffer);

	// Set AABBs
	aabb_min = Vec3{ -0.5, -0.5, -0.5 };
	aabb_max = Vec3{ 0.5, 0.5, 0.5 };
}

ColdTable::Stair::Stair(StairDesc desc, IndexBufferPtr indexBuffer, MaterialPtr material) : Renderable({
		0, 0,
		EGeometryDrawmode::DRAWMODE_TRI,
		material
	})
{
	float stepHeight = desc._height / desc._stepCount;
	float stepDepth = desc._length / desc._stepCount;

	Vertex* vertList = new Vertex[(desc._stepCount * 20) + 4];
	unsigned int* indexList = new unsigned int[(desc._stepCount * 30) + 6];
	int vertIndexTracker = 0;
	for (int i = 0; i < desc._stepCount; i++)
	{
		GenerateStep(stepHeight, desc._width, stepDepth, i, i == desc._stepCount - 1, vertList, indexList, &vertIndexTracker);
	}

	// Load the index buffer and vertex buffer
	indexBuffer->LoadIndices(indexList, sizeof(indexList) / sizeof(indexList[0]));
	LoadVerticesInIndex(vertList, sizeof(vertList) / sizeof(vertList[0]), indexBuffer);

	// Set AABBs
	aabb_min = Vec3{ -0.5, -0.5, -0.5 };
	aabb_max = Vec3{ 0.5, 0.5, 0.5 };
}

void ColdTable::Stair::GenerateStep(float _stepHeight, float _stepWidth, float _stepDepth, int stepOffset, bool isLast,
	Vertex* vertList, unsigned int* indexList, int* indexTracker)
{
	// Generate Front
	GenerateZFace(Vec3(0.0f, _stepHeight * stepOffset, _stepDepth * stepOffset), Vec3::Forward, _stepHeight, _stepWidth, stepOffset * 20 + 0, vertList, indexList, indexTracker);
	// Generate Top
	GenerateYFace(Vec3(0.0f, _stepHeight * (stepOffset + 1), _stepDepth * stepOffset), Vec3::Up, _stepWidth, _stepDepth, stepOffset * 20 + 4, vertList, indexList, indexTracker);
	// Generate Bottom
	GenerateYFace(Vec3(0.0f, 0.0f, _stepDepth * stepOffset), Vec3::Down, _stepWidth, _stepDepth, stepOffset * 20 + 8, vertList, indexList, indexTracker);
	// Generate Left
	GenerateXFace(Vec3(0.0f, 0.0f, _stepDepth * stepOffset), Vec3::Left, _stepHeight * (stepOffset + 1), _stepDepth, stepOffset * 20 + 12, vertList, indexList, indexTracker);
	// Generate Right
	GenerateXFace(Vec3(_stepWidth, 0.0f, _stepDepth * stepOffset), Vec3::Right, _stepHeight * (stepOffset + 1), _stepDepth, stepOffset * 20 + 16, vertList, indexList, indexTracker);

	// Geneerate Back if last
	if (isLast)
		GenerateZFace(Vec3(0.0f, 0.0f, _stepDepth * (stepOffset + 1)), Vec3::Back, _stepHeight * (stepOffset + 1), _stepWidth, stepOffset * 20 + 20, vertList, indexList, indexTracker);
}

void ColdTable::Stair::GenerateZFace(Vec3 origin, Vec3 normal, float _height, float _width, int countOffset,
	Vertex* vertList, unsigned int* indexList, int* indexTracker)
{
	Vertex v0, v1, v2, v3;
	if (normal == Vec3::Back)
	{
		v3 = { origin, Vec2(1,0), normal };
		v2 = { origin + Vec3(0,_height,0), Vec2(1,1), normal };
		v1 = { origin + Vec3(_width,_height,0), Vec2(0,1), normal };
		v0 = { origin + Vec3(_width,0,0), Vec2(0,0), normal };
	}
	else
	{
		v0 = { origin, Vec2(0,0), normal };
		v1 = { origin + Vec3(0,_height,0), Vec2(0,1), normal };
		v2 = { origin + Vec3(_width,_height,0), Vec2(1,1), normal };
		v3 = { origin + Vec3(_width,0,0), Vec2(1,0), normal };
	}

	vertList[countOffset + 0] = v0;
	vertList[countOffset + 1] = v1;
	vertList[countOffset + 2] = v2;
	vertList[countOffset + 3] = v3;

	indexList[(*indexTracker)++] = static_cast<unsigned int>(countOffset + 0);
	indexList[(*indexTracker)++] = static_cast<unsigned int>(countOffset + 1);
	indexList[(*indexTracker)++] = static_cast<unsigned int>(countOffset + 2);
	indexList[(*indexTracker)++] = static_cast<unsigned int>(countOffset + 2);
	indexList[(*indexTracker)++] = static_cast<unsigned int>(countOffset + 3);
	indexList[(*indexTracker)++] = static_cast<unsigned int>(countOffset + 0);

	VertexObjectPtr vptr0 = AddVertex(v0.position, countOffset + 0);
	VertexObjectPtr vptr1 = AddVertex(v1.position, countOffset + 1);
	VertexObjectPtr vptr2 = AddVertex(v2.position, countOffset + 2);
	VertexObjectPtr vptr3 = AddVertex(v3.position, countOffset + 3);

	EdgeObjectPtr edge1 = std::make_shared<EdgeObject>(vptr0, vptr1);
	EdgeObjectPtr edge2 = std::make_shared<EdgeObject>(vptr1, vptr2);
	EdgeObjectPtr edge3 = std::make_shared<EdgeObject>(vptr2, vptr3);
	EdgeObjectPtr edge4 = std::make_shared<EdgeObject>(vptr3, vptr0);

	FaceObjectPtr face = std::make_shared<FaceObject>(edge1, edge2, edge3, edge4, normal);
	_vertexBuffer->_faceObjects.push_back(face);
}

void ColdTable::Stair::GenerateXFace(Vec3 origin, Vec3 normal, float _height, float _depth, int countOffset,
	Vertex* vertList, unsigned int* indexList, int* indexTracker)
{
	Vertex v0, v1, v2, v3;
	if (normal == Vec3::Left)
	{
		v3 = { origin, Vec2(1,0), normal };
		v2 = { origin + Vec3(0,_height,0), Vec2(1,1), normal };
		v1 = { origin + Vec3(0,_height,_depth), Vec2(0,1), normal };
		v0 = { origin + Vec3(0,0,_depth), Vec2(0,0), normal };
	}
	else
	{
		v0 = { origin, Vec2(0,0), normal };
		v1 = { origin + Vec3(0,_height,0), Vec2(0,1), normal };
		v2 = { origin + Vec3(0,_height,_depth), Vec2(1,1), normal };
		v3 = { origin + Vec3(0,0,_depth), Vec2(1,0), normal };
	}

	vertList[countOffset + 0] = v0;
	vertList[countOffset + 1] = v1;
	vertList[countOffset + 2] = v2;
	vertList[countOffset + 3] = v3;

	indexList[(*indexTracker)++] = static_cast<unsigned int>(countOffset + 0);
	indexList[(*indexTracker)++] = static_cast<unsigned int>(countOffset + 1);
	indexList[(*indexTracker)++] = static_cast<unsigned int>(countOffset + 2);
	indexList[(*indexTracker)++] = static_cast<unsigned int>(countOffset + 2);
	indexList[(*indexTracker)++] = static_cast<unsigned int>(countOffset + 3);
	indexList[(*indexTracker)++] = static_cast<unsigned int>(countOffset + 0);

	VertexObjectPtr vptr0 = AddVertex(v0.position, countOffset + 0);
	VertexObjectPtr vptr1 = AddVertex(v1.position, countOffset + 1);
	VertexObjectPtr vptr2 = AddVertex(v2.position, countOffset + 2);
	VertexObjectPtr vptr3 = AddVertex(v3.position, countOffset + 3);

	EdgeObjectPtr edge1 = std::make_shared<EdgeObject>(vptr0, vptr1);
	EdgeObjectPtr edge2 = std::make_shared<EdgeObject>(vptr1, vptr2);
	EdgeObjectPtr edge3 = std::make_shared<EdgeObject>(vptr2, vptr3);
	EdgeObjectPtr edge4 = std::make_shared<EdgeObject>(vptr3, vptr0);

	FaceObjectPtr face = std::make_shared<FaceObject>(edge1, edge2, edge3, edge4, normal);
	_vertexBuffer->_faceObjects.push_back(face);
}

void ColdTable::Stair::GenerateYFace(Vec3 origin, Vec3 normal, float _width, float _depth, int countOffset,
	Vertex* vertList, unsigned int* indexList, int* indexTracker)
{
	Vertex v0, v1, v2, v3;
	if (normal == Vec3::Down)
	{
		v3 = { origin, Vec2(1,0), normal };
		v2 = { origin + Vec3(0,0,_depth), Vec2(1,1), normal };
		v1 = { origin + Vec3(_width,0,_depth), Vec2(0,1), normal };
		v0 = { origin + Vec3(_width,0,0), Vec2(0,0), normal };
	}
	else
	{
		v0 = { origin, Vec2(0,0), normal };
		v1 = { origin + Vec3(0,0,_depth), Vec2(0,1), normal };
		v2 = { origin + Vec3(_width,0,_depth), Vec2(1,1), normal };
		v3 = { origin + Vec3(_width,0,0), Vec2(1,0), normal };
	}

	vertList[countOffset + 0] = v0;
	vertList[countOffset + 1] = v1;
	vertList[countOffset + 2] = v2;
	vertList[countOffset + 3] = v3;

	indexList[(*indexTracker)++] = static_cast<unsigned int>(countOffset + 0);
	indexList[(*indexTracker)++] = static_cast<unsigned int>(countOffset + 1);
	indexList[(*indexTracker)++] = static_cast<unsigned int>(countOffset + 2);
	indexList[(*indexTracker)++] = static_cast<unsigned int>(countOffset + 2);
	indexList[(*indexTracker)++] = static_cast<unsigned int>(countOffset + 3);
	indexList[(*indexTracker)++] = static_cast<unsigned int>(countOffset + 0);

	VertexObjectPtr vptr0 = AddVertex(v0.position, countOffset + 0);
	VertexObjectPtr vptr1 = AddVertex(v1.position, countOffset + 1);
	VertexObjectPtr vptr2 = AddVertex(v2.position, countOffset + 2);
	VertexObjectPtr vptr3 = AddVertex(v3.position, countOffset + 3);

	EdgeObjectPtr edge1 = std::make_shared<EdgeObject>(vptr0, vptr1);
	EdgeObjectPtr edge2 = std::make_shared<EdgeObject>(vptr1, vptr2);
	EdgeObjectPtr edge3 = std::make_shared<EdgeObject>(vptr2, vptr3);
	EdgeObjectPtr edge4 = std::make_shared<EdgeObject>(vptr3, vptr0);

	FaceObjectPtr face = std::make_shared<FaceObject>(edge1, edge2, edge3, edge4, normal);
	_vertexBuffer->_faceObjects.push_back(face);
}


ColdTable::VertexObjectPtr ColdTable::Stair::AddVertex(Vec3 pos, unsigned int index)
{
	for (auto vert : _vertexBuffer->_vertexObjects)
	{
		if ((vert->tempPos - pos).magnitudeSqrd() <= 0.00001f)
		{
			vert->AddVertex(index);
			return vert;
		}
	}
	VertexObjectPtr newVert = std::make_shared<VertexObject>(_vertexBuffer, index, pos);
	_vertexBuffer->_vertexObjects.push_back(newVert);
	return newVert;
}
