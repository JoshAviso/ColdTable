#pragma once
#include "ColdTable/Editor/ActionTracking/IEditAction.h"

namespace ColdTable
{
	class EditFloatAction : public IEditAction
	{
	public:
		EditFloatAction(float* address, float oldVal, float newVal):
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
		float* address = nullptr;
		float oldVal;
		float newVal;
	};
	
}

