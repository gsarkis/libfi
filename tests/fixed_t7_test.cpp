#include "fi/Fixed.hpp"
#include "fi/overflow/Saturate.hpp"
#include "fi/overflow/Throw.hpp"
#include "fi/overflow/Wrap.hpp"

#define BOOST_TEST_DYN_LINK true
#define BOOST_TEST_MODULE Fixed
#include <boost/test/unit_test.hpp>

#define CHECK_EQ(A, E) BOOST_CHECK_EQUAL((A).toString(), E)

typedef Fi::Fixed<7, 3, Fi::SIGNED, Fi::Saturate> fi7s;

BOOST_AUTO_TEST_SUITE(Fi_7_Saturate)
BOOST_AUTO_TEST_CASE( saturate_flp_construction )
{

  CHECK_EQ(fi7s(1e20), "7.875");
  CHECK_EQ(fi7s(9.0), "7.875");
  CHECK_EQ(fi7s(7.9375), "7.875");
  CHECK_EQ(fi7s(4.123), "4.0");
  CHECK_EQ(fi7s(1.0f), "1.0");
  CHECK_EQ(fi7s(0.0), "0.0");
  CHECK_EQ(fi7s(-0.0), "0.0");
  CHECK_EQ(fi7s(-1.0), "-1.0");
  CHECK_EQ(fi7s(-4.123f), "-4.0");
  CHECK_EQ(fi7s(-8.0), "-8.0");
  CHECK_EQ(fi7s(-9.0), "-8.0");
  CHECK_EQ(fi7s(-1e20), "-8.0");

}

BOOST_AUTO_TEST_CASE( saturate_str_construction )
{

  CHECK_EQ(fi7s("1000000000000000000000000.0"), "7.875");
  CHECK_EQ(fi7s("9.0"), "7.875");
  CHECK_EQ(fi7s("7.9375"), "7.875");
  CHECK_EQ(fi7s("4.123"), "4.0");
  CHECK_EQ(fi7s("1.0"), "1.0");
  CHECK_EQ(fi7s("0.0"), "0.0");
  CHECK_EQ(fi7s("-0.0"), "0.0");
  CHECK_EQ(fi7s("-1.0"), "-1.0");
  CHECK_EQ(fi7s("-4.123"), "-4.0");
  CHECK_EQ(fi7s("-8.0"), "-8.0");
  CHECK_EQ(fi7s("-9.0"), "-8.0");

  BOOST_CHECK_THROW(fi7s("abc"), std::invalid_argument);
  BOOST_CHECK_THROW(fi7s("8.0.01"), std::invalid_argument);

}

BOOST_AUTO_TEST_CASE( saturate_add )
{

  CHECK_EQ(fi7s("1.0") + fi7s("3.0"), "4.0");
  CHECK_EQ(fi7s("3.0") + fi7s("1.0"), "4.0");
  CHECK_EQ(fi7s("6.0") + fi7s("3.0"), "7.875");
  CHECK_EQ(fi7s("-1.0") + fi7s("3.0"), "2.0");
  CHECK_EQ(fi7s("-5.0") + fi7s("3.0"), "-2.0");
  CHECK_EQ(fi7s("-4.3") + fi7s("3.123"), "-1.25");
  CHECK_EQ(fi7s("-5.5") + fi7s("-1.25"), "-6.75");
  CHECK_EQ(fi7s("-5.0") + fi7s("-4.0"), "-8.0");

}

BOOST_AUTO_TEST_CASE( saturate_sub )
{

  CHECK_EQ(fi7s("1.24") - fi7s("3.24"), "-2.0");
  CHECK_EQ(fi7s("3.24") - fi7s("1.24"), "2.0");
  CHECK_EQ(fi7s("6.0") - fi7s("-3.0"), "7.875");
  CHECK_EQ(fi7s("-1.0") - fi7s("3.0"), "-4.0");
  CHECK_EQ(fi7s("-3.0") - fi7s("-5.0"), "2.0");
  CHECK_EQ(fi7s("-4.3") - fi7s("3.123"), "-7.25");
  CHECK_EQ(fi7s("-5.0") - fi7s("4.0"), "-8.0");

}

