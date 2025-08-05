#pragma once
#include "ColdTable/Editor/ActionTracking/IEditAction.h"
#include "ColdTable/Math/Quaternion.h"

namespace ColdTable
{
	class EditQuatAction : public IEditAction
	{
	public:
		EditQuatAction(Quaternion* address, Quaternion oldVal, Quaternion newVal) :
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
		Quaternion* address = nullptr;
		Quaternion oldVal;
		Quaternion newVal;
	};
	
}

