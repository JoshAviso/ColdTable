#include <ColdTable/Graphics/Renderables/Quad.h>

#include <ColdTable/All.h>

ColdTable::Quad::Quad(const QuadDesc& desc) :
	Renderable({ desc.base, {}, 0, DRAWMODE_TRI_STRIP, desc.shader })
{
	Vertex list[] = {
		desc.vert1, desc.vert2, desc.vert4, desc.vert3
	};
	UINT listSize = ARRAYSIZE(list);

	LoadVertices(list, listSize);
}
