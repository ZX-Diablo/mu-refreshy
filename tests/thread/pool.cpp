#define BOOST_TEST_MODULE thread_pool_test
#include <boost/test/unit_test.hpp>

#include <thread/pool.h>

const unsigned int POOL_SIZE = 2;

BOOST_AUTO_TEST_SUITE(constructor);
	BOOST_AUTO_TEST_CASE(empty)
	{
		BOOST_REQUIRE_NO_THROW(pool(0));
	}

	BOOST_AUTO_TEST_CASE(nonempty)
	{
		BOOST_REQUIRE_NO_THROW(pool(POOL_SIZE));
	}
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(add_task);
	BOOST_AUTO_TEST_CASE(add)
	{
		pool p;
		std::thread::id thread_id = std::this_thread::get_id();
		p.add_task([thread_id]()
		{
			BOOST_TEST(std::this_thread::get_id() != thread_id);
		});
	}
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(wait_tasks);
	BOOST_AUTO_TEST_CASE(wait)
	{
		pool p;
		BOOST_REQUIRE_NO_THROW(p.wait());
	}
BOOST_AUTO_TEST_SUITE_END();
