#define BOOST_TEST_MODULE storage_printer_printerfactory_test
#include <boost/test/unit_test.hpp>

#include <storage/printer/printerfactory.h>
#include <storage/printer/text.h>
#include <storage/printer/xml.h>

const std::string PRINTER_UNKNOWN = "unknown";
const std::string PRINTER_TEXT = "txt";
const std::string PRINTER_XML = "xml";

BOOST_AUTO_TEST_SUITE(get);
	BOOST_AUTO_TEST_CASE(get_empty)
	{
		BOOST_TEST(!printerfactory::get(std::string()));
	}

	BOOST_AUTO_TEST_CASE(get_unknown)
	{
		BOOST_TEST(!printerfactory::get(PRINTER_UNKNOWN));
	}

	BOOST_AUTO_TEST_CASE(get_text)
	{
		BOOST_TEST(std::dynamic_pointer_cast<text>(printerfactory::get(PRINTER_TEXT)));
	}

	BOOST_AUTO_TEST_CASE(get_xml)
	{
		BOOST_TEST(std::dynamic_pointer_cast<xml>(printerfactory::get(PRINTER_XML)));
	}
BOOST_AUTO_TEST_SUITE_END();
