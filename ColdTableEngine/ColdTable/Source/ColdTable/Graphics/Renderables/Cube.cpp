#include <ColdTable/Graphics/Renderables/Cube.h>

#include "ColdTable/Graphics/VertexBuffer.h"

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

	// Generate ProBuilder Objects
	VertexObjectPtr vert0 = std::make_shared<VertexObject>(_vertexBuffer, 0);
	vert0->AddVertex(13);
	vert0->AddVertex(23);
	VertexObjectPtr vert1 = std::make_shared<VertexObject>(_vertexBuffer, 1);
	vert1->AddVertex(8);
	vert1->AddVertex(22);
	VertexObjectPtr vert2 = std::make_shared<VertexObject>(_vertexBuffer, 2);
	vert2->AddVertex(11);
	vert2->AddVertex(17);
	VertexObjectPtr vert3 = std::make_shared<VertexObject>(_vertexBuffer, 3);
	vert3->AddVertex(14);
	vert3->AddVertex(16);
	VertexObjectPtr vert4 = std::make_shared<VertexObject>(_vertexBuffer, 4);
	vert4->AddVertex(15);
	vert4->AddVertex(19);
	VertexObjectPtr vert5 = std::make_shared<VertexObject>(_vertexBuffer, 5);
	vert5->AddVertex(10);
	vert5->AddVertex(18);
	VertexObjectPtr vert6 = std::make_shared<VertexObject>(_vertexBuffer, 6);
	vert6->AddVertex(9);
	vert6->AddVertex(21);
	VertexObjectPtr vert7 = std::make_shared<VertexObject>(_vertexBuffer, 7);
	vert7->AddVertex(12);
	vert7->AddVertex(20);

	// FRONT
	EdgeObjectPtr frontTopEdge = std::make_shared<EdgeObject>(vert1, vert2);
	EdgeObjectPtr frontRightEdge = std::make_shared<EdgeObject>(vert2, vert3);
	EdgeObjectPtr frontLeftEdge = std::make_shared<EdgeObject>(vert0, vert1);
	EdgeObjectPtr frontBottomEdge = std::make_shared<EdgeObject>(vert0, vert3);
	// BACK
	EdgeObjectPtr backTopEdge = std::make_shared<EdgeObject>(vert5, vert6);
	EdgeObjectPtr backRightEdge = std::make_shared<EdgeObject>(vert6, vert7);
	EdgeObjectPtr backLeftEdge = std::make_shared<EdgeObject>(vert4, vert5);
	EdgeObjectPtr backBottomEdge = std::make_shared<EdgeObject>(vert4, vert7);
	// TOP
	EdgeObjectPtr topTopEdge = std::make_shared<EdgeObject>(vert5, vert6);
	EdgeObjectPtr topRightEdge = std::make_shared<EdgeObject>(vert2, vert5);
	EdgeObjectPtr topLeftEdge = std::make_shared<EdgeObject>(vert1, vert6);
	EdgeObjectPtr topBottomEdge = std::make_shared<EdgeObject>(vert1, vert2);
	// BOTTOM
	EdgeObjectPtr bottomTopEdge = std::make_shared<EdgeObject>(vert4, vert7);
	EdgeObjectPtr bottomRightEdge = std::make_shared<EdgeObject>(vert3, vert4);
	EdgeObjectPtr bottomLeftEdge = std::make_shared<EdgeObject>(vert0, vert7);
	EdgeObjectPtr bottomBottomEdge = std::make_shared<EdgeObject>(vert0, vert3);
	// RIGHT
	EdgeObjectPtr rightTopEdge = std::make_shared<EdgeObject>(vert1, vert6);
	EdgeObjectPtr rightRightEdge = std::make_shared<EdgeObject>(vert0, vert1);
	EdgeObjectPtr rightLeftEdge = std::make_shared<EdgeObject>(vert6, vert7);
	EdgeObjectPtr rightBottomEdge = std::make_shared<EdgeObject>(vert0, vert7);
	// LEFT
	EdgeObjectPtr leftTopEdge = std::make_shared<EdgeObject>(vert2, vert5);
	EdgeObjectPtr leftRightEdge = std::make_shared<EdgeObject>(vert4, vert5);
	EdgeObjectPtr leftLeftEdge = std::make_shared<EdgeObject>(vert2, vert3);
	EdgeObjectPtr leftBottomEdge = std::make_shared<EdgeObject>(vert3, vert4);

	FaceObjectPtr frontFace = std::make_shared<FaceObject>(frontTopEdge, frontRightEdge, frontLeftEdge, frontBottomEdge, Vec3::Forward);
	FaceObjectPtr backFace = std::make_shared<FaceObject>(backTopEdge, backRightEdge, backLeftEdge, backBottomEdge, Vec3::Back);
	FaceObjectPtr topFace = std::make_shared<FaceObject>(topTopEdge, topRightEdge, topLeftEdge, topBottomEdge, Vec3::Up);
	FaceObjectPtr bottomFace = std::make_shared<FaceObject>(bottomTopEdge, bottomRightEdge, bottomLeftEdge, bottomBottomEdge, Vec3::Down);
	FaceObjectPtr rightFace = std::make_shared<FaceObject>(rightTopEdge, rightRightEdge, rightLeftEdge, rightBottomEdge, Vec3::Right);
	FaceObjectPtr leftFace = std::make_shared<FaceObject>(leftTopEdge, leftRightEdge, leftLeftEdge, leftBottomEdge, Vec3::Left);

	_vertexBuffer->_vertexObjects.push_back(vert0);
	_vertexBuffer->_vertexObjects.push_back(vert1);
	_vertexBuffer->_vertexObjects.push_back(vert2);
	_vertexBuffer->_vertexObjects.push_back(vert3);
	_vertexBuffer->_vertexObjects.push_back(vert4);
	_vertexBuffer->_vertexObjects.push_back(vert5);
	_vertexBuffer->_vertexObjects.push_back(vert6);
	_vertexBuffer->_vertexObjects.push_back(vert7);

	_vertexBuffer->_faceObjects.push_back(frontFace);
	_vertexBuffer->_faceObjects.push_back(backFace);
	_vertexBuffer->_faceObjects.push_back(topFace);
	_vertexBuffer->_faceObjects.push_back(bottomFace);
	_vertexBuffer->_faceObjects.push_back(rightFace);
	_vertexBuffer->_faceObjects.push_back(leftFace);

	aabb_min = Vec3{ -0.5, -0.5, -0.5 };
	aabb_max = Vec3{ 0.5, 0.5, 0.5 };
}

