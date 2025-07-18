#pragma once
#include "Component.h"


namespace ColdTable
{
	class DebugBlurbComponent : public Component
	{
	public:
		DebugBlurbComponent(GameObjectPtr Owner, const String& blurbText = "") : Component(Owner, { EComponentType::Debug }), _blurbText(blurbText){}

	private:
		String _blurbText;

		friend class DebugBlurbSystem;
	};
	
}

