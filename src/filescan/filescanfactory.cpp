#include <filescan/filescanfactory.h>
#include <filescan/allfilescan.h>
#include <filescan/artistfilescan.h>
#include <filescan/artistalbumfilescan.h>

filescanfactory::ifilescan_t filescanfactory::get (const std::string& type)
{
	if (type == "all")
	{
		return std::make_shared<allfilescan>();
	}
	else if (type == "artist")
	{
		return std::make_shared<artistfilescan>();
	}
	else if (type == "album")
	{
		return std::make_shared<artistalbumfilescan>();
	}

	return nullptr;
}
