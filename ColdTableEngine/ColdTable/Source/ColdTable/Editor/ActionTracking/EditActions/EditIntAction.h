#pragma once
#include "ColdTable/Editor/ActionTracking/IEditAction.h"

namespace ColdTable
{
	class EditIntAction : public IEditAction
	{
	public:
		EditIntAction(int* address, int oldVal, int newVal) :
			address(address), oldVal(oldVal), newVal(newVal) {}

		void Undo() override
		{
			if (address == nullptr) return;
			*address = oldVal;
		}
		void Redo() override
		{
			if (address == nullptr) return;
			*address = newVal;
		}
	private:
		int* address = nullptr;
		int oldVal;
		int newVal;
	};
	
}

