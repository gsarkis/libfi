
#include "fi/Fixed.hpp"
#include "fi/overflow/Saturate.hpp"
#include "fi/overflow/Throw.hpp"
#include "fi/overflow/Wrap.hpp"
#include "fi/rounding/Classic.hpp"

#define BOOST_TEST_DYN_LINK true
#define BOOST_TEST_MODULE Fixed
#include <boost/test/unit_test.hpp>

#define CHECK_EQ(A, E) BOOST_CHECK_EQUAL((A).toString(), E)

typedef Fi::Fixed<8, 4, Fi::SIGNED, Fi::Saturate> fi8s;

BOOST_AUTO_TEST_SUITE(Saturate)
BOOST_AUTO_TEST_CASE( saturate_flp_construction )
{

	CHECK_EQ(fi8s(1e20), "7.9375" );
	CHECK_EQ(fi8s(9.0), "7.9375" );
	CHECK_EQ(fi8s(7.9375), "7.9375");
	CHECK_EQ(fi8s(4.123), "4.0625");
	CHECK_EQ(fi8s(1.0f), "1.0");
	CHECK_EQ(fi8s(0.0), "0.0");
	CHECK_EQ(fi8s(-0.0), "0.0");
	CHECK_EQ(fi8s(-1.0), "-1.0");
	CHECK_EQ(fi8s(-4.123f), "-4.0625");
	CHECK_EQ(fi8s(-8.0), "-8.0");
	CHECK_EQ(fi8s(-9.0), "-8.0");
	CHECK_EQ(fi8s(-1e20), "-8.0");

	CHECK_EQ(fi8s(-0.825705595476718), "-0.8125");
	CHECK_EQ(fi8s(-3.852462095122293), "-3.8125");
	CHECK_EQ(fi8s(-3.216062938684098), "-3.1875");
	CHECK_EQ(fi8s( 6.088384207074370), "6.0625");
	CHECK_EQ(fi8s( 0.832614278826776), "0.8125");
	CHECK_EQ(fi8s( 5.440249449484426), "5.4375");
	CHECK_EQ(fi8s(-6.422742856331885), "-6.375");
	CHECK_EQ(fi8s(-0.457380693528814), "-0.4375");
	CHECK_EQ(fi8s( 7.064531876290451), "7.0625");
	CHECK_EQ(fi8s(-0.628418377612132), "-0.625");

	CHECK_EQ(fi8s(-3.205362909730596), "-3.1875");
	CHECK_EQ(fi8s( 5.950790413457298), "5.9375");
	CHECK_EQ(fi8s(-1.326810404461233), "-1.3125");
	CHECK_EQ(fi8s( 4.881166853660890), "4.875");
	CHECK_EQ(fi8s(-4.139684117154774), "-4.125");
	CHECK_EQ(fi8s(-7.840253558399688), "-7.8125");
	CHECK_EQ(fi8s( 7.672889625019833), "7.625");
	CHECK_EQ(fi8s(-4.475611026624939), "-4.4375");
	CHECK_EQ(fi8s(-6.503440029460585), "-6.5");
	CHECK_EQ(fi8s( 5.605407919033070), "5.5625");

}

BOOST_AUTO_TEST_CASE( saturate_str_construction )
{

	CHECK_EQ(fi8s("1000000000000000000000000.0"), "7.9375");
	CHECK_EQ(fi8s("9.0"), "7.9375" );
	CHECK_EQ(fi8s("7.9375"), "7.9375");
	CHECK_EQ(fi8s("4.123"), "4.0625");
	CHECK_EQ(fi8s("1.0"), "1.0");
	CHECK_EQ(fi8s("0.0"), "0.0");
	CHECK_EQ(fi8s("-0.0"), "0.0");
	CHECK_EQ(fi8s("-1.0"), "-1.0");
	CHECK_EQ(fi8s("-4.123"), "-4.0625");
	CHECK_EQ(fi8s("-8.0"), "-8.0");
	CHECK_EQ(fi8s("-9.0"), "-8.0");

	CHECK_EQ(fi8s("-0.825705595476718"), "-0.8125");
	CHECK_EQ(fi8s("-3.852462095122293"), "-3.8125");
	CHECK_EQ(fi8s("-3.216062938684098"), "-3.1875");
	CHECK_EQ(fi8s( "6.088384207074370"), "6.0625");
	CHECK_EQ(fi8s( "0.832614278826776"), "0.8125");
	CHECK_EQ(fi8s( "5.440249449484426"), "5.4375");
	CHECK_EQ(fi8s("-6.422742856331885"), "-6.375");
	CHECK_EQ(fi8s("-0.457380693528814"), "-0.4375");
	CHECK_EQ(fi8s( "7.064531876290451"), "7.0625");
	CHECK_EQ(fi8s("-0.628418377612132"), "-0.625");

	CHECK_EQ(fi8s("-3.205362909730596"), "-3.1875");
	CHECK_EQ(fi8s( "5.950790413457298"), "5.9375");
	CHECK_EQ(fi8s("-1.326810404461233"), "-1.3125");
	CHECK_EQ(fi8s( "4.881166853660890"), "4.875");
	CHECK_EQ(fi8s("-4.139684117154774"), "-4.125");
	CHECK_EQ(fi8s("-7.840253558399688"), "-7.8125");
	CHECK_EQ(fi8s( "7.672889625019833"), "7.625");
	CHECK_EQ(fi8s("-4.475611026624939"), "-4.4375");
	CHECK_EQ(fi8s("-6.503440029460585"), "-6.5");
	CHECK_EQ(fi8s( "5.605407919033070"), "5.5625");

	BOOST_CHECK_THROW(fi8s("abc"), std::invalid_argument);
	BOOST_CHECK_THROW(fi8s("8.0.01"), std::invalid_argument);

}

