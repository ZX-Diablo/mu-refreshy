#define BOOST_TEST_MODULE storage_reader_xml_test
#include <boost/test/unit_test.hpp>

#include <storage/reader/xml.h>

#include <sstream>

const std::string RELEASE_ID = "A123";
const std::string RELEASE_TITLE = "Music album";
const std::string RELEASE_TYPE = "full album";
const std::string RELEASE_DATE = "2000-06-13";

const std::string ARTIST_ID = "D34H";
const std::string ARTIST_NAME = "Various";
const std::string ARTIST_OTHER_ID = "J18K";
const std::string ARTIST_OTHER_NAME = "Musician";

const artist::id_set_t ARTIST_IDS = { ARTIST_ID, ARTIST_OTHER_ID };

const artist_ptr_t ARTIST_NAMED = std::make_shared<artist>(ARTIST_ID, ARTIST_NAME);

std::stringstream XML_EMPTY;
std::stringstream XML_BAD("<?xml version=\"1.0\"?><storage>");
std::stringstream XML_NO_ARTISTS("<?xml version=\"1.0\"?><storage><artists></artists></storage>");

std::stringstream XML_ARTIST_NO_DATA(
	"<?xml version=\"1.0\"?>"
	"<storage><artists>"
		"<artist id=\"" + ARTIST_ID + "\" name=\"" + ARTIST_NAME + "\" />"
	"</artists></storage>"
);

std::stringstream XML_ARTIST_IDS(
	"<?xml version=\"1.0\"?>"
	"<storage><artists>"
		"<artist id=\"" + ARTIST_ID + "\" name=\"" + ARTIST_NAME + "\">"
			"<ids>"
				"<id>" + ARTIST_ID + "</id>"
				"<id>" + ARTIST_OTHER_ID + "</id>"
			"</ids>"
		"</artist>"
	"</artists></storage>"
);

std::stringstream XML_ARTIST_LOCAL_RELEASE(
	"<?xml version=\"1.0\"?>"
	"<storage><artists>"
		"<artist id=\"" + ARTIST_ID + "\" name=\"" + ARTIST_NAME + "\">"
			"<releases>"
				"<release type=\"local\">"
					"<id>" + RELEASE_ID + "</id>"
					"<title>" + RELEASE_TITLE + "</title>"
					"<type>" + RELEASE_TYPE + "</type>"
					"<date>" + RELEASE_DATE + "</date>"
				"</release>"
			"</releases>"
		"</artist>"
	"</artists></storage>"
);

std::stringstream XML_ARTIST_REMOTE_RELEASE(
	"<?xml version=\"1.0\"?>"
	"<storage><artists>"
		"<artist id=\"" + ARTIST_ID + "\" name=\"" + ARTIST_NAME + "\">"
			"<releases>"
				"<release type=\"remote\">"
					"<id>" + RELEASE_ID + "</id>"
					"<title>" + RELEASE_TITLE + "</title>"
					"<type>" + RELEASE_TYPE + "</type>"
					"<date>" + RELEASE_DATE + "</date>"
				"</release>"
			"</releases>"
		"</artist>"
	"</artists></storage>"
);

std::stringstream XML_ARTIST_EXISTING(
	"<?xml version=\"1.0\"?>"
	"<storage><artists>"
		"<artist id=\"" + ARTIST_ID + "\" name=\"" + ARTIST_NAME + "\">"
			"<releases>"
				"<release type=\"local\">"
					"<id>" + RELEASE_ID + "</id>"
					"<title>" + RELEASE_TITLE + "</title>"
					"<type>" + RELEASE_TYPE + "</type>"
					"<date>" + RELEASE_DATE + "</date>"
				"</release>"
			"</releases>"
		"</artist>"
	"</artists></storage>"
);

std::stringstream XML_ARTIST_NOT_EXISTING(
	"<?xml version=\"1.0\"?>"
	"<storage><artists>"
		"<artist id=\"" + ARTIST_OTHER_ID + "\" name=\"" + ARTIST_OTHER_NAME + "\" />"
	"</artists></storage>"
);

using namespace reader;

BOOST_TEST_DONT_PRINT_LOG_VALUE(storage::const_iterator);

