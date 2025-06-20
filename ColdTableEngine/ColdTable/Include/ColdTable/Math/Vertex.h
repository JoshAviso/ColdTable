#pragma once
#include <ColdTable/Math/Vec3.h>
#include <ColdTable/Math/Vec2.h>

namespace ColdTable
{
	struct Vertex
	{
		Vec3 position;
		Vec2 texcoord;
		Vec3 normal;
		Vec3 color;
		//Vec3 color1;

		explicit Vertex(const Vec3& position) : position(position) {}
		Vertex(const Vec3& position, const Vec2& texcoord, const Vec3& normal) : position(position), texcoord(texcoord), normal(normal), color(Vec3(1.0f)){}
		Vertex(const Vec3& position, const Vec2& texcoord, const Vec3& normal, const Vec3& color) : position(position), texcoord(texcoord), normal(normal), color(color) {}
		//explicit Vertex(const Vec3& position) : position(position), color({1.0f, 1.0f, 1.0f}), color1({1.0f, 1.0f, 1.0f}){}
		//Vertex(const Vec3& position, const Vec3& color): position(position), color(color), color1(color){}
		//Vertex(const Vec3& position, const Vec3& color, const Vec3& color1) : position(position), color(color), color1(color1) {}
	};
}