BOOST_AUTO_TEST_CASE( saturate_add )
{

	CHECK_EQ(fi8s("1.0") + fi8s("3.0"), "4.0");
	CHECK_EQ(fi8s("3.0") + fi8s("1.0"), "4.0");
	CHECK_EQ(fi8s("6.0") + fi8s("3.0"), "7.9375");
	CHECK_EQ(fi8s("-1.0") + fi8s("3.0"), "2.0");
	CHECK_EQ(fi8s("-5.0") + fi8s("3.0"), "-2.0");
	CHECK_EQ(fi8s("-4.3") + fi8s("3.123"), "-1.1875");
	CHECK_EQ(fi8s("-5.5") + fi8s("-1.25"), "-6.75");
	CHECK_EQ(fi8s("-5.0") + fi8s("-4.0"), "-8.0");

}

BOOST_AUTO_TEST_CASE( saturate_sub )
{

	CHECK_EQ(fi8s("1.24") - fi8s("3.24"), "-2.0");
	CHECK_EQ(fi8s("3.24") - fi8s("1.24"), "2.0");
	CHECK_EQ(fi8s("6.0") - fi8s("-3.0"), "7.9375");
	CHECK_EQ(fi8s("-1.0") - fi8s("3.0"), "-4.0");
	CHECK_EQ(fi8s("-3.0") - fi8s("-5.0"), "2.0");
	CHECK_EQ(fi8s("-4.3") - fi8s("3.123"), "-7.3125");
	CHECK_EQ(fi8s("-5.0") - fi8s("4.0"), "-8.0");

}

BOOST_AUTO_TEST_CASE( saturate_mul )
{
	//Directed
	CHECK_EQ(fi8s("0") * fi8s("6.234"), "0.0");
	CHECK_EQ(fi8s("-1.234") * fi8s("0.0"), "0.0");
	CHECK_EQ(fi8s("-1.125") * fi8s("1.0"), "-1.125");
	CHECK_EQ(fi8s("1.0") * fi8s("1.125"), "1.125");
	CHECK_EQ(fi8s("7.9375") * fi8s("7.9375"), "7.9375");
	CHECK_EQ(fi8s("-8.0") * fi8s("7.9375"), "-8.0");
	CHECK_EQ(fi8s("7.9375") * fi8s("-8.0"), "-8.0");
	CHECK_EQ(fi8s("-8.0") * fi8s("-8.0"), "7.9375");
	//Random
	CHECK_EQ(fi8s("-0.825705595476718") * fi8s("-3.205362909730596"), "2.5625");
	CHECK_EQ(fi8s("-3.852462095122293") * fi8s( "5.950790413457298"), "-8.0");
	CHECK_EQ(fi8s("-3.216062938684098") * fi8s("-1.326810404461233"), "4.125");
	CHECK_EQ(fi8s( "6.088384207074370") * fi8s( "4.881166853660890"), "7.9375");
	CHECK_EQ(fi8s( "0.832614278826776") * fi8s("-4.139684117154774"), "-3.3125");
	CHECK_EQ(fi8s( "5.440249449484426") * fi8s("-7.840253558399688"), "-8.0");
	CHECK_EQ(fi8s("-6.422742856331885") * fi8s( "7.672889625019833"), "-8.0");
	CHECK_EQ(fi8s("-0.457380693528814") * fi8s("-4.475611026624939"), "1.9375");
	CHECK_EQ(fi8s( "7.064531876290451") * fi8s("-6.503440029460585"), "-8.0");
	CHECK_EQ(fi8s("-0.628418377612132") * fi8s( "5.605407919033070"), "-3.4375");

}

