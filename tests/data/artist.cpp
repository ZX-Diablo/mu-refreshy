#define BOOST_TEST_MODULE data_artist_test
#include <boost/test/unit_test.hpp>

#include <data/artist.h>

const std::string ARTIST_ID = "D34H";
const std::string ARTIST_NAME = "artist";
const std::string ARTIST_OTHER_ID = "O5J9";

const artist::id_set_t ARTIST_ONE_ID_SET = { ARTIST_ID };
const artist::id_set_t ARTIST_MULTI_ID_SET = { ARTIST_ID, ARTIST_OTHER_ID };

const std::string RELEASE_ID = "A123";
const std::string RELEASE_TITLE = "Music album";
const std::string RELEASE_TYPE = "full album";
const std::string RELEASE_DATE = "2000-06-13";

const release_ptr_t RELEASE = std::make_shared<release>(RELEASE_ID, RELEASE_TITLE, RELEASE_TYPE, date(RELEASE_DATE));
const release_set_t RELEASE_SET = { RELEASE };
const unsigned int RELEASE_SET_SIZE_EXPECTED = 1;

BOOST_AUTO_TEST_SUITE(constructors);
	BOOST_AUTO_TEST_CASE(empty)
	{
		artist a = artist(std::string());
		BOOST_TEST(a.get_id() == std::string());
		BOOST_TEST(a.get_name() == std::string());
		BOOST_TEST(a.get_ids().empty());
		BOOST_TEST(a.get_releases().empty());
		BOOST_TEST(a.get_local_releases().empty());
	}

	BOOST_AUTO_TEST_CASE(name)
	{
		artist a(ARTIST_NAME);
		BOOST_TEST(a.get_id() == std::string());
		BOOST_TEST(a.get_name() == ARTIST_NAME);
		BOOST_TEST(a.get_ids().empty());
		BOOST_TEST(a.get_releases().empty());
		BOOST_TEST(a.get_local_releases().empty());
	}

	BOOST_AUTO_TEST_CASE(id)
	{
		artist a(ARTIST_ID, std::string());
		BOOST_TEST(a.get_id() == ARTIST_ID);
		BOOST_TEST(a.get_name() == std::string());
		BOOST_TEST(a.get_ids() == ARTIST_ONE_ID_SET);
		BOOST_TEST(a.get_releases().empty());
		BOOST_TEST(a.get_local_releases().empty());
	}

	BOOST_AUTO_TEST_CASE(id_name)
	{
		artist a(ARTIST_ID, ARTIST_NAME);
		BOOST_TEST(a.get_id() == ARTIST_ID);
		BOOST_TEST(a.get_name() == ARTIST_NAME);
		BOOST_TEST(a.get_ids() == ARTIST_ONE_ID_SET);
		BOOST_TEST(a.get_releases().empty());
		BOOST_TEST(a.get_local_releases().empty());
	}

	BOOST_AUTO_TEST_CASE(release)
	{
		artist a(RELEASE_SET, {});
		BOOST_TEST(a.get_id() == std::string());
		BOOST_TEST(a.get_name() == std::string());
		BOOST_TEST(a.get_ids().empty());
		BOOST_REQUIRE(a.get_releases().size() == RELEASE_SET_SIZE_EXPECTED);
		BOOST_TEST(a.get_local_releases().empty());

		release_ptr_t r = *a.get_releases().begin();
		BOOST_TEST(r->get_id() == RELEASE_ID);
		BOOST_TEST(r->get_title() == RELEASE_TITLE);
		BOOST_TEST(r->get_type() == RELEASE_TYPE);
		BOOST_TEST(r->get_date().get() == RELEASE_DATE);
	}

	BOOST_AUTO_TEST_CASE(local_release)
	{
		artist a({}, RELEASE_SET);
		BOOST_TEST(a.get_id() == std::string());
		BOOST_TEST(a.get_name() == std::string());
		BOOST_TEST(a.get_ids().empty());
		BOOST_TEST(a.get_releases().empty());
		BOOST_REQUIRE(a.get_local_releases().size() == RELEASE_SET_SIZE_EXPECTED);

		release_ptr_t r = *a.get_local_releases().begin();
		BOOST_TEST(r->get_id() == RELEASE_ID);
		BOOST_TEST(r->get_title() == RELEASE_TITLE);
		BOOST_TEST(r->get_type() == RELEASE_TYPE);
		BOOST_TEST(r->get_date().get() == RELEASE_DATE);
	}
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(releases);
	BOOST_AUTO_TEST_CASE(add_empty_release)
	{
		artist a = artist(std::string());
		a.add_release(nullptr);
		BOOST_TEST(a.get_releases().empty());
		BOOST_TEST(a.get_local_releases().empty());
	}

	BOOST_AUTO_TEST_CASE(add_notempty_release)
	{
		artist a = artist(std::string());
		a.add_release(RELEASE);
		BOOST_REQUIRE(a.get_releases().size() == RELEASE_SET_SIZE_EXPECTED);
		BOOST_TEST(a.get_local_releases().empty());

		release_ptr_t r = *a.get_releases().begin();
		BOOST_TEST(r->get_id() == RELEASE_ID);
		BOOST_TEST(r->get_title() == RELEASE_TITLE);
		BOOST_TEST(r->get_type() == RELEASE_TYPE);
		BOOST_TEST(r->get_date().get() == RELEASE_DATE);
	}

	BOOST_AUTO_TEST_CASE(add_empty_local_release)
	{
		artist a = artist(std::string());
		a.add_local_release(nullptr);
		BOOST_TEST(a.get_releases().empty());
		BOOST_TEST(a.get_local_releases().empty());
	}

	BOOST_AUTO_TEST_CASE(add_notempty_local_release)
	{
		artist a = artist(std::string());
		a.add_local_release(RELEASE);
		BOOST_TEST(a.get_releases().empty());
		BOOST_REQUIRE(a.get_local_releases().size() == RELEASE_SET_SIZE_EXPECTED);

		release_ptr_t r = *a.get_local_releases().begin();
		BOOST_TEST(r->get_id() == RELEASE_ID);
		BOOST_TEST(r->get_title() == RELEASE_TITLE);
		BOOST_TEST(r->get_type() == RELEASE_TYPE);
		BOOST_TEST(r->get_date().get() == RELEASE_DATE);
	}

	BOOST_AUTO_TEST_CASE(clear_releases)
	{
		artist a(RELEASE_SET, RELEASE_SET);
		a.clear_releases();
		BOOST_TEST(a.get_releases().empty());
		BOOST_TEST(a.get_local_releases().size() == RELEASE_SET_SIZE_EXPECTED);
	}
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(add_id);
	BOOST_AUTO_TEST_CASE(add_default_id)
	{
		artist a = artist(std::string());
		a.add_id(ARTIST_ID);
		BOOST_TEST(a.get_id() == ARTIST_ID);
		BOOST_TEST(a.get_ids() == ARTIST_ONE_ID_SET);
	}

	BOOST_AUTO_TEST_CASE(add_nondefault_id_still_default)
	{
		artist a = artist(std::string());
		a.add_id(ARTIST_ID, false);
		BOOST_TEST(a.get_id() == ARTIST_ID);
		BOOST_TEST(a.get_ids() == ARTIST_ONE_ID_SET);
	}

	BOOST_AUTO_TEST_CASE(add_duplicate_ids)
	{
		artist a(ARTIST_ID, std::string());
		a.add_id(ARTIST_ID);
		BOOST_TEST(a.get_id() == ARTIST_ID);
		BOOST_TEST(a.get_ids() == ARTIST_ONE_ID_SET);
	}

	BOOST_AUTO_TEST_CASE(add_unique_ids_not_change_default)
	{
		artist a(ARTIST_ID, std::string());
		a.add_id(ARTIST_OTHER_ID, false);
		BOOST_TEST(a.get_id() == ARTIST_ID);
		BOOST_TEST(a.get_ids() == ARTIST_MULTI_ID_SET);
	}

	BOOST_AUTO_TEST_CASE(add_unique_ids_change_default)
	{
		artist a(ARTIST_ID, std::string());
		a.add_id(ARTIST_OTHER_ID);
		BOOST_TEST(a.get_id() == ARTIST_OTHER_ID);
		BOOST_TEST(a.get_ids() == ARTIST_MULTI_ID_SET);
	}
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(checks);
	BOOST_AUTO_TEST_CASE(has_id_false)
	{
		artist a = artist(std::string());
		BOOST_TEST(!a.has_id());
	}

	BOOST_AUTO_TEST_CASE(has_id_true)
	{
		artist a(ARTIST_ID, std::string());
		BOOST_TEST(a.has_id());
	}

	BOOST_AUTO_TEST_CASE(has_releases_false)
	{
		artist a = artist(release_set_t(), release_set_t());
		BOOST_TEST(!a.has_releases());
	}

	BOOST_AUTO_TEST_CASE(has_releases_true)
	{
		artist a(RELEASE_SET, {});
		BOOST_TEST(a.has_releases());
	}

	BOOST_AUTO_TEST_CASE(has_local_releases_false)
	{
		artist a = artist(release_set_t(), release_set_t());
		BOOST_TEST(!a.has_local_releases());
	}

	BOOST_AUTO_TEST_CASE(has_local_releases_true)
	{
		artist a({}, RELEASE_SET);
		BOOST_TEST(a.has_local_releases());
	}
BOOST_AUTO_TEST_SUITE_END();
