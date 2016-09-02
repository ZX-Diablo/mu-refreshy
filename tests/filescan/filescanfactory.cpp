#define BOOST_TEST_MODULE filescan_filescanfactory_test
#include <boost/test/unit_test.hpp>

#include <filescan/filescanfactory.h>

#include "filescan/allfilescan.h"
#include "data/artist.h"
#include "filescan/artistfilescan.h"
#include "filescan/artistalbumfilescan.h"

const std::string FILESCAN_UNKNOWN = "unknown";
const std::string FILESCAN_ALL = "all";
const std::string FILESCAN_ARTIST = "artist";
const std::string FILESCAN_ALBUM = "album";

BOOST_TEST_DONT_PRINT_LOG_VALUE(filescanfactory::ifilescan_t);

BOOST_AUTO_TEST_SUITE(get);
	BOOST_AUTO_TEST_CASE(get_empty)
	{
		BOOST_TEST(!filescanfactory::get(std::string()));
	}

	BOOST_AUTO_TEST_CASE(get_unknown)
	{
		BOOST_TEST(!filescanfactory::get(FILESCAN_UNKNOWN));
	}

	BOOST_AUTO_TEST_CASE(get_all)
	{
		BOOST_TEST(std::dynamic_pointer_cast<allfilescan>(filescanfactory::get(FILESCAN_ALL)));
	}

	BOOST_AUTO_TEST_CASE(get_artist)
	{
		BOOST_TEST(std::dynamic_pointer_cast<artistfilescan>(filescanfactory::get(FILESCAN_ARTIST)));
	}

	BOOST_AUTO_TEST_CASE(get_album)
	{
		BOOST_TEST(std::dynamic_pointer_cast<artistalbumfilescan>(filescanfactory::get(FILESCAN_ALBUM)));
	}
BOOST_AUTO_TEST_SUITE_END();