BOOST_AUTO_TEST_CASE( saturate_div )
{

	CHECK_EQ(fi8s("0") / fi8s("6.234"), "0.0");
	CHECK_EQ(fi8s("-1.125") / fi8s("1.0"), "-1.125");
	CHECK_EQ(fi8s("6.125") / fi8s("1.0"), "6.125");

	CHECK_EQ(fi8s("-0.825705595476718") / fi8s("-3.205362909730596"), "0.25");
	CHECK_EQ(fi8s("-3.852462095122293") / fi8s( "5.950790413457298"), "-0.625");
	CHECK_EQ(fi8s("-3.216062938684098") / fi8s("-1.326810404461233"), "2.375");
	CHECK_EQ(fi8s( "6.088384207074370") / fi8s( "4.881166853660890"), "1.1875");
	CHECK_EQ(fi8s( "0.832614278826776") / fi8s("-4.139684117154774"), "-0.1875");
	CHECK_EQ(fi8s( "5.440249449484426") / fi8s("-7.840253558399688"), "-0.6875");
	CHECK_EQ(fi8s("-6.422742856331885") / fi8s( "7.672889625019833"), "-0.8125");
	CHECK_EQ(fi8s("-0.457380693528814") / fi8s("-4.475611026624939"), "0.0625");
	CHECK_EQ(fi8s( "7.064531876290451") / fi8s("-6.503440029460585"), "-1.0625");
	CHECK_EQ(fi8s("-0.628418377612132") / fi8s( "5.605407919033070"), "-0.0625");

	CHECK_EQ(fi8s("-4.919283268629641") / fi8s( "5.928424508882099"), "-0.8125");
	CHECK_EQ(fi8s( "6.004846603752069") / fi8s( "3.144192242042575"), "1.875");
	CHECK_EQ(fi8s("-7.705448601940077") / fi8s( "0.541743305247829"), "-8.0");
	CHECK_EQ(fi8s( "5.017179900089733") / fi8s("-4.164916673975533"), "-1.1875");
	CHECK_EQ(fi8s("-7.806926337932302") / fi8s("-1.834076380613423"), "4.25");
	CHECK_EQ(fi8s("-0.076853662774759") / fi8s( "0.807138478562926"), "-0.0625");
	CHECK_EQ(fi8s( "7.430962261645783") / fi8s("-0.653754582998705"), "-8.0");
	CHECK_EQ(fi8s("-1.059170631008655") / fi8s( "1.213895860938496"), "-0.8125");
	CHECK_EQ(fi8s( "4.752718501906477") / fi8s( "6.401310165480160"), "0.6875");
	CHECK_EQ(fi8s( "4.594857847443615") / fi8s("-2.935825738424397"), "-1.5625");

}

//TODO: implement Fix::multLShift
// BOOST_AUTO_TEST_CASE( saturate_mul_shift )
// {
// 	fi8s a("0");
// 	fi8s b("6.234");
// 	CHECK_EQ(a.multLShift(b, 0), "0.0");
// }

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////

typedef Fi::Fixed<8, 4, Fi::SIGNED, Fi::Saturate, Fi::Classic> fi8sCl;

BOOST_AUTO_TEST_SUITE(Saturate_Classic)
BOOST_AUTO_TEST_CASE( sat_classic_fp_construction )
{
	CHECK_EQ(fi8sCl(1e20), "7.9375" );
	CHECK_EQ(fi8sCl(9.0), "7.9375" );
	CHECK_EQ(fi8sCl(7.9375), "7.9375");	
	CHECK_EQ(fi8sCl(4.123), "4.125");
	CHECK_EQ(fi8sCl(1.0f), "1.0");
	CHECK_EQ(fi8sCl(0.0), "0.0");
	CHECK_EQ(fi8sCl(-0.0), "0.0");
	CHECK_EQ(fi8sCl(-1.0), "-1.0");
	CHECK_EQ(fi8sCl(-4.123f), "-4.125");
	CHECK_EQ(fi8sCl(-8.0), "-8.0");
	CHECK_EQ(fi8sCl(-9.0), "-8.0");
	CHECK_EQ(fi8sCl(-1e20), "-8.0");
}