BOOST_AUTO_TEST_CASE( saturate_mul )
{
  //Directed
  CHECK_EQ(fi7s("0") * fi7s("6.234"), "0.0");
  CHECK_EQ(fi7s("-1.234") * fi7s("0.0"), "0.0");
  CHECK_EQ(fi7s("-1.125") * fi7s("1.0"), "-1.125");
  CHECK_EQ(fi7s("1.0") * fi7s("1.125"), "1.125");
  CHECK_EQ(fi7s("100") * fi7s("-100"), "-8.0");
  CHECK_EQ(fi7s("-100") * fi7s("100"), "-8.0");
  CHECK_EQ(fi7s("100") * fi7s("100"), "7.875");
  CHECK_EQ(fi7s("-100") * fi7s("-100"), "7.875");
  //Random
  CHECK_EQ(fi7s("-0.825705595476718") * fi7s("-3.205362909730596"), "2.25");
  CHECK_EQ(fi7s("-3.852462095122293") * fi7s( "5.950790413457298"), "-8.0");
  CHECK_EQ(fi7s("-3.216062938684098") * fi7s("-1.326810404461233"), "3.875");
  CHECK_EQ(fi7s( "6.088384207074370") * fi7s("4.881166853660890"), "7.875");
  CHECK_EQ(fi7s( "0.832614278826776") * fi7s("-4.139684117154774"), "-3.0");
  CHECK_EQ(fi7s( "5.440249449484426") * fi7s("-7.840253558399688"), "-8.0");
  CHECK_EQ(fi7s("-6.422742856331885") * fi7s( "7.672889625019833"), "-8.0");
  CHECK_EQ(fi7s("-0.457380693528814") * fi7s("-4.475611026624939"), "1.625");
  CHECK_EQ(fi7s( "7.064531876290451") * fi7s("-6.503440029460585"), "-8.0");
  CHECK_EQ(fi7s("-0.628418377612132") * fi7s( "5.605407919033070"), "-3.375");

}

BOOST_AUTO_TEST_CASE( saturate_div )
{

  CHECK_EQ(fi7s("0") / fi7s("6.234"), "0.0");
  CHECK_EQ(fi7s("-1.125") / fi7s("1.0"), "-1.125");
  CHECK_EQ(fi7s("6.125") / fi7s("1.0"), "6.125");

  CHECK_EQ(fi7s("-4.919283268629641") / fi7s( "5.928424508882099"), "-0.75");
  CHECK_EQ(fi7s( "6.004846603752069") / fi7s( "3.144192242042575"), "1.875" );
  CHECK_EQ(fi7s("-7.705448601940077") / fi7s( "0.541743305247829"), "-8.0"  );
  CHECK_EQ(fi7s( "5.017179900089733") / fi7s("-4.164916673975533"), "-1.125");
  CHECK_EQ(fi7s("-7.806926337932302") / fi7s("-1.834076380613423"), "4.375" );
  CHECK_EQ(fi7s("-0.076853662774759") / fi7s( "0.807138478562926"), "0.0"   );
  CHECK_EQ(fi7s( "7.430962261645783") / fi7s("-0.653754582998705"), "-8.0"  );
  CHECK_EQ(fi7s("-1.059170631008655") / fi7s( "1.213895860938496"), "-0.875");
  CHECK_EQ(fi7s( "4.752718501906477") / fi7s( "6.401310165480160"), "0.625" );
  CHECK_EQ(fi7s( "4.594857847443615") / fi7s("-2.935825738424397"), "-1.5"  );

}

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////

typedef Fi::Fixed<7, 3, Fi::SIGNED, Fi::Wrap> fi7w;

BOOST_AUTO_TEST_SUITE(Fi_7_Wrap)
BOOST_AUTO_TEST_CASE( wrap_flp_construction )
{

  CHECK_EQ(fi7w(1e20), "0.0");
  CHECK_EQ(fi7w(9.0), "-7.0");
  CHECK_EQ(fi7w(7.9375), "7.875");
  CHECK_EQ(fi7w(4.123), "4.0");
  CHECK_EQ(fi7w(1.0f), "1.0");
  CHECK_EQ(fi7w(0.0), "0.0");
  CHECK_EQ(fi7w(-0.0), "0.0");
  CHECK_EQ(fi7w(-1.0), "-1.0");
  CHECK_EQ(fi7w(-4.123f), "-4.0");
  CHECK_EQ(fi7w(-8.0), "-8.0");
  CHECK_EQ(fi7w(-9.0), "7.0");

}

