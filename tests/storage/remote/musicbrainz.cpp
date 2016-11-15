#define BOOST_TEST_MODULE storage_remote_musicbrainz_test
#include <boost/test/unit_test.hpp>

#include <storage/remote/musicbrainz.h>
#include <test/defines.h>

const std::string USER_AGENT = "mu-refreshy/test (https://github.com/ZX-Diablo/mu-refreshy)";

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
	BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE(search_releases);
		BOOST_AUTO_TEST_CASE(empty)
		{
			musicbrainz m(USER_AGENT);
			release_set_t r = m.search_releases(std::string());
			BOOST_TEST(r.empty());
		}
	BOOST_AUTO_TEST_SUITE_END();
BOOST_AUTO_TEST_SUITE_END();
