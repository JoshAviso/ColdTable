#pragma once
#include "Renderable.h"
#include <ColdTable/Graphics/IndexBuffer.h>

namespace ColdTable
{
	struct CylinderDesc
	{
		int _sideCount;
		float _length;
		float _radius;
		bool _isHorizontal;
	};
class Cylinder: public Renderable
{
public:
	Cylinder(CylinderDesc desc, IndexBufferPtr indexBuffer, ShaderPtr shader);
	Cylinder(CylinderDesc desc, IndexBufferPtr indexBuffer, MaterialPtr material);

private:
	void GenerateSide(Vec3 center, Vec3 normal, Vec3 up, float height, float width, int sideOffset, int sideCount, Vertex* vertlist, unsigned int* indexList, unsigned int* vertTracker, unsigned int *indexTracker);
	void GenerateCap(Vec3 center, Vec3 normal, Vec3 forward, float radius, float anglePerSide, int sideCount, Vertex* vertlist, unsigned int* indexList, unsigned int* vertTracker, unsigned int* indexTracker);

	VertexObjectPtr AddVertex(Vec3 pos, unsigned int index);
};
}