BOOST_AUTO_TEST_CASE( wrap_str_construction )
{

  CHECK_EQ(fi7w("1000000000000000000000000.0"), "0.0");
  CHECK_EQ(fi7w("9.0"), "-7.0");
  CHECK_EQ(fi7w("7.9375"), "7.875");
  CHECK_EQ(fi7w("4.123"), "4.0");
  CHECK_EQ(fi7w("1.0"), "1.0");
  CHECK_EQ(fi7w("0.0"), "0.0");
  CHECK_EQ(fi7w("-0.0"), "0.0");
  CHECK_EQ(fi7w("-1.0"), "-1.0");
  CHECK_EQ(fi7w("-4.123"), "-4.0");
  CHECK_EQ(fi7w("-8.0"), "-8.0");
  CHECK_EQ(fi7w("-9.0"), "7.0");

  BOOST_CHECK_THROW(fi7w("abc"), std::invalid_argument);
  BOOST_CHECK_THROW(fi7w("8.0.01"), std::invalid_argument);

}

BOOST_AUTO_TEST_CASE( wrap_add )
{

  CHECK_EQ(fi7w("1.0") + fi7w("3.0"), "4.0");
  CHECK_EQ(fi7w("3.0") + fi7w("1.0"), "4.0");
  CHECK_EQ(fi7w("6.0") + fi7w("3.0"), "-7.0");
  CHECK_EQ(fi7w("-1.0") + fi7w("3.0"), "2.0");
  CHECK_EQ(fi7w("-5.0") + fi7w("3.0"), "-2.0");
  CHECK_EQ(fi7w("-4.3") + fi7w("3.123"), "-1.25");
  CHECK_EQ(fi7w("-5.5") + fi7w("-1.25"), "-6.75");
  CHECK_EQ(fi7w("-5.0") + fi7w("-4.0"), "7.0");

}

BOOST_AUTO_TEST_CASE( wrap_sub )
{

  CHECK_EQ(fi7w("1.24") - fi7w("3.24"), "-2.0");
  CHECK_EQ(fi7w("3.24") - fi7w("1.24"), "2.0");
  CHECK_EQ(fi7w("6.0") - fi7w("-3.0"), "-7.0");
  CHECK_EQ(fi7w("-1.0") - fi7w("3.0"), "-4.0");
  CHECK_EQ(fi7w("-3.0") - fi7w("-5.0"), "2.0");
  CHECK_EQ(fi7w("-4.3") - fi7w("3.123"), "-7.25");
  CHECK_EQ(fi7w("-5.0") - fi7w("4.0"), "7.0");

}

BOOST_AUTO_TEST_CASE( wrap_mul )
{
  //Directed
  CHECK_EQ(fi7w("0") * fi7w("6.234"), "0.0");
  CHECK_EQ(fi7w("-1.234") * fi7w("0.0"), "0.0");
  CHECK_EQ(fi7w("-1.125") * fi7w("1.0"), "-1.125");
  CHECK_EQ(fi7w("1.0") * fi7w("1.125"), "1.125");
  CHECK_EQ(fi7w("7.875") * fi7w("7.875"), "-2.0");
  CHECK_EQ(fi7w("-8.0") * fi7w("7.875"), "1.0");
  CHECK_EQ(fi7w("7.875") * fi7w("-8.0"), "1.0");
  CHECK_EQ(fi7w("-8.0") * fi7w("-8.0"), "0.0");
  //Random
  CHECK_EQ(fi7w("-0.825705595476718") * fi7w("-3.205362909730596"), "2.25");
  CHECK_EQ(fi7w("-3.852462095122293") * fi7w( "5.950790413457298"), "-6.0");
  CHECK_EQ(fi7w("-3.216062938684098") * fi7w("-1.326810404461233"), "3.875");
  CHECK_EQ(fi7w( "6.088384207074370") * fi7w( "4.881166853660890"), "-2.75");
  CHECK_EQ(fi7w( "0.832614278826776") * fi7w("-4.139684117154774"), "-3.0");
  CHECK_EQ(fi7w( "5.440249449484426") * fi7w("-7.840253558399688"), "6.375");
  CHECK_EQ(fi7w("-6.422742856331885") * fi7w( "7.672889625019833"), "-0.5");
  CHECK_EQ(fi7w("-0.457380693528814") * fi7w("-4.475611026624939"), "1.625");
  CHECK_EQ(fi7w( "7.064531876290451") * fi7w("-6.503440029460585"), "2.5");
  CHECK_EQ(fi7w("-0.628418377612132") * fi7w( "5.605407919033070"), "-3.375");

}

