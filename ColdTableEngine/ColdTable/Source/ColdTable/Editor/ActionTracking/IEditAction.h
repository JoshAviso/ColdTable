#pragma once
#include <memory>

namespace ColdTable
{
	class IEditAction
	{
	public:
		virtual ~IEditAction() = default;

		virtual void Undo() = 0;
		virtual void Redo() = 0;
	};
	using EditActionPtr = std::unique_ptr<IEditAction>;
}

