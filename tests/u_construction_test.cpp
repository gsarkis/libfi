#include "fi/Fixed.hpp"
#include "fi/overflow/Saturate.hpp"

#define BOOST_TEST_DYN_LINK true
#define BOOST_TEST_MODULE construction
#include <boost/test/unit_test.hpp>

#define CHECK_EQ(A, E) BOOST_CHECK_EQUAL((A).toString(), E)

typedef Fi::Fixed<15, 5, Fi::UNSIGNED, Fi::Saturate> fi15s;

BOOST_AUTO_TEST_SUITE(construction)

BOOST_AUTO_TEST_CASE( double_construction )
{

  CHECK_EQ(fi15s(1e40), "1023.96875");
  CHECK_EQ(fi15s(-1e40), "0.0");
  CHECK_EQ(fi15s(0.0), "0.0");
  CHECK_EQ(fi15s(-0.0), "0.0");

  CHECK_EQ(fi15s(760.9676), "760.9375");
  CHECK_EQ(fi15s(401.6405), "401.625" );
  CHECK_EQ(fi15s(671.2094), "671.1875");
  CHECK_EQ(fi15s(175.2952), "175.28125");
  CHECK_EQ(fi15s(722.9912), "722.96875");
  CHECK_EQ(fi15s( 32.5968),  "32.59375");
  CHECK_EQ(fi15s(283.5691), "283.5625");
  CHECK_EQ(fi15s( 47.2795),  "47.25"  );
  CHECK_EQ(fi15s( 99.4629),  "99.4375");
  CHECK_EQ(fi15s(843.2208), "843.21875");
  

}

BOOST_AUTO_TEST_CASE( float_construction )
{

  CHECK_EQ(fi15s(1e20f), "1023.96875");
  CHECK_EQ(fi15s(-1e20f), "0.0");
  CHECK_EQ(fi15s(0.0f), "0.0");
  CHECK_EQ(fi15s(-0.0f), "0.0");

  CHECK_EQ(fi15s(760.9676f), "760.9375");
  CHECK_EQ(fi15s(401.6405f), "401.625" );
  CHECK_EQ(fi15s(671.2094f), "671.1875");
  CHECK_EQ(fi15s(175.2952f), "175.28125");
  CHECK_EQ(fi15s(722.9912f), "722.96875");
  CHECK_EQ(fi15s( 32.5968f),  "32.59375");
  CHECK_EQ(fi15s(283.5691f), "283.5625");
  CHECK_EQ(fi15s( 47.2795f),  "47.25"  );
  CHECK_EQ(fi15s( 99.4629f),  "99.4375");
  CHECK_EQ(fi15s(843.2208f), "843.21875");
  

}


BOOST_AUTO_TEST_CASE( string_construction )
{

  CHECK_EQ(fi15s(""), "0.0");
  CHECK_EQ(fi15s("+0.0"), "0.0");
  CHECK_EQ(fi15s("0.0"), "0.0");
  CHECK_EQ(fi15s("0"), "0.0");
  CHECK_EQ(fi15s("00001.500"), "1.5");
  CHECK_EQ(fi15s("0.0000"), "0.0");
  CHECK_EQ(fi15s("0000000.0000000000000"), "0.0");
  CHECK_EQ(fi15s("+0000000.0000000000000"), "0.0");
  CHECK_EQ(fi15s("00000000001.0000000000000"), "1.0");
  CHECK_EQ(fi15s("+00000000001.0000000000000"), "1.0");
  CHECK_EQ(fi15s(".25"), "0.25");
  CHECK_EQ(fi15s("+.25"), "0.25");
  CHECK_EQ(fi15s("1."), "1.0");
  CHECK_EQ(fi15s("+1."), "1.0");
  CHECK_EQ(fi15s("+.0"), "0.0");
  CHECK_EQ(fi15s("1000000000000000000000000.0"), "1023.96875");

  CHECK_EQ(fi15s("760.9676"), "760.9375");
  CHECK_EQ(fi15s("401.6405"), "401.625" );
  CHECK_EQ(fi15s("671.2094"), "671.1875");
  CHECK_EQ(fi15s("175.2952"), "175.28125");
  CHECK_EQ(fi15s("722.9912"), "722.96875");
  CHECK_EQ(fi15s( "32.5968"),  "32.59375");
  CHECK_EQ(fi15s("283.5691"), "283.5625");
  CHECK_EQ(fi15s( "47.2795"),  "47.25"  );
  CHECK_EQ(fi15s( "99.4629"),  "99.4375");
  CHECK_EQ(fi15s("843.2208"), "843.21875");

}


BOOST_AUTO_TEST_CASE( faulty_construction )
{

  BOOST_CHECK_THROW(fi15s("abc"), std::invalid_argument);
  BOOST_CHECK_THROW(fi15s("-c"), std::invalid_argument);
  BOOST_CHECK_THROW(fi15s("+c"), std::invalid_argument);
  BOOST_CHECK_THROW(fi15s("1c"), std::invalid_argument);
  BOOST_CHECK_THROW(fi15s("-1c"), std::invalid_argument);
  BOOST_CHECK_THROW(fi15s("8.0.01"), std::invalid_argument);
  BOOST_CHECK_THROW(fi15s("8..0"), std::invalid_argument);
  BOOST_CHECK_THROW(fi15s("8.+1"), std::invalid_argument);
  BOOST_CHECK_THROW(fi15s("+"), std::invalid_argument);
  BOOST_CHECK_THROW(fi15s("-"), std::invalid_argument);
  BOOST_CHECK_THROW(fi15s(" "), std::invalid_argument);
  BOOST_CHECK_THROW(fi15s(" 1"), std::invalid_argument);
  BOOST_CHECK_THROW(fi15s("1 "), std::invalid_argument);
  BOOST_CHECK_THROW(fi15s("0000000-"), std::invalid_argument);
  BOOST_CHECK_THROW(fi15s("0000000+"), std::invalid_argument);
  BOOST_CHECK_THROW(fi15s("9f"), std::invalid_argument);
  BOOST_CHECK_THROW(fi15s("+9f"), std::invalid_argument);
  BOOST_CHECK_THROW(fi15s("-9f"), std::invalid_argument);
  BOOST_CHECK_THROW(fi15s("+."), std::invalid_argument);
  BOOST_CHECK_THROW(fi15s("-."), std::invalid_argument);
  BOOST_CHECK_THROW(fi15s("."), std::invalid_argument);

}


BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////
