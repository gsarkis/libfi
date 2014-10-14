#include "fi/Fixed.hpp"
#include "fi/overflow/Throw.hpp"

#define BOOST_TEST_DYN_LINK true
#define BOOST_TEST_MODULE construction
#include <boost/test/unit_test.hpp>

#define CHECK_EQ(A, E) BOOST_CHECK_EQUAL((A).toString(), E)


BOOST_AUTO_TEST_SUITE(construction_signed)
typedef Fi::Fixed<16, 15, Fi::SIGNED, Fi::Throw> fi16s;

BOOST_AUTO_TEST_CASE( u_from_string )
{

	CHECK_EQ( fi16s("0.043731689453125"), "0.043731689453125" );

}

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////
