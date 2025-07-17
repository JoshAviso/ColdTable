#pragma once
#include "Component.h"


namespace ColdTable
{
	class DebugBlurbComponent : public Component
	{
	public:
		DebugBlurbComponent(const String& blurbText = "") : Component({ EComponentType::Debug }), _blurbText(blurbText){}

	private:
		String _blurbText;

		friend class DebugBlurbSystem;
	};
	
}

