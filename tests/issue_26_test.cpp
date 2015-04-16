#include "fi/Fixed.hpp"
#include "fi/overflow/Saturate.hpp"
#include "fi/overflow/Throw.hpp"
#include "fi/overflow/Wrap.hpp"

#define BOOST_TEST_DYN_LINK true
#define BOOST_TEST_MODULE issue_26
#include <boost/test/unit_test.hpp>

#define CHECK_EQ(A, E) BOOST_CHECK_EQUAL((A).toString(), E)

typedef Fi::Fixed<16, 16, Fi::SIGNED, Fi::Saturate> fi16s;

BOOST_AUTO_TEST_SUITE(Wrap)
BOOST_AUTO_TEST_CASE( wrap_signed_construction )
{

	CHECK_EQ(fi16s("0.1"), "0.0999908447265625");
	CHECK_EQ(fi16s(0.1), "0.0999908447265625");

}

BOOST_AUTO_TEST_SUITE_END()