BOOST_AUTO_TEST_CASE( wrap_div )
{

  CHECK_EQ(fi7w("0") / fi7w("6.234"), "0.0");
  CHECK_EQ(fi7w("-1.125") / fi7w("1.0"), "-1.125");
  CHECK_EQ(fi7w("6.125") / fi7w("1.0"), "6.125");

  CHECK_EQ(fi7w("-4.919283268629641") / fi7w( "5.928424508882099"), "-0.75");
  CHECK_EQ(fi7w( "6.004846603752069") / fi7w( "3.144192242042575"), "1.875");
  CHECK_EQ(fi7w("-7.705448601940077") / fi7w( "0.541743305247829"), "0.75");
  CHECK_EQ(fi7w( "5.017179900089733") / fi7w("-4.164916673975533"), "-1.125");
  CHECK_EQ(fi7w("-7.806926337932302") / fi7w("-1.834076380613423"), "4.375");
  CHECK_EQ(fi7w("-0.076853662774759") / fi7w( "0.807138478562926"), "0.0");
  CHECK_EQ(fi7w( "7.430962261645783") / fi7w("-0.653754582998705"), "4.25");
  CHECK_EQ(fi7w("-1.059170631008655") / fi7w( "1.213895860938496"), "-0.875");
  CHECK_EQ(fi7w( "4.752718501906477") / fi7w( "6.401310165480160"), "0.625");
  CHECK_EQ(fi7w( "4.594857847443615") / fi7w("-2.935825738424397"), "-1.5");

}

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////

typedef Fi::Fixed<7, 3, Fi::SIGNED, Fi::Throw> fi7of;

BOOST_AUTO_TEST_SUITE(Fi_7_Throw)
BOOST_AUTO_TEST_CASE( overflowexception_flp_construction )
{

  BOOST_CHECK_THROW(fi7of(1e20), std::overflow_error);
  BOOST_CHECK_THROW(fi7of(9.0), std::overflow_error);
  BOOST_CHECK_THROW(fi7of(8.0), std::overflow_error);
  CHECK_EQ(fi7of(4.123), "4.0");
  CHECK_EQ(fi7of(1.0f), "1.0");
  CHECK_EQ(fi7of(0.0), "0.0");
  CHECK_EQ(fi7of(-0.0), "0.0");
  CHECK_EQ(fi7of(-1.0), "-1.0");
  CHECK_EQ(fi7of(-4.123f), "-4.0");
  CHECK_EQ(fi7of(-8.0), "-8.0");
  BOOST_CHECK_THROW(fi7of(-9.0), std::overflow_error);
  BOOST_CHECK_THROW(fi7of(-1e20), std::overflow_error);
}

BOOST_AUTO_TEST_CASE( overflowexception_str_construction )
{

  BOOST_CHECK_THROW(fi7of("1000000000000000000000000.0"), std::overflow_error);
  BOOST_CHECK_THROW(fi7of("9.0"), std::overflow_error);

  //Ok due to rounding rules
  CHECK_EQ(fi7of("7.9375"), "7.875");
  CHECK_EQ(fi7of("4.123"), "4.0");
  CHECK_EQ(fi7of("1.0"), "1.0");
  CHECK_EQ(fi7of("0.0"), "0.0");
  CHECK_EQ(fi7of("-0.0"), "0.0");
  CHECK_EQ(fi7of("-1.0"), "-1.0");
  CHECK_EQ(fi7of("-4.123"), "-4.0");
  CHECK_EQ(fi7of("-8.0"), "-8.0");
  BOOST_CHECK_THROW(fi7of("-9.0"), std::overflow_error);

  BOOST_CHECK_THROW(fi7of("abc"), std::invalid_argument);
  BOOST_CHECK_THROW(fi7of("8.0.01"), std::invalid_argument);

}

BOOST_AUTO_TEST_CASE( overflowexception_add )
{

  CHECK_EQ(fi7of("1.0") + fi7of("3.0"), "4.0");
  CHECK_EQ(fi7of("3.0") + fi7of("1.0"), "4.0");
  BOOST_CHECK_THROW(fi7of("6.0") + fi7of("3.0"), std::overflow_error);
  CHECK_EQ(fi7of("-1.0") + fi7of("3.0"), "2.0");
  CHECK_EQ(fi7of("-5.0") + fi7of("3.0"), "-2.0");
  CHECK_EQ(fi7of("-4.3") + fi7of("3.123"), "-1.25");
  CHECK_EQ(fi7of("-5.5") + fi7of("-1.25"), "-6.75");
  BOOST_CHECK_THROW(fi7of("-5.0") + fi7of("-4.0"), std::overflow_error);

}

