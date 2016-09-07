#define BOOST_TEST_MODULE data_release_test
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>

#include <data/release.h>
#include <list>

const std::string RELEASE_ID = "A123";
const std::string RELEASE_TITLE = "Music album";
const std::string RELEASE_TYPE = "full album";
const std::string RELEASE_DATE = "2000-06-13";
const std::string RELEASE_ID_OTHER = "B987";

const std::string RELEASE_DATE_PREV_YEAR = "1999-06-13";
const std::string RELEASE_DATE_PREV_MONTH = "2000-05-13";
const std::string RELEASE_DATE_PREV_DAY = "2000-06-12";
const std::string RELEASE_DATE_NEXT_DAY = "2000-06-14";
const std::string RELEASE_DATE_NEXT_MONTH = "2000-07-13";
const std::string RELEASE_DATE_NEXT_YEAR = "2001-06-13";

typedef std::list<std::string> string_list_t;
const string_list_t PREV_DATES = { RELEASE_DATE_PREV_YEAR, RELEASE_DATE_PREV_MONTH, RELEASE_DATE_PREV_DAY };
const string_list_t NEXT_DATES = { RELEASE_DATE_NEXT_YEAR, RELEASE_DATE_NEXT_MONTH, RELEASE_DATE_NEXT_DAY };

BOOST_AUTO_TEST_SUITE(constructors);
	BOOST_AUTO_TEST_CASE(empty)
	{
		release r = release(std::string(), std::string(), std::string(), date());
		BOOST_TEST(r.get_id() == std::string());
		BOOST_TEST(r.get_title() == std::string());
		BOOST_TEST(r.get_type() == std::string());
		BOOST_TEST(r.get_date().get() == date::default_date);
	}

	BOOST_AUTO_TEST_CASE(params)
	{
		release r(RELEASE_ID, RELEASE_TITLE, RELEASE_TYPE, date(RELEASE_DATE));
		BOOST_TEST(r.get_id() == RELEASE_ID);
		BOOST_TEST(r.get_title() == RELEASE_TITLE);
		BOOST_TEST(r.get_type() == RELEASE_TYPE);
		BOOST_TEST(r.get_date().get() == RELEASE_DATE);
	}
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(ordering);
	BOOST_AUTO_TEST_CASE(empty_ids)
	{
		release r1(std::string(), std::string(), std::string(), RELEASE_DATE);
		release r2(std::string(), std::string(), std::string(), RELEASE_DATE_PREV_DAY);
		BOOST_TEST(r2 < r1);
	}

	BOOST_AUTO_TEST_CASE(different_ids)
	{
		release r1(RELEASE_ID, std::string(), std::string(), RELEASE_DATE);
		release r2(RELEASE_ID_OTHER, std::string(), std::string(), RELEASE_DATE_PREV_DAY);
		BOOST_TEST(r2 < r1);
	}

	BOOST_AUTO_TEST_CASE(equal_ids)
	{
		release r1(RELEASE_ID, std::string(), std::string(), RELEASE_DATE);
		release r2(RELEASE_ID, std::string(), std::string(), RELEASE_DATE_PREV_DAY);
		BOOST_TEST(!(r2 < r1));
	}

	BOOST_AUTO_TEST_CASE(equal_dates)
	{
		release r1(std::string(), std::string(), std::string(), RELEASE_DATE);
		release r2(std::string(), std::string(), std::string(), RELEASE_DATE);
		BOOST_TEST(!(r2 < r1));
	}

	BOOST_DATA_TEST_CASE(prev_dates, boost::unit_test::data::make(PREV_DATES))
	{
		release r1(std::string(), std::string(), std::string(), RELEASE_DATE);
		release r2(std::string(), std::string(), std::string(), sample);
		BOOST_TEST(r2 < r1);
	}

	BOOST_DATA_TEST_CASE(next_dates, boost::unit_test::data::make(NEXT_DATES))
	{
		release r1(std::string(), std::string(), std::string(), RELEASE_DATE);
		release r2(std::string(), std::string(), std::string(), sample);
		BOOST_TEST(!(r2 < r1));
	}
BOOST_AUTO_TEST_SUITE_END();
