#include <storage/printer/printerfactory.h>
#include <storage/printer/text.h>
#include <storage/printer/xml.h>

namespace printer
{

printerfactory::iprinter_t printerfactory::get (const std::string& type)
{
	if (type == "txt")
	{
		return std::make_shared<text>();
	}
	else if (type == "xml")
	{
		return std::make_shared<xml>();
	}

	return nullptr;
}

}
