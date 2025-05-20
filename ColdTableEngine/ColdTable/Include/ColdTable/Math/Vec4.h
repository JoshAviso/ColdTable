#pragma once
#include <ColdTable/Core/Core.h>

namespace ColdTable
{
	class Vec4
	{
	public:
		Vec4() = default;
		Vec4(f32 x, f32 y, f32 z, f32 w): x(x), y(y), z(z), w(w){}
	public:
		f32 x{}, y{}, z{}, w{};
	};
}