BOOST_AUTO_TEST_CASE( saturate_mul_shift )
{
	// Directed
	CHECK_EQ(multLShift(fi8sCl("0"),fi8sCl("6.234"), 0), "0.0");
	BOOST_CHECK_THROW(multLShift(fi8sCl("0"),fi8sCl("6.234"), -1),
	                  std::runtime_error);
	BOOST_CHECK_THROW(multLShift(fi8sCl("0"),fi8sCl("6.234"), 5),
	                  std::runtime_error);
	CHECK_EQ(multLShift(fi8sCl("0"),fi8sCl("6.234"), 2), "0.0");

	CHECK_EQ(multLShift(fi8sCl("1.0"),fi8sCl("1.125"), 0), "1.125");
	CHECK_EQ(multLShift(fi8sCl("1.0"),fi8sCl("1.125"), 1), "2.25");
	CHECK_EQ(multLShift(fi8sCl("0.5"),fi8sCl("0.0625"),0), "0.0625");
	CHECK_EQ(multLShift(fi8sCl("0.5"),fi8sCl("0.0625"),1), "0.0625");
	CHECK_EQ(multLShift(fi8sCl("0.25"),fi8sCl("0.0625"),0), "0.0");
	CHECK_EQ(multLShift(fi8sCl("0.25"),fi8sCl("0.0625"),1), "0.0625");
	CHECK_EQ(multLShift(fi8sCl("0.25"),fi8sCl("0.0625"),2), "0.0625");
	CHECK_EQ(multLShift(fi8sCl("1.5"),fi8sCl("0.0625"),0), "0.125");	
	CHECK_EQ(multLShift(fi8sCl("1.5"),fi8sCl("0.0625"),1), "0.1875");

	CHECK_EQ(multLShift(fi8sCl("-1.0"),fi8sCl("1.125"), 0), "-1.125");
	CHECK_EQ(multLShift(fi8sCl("-1.0"),fi8sCl("1.125"), 1), "-2.25");
	CHECK_EQ(multLShift(fi8sCl("-0.5"),fi8sCl("0.0625"),0), "-0.0625");
	CHECK_EQ(multLShift(fi8sCl("-0.5"),fi8sCl("0.0625"),1), "-0.0625");	
	CHECK_EQ(multLShift(fi8sCl("-0.25"),fi8sCl("0.0625"),0), "0.0");
	CHECK_EQ(multLShift(fi8sCl("-0.25"),fi8sCl("0.0625"),1), "-0.0625");
	CHECK_EQ(multLShift(fi8sCl("-0.25"),fi8sCl("0.0625"),2), "-0.0625");
	CHECK_EQ(multLShift(fi8sCl("-1.5"),fi8sCl("0.0625"),0), "-0.125");	
	CHECK_EQ(multLShift(fi8sCl("-1.5"),fi8sCl("0.0625"),1), "-0.1875");

	CHECK_EQ(multLShift(fi8sCl("7.9375"),fi8sCl("7.9375"), 0), "7.9375");
	CHECK_EQ(multLShift(fi8sCl("7.9375"),fi8sCl("7.9375"), 1), "7.9375");
	CHECK_EQ(multLShift(fi8sCl("7.9375"),fi8sCl("7.9375"), 2), "7.9375");
	CHECK_EQ(multLShift(fi8sCl("7.9375"),fi8sCl("7.9375"), 3), "7.9375");
	CHECK_EQ(multLShift(fi8sCl("7.9375"),fi8sCl("7.9375"), 4), "7.9375");
	
	CHECK_EQ(multLShift(fi8sCl("-8.0"),fi8sCl("7.9375"), 0), "-8.0");
	CHECK_EQ(multLShift(fi8sCl("-8.0"),fi8sCl("7.9375"), 1), "-8.0");
	CHECK_EQ(multLShift(fi8sCl("-8.0"),fi8sCl("7.9375"), 2), "-8.0");
	CHECK_EQ(multLShift(fi8sCl("-8.0"),fi8sCl("7.9375"), 3), "-8.0");
	CHECK_EQ(multLShift(fi8sCl("-8.0"),fi8sCl("7.9375"), 4), "-8.0");

	CHECK_EQ(multLShift(fi8sCl("-8.0"),fi8sCl("-8.0"), 0), "7.9375");
	CHECK_EQ(multLShift(fi8sCl("-8.0"),fi8sCl("-8.0"), 1), "7.9375");
	CHECK_EQ(multLShift(fi8sCl("-8.0"),fi8sCl("-8.0"), 2), "7.9375");
	CHECK_EQ(multLShift(fi8sCl("-8.0"),fi8sCl("-8.0"), 3), "7.9375");
	CHECK_EQ(multLShift(fi8sCl("-8.0"),fi8sCl("-8.0"), 4), "7.9375");

	// Semi-Random
	CHECK_EQ(multLShift(fi8sCl("-0.825705595476718"),fi8sCl("-3.205362909730596"),0),
	         "2.5625");
	CHECK_EQ(multLShift(fi8sCl("-0.8125"),fi8sCl("-3.1875"),1), "5.1875");
	CHECK_EQ(multLShift(fi8sCl("-0.8125"),fi8sCl("-3.1875"),2), "7.9375");
	CHECK_EQ(multLShift(fi8sCl("-0.8125"),fi8sCl("-3.1875"),3), "7.9375");
	CHECK_EQ(multLShift(fi8sCl("-0.8125"),fi8sCl("-3.1875"),4), "7.9375");

	CHECK_EQ(multLShift(fi8sCl("0.4375"),fi8sCl("-4.5"),0), "-2.0");
	CHECK_EQ(multLShift(fi8sCl("0.4375"),fi8sCl("-4.5"),1), "-3.9375");
	CHECK_EQ(multLShift(fi8sCl("0.4375"),fi8sCl("-4.5"),2), "-7.875");
	CHECK_EQ(multLShift(fi8sCl("0.4375"),fi8sCl("-4.5"),3), "-8.0");
}

BOOST_AUTO_TEST_SUITE_END()
	
////////////////////////////////////////////////////////////////////////////////
	
typedef Fi::Fixed<8, 4, Fi::SIGNED, Fi::Wrap> fi8w;

BOOST_AUTO_TEST_SUITE(Wrap)

BOOST_AUTO_TEST_CASE( wrap_flp_construction )
{

	CHECK_EQ(fi8w(1e20), "0.0" );
	CHECK_EQ(fi8w(9.0), "-7.0");
	CHECK_EQ(fi8w(7.9375), "7.9375");
	CHECK_EQ(fi8w(4.123), "4.0625");
	CHECK_EQ(fi8w(1.0f), "1.0");
	CHECK_EQ(fi8w(0.0), "0.0");
	CHECK_EQ(fi8w(-0.0), "0.0");
	CHECK_EQ(fi8w(-1.0), "-1.0");
	CHECK_EQ(fi8w(-4.123f), "-4.0625");
	CHECK_EQ(fi8w(-8.0), "-8.0");
	CHECK_EQ(fi8w(-9.0), "7.0");

	CHECK_EQ(fi8w(-0.825705595476718), "-0.8125");
	CHECK_EQ(fi8w(-3.852462095122293), "-3.8125");
	CHECK_EQ(fi8w(-3.216062938684098), "-3.1875");
	CHECK_EQ(fi8w(6.088384207074370), "6.0625");
	CHECK_EQ(fi8w(0.832614278826776), "0.8125");
	CHECK_EQ(fi8w(5.440249449484426), "5.4375");
	CHECK_EQ(fi8w(-6.422742856331885), "-6.375");
	CHECK_EQ(fi8w(-0.457380693528814), "-0.4375");
	CHECK_EQ(fi8w(7.064531876290451), "7.0625");
	CHECK_EQ(fi8w(-0.628418377612132), "-0.625");


	CHECK_EQ(fi8w(-3.205362909730596), "-3.1875");
	CHECK_EQ(fi8w(5.950790413457298), "5.9375");
	CHECK_EQ(fi8w(-1.326810404461233), "-1.3125");
	CHECK_EQ(fi8w(4.881166853660890), "4.875");
	CHECK_EQ(fi8w(-4.139684117154774), "-4.125");
	CHECK_EQ(fi8w(-7.840253558399688), "-7.8125");
	CHECK_EQ(fi8w(7.672889625019833), "7.625");
	CHECK_EQ(fi8w(-4.475611026624939), "-4.4375");
	CHECK_EQ(fi8w(-6.503440029460585), "-6.5");
	CHECK_EQ(fi8w(5.605407919033070), "5.5625");

}

