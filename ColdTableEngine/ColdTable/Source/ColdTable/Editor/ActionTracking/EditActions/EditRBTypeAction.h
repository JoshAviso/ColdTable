#pragma once
#include <reactphysics3d/components/RigidBodyComponents.h>

#include "ColdTable/Editor/ActionTracking/IEditAction.h"
#include "ColdTable/Math/Vec3.h"

namespace ColdTable
{
	class EditRBTypeAction : public IEditAction
	{
	public:
		EditRBTypeAction(reactphysics3d::BodyType* address, reactphysics3d::BodyType oldVal, reactphysics3d::BodyType newVal) :
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
		reactphysics3d::BodyType* address = nullptr;
		reactphysics3d::BodyType oldVal;
		reactphysics3d::BodyType newVal;
	};
	
}

