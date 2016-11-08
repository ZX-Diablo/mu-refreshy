#define BOOST_TEST_MODULE storage_musicdb_test
#include <boost/test/unit_test.hpp>

#include <storage/musicdb.h>

BOOST_AUTO_TEST_SUITE(fill);
	BOOST_AUTO_TEST_CASE(empty)
	{
		musicdb db((std::string()));
		BOOST_REQUIRE_NO_THROW(db.fill(nullptr));
	}
BOOST_AUTO_TEST_SUITE_END();
