#define BOOST_TEST_MODULE filescan_artistalbumfilescan_test
#include <boost/test/unit_test.hpp>

#include <filescan/artistalbumfilescan.h>
#include <test/defines.h>

const ifilescan::path_t PATH_ROOT = "./test_root";
const ifilescan::path_t PATH_ARTIST = PATH_ROOT / "artist";
const ifilescan::path_t PATH_ALBUM = PATH_ARTIST / "album";

const ifilescan::path_t FILE_ROOT = PATH_ROOT / "song1.mp3";
const ifilescan::path_t FILE_ARTIST = PATH_ARTIST / "song2.mp3";
const ifilescan::path_t FILE_ALBUM = PATH_ALBUM / "song3.mp3";
const ifilescan::path_t FILE_NOT_MP3 = FILE_ALBUM / "lyrics.txt";

const ifilescan::path_t PATH_ROOT_NONEXISTING = "./abc";
const ifilescan::path_t PATH_ROOT_NOT_DIRECTORY = FILE_ROOT;

const unsigned int PATHS_EXPECTED_SIZE = 1;

BOOST_TEST_DONT_PRINT_LOG_VALUE(ifilescan::path_list_t::iterator);

struct filesystem_fixture
{
	filesystem_fixture ()
	{
		boost::filesystem::create_directories(PATH_ALBUM);
		boost::filesystem::ofstream(FILE_ROOT).close();
		boost::filesystem::ofstream(FILE_ARTIST).close();
		boost::filesystem::ofstream(FILE_ALBUM).close();
		boost::filesystem::ofstream(FILE_NOT_MP3).close();
	}

	~filesystem_fixture ()
	{
		boost::filesystem::remove_all(PATH_ROOT);
	}
};

BOOST_AUTO_TEST_SUITE(scan,
	* boost::unit_test::enable_if<BOOST_TEST_INTEGRATION_ENABLED>()
	* boost::unit_test::label(BOOST_TEST_INTEGRATION_LABEL)
	* boost::unit_test::fixture<filesystem_fixture>()
);
	BOOST_AUTO_TEST_CASE(scan_root_nonexisting)
	{
		artistalbumfilescan aafs;
		BOOST_TEST(aafs.scan(PATH_ROOT_NONEXISTING).empty());
	}

	BOOST_AUTO_TEST_CASE(scan_root_not_directory)
	{
		artistalbumfilescan aafs;
		BOOST_TEST(aafs.scan(PATH_ROOT_NOT_DIRECTORY).empty());
	}

	BOOST_AUTO_TEST_CASE(scan_hierarchy)
	{
		artistalbumfilescan aafs;
		ifilescan::path_list_t paths = aafs.scan(PATH_ROOT);
		BOOST_TEST(paths.size() == PATHS_EXPECTED_SIZE);
		BOOST_TEST(std::find(paths.begin(), paths.end(), FILE_ALBUM) != paths.end());
	}
BOOST_AUTO_TEST_SUITE_END();
