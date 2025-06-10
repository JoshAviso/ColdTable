#include <ColdTable/Graphics/Renderables/Quad.h>

#include <ColdTable/All.h>

ColdTable::Quad::Quad(const QuadDesc& desc) :
	Renderable({ {}, 0, DRAWMODE_TRI_STRIP, desc.material })
{
	Vertex list[] = {
		desc.vert1, desc.vert2, desc.vert4, desc.vert3
	};
	UINT listSize = ARRAYSIZE(list);

	LoadVertices(list, listSize);
}
