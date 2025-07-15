#include <ColdTable/Graphics/Renderables/Cylinder.h>

#include "ColdTable/Graphics/VertexBuffer.h"

ColdTable::Cylinder::Cylinder(CylinderDesc desc, IndexBufferPtr indexBuffer, ShaderPtr shader) : Renderable({
    0, 0,
    EGeometryDrawmode::DRAWMODE_TRI,
    nullptr
}, shader)
{
	Vec3 up = Vec3::Up;
	Vec3 forward = Vec3::Forward;
	if (desc._isHorizontal)
	{
		up = Vec3::Right;
		forward = Vec3::Up;
	}
	float anglePerSide = 360.0f / desc._sideCount;
	float sideWidth = desc._radius * sqrt(2 * (1 - cos(anglePerSide * M_PIf / 180.0f)));
	unsigned int vertCount = 8 * desc._sideCount + 2;
	unsigned int indexCount = 12 * desc._sideCount;

	Vertex* vertlist = new Vertex[vertCount];
	unsigned int* indexList = new unsigned int[indexCount];
	unsigned int indexTracker = 0;
	unsigned int vertexTracker = 0;

	Vec3 capForward = forward;
	if (desc._sideCount % 2 == 0)
		capForward = forward.rotateAroundAxis(up, -(anglePerSide / 2.0f));
	// Generate Top
	GenerateCap(up * desc._length / 2.0f, up, capForward, desc._radius, anglePerSide, desc._sideCount, vertlist, indexList, &vertexTracker, &indexTracker);
	// Generate Bottom
	GenerateCap(-up * desc._length / 2.0f, -up, capForward, desc._radius, anglePerSide, desc._sideCount, vertlist, indexList, &vertexTracker, &indexTracker);

	for (int i = 0; i < desc._sideCount; i++)
	{
		Vec3 localForward = forward.rotateAroundAxis(up, anglePerSide * i);
		GenerateSide(-localForward * (sqrt((desc._radius * desc._radius) - (sideWidth * sideWidth / 4.0f))), localForward, up, desc._length, sideWidth, i, desc._sideCount, vertlist, indexList, &vertexTracker, &indexTracker);
	}


	indexBuffer->LoadIndices(indexList, indexCount);
	LoadVerticesInIndex(vertlist, vertCount, indexBuffer);


	aabb_min = Vec3{ -0.5, -0.5, -0.5 };
	aabb_max = Vec3{ 0.5, 0.5, 0.5 };
}

ColdTable::Cylinder::Cylinder(CylinderDesc desc, IndexBufferPtr indexBuffer, MaterialPtr material) : Renderable({
		0, 0,
		EGeometryDrawmode::DRAWMODE_TRI,
		material
	})
{
	Vec3 up = Vec3::Up;
	Vec3 forward = Vec3::Forward;
	if (desc._isHorizontal)
	{
		up = Vec3::Right;
		forward = Vec3::Up;
	}
	float anglePerSide = 360.0f / desc._sideCount;
	float sideWidth = desc._radius * sqrt(2 * (1 - cos(anglePerSide * M_PIf / 180.0f)));
	unsigned int vertCount = 8 * desc._sideCount + 2;
	unsigned int indexCount = 12 * desc._sideCount;

	Vertex* vertlist = new Vertex[vertCount];
	unsigned int* indexList = new unsigned int[indexCount];
	unsigned int indexTracker = 0;
	unsigned int vertexTracker = 0;

	Vec3 capForward = forward;
	if (desc._sideCount % 2 == 0)
		capForward = forward.rotateAroundAxis(up, -(anglePerSide/2.0f));
	// Generate Top
	GenerateCap(up * desc._length / 2.0f, up, capForward, desc._radius, anglePerSide, desc._sideCount, vertlist, indexList, &vertexTracker, &indexTracker);
	// Generate Bottom
	GenerateCap(-up * desc._length / 2.0f, -up, capForward, desc._radius, anglePerSide, desc._sideCount, vertlist, indexList, &vertexTracker, &indexTracker);

	for (int i = 0; i < desc._sideCount; i++)
	{
		Vec3 localForward = forward.rotateAroundAxis(up, anglePerSide * (float)i);
		GenerateSide(localForward * (sqrt((desc._radius * desc._radius) - (sideWidth * sideWidth / 4.0f))), localForward, up, desc._length, sideWidth, i, desc._sideCount, vertlist, indexList, &vertexTracker, &indexTracker);
	}


	indexBuffer->LoadIndices(indexList, indexCount);
	LoadVerticesInIndex(vertlist, vertCount, indexBuffer);


	aabb_min = Vec3{ -0.5, -0.5, -0.5 };
	aabb_max = Vec3{ 0.5, 0.5, 0.5 };
}

