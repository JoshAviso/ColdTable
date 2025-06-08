#pragma once
#include <ColdTable/Graphics/Renderables/Renderable.h>

#include "ColdTable/Input/IInputListener.h"

namespace ColdTable
{
	class Quad : public Renderable
	{
	public:
		Quad(const QuadDesc& desc);
	};
}

