#define BOOST_TEST_MODULE data_release_test
#include <boost/test/unit_test.hpp>

#include <data/release.h>
#include <fakeit.hpp>
#include <list>

const std::string RELEASE_ID = "A123";
const std::string RELEASE_TITLE = "Music album";
const std::string RELEASE_TYPE = "full album";
const std::string RELEASE_DATE = "2000-06-13";
const unsigned int RELEASE_YEAR = 2000;
const std::string RELEASE_YEAR_EXPECTED = "2000-01-01";
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

BOOST_TEST_DONT_PRINT_LOG_VALUE(release); // Note: write release printing?

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

	BOOST_AUTO_TEST_CASE(tag_empty)
	{
		release r((TagLib::Tag*)nullptr);
		BOOST_TEST(r.get_id() == std::string());
		BOOST_TEST(r.get_title() == std::string());
		BOOST_TEST(r.get_type() == std::string());
		BOOST_TEST(r.get_date().get() == date::default_date);
	}

	BOOST_AUTO_TEST_CASE(tag)
	{
		fakeit::Mock<TagLib::Tag> tag_mock;

		fakeit::When(Method(tag_mock, album)).AlwaysReturn(RELEASE_TITLE);
		fakeit::When(Method(tag_mock, year)).AlwaysReturn(RELEASE_YEAR);

		release r(&tag_mock.get());
		BOOST_TEST(r.get_id() == std::string());
		BOOST_TEST(r.get_title() == RELEASE_TITLE);
		BOOST_TEST(r.get_type() == std::string());
		BOOST_TEST(r.get_date().get() == RELEASE_YEAR_EXPECTED);

		fakeit::Verify(Method(tag_mock, album)).Once();
		fakeit::Verify(Method(tag_mock, year)).Once();
		fakeit::VerifyNoOtherInvocations(tag_mock);
	}

	BOOST_AUTO_TEST_CASE(release_group_empty)
	{
		release r((MusicBrainz5::CReleaseGroup*)nullptr);
		BOOST_TEST(r.get_id() == std::string());
		BOOST_TEST(r.get_title() == std::string());
		BOOST_TEST(r.get_type() == std::string());
		BOOST_TEST(r.get_date().get() == date::default_date);
	}

	BOOST_AUTO_TEST_CASE(release_group)
	{
		// Can't fake MusicBrainz5::CReleaseGroup
	}
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(ordering);
	BOOST_AUTO_TEST_CASE(empty_ids)
	{
		release r1(std::string(), std::string(), std::string(), RELEASE_DATE);
		release r2(std::string(), std::string(), std::string(), RELEASE_DATE_PREV_DAY);
		BOOST_TEST(r2 < r1);
	}
BOOST_AUTO_TEST_SUITE_END();
