#include <ColdTable/Graphics/Renderables/Cube.h>

ColdTable::Cube::Cube(IndexBufferPtr indexBuffer, ShaderPtr shader): Renderable({
		0, 0,
		EGeometryDrawmode::DRAWMODE_TRI,
		nullptr
	}, shader)
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

	indexBuffer->LoadIndices(indexList, ARRAYSIZE(indexList));
	LoadVerticesInIndex(vertlist, ARRAYSIZE(vertlist), indexBuffer);


	aabb_min = Vec3{ -0.5, -0.5, -0.5 };
	aabb_max = Vec3{ 0.5, 0.5, 0.5 };
}
