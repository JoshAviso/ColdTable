#pragma once
#include <string>

namespace ColdTable
{
	struct JsonValue;
	class ISerializeable
	{
	protected:
		~ISerializeable() = default;

	private:
		virtual void FromJson(const JsonValue& json) = 0;
		virtual JsonValue ToJson() const = 0;
	};
}

