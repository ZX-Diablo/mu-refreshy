#define BOOST_TEST_MODULE storage_remote_musicbrainz_test
#include <boost/test/unit_test.hpp>

#include <storage/remote/musicbrainz.h>
#include <test/defines.h>

const std::string USER_AGENT = "mu-refreshy/test (https://github.com/ZX-Diablo/mu-refreshy)";
const std::string ARTIST = "Death";
const std::string RELEASE = "Human";
const std::string RELEASE_NOT_EXISTING = "qwerty";

const std::string ARTIST_ID = "dbb3b771-ae77-4381-b61c-758b5b7898ec";
const std::string ARTIST_INVALID_ID = "123";

BOOST_AUTO_TEST_SUITE(search,
	* boost::unit_test::enable_if<BOOST_TEST_INTEGRATION_ENABLED>()
	* boost::unit_test::label(BOOST_TEST_INTEGRATION_LABEL)
);
	BOOST_AUTO_TEST_SUITE(search_artists);
		BOOST_AUTO_TEST_CASE(empty)
		{
			musicbrainz m(USER_AGENT);
			artist_list_t a = m.search_artists(std::string(), std::string());
			BOOST_TEST(a.empty());
		}

		BOOST_AUTO_TEST_CASE(not_existing)
		{
			musicbrainz m(USER_AGENT);
			artist_list_t a = m.search_artists(ARTIST, RELEASE_NOT_EXISTING);
			BOOST_TEST(a.empty());
		}

		BOOST_AUTO_TEST_CASE(search_success)
		{
			musicbrainz m(USER_AGENT);
			artist_list_t a = m.search_artists(ARTIST, RELEASE);
			BOOST_TEST(!a.empty());
		}
	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(search_releases);
		BOOST_AUTO_TEST_CASE(empty)
		{
			musicbrainz m(USER_AGENT);
			release_set_t r = m.search_releases(std::string());
			BOOST_TEST(r.empty());
		}

		BOOST_AUTO_TEST_CASE(invalid_id)
		{
			musicbrainz m(USER_AGENT);
			release_set_t r = m.search_releases(ARTIST_INVALID_ID);
			BOOST_TEST(r.empty());
		}

		BOOST_AUTO_TEST_CASE(search_success)
		{
			musicbrainz m(USER_AGENT);
			release_set_t r = m.search_releases(ARTIST_ID);
			BOOST_TEST(!r.empty());
		}
	BOOST_AUTO_TEST_SUITE_END();
BOOST_AUTO_TEST_SUITE_END();