BOOST_AUTO_TEST_CASE( overflowexception_sub )
{

  CHECK_EQ(fi7of("1.24") - fi7of("3.24"), "-2.0");
  CHECK_EQ(fi7of("3.24") - fi7of("1.24"), "2.0");
  BOOST_CHECK_THROW(fi7of("6.0") - fi7of("-3.0"), std::overflow_error);
  CHECK_EQ(fi7of("-1.0") - fi7of("3.0"), "-4.0");
  CHECK_EQ(fi7of("-3.0") - fi7of("-5.0"), "2.0");
  CHECK_EQ(fi7of("-4.3") - fi7of("3.123"), "-7.25");
  BOOST_CHECK_THROW(fi7of("-5.0") - fi7of("4.0"), std::overflow_error);

}

BOOST_AUTO_TEST_CASE( overflowexception_mul )
{
  //Directed
  CHECK_EQ(fi7of("0") * fi7of("6.234"), "0.0");
  CHECK_EQ(fi7of("-1.234") * fi7of("0.0"), "0.0");
  CHECK_EQ(fi7of("-1.125") * fi7of("1.0"), "-1.125");
  CHECK_EQ(fi7of("1.0") * fi7of("1.125"), "1.125");
  BOOST_CHECK_THROW(fi7of("100") * fi7of("-100"), std::overflow_error);
  BOOST_CHECK_THROW(fi7of("-100") * fi7of("100"), std::overflow_error);
  BOOST_CHECK_THROW(fi7of("100") * fi7of("100"), std::overflow_error);
  BOOST_CHECK_THROW(fi7of("-100") * fi7of("-100"), std::overflow_error);
  //Random
  CHECK_EQ(fi7of("-0.825705595476718") * fi7of("-3.205362909730596"), "2.25");
  BOOST_CHECK_THROW(fi7of("-3.852462095122293") * fi7of( "5.950790413457298"), std::overflow_error);
  CHECK_EQ(fi7of("-3.216062938684098") * fi7of("-1.326810404461233"), "3.875");
  BOOST_CHECK_THROW(fi7of( "6.088384207074370") * fi7of("4.881166853660890"), std::overflow_error);
  CHECK_EQ(fi7of( "0.832614278826776") * fi7of("-4.139684117154774"), "-3.0");
  BOOST_CHECK_THROW(fi7of( "5.440249449484426") * fi7of("-7.840253558399688"), std::overflow_error);
  BOOST_CHECK_THROW(fi7of("-6.422742856331885") * fi7of( "7.672889625019833"), std::overflow_error);
  CHECK_EQ(fi7of("-0.457380693528814") * fi7of("-4.475611026624939"), "1.625");
  BOOST_CHECK_THROW(fi7of( "7.064531876290451") * fi7of("-6.503440029460585"), std::overflow_error);
  CHECK_EQ(fi7of("-0.628418377612132") * fi7of( "5.605407919033070"), "-3.375");

}

BOOST_AUTO_TEST_CASE( overflowexception_div )
{

  CHECK_EQ(fi7of("0") / fi7of("6.234"), "0.0");
  CHECK_EQ(fi7of("-1.125") / fi7of("1.0"), "-1.125");
  CHECK_EQ(fi7of("6.125") / fi7of("1.0"), "6.125");

  CHECK_EQ(fi7of("-4.919283268629641") / fi7of( "5.928424508882099"), "-0.75");
  CHECK_EQ(fi7of( "6.004846603752069") / fi7of( "3.144192242042575"), "1.875" );
  BOOST_CHECK_THROW(fi7of("-7.705448601940077") / fi7of( "0.541743305247829"), std::overflow_error);
  CHECK_EQ(fi7of( "5.017179900089733") / fi7of("-4.164916673975533"), "-1.125");
  CHECK_EQ(fi7of("-7.806926337932302") / fi7of("-1.834076380613423"), "4.375" );
  CHECK_EQ(fi7of("-0.076853662774759") / fi7of( "0.807138478562926"), "0.0"   );
  BOOST_CHECK_THROW(fi7of( "7.430962261645783") / fi7of("-0.653754582998705"),std::overflow_error);
  CHECK_EQ(fi7of("-1.059170631008655") / fi7of( "1.213895860938496"), "-0.875");
  CHECK_EQ(fi7of( "4.752718501906477") / fi7of( "6.401310165480160"), "0.625" );
  CHECK_EQ(fi7of( "4.594857847443615") / fi7of("-2.935825738424397"), "-1.5"  );

}

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////