ColdTable::Cube::Cube(IndexBufferPtr indexBuffer, MaterialPtr material) : Renderable({
		0, 0,
		EGeometryDrawmode::DRAWMODE_TRI,
		material
	})
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

	// Generate ProBuilder Objects
	VertexObjectPtr vert0 = std::make_shared<VertexObject>(_vertexBuffer, 0);
	vert0->AddVertex(13);
	vert0->AddVertex(23);
	VertexObjectPtr vert1 = std::make_shared<VertexObject>(_vertexBuffer, 1);
	vert1->AddVertex(8);
	vert1->AddVertex(22);
	VertexObjectPtr vert2 = std::make_shared<VertexObject>(_vertexBuffer, 2);
	vert2->AddVertex(11);
	vert2->AddVertex(17);
	VertexObjectPtr vert3 = std::make_shared<VertexObject>(_vertexBuffer, 3);
	vert3->AddVertex(14);
	vert3->AddVertex(16);
	VertexObjectPtr vert4 = std::make_shared<VertexObject>(_vertexBuffer, 4);
	vert4->AddVertex(15);
	vert4->AddVertex(19);
	VertexObjectPtr vert5 = std::make_shared<VertexObject>(_vertexBuffer, 5);
	vert5->AddVertex(10);
	vert5->AddVertex(18);
	VertexObjectPtr vert6 = std::make_shared<VertexObject>(_vertexBuffer, 6);
	vert6->AddVertex(9);
	vert6->AddVertex(21);
	VertexObjectPtr vert7 = std::make_shared<VertexObject>(_vertexBuffer, 7);
	vert7->AddVertex(12);
	vert7->AddVertex(20);

	// FRONT
	EdgeObjectPtr frontTopEdge = std::make_shared<EdgeObject>(vert1, vert2);
	EdgeObjectPtr frontRightEdge = std::make_shared<EdgeObject>(vert2, vert3);
	EdgeObjectPtr frontLeftEdge = std::make_shared<EdgeObject>(vert0, vert1);
	EdgeObjectPtr frontBottomEdge = std::make_shared<EdgeObject>(vert0, vert3);
	// BACK
	EdgeObjectPtr backTopEdge = std::make_shared<EdgeObject>(vert5, vert6);
	EdgeObjectPtr backRightEdge = std::make_shared<EdgeObject>(vert6, vert7);
	EdgeObjectPtr backLeftEdge = std::make_shared<EdgeObject>(vert4, vert5);
	EdgeObjectPtr backBottomEdge = std::make_shared<EdgeObject>(vert4, vert7);
	// TOP
	EdgeObjectPtr topTopEdge = std::make_shared<EdgeObject>(vert5, vert6);
	EdgeObjectPtr topRightEdge = std::make_shared<EdgeObject>(vert2, vert5);
	EdgeObjectPtr topLeftEdge = std::make_shared<EdgeObject>(vert1, vert6);
	EdgeObjectPtr topBottomEdge = std::make_shared<EdgeObject>(vert1, vert2);
	// BOTTOM
	EdgeObjectPtr bottomTopEdge = std::make_shared<EdgeObject>(vert4, vert7);
	EdgeObjectPtr bottomRightEdge = std::make_shared<EdgeObject>(vert3, vert4);
	EdgeObjectPtr bottomLeftEdge = std::make_shared<EdgeObject>(vert0, vert7);
	EdgeObjectPtr bottomBottomEdge = std::make_shared<EdgeObject>(vert0, vert3);
	// RIGHT
	EdgeObjectPtr rightTopEdge = std::make_shared<EdgeObject>(vert1, vert6);
	EdgeObjectPtr rightRightEdge = std::make_shared<EdgeObject>(vert0, vert1);
	EdgeObjectPtr rightLeftEdge = std::make_shared<EdgeObject>(vert6, vert7);
	EdgeObjectPtr rightBottomEdge = std::make_shared<EdgeObject>(vert0, vert7);
	// LEFT
	EdgeObjectPtr leftTopEdge = std::make_shared<EdgeObject>(vert2, vert5);
	EdgeObjectPtr leftRightEdge = std::make_shared<EdgeObject>(vert4, vert5);
	EdgeObjectPtr leftLeftEdge = std::make_shared<EdgeObject>(vert2, vert3);
	EdgeObjectPtr leftBottomEdge = std::make_shared<EdgeObject>(vert3, vert4);

	FaceObjectPtr frontFace = std::make_shared<FaceObject>(frontTopEdge, frontRightEdge, frontLeftEdge, frontBottomEdge, Vec3::Forward);
	FaceObjectPtr backFace = std::make_shared<FaceObject>(backTopEdge, backRightEdge, backLeftEdge, backBottomEdge, Vec3::Back);
	FaceObjectPtr topFace = std::make_shared<FaceObject>(topTopEdge, topRightEdge, topLeftEdge, topBottomEdge, Vec3::Up);
	FaceObjectPtr bottomFace = std::make_shared<FaceObject>(bottomTopEdge, bottomRightEdge, bottomLeftEdge, bottomBottomEdge, Vec3::Down);
	FaceObjectPtr rightFace = std::make_shared<FaceObject>(rightTopEdge, rightRightEdge, rightLeftEdge, rightBottomEdge, Vec3::Right);
	FaceObjectPtr leftFace = std::make_shared<FaceObject>(leftTopEdge, leftRightEdge, leftLeftEdge, leftBottomEdge, Vec3::Left);

	_vertexBuffer->_vertexObjects.push_back(vert0);
	_vertexBuffer->_vertexObjects.push_back(vert1);
	_vertexBuffer->_vertexObjects.push_back(vert2);
	_vertexBuffer->_vertexObjects.push_back(vert3);
	_vertexBuffer->_vertexObjects.push_back(vert4);
	_vertexBuffer->_vertexObjects.push_back(vert5);
	_vertexBuffer->_vertexObjects.push_back(vert6);
	_vertexBuffer->_vertexObjects.push_back(vert7);

	_vertexBuffer->_faceObjects.push_back(frontFace);
	_vertexBuffer->_faceObjects.push_back(backFace);
	_vertexBuffer->_faceObjects.push_back(topFace);
	_vertexBuffer->_faceObjects.push_back(bottomFace);
	_vertexBuffer->_faceObjects.push_back(rightFace);
	_vertexBuffer->_faceObjects.push_back(leftFace);

	aabb_min = Vec3{ -0.5, -0.5, -0.5 };
	aabb_max = Vec3{ 0.5, 0.5, 0.5 };
}
