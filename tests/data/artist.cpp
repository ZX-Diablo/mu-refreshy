#define BOOST_TEST_MODULE data_artist_test
#include <boost/test/unit_test.hpp>

#include <data/artist.h>
#include <fakeit.hpp>

const std::string ARTIST_ID = "D34H";
const std::string ARTIST_NAME = "artist";

const std::string RELEASE_ID = "A123";
const std::string RELEASE_TITLE = "Music album";
const std::string RELEASE_TYPE = "full album";
const std::string RELEASE_DATE = "2000-06-13";
const unsigned int RELEASE_YEAR = 2000;
const std::string RELEASE_YEAR_EXPECTED = "2000-01-01";

BOOST_AUTO_TEST_SUITE(constructors);
	BOOST_AUTO_TEST_CASE(empty)
	{
		artist a = artist(std::string(), std::string());
		BOOST_TEST(a.get_id() == std::string());
		BOOST_TEST(a.get_name() == std::string());
		BOOST_TEST(a.get_releases().size() == 0);
		BOOST_TEST(a.get_local_releases().size() == 0);
	}

	BOOST_AUTO_TEST_CASE(params)
	{
		artist a(ARTIST_ID, ARTIST_NAME);
		BOOST_TEST(a.get_id() == ARTIST_ID);
		BOOST_TEST(a.get_name() == ARTIST_NAME);
		BOOST_TEST(a.get_releases().size() == 0);
		BOOST_TEST(a.get_local_releases().size() == 0);
	}

	BOOST_AUTO_TEST_CASE(tag_empty)
	{
		artist a((TagLib::Tag*)nullptr);
		BOOST_TEST(a.get_id() == std::string());
		BOOST_TEST(a.get_name() == std::string());
		BOOST_TEST(a.get_releases().size() == 0);
		BOOST_TEST(a.get_local_releases().size() == 0);
	}

	BOOST_AUTO_TEST_CASE(tag)
	{
		fakeit::Mock<TagLib::Tag> tag_mock;

		fakeit::When(Method(tag_mock, artist)).AlwaysReturn(ARTIST_NAME);
		fakeit::When(Method(tag_mock, album)).AlwaysReturn(RELEASE_TITLE);
		fakeit::When(Method(tag_mock, year)).AlwaysReturn(RELEASE_YEAR);

		artist a(&tag_mock.get());
		BOOST_TEST(a.get_id() == std::string());
		BOOST_TEST(a.get_name() == ARTIST_NAME);
		BOOST_TEST(a.get_releases().size() == 0);
		BOOST_TEST(a.get_local_releases().size() == 1);

		release_ptr_t r = *a.get_local_releases().begin();
		BOOST_TEST(r->get_id() == std::string());
		BOOST_TEST(r->get_title() == RELEASE_TITLE);
		BOOST_TEST(r->get_type() == std::string());
		BOOST_TEST(r->get_date().get() == RELEASE_YEAR_EXPECTED);

		fakeit::Verify(Method(tag_mock, artist)).Once();
		fakeit::Verify(Method(tag_mock, album)).Once();
		fakeit::Verify(Method(tag_mock, year)).Once();
		fakeit::VerifyNoOtherInvocations(tag_mock);
	}

	BOOST_AUTO_TEST_CASE(cartist_empty)
	{
		artist a((MusicBrainz5::CArtist*)nullptr);
		BOOST_TEST(a.get_id() == std::string());
		BOOST_TEST(a.get_name() == std::string());
		BOOST_TEST(a.get_releases().size() == 0);
		BOOST_TEST(a.get_local_releases().size() == 0);
	}

	BOOST_AUTO_TEST_CASE(cartist)
	{
		// Can't fake MusicBrainz5::CArtist
	}
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(releases);
	BOOST_AUTO_TEST_CASE(add_empty_release)
	{
		artist a = artist(std::string(), std::string());
		a.add_release(nullptr);
		BOOST_TEST(a.get_releases().size() == 0);
	}

	BOOST_AUTO_TEST_CASE(add_notempty_release)
	{
		artist a = artist(std::string(), std::string());
		a.add_release(std::make_shared<release>(RELEASE_ID, RELEASE_TITLE, RELEASE_TYPE, date(RELEASE_DATE)));
		BOOST_TEST(a.get_releases().size() == 1);

		release_ptr_t r = *a.get_releases().begin();
		BOOST_TEST(r->get_id() == RELEASE_ID);
		BOOST_TEST(r->get_title() == RELEASE_TITLE);
		BOOST_TEST(r->get_type() == RELEASE_TYPE);
		BOOST_TEST(r->get_date().get() == RELEASE_DATE);
	}

	BOOST_AUTO_TEST_CASE(add_empty_local_release)
	{
		artist a = artist(std::string(), std::string());
		a.add_local_release(nullptr);
		BOOST_TEST(a.get_local_releases().size() == 0);
	}

	BOOST_AUTO_TEST_CASE(add_notempty_local_release)
	{
		artist a = artist(std::string(), std::string());
		a.add_local_release(std::make_shared<release>(RELEASE_ID, RELEASE_TITLE, RELEASE_TYPE, date(RELEASE_DATE)));
		BOOST_TEST(a.get_local_releases().size() == 1);

		release_ptr_t r = *a.get_local_releases().begin();
		BOOST_TEST(r->get_id() == RELEASE_ID);
		BOOST_TEST(r->get_title() == RELEASE_TITLE);
		BOOST_TEST(r->get_type() == RELEASE_TYPE);
		BOOST_TEST(r->get_date().get() == RELEASE_DATE);
	}

	BOOST_AUTO_TEST_CASE(clear_releases)
	{
		// No way to create artist with filled releases, overlaps with add_notempty_release
		artist a = artist(std::string(), std::string());
		BOOST_TEST(a.get_releases().size() == 0);

		a.add_release(std::make_shared<release>(RELEASE_ID, RELEASE_TITLE, RELEASE_TYPE, date(RELEASE_DATE)));
		BOOST_TEST(a.get_releases().size() == 1);

		a.clear_releases();
		BOOST_TEST(a.get_releases().size() == 0);
	}
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(setters);
	BOOST_AUTO_TEST_CASE(set_id)
	{
		artist a = artist(std::string(), std::string());
		a.set_id(ARTIST_ID);
		BOOST_TEST(a.get_id() == ARTIST_ID);
	}
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(checks);
	BOOST_AUTO_TEST_CASE(has_id_false)
	{
		artist a = artist(std::string(), std::string());
		BOOST_TEST(!a.has_id());
	}

	BOOST_AUTO_TEST_CASE(has_id_true)
	{
		artist a = artist(ARTIST_ID, std::string());
		BOOST_TEST(a.has_id());
	}

	BOOST_AUTO_TEST_CASE(has_releases_false)
	{
		artist a = artist(std::string(), std::string());
		BOOST_TEST(!a.has_releases());
	}

	BOOST_AUTO_TEST_CASE(has_releases_true)
	{
		// No way to create artist with filled releases, overlaps with add_notempty_release
		artist a = artist(std::string(), std::string());
		a.add_release(std::make_shared<release>(RELEASE_ID, RELEASE_TITLE, RELEASE_TYPE, date(RELEASE_DATE)));
		BOOST_TEST(a.has_releases());
	}

	BOOST_AUTO_TEST_CASE(has_local_releases_false)
	{
		artist a = artist(std::string(), std::string());
		BOOST_TEST(!a.has_local_releases());
	}

	BOOST_AUTO_TEST_CASE(has_local_releases_true)
	{
		// No way to create artist with filled local releases, overlaps with add_notempty_local_release
		artist a = artist(std::string(), std::string());
		a.add_local_release(std::make_shared<release>(RELEASE_ID, RELEASE_TITLE, RELEASE_TYPE, date(RELEASE_DATE)));
		BOOST_TEST(a.has_local_releases());
	}
BOOST_AUTO_TEST_SUITE_END();
