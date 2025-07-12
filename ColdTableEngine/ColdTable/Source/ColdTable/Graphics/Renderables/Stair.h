#pragma once
#include "Renderable.h"
#include <ColdTable/Graphics/IndexBuffer.h>

namespace ColdTable
{
	struct StairDesc
	{
		int _stepCount;
		float _height;
		float _width;
		float _length;
	};
class Stair: public Renderable
{
public:
	Stair(StairDesc desc, IndexBufferPtr indexBuffer, ShaderPtr shader);
	Stair(StairDesc desc, IndexBufferPtr indexBuffer, MaterialPtr material);

private:
	void GenerateStep(float _stepHeight, float _stepWidth, float _stepDepth, int stepOffset, bool isLast, Vertex* vertList, unsigned int* indexList, int* indexTracker);
	void GenerateZFace(Vec3 origin, Vec3 normal, float _height, float _width, int countOffset, Vertex* vertList, unsigned int* indexList, int* indexTracker);
	void GenerateXFace(Vec3 origin, Vec3 normal, float _height, float _depth, int countOffset, Vertex* vertList, unsigned int* indexList, int* indexTracker);
	void GenerateYFace(Vec3 origin, Vec3 normal, float _width, float _depth, int countOffset, Vertex* vertList, unsigned int* indexList, int* indexTracker);

	VertexObjectPtr AddVertex(Vec3 pos, unsigned int index);
};
}

