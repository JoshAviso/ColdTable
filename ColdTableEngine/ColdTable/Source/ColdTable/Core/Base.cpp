#include <ColdTable/Core/Base.h>
using namespace ColdTable;


Base::Base(const BaseDesc& desc): _logger(desc.logger)
{

}

Base::~Base()
{

}

Logger& Base::getLogger() noexcept
{
	return _logger;
}