void ColdTable::Cylinder::GenerateSide(Vec3 center, Vec3 normal, Vec3 up, float height, float width, int sideOffset, int sideCount, Vertex* vertlist, unsigned int* indexList, unsigned int* vertTracker, unsigned int* indexTracker)
{
	Vec3 right = up.cross(normal);
	Vertex v0, v1, v2, v3;
	v0 = {(center + (-right * (width / 2.0f)) + (-up * (height / 2.0f))), Vec2(0,0), normal};
	v1 = {(center + (-right * (width / 2.0f)) + (up * (height / 2.0f))), Vec2(0,1), normal};
	v2 = {(center + (right * (width / 2.0f)) + (up * (height / 2.0f))), Vec2(1,1), normal};
	v3 = {(center + (right * (width / 2.0f)) + (-up * (height / 2.0f))), Vec2(1,0), normal};

	vertlist[*vertTracker + 0] = v0;
	vertlist[*vertTracker + 1] = v1;
	vertlist[*vertTracker + 2] = v2;
	vertlist[*vertTracker + 3] = v3;

	indexList[(*indexTracker)++] = (*vertTracker + 0);
	indexList[(*indexTracker)++] = (*vertTracker + 1);
	indexList[(*indexTracker)++] = (*vertTracker + 2);
	indexList[(*indexTracker)++] = (*vertTracker + 2);
	indexList[(*indexTracker)++] = (*vertTracker + 3);
	indexList[(*indexTracker)++] = (*vertTracker + 0);

	VertexObjectPtr v0ptr = AddVertex(v0.position, *vertTracker + 0);
	VertexObjectPtr v1ptr = AddVertex(v1.position, *vertTracker + 1);
	VertexObjectPtr v2ptr = AddVertex(v2.position, *vertTracker + 2);
	VertexObjectPtr v3ptr = AddVertex(v3.position, *vertTracker + 3);

	EdgeObjectPtr edge1 = std::make_shared<EdgeObject>(v0ptr, v1ptr);
	EdgeObjectPtr edge2 = std::make_shared<EdgeObject>(v1ptr, v2ptr);
	EdgeObjectPtr edge3 = std::make_shared<EdgeObject>(v2ptr, v3ptr);
	EdgeObjectPtr edge4 = std::make_shared<EdgeObject>(v3ptr, v0ptr);

	FaceObjectPtr sideface = std::make_shared<FaceObject>(edge1, edge2, edge3, edge4, normal);
	_vertexBuffer->_faceObjects.push_back(sideface);

	*vertTracker += 4;
}

void ColdTable::Cylinder::GenerateCap(Vec3 center, Vec3 normal, Vec3 forward, float radius, float anglePerSide, int sideCount, Vertex* vertlist, unsigned int* indexList, unsigned int* vertTracker, unsigned int* indexTracker)
{
	Vertex centerVert = {center, Vec2(0, 0), normal};
	vertlist[*vertTracker] = centerVert;
	VertexObjectPtr centerVertPtr = AddVertex(centerVert.position, *vertTracker);

	Vec3 initForward = forward;
	std::vector<EdgeObjectPtr> capEdges;

	// Generate Side Tris
	for (int i = 0; i < sideCount; i++)
	{
		Vec3 f1 = initForward.rotateAroundAxis(normal, anglePerSide * i);
		Vec3 f2 = initForward.rotateAroundAxis(normal, anglePerSide * (float)(i + 1));

		Vertex v1 = { center + (f1 * radius), Vec2(0,1), normal, normal};
		Vertex v2 = { center + (f2 * radius), Vec2(1,1), normal, normal};

		int i1 = (*vertTracker + 1) + (i*2);
		int i2 = (*vertTracker + 1) + (i*2) + 1;

		vertlist[i1] = v1;
		vertlist[i2] = v2;

		indexList[(*indexTracker)++] = *vertTracker;
		indexList[(*indexTracker)++] = i1;
		indexList[(*indexTracker)++] = i2;

		VertexObjectPtr v1ptr = AddVertex(v1.position, i1);
		VertexObjectPtr v2ptr = AddVertex(v2.position, i2);

		EdgeObjectPtr edge1 = std::make_shared<EdgeObject>(centerVertPtr, v1ptr);
		EdgeObjectPtr edge2 = std::make_shared<EdgeObject>(centerVertPtr, v2ptr);
		EdgeObjectPtr edge3 = std::make_shared<EdgeObject>(v1ptr, v2ptr);

		capEdges.push_back(edge1);
		capEdges.push_back(edge2);
		capEdges.push_back(edge3);
	}

	FaceObjectPtr capFace = std::make_shared<FaceObject>(normal);
	for (auto edgeObject : capEdges)
	{
		capFace->AddEdge(edgeObject);
	}
	_vertexBuffer->_faceObjects.push_back(capFace);

	*vertTracker += 2 * sideCount + 1;
}

ColdTable::VertexObjectPtr ColdTable::Cylinder::AddVertex(Vec3 pos, unsigned int index)
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
