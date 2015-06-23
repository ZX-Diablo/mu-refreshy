#include "../include/filescanfactory.h"
#include "../include/allfilescan.h"
#include "../include/artistfilescan.h"
#include "../include/artistalbumfilescan.h"

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
