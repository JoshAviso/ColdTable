#include "ActionManager.h"

ColdTable::ActionManager* ColdTable::ActionManager::Instance = nullptr;
void ColdTable::ActionManager::Initialize(UINT maxTracked)
{
	if (Instance != nullptr) return;
	Instance = new ActionManager(maxTracked);
}

void ColdTable::ActionManager::PushAction(EditActionPtr action)
{
	action->Redo();
	_undoQueue.push_back(std::move(action));
	_redoQueue.clear();

	if (_undoQueue.size() > _maxTracking)
		_undoQueue.pop_front(); 
}

void ColdTable::ActionManager::Undo()
{
	if (_undoQueue.empty()) return;
	auto action = std::move(_undoQueue.back());
	_undoQueue.pop_back();
	action->Undo();
	_redoQueue.push_back(std::move(action));
}

void ColdTable::ActionManager::Redo()
{

	if (_redoQueue.empty()) return;
	auto action = std::move(_redoQueue.back());
	_redoQueue.pop_back();
	action->Redo();
	_undoQueue.push_back(std::move(action));

	if (_undoQueue.size() > _maxTracking)
		_undoQueue.pop_front();
}

ColdTable::ActionManager::ActionManager(UINT maxTracked) : _maxTracking(maxTracked){}