BOOST_AUTO_TEST_CASE( wrap_str_construction )
{

	CHECK_EQ(fi8w("1000000000000000000000000.0"), "0.0");
	CHECK_EQ(fi8w("9.0"), "-7.0");
	CHECK_EQ(fi8w("7.9375"), "7.9375");
	CHECK_EQ(fi8w("4.123"), "4.0625");
	CHECK_EQ(fi8w("1.0"), "1.0");
	CHECK_EQ(fi8w("0.0"), "0.0");
	CHECK_EQ(fi8w("-0.0"), "0.0");
	CHECK_EQ(fi8w("-1.0"), "-1.0");
	CHECK_EQ(fi8w("-4.123"), "-4.0625");
	CHECK_EQ(fi8w("-8.0"), "-8.0");
	CHECK_EQ(fi8w("-9.0"), "7.0");

	CHECK_EQ(fi8w("-0.825705595476718"), "-0.8125");
	CHECK_EQ(fi8w("-3.852462095122293"), "-3.8125");
	CHECK_EQ(fi8w("-3.216062938684098"), "-3.1875");
	CHECK_EQ(fi8w( "6.088384207074370"), "6.0625");
	CHECK_EQ(fi8w( "0.832614278826776"), "0.8125");
	CHECK_EQ(fi8w( "5.440249449484426"), "5.4375");
	CHECK_EQ(fi8w("-6.422742856331885"), "-6.375");
	CHECK_EQ(fi8w("-0.457380693528814"), "-0.4375");
	CHECK_EQ(fi8w( "7.064531876290451"), "7.0625");
	CHECK_EQ(fi8w("-0.628418377612132"), "-0.625");


	CHECK_EQ(fi8w("-3.205362909730596"), "-3.1875");
	CHECK_EQ(fi8w( "5.950790413457298"), "5.9375");
	CHECK_EQ(fi8w("-1.326810404461233"), "-1.3125");
	CHECK_EQ(fi8w("4.881166853660890"), "4.875");
	CHECK_EQ(fi8w("-4.139684117154774"), "-4.125");
	CHECK_EQ(fi8w("-7.840253558399688"), "-7.8125");
	CHECK_EQ(fi8w( "7.672889625019833"), "7.625");
	CHECK_EQ(fi8w("-4.475611026624939"), "-4.4375");
	CHECK_EQ(fi8w("-6.503440029460585"), "-6.5");
	CHECK_EQ(fi8w( "5.605407919033070"), "5.5625");

	BOOST_CHECK_THROW(fi8w("abc"), std::invalid_argument);
	BOOST_CHECK_THROW(fi8w("8.0.01"), std::invalid_argument);

}

BOOST_AUTO_TEST_CASE( wrap_add )
{
	CHECK_EQ(fi8w("1.0") + fi8w("3.0"), "4.0");
	CHECK_EQ(fi8w("3.0") + fi8w("1.0"), "4.0");
	CHECK_EQ(fi8w("6.0") + fi8w("3.0"), "-7.0");
	CHECK_EQ(fi8w("-1.0") + fi8w("3.0"), "2.0");
	CHECK_EQ(fi8w("-5.0") + fi8w("3.0"), "-2.0");
	CHECK_EQ(fi8w("-4.3") + fi8w("3.123"), "-1.1875");
	CHECK_EQ(fi8w("-5.5") + fi8w("-1.25"), "-6.75");
	CHECK_EQ(fi8w("-5.0") + fi8w("-4.0"), "7.0");

}

BOOST_AUTO_TEST_CASE( wrap_sub )
{

	CHECK_EQ(fi8w("1.24") - fi8w("3.24"), "-2.0");
	CHECK_EQ(fi8w("3.24") - fi8w("1.24"), "2.0");
	CHECK_EQ(fi8w("6.0") - fi8w("-3.0"), "-7.0");
	CHECK_EQ(fi8w("-1.0") - fi8w("3.0"), "-4.0");
	CHECK_EQ(fi8w("-3.0") - fi8w("-5.0"), "2.0");
	CHECK_EQ(fi8w("-4.3") - fi8w("3.123"), "-7.3125");
	CHECK_EQ(fi8w("-5.0") - fi8w("4.0"), "7.0");

}

