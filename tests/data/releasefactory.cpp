#define BOOST_TEST_MODULE data_releasefactory_test
#include <boost/test/unit_test.hpp>

#include <data/releasefactory.h>
#include <fakeit.hpp>

const std::string RELEASE_TITLE = "Music album";
const unsigned int RELEASE_YEAR = 2000;
const std::string RELEASE_YEAR_EXPECTED = "2000-01-01";

BOOST_AUTO_TEST_SUITE(get);
	BOOST_AUTO_TEST_CASE(tag_empty)
	{
		BOOST_TEST(!releasefactory::get((TagLib::Tag*)nullptr));
	}

	BOOST_AUTO_TEST_CASE(tag)
	{
		fakeit::Mock<TagLib::Tag> tag_mock;

		fakeit::When(Method(tag_mock, album)).AlwaysReturn(RELEASE_TITLE);
		fakeit::When(Method(tag_mock, year)).AlwaysReturn(RELEASE_YEAR);

		release_ptr_t r = releasefactory::get(&tag_mock.get());
		BOOST_TEST(r->get_id() == std::string());
		BOOST_TEST(r->get_title() == RELEASE_TITLE);
		BOOST_TEST(r->get_type() == std::string());
		BOOST_TEST(r->get_date().get() == RELEASE_YEAR_EXPECTED);

		fakeit::Verify(Method(tag_mock, album)).Once();
		fakeit::Verify(Method(tag_mock, year)).Once();
		fakeit::VerifyNoOtherInvocations(tag_mock);
	}

	BOOST_AUTO_TEST_CASE(release_group_empty)
	{
		BOOST_TEST(!releasefactory::get((MusicBrainz5::CReleaseGroup*)nullptr));
	}

	BOOST_AUTO_TEST_CASE(release_group)
	{
		BOOST_TEST_MESSAGE("Can't fake MusicBrainz5::CReleaseGroup. Skip test");
	}
BOOST_AUTO_TEST_SUITE_END();
