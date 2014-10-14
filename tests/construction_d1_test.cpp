#include "fi/Fixed.hpp"
#include "fi/overflow/Throw.hpp"

#define BOOST_TEST_DYN_LINK true
#define BOOST_TEST_MODULE construction
#include <boost/test/unit_test.hpp>

#define CHECK_EQ(A, E) BOOST_CHECK_EQUAL((A).toString(), E)


BOOST_AUTO_TEST_SUITE(construction_signed)

BOOST_AUTO_TEST_CASE( s_from_string_4 )
{

	typedef Fi::Fixed<4, 3, Fi::SIGNED, Fi::Throw> fi4s;
	CHECK_EQ( fi4s("0.375"), "0.375" );

}

BOOST_AUTO_TEST_CASE( s_from_string_16 )
{

	typedef Fi::Fixed<16, 15, Fi::SIGNED, Fi::Throw> fi16s;
	CHECK_EQ( fi16s("0.043731689453125"), "0.043731689453125" );

}


BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE(construction_unsigned)

BOOST_AUTO_TEST_CASE( u_from_string_4 )
{

	typedef Fi::Fixed<4, 3, Fi::UNSIGNED, Fi::Throw> fi4;
	CHECK_EQ( fi4("0.375"), "0.375" );

}

BOOST_AUTO_TEST_CASE( u_from_string_16 )
{

	typedef Fi::Fixed<16, 15, Fi::UNSIGNED, Fi::Throw> fi16;
	CHECK_EQ( fi16("0.043731689453125"), "0.043731689453125" );

}


BOOST_AUTO_TEST_SUITE_END()
