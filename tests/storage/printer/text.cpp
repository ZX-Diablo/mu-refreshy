#define BOOST_TEST_MODULE storage_printer_text_test
#include <boost/test/unit_test.hpp>

#include <storage/printer/text.h>

#include <sstream>

const storage EMPTY_STORAGE;

BOOST_AUTO_TEST_SUITE(print);
	BOOST_AUTO_TEST_CASE(empty)
	{
		text p;
		std::stringstream ss;

		p.print(EMPTY_STORAGE, ss);

		BOOST_TEST(ss.str().empty());
	}
BOOST_AUTO_TEST_SUITE_END();
