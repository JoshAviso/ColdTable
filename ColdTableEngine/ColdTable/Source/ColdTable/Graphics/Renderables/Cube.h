#pragma once
#include "Renderable.h"
#include <ColdTable/Graphics/IndexBuffer.h>

namespace ColdTable
{
	
class Cube: public Renderable
{
public:
	Cube(IndexBufferPtr indexBuffer, ShaderPtr shader);
	Cube(IndexBufferPtr indexBuffer, MaterialPtr material);
};
}

