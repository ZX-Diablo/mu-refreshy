#define BOOST_TEST_MODULE storage_musicdb_test
#include <boost/test/unit_test.hpp>

#include <storage/musicdb.h>
#include <fakeit.hpp>

const std::string ARTIST_ID = "D34H";
const std::string ARTIST_NAME = "artist";
const std::string REMOTE_ARTIST_ID = "E4T8";

const artist::id_set_t ARTIST_ID_SET = { ARTIST_ID };
const artist::id_set_t ARTIST_MULTI_ID_SET = { ARTIST_ID, REMOTE_ARTIST_ID };

const std::string RELEASE_ID = "A123";
const std::string RELEASE_TITLE = "Music album";
const std::string RELEASE_TYPE = "full album";
const std::string RELEASE_DATE = "2000-06-13";

const std::string REMOTE_RELEASE_ID = "B456";
const std::string REMOTE_RELEASE_TITLE = "Long play album";
const std::string REMOTE_RELEASE_TYPE = "full album";
const std::string REMOTE_RELEASE_DATE = "2006-07-02";

const release_ptr_t RELEASE = std::make_shared<release>(RELEASE_ID, RELEASE_TITLE, RELEASE_TYPE, date(RELEASE_DATE));
const release_ptr_t REMOTE_RELEASE = std::make_shared<release>(
		REMOTE_RELEASE_ID, REMOTE_RELEASE_TITLE, REMOTE_RELEASE_TYPE, date(REMOTE_RELEASE_DATE));
const artist_ptr_t REMOTE_ARTIST = std::make_shared<artist>(REMOTE_ARTIST_ID, ARTIST_NAME);