BOOST_AUTO_TEST_CASE( wrap_mul )
{

	//directed
	CHECK_EQ(fi8w("7.9375") * fi8w("7.9375"), "-1.0");
	CHECK_EQ(fi8w("-8.0") * fi8w("7.9375"), "0.5");
	CHECK_EQ(fi8w("7.9375") * fi8w("-8.0"), "0.5");
	CHECK_EQ(fi8w("-8.0") * fi8w("-8.0"), "0.0");
	//random
	CHECK_EQ(fi8w("-0.825705595476718") * fi8w("-3.205362909730596"), "2.5625");
	CHECK_EQ(fi8w("-3.852462095122293") * fi8w( "5.950790413457298"), "-6.625");
	CHECK_EQ(fi8w("-3.216062938684098") * fi8w("-1.326810404461233"), "4.125");
	CHECK_EQ(fi8w( "6.088384207074370") * fi8w( "4.881166853660890"), "-2.5");
	CHECK_EQ(fi8w( "0.832614278826776") * fi8w("-4.139684117154774"), "-3.3125");
	CHECK_EQ(fi8w( "5.440249449484426") * fi8w("-7.840253558399688"), "5.5625");
	CHECK_EQ(fi8w("-6.422742856331885") * fi8w( "7.672889625019833"), "-0.5625");
	CHECK_EQ(fi8w("-0.457380693528814") * fi8w("-4.475611026624939"), "1.9375");
	CHECK_EQ(fi8w( "7.064531876290451") * fi8w("-6.503440029460585"), "2.125");
	CHECK_EQ(fi8w("-0.628418377612132") * fi8w( "5.605407919033070"), "-3.4375");

}

BOOST_AUTO_TEST_CASE( wrap_div )
{

	CHECK_EQ(fi8w("0") / fi8w("6.234"), "0.0");
	CHECK_EQ(fi8w("-1.125") / fi8w("1.0"), "-1.125");
	CHECK_EQ(fi8w("6.125") / fi8w("1.0"), "6.125");

	CHECK_EQ(fi8w("-0.825705595476718") / fi8w("-3.205362909730596"), "0.25");
	CHECK_EQ(fi8w("-3.852462095122293") / fi8w( "5.950790413457298"), "-0.625");
	CHECK_EQ(fi8w("-3.216062938684098") / fi8w("-1.326810404461233"), "2.375");
	CHECK_EQ(fi8w( "6.088384207074370") / fi8w( "4.881166853660890"), "1.1875");
	CHECK_EQ(fi8w( "0.832614278826776") / fi8w("-4.139684117154774"), "-0.1875");
	CHECK_EQ(fi8w( "5.440249449484426") / fi8w("-7.840253558399688"), "-0.6875");
	CHECK_EQ(fi8w("-6.422742856331885") / fi8w( "7.672889625019833"), "-0.8125");
	CHECK_EQ(fi8w("-0.457380693528814") / fi8w("-4.475611026624939"), "0.0625");
	CHECK_EQ(fi8w( "7.064531876290451") / fi8w("-6.503440029460585"), "-1.0625");
	CHECK_EQ(fi8w("-0.628418377612132") / fi8w( "5.605407919033070"), "-0.0625");

	CHECK_EQ(fi8w("-4.919283268629641") / fi8w( "5.928424508882099"), "-0.8125");
	CHECK_EQ(fi8w( "6.004846603752069") / fi8w( "3.144192242042575"), "1.875");
	CHECK_EQ(fi8w("-7.705448601940077") / fi8w( "0.541743305247829"), "0.625");
	CHECK_EQ(fi8w( "5.017179900089733") / fi8w("-4.164916673975533"), "-1.1875");
	CHECK_EQ(fi8w("-7.806926337932302") / fi8w("-1.834076380613423"), "4.25");
	CHECK_EQ(fi8w("-0.076853662774759") / fi8w( "0.807138478562926"), "-0.0625");
	CHECK_EQ(fi8w( "7.430962261645783") / fi8w("-0.653754582998705"), "4.25");
	CHECK_EQ(fi8w("-1.059170631008655") / fi8w( "1.213895860938496"), "-0.8125");
	CHECK_EQ(fi8w( "4.752718501906477") / fi8w( "6.401310165480160"), "0.6875");
	CHECK_EQ(fi8w( "4.594857847443615") / fi8w("-2.935825738424397"), "-1.5625");

}

BOOST_AUTO_TEST_SUITE_END()


////////////////////////////////////////////////////////////////////////////////

typedef Fi::Fixed<8, 4, Fi::SIGNED, Fi::Throw> fi8of;

