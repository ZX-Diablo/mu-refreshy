#define BOOST_TEST_MODULE data_artistfactory_test
#include <boost/test/unit_test.hpp>

#include <data/artistfactory.h>
#include <fakeit.hpp>

const std::string ARTIST_NAME = "artist";

const std::string RELEASE_TITLE = "Music album";
const unsigned int RELEASE_YEAR = 2000;
const std::string RELEASE_YEAR_EXPECTED = "2000-01-01";
const unsigned int RELEASE_SET_SIZE_EXPECTED = 1;

BOOST_AUTO_TEST_SUITE(get);
	BOOST_AUTO_TEST_CASE(tag_empty)
	{
		BOOST_TEST(!artistfactory::get((TagLib::Tag*)nullptr));
	}

	BOOST_AUTO_TEST_CASE(tag)
	{
		fakeit::Mock<TagLib::Tag> tag_mock;

		fakeit::When(Method(tag_mock, artist)).AlwaysReturn(ARTIST_NAME);
		fakeit::When(Method(tag_mock, album)).AlwaysReturn(RELEASE_TITLE);
		fakeit::When(Method(tag_mock, year)).AlwaysReturn(RELEASE_YEAR);

		artist_ptr_t a = artistfactory::get(&tag_mock.get());
		BOOST_TEST(a->get_id() == std::string());
		BOOST_TEST(a->get_name() == ARTIST_NAME);
		BOOST_TEST(a->get_ids().empty());
		BOOST_TEST(a->get_releases().empty());
		BOOST_REQUIRE(a->get_local_releases().size() == RELEASE_SET_SIZE_EXPECTED);

		release_ptr_t r = *a->get_local_releases().begin();
		BOOST_TEST(r->get_id() == std::string());
		BOOST_TEST(r->get_title() == RELEASE_TITLE);
		BOOST_TEST(r->get_type() == std::string());
		BOOST_TEST(r->get_date().get() == RELEASE_YEAR_EXPECTED);

		fakeit::Verify(Method(tag_mock, artist)).Once();
		fakeit::Verify(Method(tag_mock, album)).Once();
		fakeit::Verify(Method(tag_mock, year)).Once();
		fakeit::VerifyNoOtherInvocations(tag_mock);
	}

	BOOST_AUTO_TEST_CASE(artist_empty)
	{
		BOOST_TEST(!artistfactory::get((MusicBrainz5::CArtist*)nullptr));
	}

	BOOST_AUTO_TEST_CASE(artist)
	{
		BOOST_TEST_MESSAGE("Can't fake MusicBrainz5::CArtist. Skip test");
	}
BOOST_AUTO_TEST_SUITE_END();
