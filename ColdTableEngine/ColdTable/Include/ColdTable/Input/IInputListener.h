#pragma once
#include <ColdTable/Core/Core.h>
#include <ColdTable/Math/Vec2.h>

namespace ColdTable
{
class IInputListener
{
public:
	IInputListener();
	virtual ~IInputListener();

	virtual void OnKeyDown(int key);
	virtual void OnKeyUp(int key);

	virtual void OnMouseMove(Vec2 delta);
	virtual void OnLeftMouseDown(Vec2 pos);
	virtual void OnRightMouseDown(Vec2 pos);
	virtual void OnLeftMouseUp(Vec2 pos);
	virtual void OnRightMouseUp(Vec2 pos);

};
	
}

