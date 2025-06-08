#include <ColdTable/Input/IInputListener.h>

#include "InputSystem.h"

ColdTable::IInputListener::IInputListener()
{
	InputSystem::Instance->AddListener(this);
}

ColdTable::IInputListener::~IInputListener()
{
	InputSystem::Instance->RemoveListener(this);
}

void ColdTable::IInputListener::OnKeyDown(int key){}
void ColdTable::IInputListener::OnKeyUp(int key){}
void ColdTable::IInputListener::OnMouseMove(Vec2 delta){}
void ColdTable::IInputListener::OnLeftMouseDown(Vec2 pos){}
void ColdTable::IInputListener::OnRightMouseDown(Vec2 pos){}
void ColdTable::IInputListener::OnLeftMouseUp(Vec2 pos){}
void ColdTable::IInputListener::OnRightMouseUp(Vec2 pos){}