BOOST_AUTO_TEST_SUITE(fill);
	BOOST_AUTO_TEST_CASE(empty_remote_empty_artist)
	{
		musicdb db(nullptr);
		BOOST_REQUIRE_NO_THROW(db.fill(nullptr));
	}

	BOOST_AUTO_TEST_CASE(empty_remote_nonempty_artist)
	{
		const artist_ptr_t ARTIST = std::make_shared<artist>(ARTIST_ID, ARTIST_NAME);

		musicdb db(nullptr);
		BOOST_REQUIRE_NO_THROW(db.fill(ARTIST));
		BOOST_TEST(ARTIST->get_id() == ARTIST_ID);
		BOOST_TEST(ARTIST->get_ids() == ARTIST_ID_SET);
		BOOST_TEST(!ARTIST->has_releases());
	}

	BOOST_AUTO_TEST_CASE(nonempty_remote_empty_artist)
	{
		fakeit::Mock<iremote> remote_mock;

		fakeit::Fake(Method(remote_mock, search_artists));
		fakeit::Fake(Method(remote_mock, search_releases));

		musicdb db(iremote_t(&remote_mock.get(), [](iremote*) {}));
		BOOST_REQUIRE_NO_THROW(db.fill(nullptr));

		fakeit::VerifyNoOtherInvocations(remote_mock);
	}

	BOOST_AUTO_TEST_CASE(artist_with_no_local_releases)
	{
		const artist_ptr_t ARTIST = std::make_shared<artist>(ARTIST_ID, ARTIST_NAME);

		fakeit::Mock<iremote> remote_mock;

		fakeit::Fake(Method(remote_mock, search_artists));
		fakeit::Fake(Method(remote_mock, search_releases));

		musicdb db(iremote_t(&remote_mock.get(), [](iremote*) {}));
		BOOST_REQUIRE_NO_THROW(db.fill(ARTIST));
		BOOST_TEST(ARTIST->get_id() == ARTIST_ID);
		BOOST_TEST(ARTIST->get_ids() == ARTIST_ID_SET);
		BOOST_TEST(!ARTIST->has_releases());

		fakeit::VerifyNoOtherInvocations(remote_mock);
	}

	BOOST_AUTO_TEST_CASE(artists_not_found)
	{
		const artist_ptr_t ARTIST = std::make_shared<artist>(ARTIST_ID, ARTIST_NAME);

		fakeit::Mock<iremote> remote_mock;

		fakeit::When(Method(remote_mock, search_artists)).AlwaysReturn(artist_list_t());
		fakeit::Fake(Method(remote_mock, search_releases));

		musicdb db(iremote_t(&remote_mock.get(), [](iremote*) {}));
		ARTIST->add_local_release(RELEASE);
		BOOST_REQUIRE_NO_THROW(db.fill(ARTIST));
		BOOST_TEST(ARTIST->get_id() == ARTIST_ID);
		BOOST_TEST(ARTIST->get_ids() == ARTIST_ID_SET);
		BOOST_TEST(!ARTIST->has_releases());

		fakeit::Verify(Method(remote_mock, search_artists)).Once();
		fakeit::VerifyNoOtherInvocations(remote_mock);
	}

	BOOST_AUTO_TEST_CASE(artist_found_releases_not_found)
	{
		const artist_ptr_t ARTIST = std::make_shared<artist>(ARTIST_ID, ARTIST_NAME);

		fakeit::Mock<iremote> remote_mock;

		fakeit::When(Method(remote_mock, search_artists)).AlwaysReturn({ REMOTE_ARTIST });
		fakeit::When(Method(remote_mock, search_releases)).AlwaysReturn(release_set_t());

		musicdb db(iremote_t(&remote_mock.get(), [](iremote*) {}));
		ARTIST->add_local_release(RELEASE);
		BOOST_REQUIRE_NO_THROW(db.fill(ARTIST));
		BOOST_TEST(ARTIST->get_id() == ARTIST_ID);
		BOOST_TEST(ARTIST->get_ids() == ARTIST_MULTI_ID_SET);
		BOOST_TEST(!ARTIST->has_releases());

		fakeit::Verify(Method(remote_mock, search_artists)).Once();
		fakeit::Verify(Method(remote_mock, search_releases)).Once();
		fakeit::VerifyNoOtherInvocations(remote_mock);
	}

	BOOST_AUTO_TEST_CASE(artist_found_release_found)
	{
		const artist_ptr_t ARTIST = std::make_shared<artist>(ARTIST_ID, ARTIST_NAME);

		fakeit::Mock<iremote> remote_mock;

		fakeit::When(Method(remote_mock, search_artists)).AlwaysReturn({ REMOTE_ARTIST });
		fakeit::When(Method(remote_mock, search_releases)).AlwaysReturn({ REMOTE_RELEASE });

		musicdb db(iremote_t(&remote_mock.get(), [](iremote*) {}));
		ARTIST->add_release(RELEASE);
		ARTIST->add_local_release(RELEASE);
		BOOST_REQUIRE_NO_THROW(db.fill(ARTIST));
		BOOST_TEST(ARTIST->get_id() == ARTIST_ID);
		BOOST_TEST(ARTIST->get_ids() == ARTIST_MULTI_ID_SET);
		BOOST_REQUIRE(ARTIST->get_releases().size() == 1);

		release_ptr_t r = *ARTIST->get_releases().begin();
		BOOST_TEST(r->get_id() == REMOTE_RELEASE_ID);
		BOOST_TEST(r->get_title() == REMOTE_RELEASE_TITLE);
		BOOST_TEST(r->get_type() == REMOTE_RELEASE_TYPE);
		BOOST_TEST(r->get_date().get() == REMOTE_RELEASE_DATE);

		fakeit::Verify(Method(remote_mock, search_artists)).Once();
		fakeit::Verify(Method(remote_mock, search_releases)).Once();
		fakeit::VerifyNoOtherInvocations(remote_mock);
	}

	BOOST_AUTO_TEST_CASE(artist_found_on_second_try)
	{
		const artist_ptr_t ARTIST = std::make_shared<artist>(ARTIST_ID, ARTIST_NAME);

		fakeit::Mock<iremote> remote_mock;

		fakeit::When(Method(remote_mock, search_artists)).Return(artist_list_t()).AlwaysReturn({ REMOTE_ARTIST });
		fakeit::When(Method(remote_mock, search_releases)).AlwaysReturn(release_set_t());

		musicdb db(iremote_t(&remote_mock.get(), [](iremote*) {}));
		ARTIST->add_local_release(RELEASE);
		ARTIST->add_local_release(REMOTE_RELEASE);
		BOOST_REQUIRE_NO_THROW(db.fill(ARTIST));
		BOOST_TEST(ARTIST->get_id() == ARTIST_ID);
		BOOST_TEST(ARTIST->get_ids() == ARTIST_MULTI_ID_SET);
		BOOST_TEST(!ARTIST->has_releases());

		fakeit::Verify(Method(remote_mock, search_artists)).Exactly(2);
		fakeit::Verify(Method(remote_mock, search_releases)).Once();
		fakeit::VerifyNoOtherInvocations(remote_mock);
	}
BOOST_AUTO_TEST_SUITE_END();
