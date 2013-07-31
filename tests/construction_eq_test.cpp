#include "fi/Fixed.hpp"
#include "fi/overflow/Saturate.hpp"

#define BOOST_TEST_DYN_LINK true
#define BOOST_TEST_MODULE construction
#include <boost/test/unit_test.hpp>

#define CHECK_EQ(A, E) BOOST_CHECK_EQUAL((A).toString(), E)

typedef Fi::Fixed<4, 4, Fi::SIGNED, Fi::Saturate> fi4s;

BOOST_AUTO_TEST_SUITE(construction)

BOOST_AUTO_TEST_CASE( float_construction )
{

	CHECK_EQ(fi4s(1e40), "0.4375");
	CHECK_EQ(fi4s(9.0), "0.4375");
	CHECK_EQ(fi4s(7.9375), "0.4375");
	CHECK_EQ(fi4s(1.0), "0.4375");
	CHECK_EQ(fi4s(.9375), "0.4375");
	CHECK_EQ(fi4s(0.0), "0.0");
	CHECK_EQ(fi4s(-0.0), "0.0");
	CHECK_EQ(fi4s(-1.0), "-0.5");
	CHECK_EQ(fi4s(-7.9375), "-0.5");
	CHECK_EQ(fi4s(-.9375), "-0.5");
	CHECK_EQ(fi4s(-1e40), "-0.5");

	CHECK_EQ(fi4s(1e20f), "0.4375");
	CHECK_EQ(fi4s(9.0f), "0.4375");
	CHECK_EQ(fi4s(7.9375f), "0.4375");
	CHECK_EQ(fi4s(1.0f), "0.4375");
	CHECK_EQ(fi4s(.9375f), "0.4375");
	CHECK_EQ(fi4s(0.0f), "0.0");
	CHECK_EQ(fi4s(-0.0f), "0.0");
	CHECK_EQ(fi4s(-1.0f), "-0.5");
	CHECK_EQ(fi4s(-7.9375f), "-0.5");
	CHECK_EQ(fi4s(-.9375f), "-0.5");
	CHECK_EQ(fi4s(-1e20f), "-0.5");

	CHECK_EQ(fi4s(-0.0782), "-0.0625");
	CHECK_EQ(fi4s( 0.4157),  "0.375" );
	CHECK_EQ(fi4s( 0.2922),  "0.25"  );
	CHECK_EQ(fi4s( 0.4595),  "0.4375");
	CHECK_EQ(fi4s( 0.1557),  "0.125" );
	CHECK_EQ(fi4s(-0.4643), "-0.4375");
	CHECK_EQ(fi4s( 0.3491),  "0.3125");
	CHECK_EQ(fi4s( 0.4340),  "0.375" );
	CHECK_EQ(fi4s( 0.1787),  "0.125" );
	CHECK_EQ(fi4s( 0.2577),  "0.25"  );

	CHECK_EQ(fi4s(-0.0782f), "-0.0625");
	CHECK_EQ(fi4s( 0.4157f),  "0.375" );
	CHECK_EQ(fi4s( 0.2922f),  "0.25"  );
	CHECK_EQ(fi4s( 0.4595f),  "0.4375");
	CHECK_EQ(fi4s( 0.1557f),  "0.125" );
	CHECK_EQ(fi4s(-0.4643f), "-0.4375");
	CHECK_EQ(fi4s( 0.3491f),  "0.3125");
	CHECK_EQ(fi4s( 0.4340f),  "0.375" );
	CHECK_EQ(fi4s( 0.1787f),  "0.125" );
	CHECK_EQ(fi4s( 0.2577f),  "0.25"  );

}