BOOST_AUTO_TEST_SUITE(Throw)
BOOST_AUTO_TEST_CASE( overflowexception_flp_construction )
{

	BOOST_CHECK_THROW(fi8of(1e20), std::overflow_error);
	BOOST_CHECK_THROW(fi8of(9.0), std::overflow_error);
	CHECK_EQ(fi8of(7.9375), "7.9375");
	CHECK_EQ(fi8of(4.123), "4.0625");
	CHECK_EQ(fi8of(1.0f), "1.0");
	CHECK_EQ(fi8of(0.0), "0.0");
	CHECK_EQ(fi8of(-0.0), "0.0");
	CHECK_EQ(fi8of(-1.0), "-1.0");
	CHECK_EQ(fi8of(-4.123f), "-4.0625");
	CHECK_EQ(fi8of(-8.0), "-8.0");
	BOOST_CHECK_THROW(fi8of(-9.0), std::overflow_error);
	BOOST_CHECK_THROW(fi8of(-1e20), std::overflow_error);

	CHECK_EQ(fi8of(-0.825705595476718), "-0.8125");
	CHECK_EQ(fi8of(-3.852462095122293), "-3.8125");
	CHECK_EQ(fi8of(-3.216062938684098), "-3.1875");
	CHECK_EQ(fi8of( 6.088384207074370), "6.0625");
	CHECK_EQ(fi8of( 0.832614278826776), "0.8125");
	CHECK_EQ(fi8of( 5.440249449484426), "5.4375");
	CHECK_EQ(fi8of(-6.422742856331885), "-6.375");
	CHECK_EQ(fi8of(-0.457380693528814), "-0.4375");
	CHECK_EQ(fi8of( 7.064531876290451), "7.0625");
	CHECK_EQ(fi8of(-0.628418377612132), "-0.625");

	CHECK_EQ(fi8of(-3.205362909730596), "-3.1875");
	CHECK_EQ(fi8of( 5.950790413457298), "5.9375");
	CHECK_EQ(fi8of(-1.326810404461233), "-1.3125");
	CHECK_EQ(fi8of( 4.881166853660890), "4.875");
	CHECK_EQ(fi8of(-4.139684117154774), "-4.125");
	CHECK_EQ(fi8of(-7.840253558399688), "-7.8125");
	CHECK_EQ(fi8of( 7.672889625019833), "7.625");
	CHECK_EQ(fi8of(-4.475611026624939), "-4.4375");
	CHECK_EQ(fi8of(-6.503440029460585), "-6.5");
	CHECK_EQ(fi8of( 5.605407919033070), "5.5625");

}

BOOST_AUTO_TEST_CASE( overflowexception_str_construction )
{

	BOOST_CHECK_THROW(fi8of("1000000000000000000000000.0"), std::overflow_error);
	BOOST_CHECK_THROW(fi8of("9.0"), std::overflow_error);
	CHECK_EQ(fi8of("7.9375"), "7.9375");
	CHECK_EQ(fi8of("4.123"), "4.0625");
	CHECK_EQ(fi8of("1.0"), "1.0");
	CHECK_EQ(fi8of("0.0"), "0.0");
	CHECK_EQ(fi8of("-0.0"), "0.0");
	CHECK_EQ(fi8of("-1.0"), "-1.0");
	CHECK_EQ(fi8of("-4.123"), "-4.0625");
	CHECK_EQ(fi8of("-8.0"), "-8.0");
	BOOST_CHECK_THROW(fi8of("-9.0"), std::overflow_error);

	CHECK_EQ(fi8of("-0.825705595476718"), "-0.8125");
	CHECK_EQ(fi8of("-3.852462095122293"), "-3.8125");
	CHECK_EQ(fi8of("-3.216062938684098"), "-3.1875");
	CHECK_EQ(fi8of( "6.088384207074370"), "6.0625");
	CHECK_EQ(fi8of( "0.832614278826776"), "0.8125");
	CHECK_EQ(fi8of( "5.440249449484426"), "5.4375");
	CHECK_EQ(fi8of("-6.422742856331885"), "-6.375");
	CHECK_EQ(fi8of("-0.457380693528814"), "-0.4375");
	CHECK_EQ(fi8of( "7.064531876290451"), "7.0625");
	CHECK_EQ(fi8of("-0.628418377612132"), "-0.625");

	CHECK_EQ(fi8of("-3.205362909730596"), "-3.1875");
	CHECK_EQ(fi8of( "5.950790413457298"), "5.9375");
	CHECK_EQ(fi8of("-1.326810404461233"), "-1.3125");
	CHECK_EQ(fi8of( "4.881166853660890"), "4.875");
	CHECK_EQ(fi8of("-4.139684117154774"), "-4.125");
	CHECK_EQ(fi8of("-7.840253558399688"), "-7.8125");
	CHECK_EQ(fi8of( "7.672889625019833"), "7.625");
	CHECK_EQ(fi8of("-4.475611026624939"), "-4.4375");
	CHECK_EQ(fi8of("-6.503440029460585"), "-6.5");
	CHECK_EQ(fi8of( "5.605407919033070"), "5.5625");

	BOOST_CHECK_THROW(fi8of("abc"), std::invalid_argument);
	BOOST_CHECK_THROW(fi8of("8.0.01"), std::invalid_argument);

}

BOOST_AUTO_TEST_CASE( overflowexception_add )
{

	CHECK_EQ(fi8of("1.0") + fi8of("3.0"), "4.0");
	CHECK_EQ(fi8of("3.0") + fi8of("1.0"), "4.0");
	BOOST_CHECK_THROW(fi8of("6.0") + fi8of("3.0"), std::overflow_error);
	CHECK_EQ(fi8of("-1.0") + fi8of("3.0"), "2.0");
	CHECK_EQ(fi8of("-5.0") + fi8of("3.0"), "-2.0");
	CHECK_EQ(fi8of("-4.3") + fi8of("3.123"), "-1.1875");
	CHECK_EQ(fi8of("-5.5") + fi8of("-1.25"), "-6.75");
	BOOST_CHECK_THROW(fi8of("-5.0") + fi8of("-4.0"), std::overflow_error);

}

