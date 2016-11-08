#define BOOST_TEST_MODULE thread_pool_test
#include <boost/test/unit_test.hpp>

#include <thread/pool.h>

BOOST_AUTO_TEST_SUITE(constructor);
	BOOST_AUTO_TEST_CASE(empty)
	{
		pool p(0);
	}
BOOST_AUTO_TEST_SUITE_END();
