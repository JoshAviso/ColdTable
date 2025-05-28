#pragma once
#include <ColdTable/Core/Common.h>
#include <ColdTable/Core/Core.h>

namespace ColdTable
{
	class Base
	{
	public:
		explicit Base(const BaseDesc& desc);
		virtual ~Base();

	protected:
		Base(const Base&) = delete;
		Base(Base&&) = delete;
		Base& operator = (const Base&) = delete;
		Base& operator = (Base&&) = delete;

	};
}