BOOST_AUTO_TEST_SUITE(read_storage);
	BOOST_AUTO_TEST_CASE(empty_stream)
	{
		xml r;
		storage s;

		r.read(s, XML_EMPTY);

		BOOST_TEST(s.begin() == s.end());
	}

	BOOST_AUTO_TEST_CASE(bad_xml)
	{
		xml r;
		storage s;

		r.read(s, XML_BAD);

		BOOST_TEST(s.begin() == s.end());
	}

	BOOST_AUTO_TEST_CASE(no_artists)
	{
		xml r;
		storage s;

		r.read(s, XML_NO_ARTISTS);

		BOOST_TEST(s.begin() == s.end());
	}

	BOOST_AUTO_TEST_CASE(artist_no_data)
	{
		xml r;
		storage s;

		r.read(s, XML_ARTIST_NO_DATA);

		artist_ptr_t a = s.get_by_id(ARTIST_ID);

		BOOST_REQUIRE(a != nullptr);
		BOOST_TEST(a->get_id() == ARTIST_ID);
		BOOST_TEST(a->get_name() == ARTIST_NAME);
		BOOST_TEST(a->get_ids().size() == 1);
		BOOST_TEST(!a->has_local_releases());
		BOOST_TEST(!a->has_releases());
	}

	BOOST_AUTO_TEST_CASE(artist_ids)
	{
		xml r;
		storage s;

		r.read(s, XML_ARTIST_IDS);

		artist_ptr_t a = s.get_by_id(ARTIST_ID);

		BOOST_REQUIRE(a != nullptr);
		BOOST_TEST(a->get_id() == ARTIST_ID);
		BOOST_TEST(a->get_name() == ARTIST_NAME);
		BOOST_TEST(a->get_ids() == ARTIST_IDS);
		BOOST_TEST(!a->has_local_releases());
		BOOST_TEST(!a->has_releases());
	}

	BOOST_AUTO_TEST_CASE(artist_local_release)
	{
		xml r;
		storage s;

		r.read(s, XML_ARTIST_LOCAL_RELEASE);

		artist_ptr_t a = s.get_by_id(ARTIST_ID);

		BOOST_REQUIRE(a != nullptr);
		BOOST_TEST(a->get_id() == ARTIST_ID);
		BOOST_TEST(a->get_name() == ARTIST_NAME);
		BOOST_TEST(a->get_ids().size() == 1);
		BOOST_TEST(a->has_local_releases());
		BOOST_TEST(a->get_local_releases().size() == 1);
		BOOST_TEST(!a->has_releases());

		release_ptr_t rel = *a->get_local_releases().begin();

		BOOST_TEST(rel->get_id() == RELEASE_ID);
		BOOST_TEST(rel->get_title() == RELEASE_TITLE);
		BOOST_TEST(rel->get_type() == RELEASE_TYPE);
		BOOST_TEST(rel->get_date().get() == RELEASE_DATE);
	}

	BOOST_AUTO_TEST_CASE(artist_remote_release_become_local)
	{
		xml r;
		storage s;

		r.read(s, XML_ARTIST_REMOTE_RELEASE);

		artist_ptr_t a = s.get_by_id(ARTIST_ID);

		BOOST_REQUIRE(a != nullptr);
		BOOST_TEST(a->get_id() == ARTIST_ID);
		BOOST_TEST(a->get_name() == ARTIST_NAME);
		BOOST_TEST(a->get_ids().size() == 1);
		BOOST_TEST(a->has_local_releases());
		BOOST_TEST(a->get_local_releases().size() == 1);
		BOOST_TEST(!a->has_releases());

		release_ptr_t rel = *a->get_local_releases().begin();

		BOOST_TEST(rel->get_id() == RELEASE_ID);
		BOOST_TEST(rel->get_title() == RELEASE_TITLE);
		BOOST_TEST(rel->get_type() == RELEASE_TYPE);
		BOOST_TEST(rel->get_date().get() == RELEASE_DATE);
	}

	BOOST_AUTO_TEST_CASE(not_empty_storage_replace_existing_artist)
	{
		xml r;
		storage s(ARTIST_NAMED);

		r.read(s, XML_ARTIST_EXISTING);

		BOOST_REQUIRE(std::distance(s.begin(), s.end()) == 1);

		artist_ptr_t a = s.get_by_id(ARTIST_ID);

		BOOST_REQUIRE(a != nullptr);
		BOOST_TEST(a->get_id() == ARTIST_ID);
		BOOST_TEST(a->get_name() == ARTIST_NAME);
		BOOST_TEST(a->get_ids().size() == 1);
		BOOST_TEST(a->has_local_releases());
		BOOST_TEST(a->get_local_releases().size() == 1);
		BOOST_TEST(!a->has_releases());

		release_ptr_t rel = *a->get_local_releases().begin();

		BOOST_TEST(rel->get_id() == RELEASE_ID);
		BOOST_TEST(rel->get_title() == RELEASE_TITLE);
		BOOST_TEST(rel->get_type() == RELEASE_TYPE);
		BOOST_TEST(rel->get_date().get() == RELEASE_DATE);
	}

	BOOST_AUTO_TEST_CASE(not_empty_storage_add_new_artist)
	{
		xml r;
		storage s(ARTIST_NAMED);

		r.read(s, XML_ARTIST_NOT_EXISTING);

		BOOST_REQUIRE(std::distance(s.begin(), s.end()) == 2);
		BOOST_REQUIRE(s.get_by_id(ARTIST_ID) != nullptr);

		artist_ptr_t a = s.get_by_id(ARTIST_OTHER_ID);

		BOOST_REQUIRE(a != nullptr);
		BOOST_TEST(a->get_id() == ARTIST_OTHER_ID);
		BOOST_TEST(a->get_name() == ARTIST_OTHER_NAME);
		BOOST_TEST(a->get_ids().size() == 1);
		BOOST_TEST(!a->has_local_releases());
		BOOST_TEST(!a->has_releases());
	}
BOOST_AUTO_TEST_SUITE_END();
