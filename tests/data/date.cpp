#define BOOST_TEST_MODULE data_date_test
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>

#include <data/date.h>
#include <list>

const std::string DATE_YEAR = "2000";
const std::string DATE_YEAR_EXPECTED = "2000-01-01";
const std::string DATE_YEAR_MONTH = "2000-06";
const std::string DATE_YEAR_MONTH_EXPECTED = "2000-06-01";
const std::string FULL_DATE = "2000-06-13";

const std::string FULL_DATE_PREV_YEAR = "1999-06-13";
const std::string FULL_DATE_PREV_MONTH = "2000-05-13";
const std::string FULL_DATE_PREV_DAY = "2000-06-12";
const std::string FULL_DATE_NEXT_DAY = "2000-06-14";
const std::string FULL_DATE_NEXT_MONTH = "2000-07-13";
const std::string FULL_DATE_NEXT_YEAR = "2001-06-13";

typedef std::list<std::string> string_list_t;
const string_list_t PREV_DATES = { FULL_DATE_PREV_YEAR, FULL_DATE_PREV_MONTH, FULL_DATE_PREV_DAY };
const string_list_t NEXT_DATES = { FULL_DATE_NEXT_YEAR, FULL_DATE_NEXT_MONTH, FULL_DATE_NEXT_DAY };

BOOST_AUTO_TEST_SUITE(constructors);
	BOOST_AUTO_TEST_CASE(empty)
	{
		date d;
		BOOST_TEST(d.get() == date::default_date);
	}

	BOOST_AUTO_TEST_CASE(year)
	{
		date d(DATE_YEAR);
		BOOST_TEST(d.get() == DATE_YEAR_EXPECTED);
	}

	BOOST_AUTO_TEST_CASE(year_month)
	{
		date d(DATE_YEAR_MONTH);
		BOOST_TEST(d.get() == DATE_YEAR_MONTH_EXPECTED);
	}

	BOOST_AUTO_TEST_CASE(year_month_day)
	{
		date d(FULL_DATE);
		BOOST_TEST(d.get() == FULL_DATE);
	}

	BOOST_AUTO_TEST_CASE(copy)
	{
		date d1(FULL_DATE);
		date d2(d1);
		BOOST_TEST(d1.get() == FULL_DATE);
		BOOST_TEST(d2.get() == FULL_DATE);
	}

	BOOST_AUTO_TEST_CASE(move)
	{
		date d1(FULL_DATE);
		date d2(std::move(d1));
		BOOST_TEST(d1.get() == std::string());
		BOOST_TEST(d2.get() == FULL_DATE);
	}
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(assignment);
	BOOST_AUTO_TEST_CASE(copy)
	{
		date d1(FULL_DATE);
		date d2;
		d2 = d1;
		BOOST_TEST(d1.get() == FULL_DATE);
		BOOST_TEST(d2.get() == FULL_DATE);
	}

	BOOST_AUTO_TEST_CASE(move)
	{
		date d;
		d = date(FULL_DATE);
		BOOST_TEST(d.get() == FULL_DATE);
	}
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(ordering);
	BOOST_AUTO_TEST_CASE(equal)
	{
		BOOST_TEST(!(date() < date()));
		BOOST_TEST(!(date(FULL_DATE) < date(FULL_DATE)));
	}

	BOOST_DATA_TEST_CASE(empty, boost::unit_test::data::make({ FULL_DATE }) + PREV_DATES + NEXT_DATES)
	{
		BOOST_TEST(date() < date(sample));
	}

	BOOST_DATA_TEST_CASE(prev_dates, boost::unit_test::data::make(PREV_DATES))
	{
		BOOST_TEST(sample < date(FULL_DATE));
	}

	BOOST_DATA_TEST_CASE(next_dates, boost::unit_test::data::make(NEXT_DATES))
	{
		BOOST_TEST(date(FULL_DATE) < sample);
	}
BOOST_AUTO_TEST_SUITE_END();