BOOST_AUTO_TEST_CASE( string_construction )
{

	CHECK_EQ(fi4s(""), "0.0");
	CHECK_EQ(fi4s("-0.0"), "0.0");
	CHECK_EQ(fi4s("+0.0"), "0.0");
	CHECK_EQ(fi4s("0.0"), "0.0");
	CHECK_EQ(fi4s("0"), "0.0");
	CHECK_EQ(fi4s("00001.500"), "0.4375");
	CHECK_EQ(fi4s("0.0000"), "0.0");
	CHECK_EQ(fi4s("0000000.0000000000000"), "0.0");
	CHECK_EQ(fi4s("-0000000.0000000000000"), "0.0");
	CHECK_EQ(fi4s("+0000000.0000000000000"), "0.0");
	CHECK_EQ(fi4s("00000000000.1000000000000"), "0.0625");
	CHECK_EQ(fi4s("-00000000000.1000000000000"), "-0.0625");
	CHECK_EQ(fi4s("+00000000000.1000000000000"), "0.0625");
	CHECK_EQ(fi4s(".25"), "0.25");
	CHECK_EQ(fi4s("+.25"), "0.25");
	CHECK_EQ(fi4s("-.25"), "-0.25");
	CHECK_EQ(fi4s("1."), "0.4375");
	CHECK_EQ(fi4s("-1."), "-0.5");
	CHECK_EQ(fi4s("+1."), "0.4375");
	CHECK_EQ(fi4s("-.0"), "0.0");
	CHECK_EQ(fi4s("+.0"), "0.0");
	CHECK_EQ(fi4s("1000000000000000000000000.0"), "0.4375");
	CHECK_EQ(fi4s("-1000000000000000000000000.0"), "-0.5");

	CHECK_EQ(fi4s("-0.0782"), "-0.0625");
	CHECK_EQ(fi4s( "0.4157"),  "0.375" );
	CHECK_EQ(fi4s( "0.2922"),  "0.25"  );
	CHECK_EQ(fi4s( "0.4595"),  "0.4375");
	CHECK_EQ(fi4s( "0.1557"),  "0.125" );
	CHECK_EQ(fi4s("-0.4643"), "-0.4375");
	CHECK_EQ(fi4s( "0.3491"),  "0.3125");
	CHECK_EQ(fi4s( "0.4340"),  "0.375" );
	CHECK_EQ(fi4s( "0.1787"),  "0.125" );
	CHECK_EQ(fi4s( "0.2577"),  "0.25"  );

}


BOOST_AUTO_TEST_CASE( faulty_construction )
{

	BOOST_CHECK_THROW(fi4s("abc"), std::invalid_argument);
	BOOST_CHECK_THROW(fi4s("-c"), std::invalid_argument);
	BOOST_CHECK_THROW(fi4s("+c"), std::invalid_argument);
	BOOST_CHECK_THROW(fi4s("1c"), std::invalid_argument);
	BOOST_CHECK_THROW(fi4s("-1c"), std::invalid_argument);
	BOOST_CHECK_THROW(fi4s("8.0.01"), std::invalid_argument);
	BOOST_CHECK_THROW(fi4s("8..0"), std::invalid_argument);
	BOOST_CHECK_THROW(fi4s("8.+1"), std::invalid_argument);
	BOOST_CHECK_THROW(fi4s("+"), std::invalid_argument);
	BOOST_CHECK_THROW(fi4s("-"), std::invalid_argument);
	BOOST_CHECK_THROW(fi4s(" "), std::invalid_argument);
	BOOST_CHECK_THROW(fi4s(" 1"), std::invalid_argument);
	BOOST_CHECK_THROW(fi4s("1 "), std::invalid_argument);
	BOOST_CHECK_THROW(fi4s("0000000-"), std::invalid_argument);
	BOOST_CHECK_THROW(fi4s("0000000+"), std::invalid_argument);
	BOOST_CHECK_THROW(fi4s("9f"), std::invalid_argument);
	BOOST_CHECK_THROW(fi4s("+9f"), std::invalid_argument);
	BOOST_CHECK_THROW(fi4s("-9f"), std::invalid_argument);
	BOOST_CHECK_THROW(fi4s("+."), std::invalid_argument);
	BOOST_CHECK_THROW(fi4s("-."), std::invalid_argument);
	BOOST_CHECK_THROW(fi4s("."), std::invalid_argument);

}


BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////
