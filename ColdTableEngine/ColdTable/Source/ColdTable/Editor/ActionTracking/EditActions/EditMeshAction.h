#pragma once
#include "ColdTable/Editor/ActionTracking/IEditAction.h"
#include "ColdTable/Math/Vec3.h"

namespace ColdTable
{
	class EditMeshAction : public IEditAction
	{
	public:
		EditMeshAction(MeshPtr* address, MeshPtr oldVal, MeshPtr newVal) :
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
		MeshPtr* address = nullptr;
		MeshPtr oldVal;
		MeshPtr newVal;
	};
	
}