BOOST_AUTO_TEST_CASE( overflowexception_sub )
{

	CHECK_EQ(fi8of("1.24") - fi8of("3.24"), "-2.0");
	CHECK_EQ(fi8of("3.24") - fi8of("1.24"), "2.0");
	BOOST_CHECK_THROW(fi8of("6.0") - fi8of("-3.0"), std::overflow_error);
	CHECK_EQ(fi8of("-1.0") - fi8of("3.0"), "-4.0");
	CHECK_EQ(fi8of("-3.0") - fi8of("-5.0"), "2.0");
	CHECK_EQ(fi8of("-4.3") - fi8of("3.123"), "-7.3125");
	BOOST_CHECK_THROW(fi8of("-5.0") - fi8of("4.0"), std::overflow_error);

}

BOOST_AUTO_TEST_CASE( overflowexception_mul )
{
	//Directed
	CHECK_EQ(fi8of("0") * fi8of("6.234"), "0.0");
	CHECK_EQ(fi8of("-1.234") * fi8of("0.0"), "0.0");
	CHECK_EQ(fi8of("-1.125") * fi8of("1.0"), "-1.125");
	CHECK_EQ(fi8of("1.0") * fi8of("1.125"), "1.125");
	BOOST_CHECK_THROW(fi8of("7.9375") * fi8of("7.9375"), std::overflow_error);
	BOOST_CHECK_THROW(fi8of("-8.0") * fi8of("7.9375"), std::overflow_error);
	BOOST_CHECK_THROW(fi8of("7.9375") * fi8of("-8.0"), std::overflow_error);
	BOOST_CHECK_THROW(fi8of("-8.0") * fi8of("-8.0"), std::overflow_error);
	//Random
	CHECK_EQ(fi8of("-0.825705595476718") * fi8of("-3.205362909730596"), "2.5625");
	BOOST_CHECK_THROW(fi8of("-3.852462095122293") * fi8of( "5.950790413457298"), std::overflow_error);
	CHECK_EQ(fi8of("-3.216062938684098") * fi8of("-1.326810404461233"), "4.125");
	BOOST_CHECK_THROW(fi8of( "6.088384207074370") * fi8of( "4.881166853660890"), std::overflow_error);
	CHECK_EQ(fi8of( "0.832614278826776") * fi8of("-4.139684117154774"), "-3.3125");
	BOOST_CHECK_THROW(fi8of( "5.440249449484426") * fi8of("-7.840253558399688"), std::overflow_error);
	BOOST_CHECK_THROW(fi8of("-6.422742856331885") * fi8of( "7.672889625019833"), std::overflow_error);
	CHECK_EQ(fi8of("-0.457380693528814") * fi8of("-4.475611026624939"), "1.9375");
	BOOST_CHECK_THROW(fi8of( "7.064531876290451") * fi8of("-6.503440029460585"), std::overflow_error);
	CHECK_EQ(fi8of("-0.628418377612132") * fi8of( "5.605407919033070"), "-3.4375");

}

BOOST_AUTO_TEST_CASE( overflowexception_div )
{

	CHECK_EQ(fi8of("0") / fi8of("6.234"), "0.0");
	CHECK_EQ(fi8of("-1.125") / fi8of("1.0"), "-1.125");
	CHECK_EQ(fi8of("6.125") / fi8of("1.0"), "6.125");

	CHECK_EQ(fi8of("-0.825705595476718") / fi8of("-3.205362909730596"), "0.25");
	CHECK_EQ(fi8of("-3.852462095122293") / fi8of( "5.950790413457298"), "-0.625");
	CHECK_EQ(fi8of("-3.216062938684098") / fi8of("-1.326810404461233"), "2.375");
	CHECK_EQ(fi8of( "6.088384207074370") / fi8of( "4.881166853660890"), "1.1875");
	CHECK_EQ(fi8of( "0.832614278826776") / fi8of("-4.139684117154774"), "-0.1875");
	CHECK_EQ(fi8of( "5.440249449484426") / fi8of("-7.840253558399688"), "-0.6875");
	CHECK_EQ(fi8of("-6.422742856331885") / fi8of( "7.672889625019833"), "-0.8125");
	CHECK_EQ(fi8of("-0.457380693528814") / fi8of("-4.475611026624939"), "0.0625");
	CHECK_EQ(fi8of( "7.064531876290451") / fi8of("-6.503440029460585"), "-1.0625");
	CHECK_EQ(fi8of("-0.628418377612132") / fi8of( "5.605407919033070"), "-0.0625");

	CHECK_EQ(fi8of("-4.919283268629641") / fi8of( "5.928424508882099"), "-0.8125");
	CHECK_EQ(fi8of( "6.004846603752069") / fi8of( "3.144192242042575"), "1.875");
	BOOST_CHECK_THROW(fi8of("-7.705448601940077") / fi8of( "0.541743305247829"), std::overflow_error);
	CHECK_EQ(fi8of( "5.017179900089733") / fi8of("-4.164916673975533"), "-1.1875");
	CHECK_EQ(fi8of("-7.806926337932302") / fi8of("-1.834076380613423"), "4.25");
	CHECK_EQ(fi8of("-0.076853662774759") / fi8of( "0.807138478562926"), "-0.0625");
	BOOST_CHECK_THROW(fi8of( "7.430962261645783") / fi8of("-0.653754582998705"), std::overflow_error);
	CHECK_EQ(fi8of("-1.059170631008655") / fi8of( "1.213895860938496"), "-0.8125");
	CHECK_EQ(fi8of( "4.752718501906477") / fi8of( "6.401310165480160"), "0.6875");
	CHECK_EQ(fi8of( "4.594857847443615") / fi8of("-2.935825738424397"), "-1.5625");

}

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////
