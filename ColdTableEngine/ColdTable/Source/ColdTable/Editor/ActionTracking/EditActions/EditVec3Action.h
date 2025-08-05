#pragma once
#include "ColdTable/Editor/ActionTracking/IEditAction.h"
#include "ColdTable/Math/Vec3.h"

namespace ColdTable
{
	class EditVec3Action : public IEditAction
	{
	public:
		EditVec3Action(Vec3* address, Vec3 oldVal, Vec3 newVal) :
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
		Vec3* address = nullptr;
		Vec3 oldVal;
		Vec3 newVal;
	};
	
}

