#pragma once
#include "ColdTable/Editor/ActionTracking/IEditAction.h"
#include "ColdTable/Math/Vec3.h"

namespace ColdTable
{
	class EditMatAction : public IEditAction
	{
	public:
		EditMatAction(MaterialPtr* address, MaterialPtr oldVal, MaterialPtr newVal) :
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
		MaterialPtr* address = nullptr;
		MaterialPtr oldVal;
		MaterialPtr newVal;
	};
	
}

