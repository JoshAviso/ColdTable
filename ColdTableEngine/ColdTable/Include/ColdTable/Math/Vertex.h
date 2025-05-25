#pragma once
#include <ColdTable/Math/Vec3.h>

namespace ColdTable
{
	struct Vertex
	{
		vec3 position;
		vec3 position1;
		vec3 color;
		vec3 color1;

		explicit Vertex(vec3 position) : position(position), position1(position), color({1.0f, 1.0f, 1.0f}), color1({1.0f, 1.0f, 1.0f}){}
		Vertex(vec3 position, vec3 color): position(position), position1(position), color(color), color1(color){}
		Vertex(vec3 position, vec3 color, vec3 color1) : position(position), position1(position), color(color), color1(color1) {}
		Vertex(vec3 position, vec3 position1, vec3 color, vec3 color1) : position(position), position1(position1), color(color), color1(color1) {}
	};
}
