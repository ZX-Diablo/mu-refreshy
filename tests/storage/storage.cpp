#define BOOST_TEST_MODULE storage_storage_test
#include <boost/test/unit_test.hpp>

#include <storage/storage.h>

#include <sstream>

const std::string ARTIST_ID = "D34H";
const std::string ARTIST_NAME = "artist";
const artist_ptr_t ARTIST = std::make_shared<artist>(ARTIST_ID, ARTIST_NAME);

const std::string ARTIST_OTHER_ID = "E78J";
const std::string ARTIST_OTHER_NAME = "artist2";
const artist_ptr_t ARTIST_OTHER = std::make_shared<artist>(ARTIST_OTHER_ID, ARTIST_OTHER_NAME);

const artist_ptr_t ARTIST_SAME_ID = std::make_shared<artist>(ARTIST_ID, ARTIST_OTHER_NAME);
const artist_ptr_t ARTIST_SAME_NAME = std::make_shared<artist>(ARTIST_OTHER_ID, ARTIST_NAME);

BOOST_AUTO_TEST_SUITE(constructor);
	BOOST_AUTO_TEST_CASE(empty)
	{
		storage s;
		std::stringstream ss;
		s.print_all(ss);
		BOOST_TEST(ss.str().empty());
	}
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(add);
	BOOST_AUTO_TEST_CASE(add_empty)
	{
		storage s;
		BOOST_TEST(!s.add(nullptr));
	}

	BOOST_AUTO_TEST_CASE(add_unique)
	{
		storage s;
		BOOST_TEST(s.add(ARTIST));
		BOOST_TEST(s.get_by_id(ARTIST_ID) == ARTIST);
		BOOST_TEST(s.get_by_name(ARTIST_NAME) == ARTIST);
	}

	BOOST_AUTO_TEST_CASE(add_non_unique_full_same)
	{
		storage s;
		s.add(ARTIST); // TODO: create storage with given data?
		BOOST_TEST(!s.add(ARTIST));
		BOOST_TEST(s.get_by_id(ARTIST_ID) == ARTIST);
		BOOST_TEST(s.get_by_name(ARTIST_NAME) == ARTIST);
	}

	BOOST_AUTO_TEST_CASE(add_non_unique_id_same)
	{
		storage s;
		s.add(ARTIST);
		BOOST_TEST(s.add(ARTIST_SAME_ID));
		BOOST_TEST(s.get_by_id(ARTIST_ID) == ARTIST);
		BOOST_TEST(s.get_by_name(ARTIST_NAME) == ARTIST);
		BOOST_TEST(s.get_by_name(ARTIST_OTHER_NAME) == ARTIST_SAME_ID);
	}

	BOOST_AUTO_TEST_CASE(add_non_unique_name_same)
	{
		storage s;
		s.add(ARTIST);
		BOOST_TEST(!s.add(ARTIST_SAME_NAME));
		BOOST_TEST(s.get_by_id(ARTIST_ID) == ARTIST);
		BOOST_TEST(s.get_by_name(ARTIST_NAME) == ARTIST);
		BOOST_TEST(!s.get_by_id(ARTIST_OTHER_ID));
	}
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(replace);
	BOOST_AUTO_TEST_CASE(replace_empty)
	{
		storage s;
		BOOST_TEST(!s.replace(ARTIST));
	}

	BOOST_AUTO_TEST_CASE(replace_unique)
	{
		storage s;
		s.add(ARTIST);
		BOOST_TEST(!s.replace(ARTIST_OTHER));
		BOOST_TEST(s.get_by_id(ARTIST_ID) == ARTIST);
		BOOST_TEST(s.get_by_name(ARTIST_NAME) == ARTIST);
		BOOST_TEST(!s.get_by_id(ARTIST_OTHER_ID));
		BOOST_TEST(!s.get_by_name(ARTIST_OTHER_NAME));
	}

	BOOST_AUTO_TEST_CASE(replace_non_unique_full_same)
	{
		storage s;
		s.add(ARTIST);
		BOOST_TEST(s.replace(ARTIST));
		BOOST_TEST(s.get_by_id(ARTIST_ID) == ARTIST);
		BOOST_TEST(s.get_by_name(ARTIST_NAME) == ARTIST);
	}

	BOOST_AUTO_TEST_CASE(replace_non_unique_id_same)
	{
		storage s;
		s.add(ARTIST);
		BOOST_TEST(!s.replace(ARTIST_SAME_ID));
		BOOST_TEST(s.get_by_id(ARTIST_ID) == ARTIST);
		BOOST_TEST(s.get_by_name(ARTIST_NAME) == ARTIST);
		BOOST_TEST(!s.get_by_name(ARTIST_OTHER_NAME));
	}

	BOOST_AUTO_TEST_CASE(replace_non_unique_name_same)
	{
		storage s;
		s.add(ARTIST);
		BOOST_TEST(s.replace(ARTIST_SAME_NAME));
		BOOST_TEST(!s.get_by_id(ARTIST_ID));
		BOOST_TEST(s.get_by_id(ARTIST_OTHER_ID) == ARTIST_SAME_NAME);
		BOOST_TEST(s.get_by_name(ARTIST_NAME) == ARTIST_SAME_NAME);
	}
BOOST_AUTO_TEST_SUITE_END();
