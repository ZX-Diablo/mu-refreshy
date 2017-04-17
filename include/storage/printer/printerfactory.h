#pragma once

#include <storage/printer/iprinter.h>

#include <memory>
#include <string>

namespace printer
{
	class printerfactory
	{
	public:
		typedef std::shared_ptr<iprinter> iprinter_t;

	public:
		static iprinter_t get (const std::string& type);
	};
}
