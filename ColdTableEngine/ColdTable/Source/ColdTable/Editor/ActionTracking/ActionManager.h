#pragma once
#include <intsafe.h>
#include <queue>
#include <vector>

#include "IEditAction.h"

namespace ColdTable
{
	
class ActionManager
{
public:
	static ActionManager* Instance;
	static void Initialize(UINT maxTracked);

	void PushAction(EditActionPtr action);
	void Undo();
	void Redo();

private:
	ActionManager(UINT maxTracked);
	std::deque<EditActionPtr> _undoQueue;
	std::deque<EditActionPtr> _redoQueue;
	UINT _maxTracking;
	friend class MainMenuUI;
};
}

