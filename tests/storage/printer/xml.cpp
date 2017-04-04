#define BOOST_TEST_MODULE storage_printer_xml_test
#include <boost/test/unit_test.hpp>

#include <storage/printer/xml.h>

#include <sstream>
#include <iostream>

const std::string RELEASE_FIRST_ID = "A123";
const std::string RELEASE_FIRST_TITLE = "Music album";
const std::string RELEASE_FIRST_TYPE = "full album";
const std::string RELEASE_FIRST_DATE = "2000-06-13";

const std::string RELEASE_SECOND_ID = "B987";
const std::string RELEASE_SECOND_TITLE = "Best title";
const std::string RELEASE_SECOND_TYPE = "full album";
const std::string RELEASE_SECOND_DATE = "2010-12-05";

const release_ptr_t RELEASE_FIRST = std::make_shared<release>(
		RELEASE_FIRST_ID, RELEASE_FIRST_TITLE, RELEASE_FIRST_TYPE, date(RELEASE_FIRST_DATE));
const release_ptr_t RELEASE_SECOND = std::make_shared<release>(
		RELEASE_SECOND_ID, RELEASE_SECOND_TITLE, RELEASE_SECOND_TYPE, date(RELEASE_SECOND_DATE));

const release_set_t RELEASE_SET_LOCAL = { RELEASE_FIRST };
const release_set_t RELEASE_SET_REMOTE = { RELEASE_FIRST, RELEASE_SECOND };
const release_set_t RELEASE_SET_FULL_LOCAL = RELEASE_SET_REMOTE;

const artist_ptr_t ARTIST_EMPTY = std::make_shared<artist>(std::string());
const artist_ptr_t ARTIST_ONLY_LOCAL = std::make_shared<artist>(release_set_t(), RELEASE_SET_LOCAL);
const artist_ptr_t ARTIST_ONLY_REMOTE = std::make_shared<artist>(RELEASE_SET_REMOTE, release_set_t());
const artist_ptr_t ARTIST_LOCAL_REMOTE = std::make_shared<artist>(RELEASE_SET_REMOTE, RELEASE_SET_LOCAL);
const artist_ptr_t ARTIST_FULL_LOCAL_REMOTE = std::make_shared<artist>(RELEASE_SET_REMOTE, RELEASE_SET_FULL_LOCAL);

const storage STORAGE_EMPTY;
const storage STORAGE_ONLY_LOCAL(ARTIST_ONLY_LOCAL);
const storage STORAGE_ONLY_REMOTE(ARTIST_ONLY_REMOTE);
const storage STORAGE_LOCAL_REMOTE(ARTIST_LOCAL_REMOTE);
const storage STORAGE_FULL_LOCAL_REMOTE(ARTIST_FULL_LOCAL_REMOTE);

BOOST_AUTO_TEST_SUITE(print);
	BOOST_AUTO_TEST_CASE(empty)
	{
		xml p;
		std::stringstream ss;

		p.print(STORAGE_EMPTY, ss);

		BOOST_TEST(ss.str().find("artist ") == std::string::npos);
	}

	BOOST_AUTO_TEST_CASE(only_local)
	{
		xml p;
		std::stringstream ss;

		p.print(STORAGE_ONLY_LOCAL, ss);

		std::string res = ss.str();

		// No artist attributes testing because no way to construct such artist
		BOOST_TEST(res.find("remote") == std::string::npos);
		BOOST_TEST(res.find("local") != std::string::npos);
		BOOST_TEST(res.find(RELEASE_FIRST_ID) != std::string::npos);
		BOOST_TEST(res.find(RELEASE_FIRST_TITLE) != std::string::npos);
		BOOST_TEST(res.find(RELEASE_FIRST_TYPE) != std::string::npos);
		BOOST_TEST(res.find(RELEASE_FIRST_DATE) != std::string::npos);
	}

	BOOST_AUTO_TEST_CASE(only_remote)
	{
		xml p;
		std::stringstream ss;

		p.print(STORAGE_ONLY_REMOTE, ss);

		std::string res = ss.str();

		BOOST_TEST(res.find("local") == std::string::npos);
		BOOST_TEST(res.find("remote") != std::string::npos);
		BOOST_TEST(res.find(RELEASE_FIRST_ID) != std::string::npos);
		BOOST_TEST(res.find(RELEASE_FIRST_TITLE) != std::string::npos);
		BOOST_TEST(res.find(RELEASE_FIRST_TYPE) != std::string::npos);
		BOOST_TEST(res.find(RELEASE_FIRST_DATE) != std::string::npos);
		BOOST_TEST(res.find(RELEASE_SECOND_ID) != std::string::npos);
		BOOST_TEST(res.find(RELEASE_SECOND_TITLE) != std::string::npos);
		BOOST_TEST(res.find(RELEASE_SECOND_TYPE) != std::string::npos);
		BOOST_TEST(res.find(RELEASE_SECOND_DATE) != std::string::npos);
	}
BOOST_AUTO_TEST_SUITE_END();
