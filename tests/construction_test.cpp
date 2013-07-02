#include "fi/Fixed.hpp"
#include "fi/overflow/Throw.hpp"

#define BOOST_TEST_DYN_LINK true
#define BOOST_TEST_MODULE construction
#include <boost/test/unit_test.hpp>

#define CHECK_EQ(A, E) BOOST_CHECK_EQUAL((A).toString(), E)


BOOST_AUTO_TEST_SUITE(construction_signed)
typedef Fi::Fixed<15, 5, Fi::SIGNED, Fi::Throw> fi15s;

BOOST_AUTO_TEST_CASE( float_construction_no_overflow )
{

  CHECK_EQ(fi15s(511.96875), "511.96875");
  CHECK_EQ(fi15s(9.0), "9.0");
  CHECK_EQ(fi15s(7.9375), "7.9375");
  CHECK_EQ(fi15s(1.0), "1.0");
  CHECK_EQ(fi15s(0.0), "0.0");
  CHECK_EQ(fi15s(-0.0), "0.0");
  CHECK_EQ(fi15s(-1.0), "-1.0");
  CHECK_EQ(fi15s(-7.9375), "-7.9375");
  CHECK_EQ(fi15s(-.9375), "-0.9375");
  CHECK_EQ(fi15s(.9375), "0.9375");
  CHECK_EQ(fi15s(-512.0), "-512.0");

  CHECK_EQ(fi15s(9.0f), "9.0");
  CHECK_EQ(fi15s(7.9375f), "7.9375");
  CHECK_EQ(fi15s(1.0f), "1.0");
  CHECK_EQ(fi15s(0.0f), "0.0");
  CHECK_EQ(fi15s(-0.0f), "0.0");
  CHECK_EQ(fi15s(-1.0f), "-1.0");
  CHECK_EQ(fi15s(-7.9375f), "-7.9375");
  CHECK_EQ(fi15s(-.9375f), "-0.9375");
  CHECK_EQ(fi15s(.9375f), "0.9375");

}

BOOST_AUTO_TEST_CASE( construction_overflow )
{

  BOOST_CHECK_THROW(fi15s(512.0), Fi::PositiveOverflow);
  BOOST_CHECK_THROW(fi15s(-512.03125), Fi::NegativeOverflow);

  BOOST_CHECK_THROW(fi15s(1e40), Fi::PositiveOverflow);
  BOOST_CHECK_THROW(fi15s(-1e40), Fi::NegativeOverflow);

  BOOST_CHECK_THROW(fi15s(1e20), Fi::PositiveOverflow);
  BOOST_CHECK_THROW(fi15s(-1e20), Fi::NegativeOverflow);

  BOOST_CHECK_THROW(fi15s(1e20f), Fi::PositiveOverflow);
  BOOST_CHECK_THROW(fi15s(-1e20f), Fi::NegativeOverflow);


  BOOST_CHECK_THROW(fi15s("512.0"), Fi::PositiveOverflow);
  BOOST_CHECK_THROW(fi15s("-512.03125"), Fi::NegativeOverflow);

  BOOST_CHECK_THROW(fi15s("1000000000000000000000000.0"), Fi::PositiveOverflow);
  BOOST_CHECK_THROW(fi15s("-1000000000000000000000000.0"), Fi::NegativeOverflow);

}


BOOST_AUTO_TEST_CASE( string_construction )
{

  CHECK_EQ(fi15s(""), "0.0");
  CHECK_EQ(fi15s("-0.0"), "0.0");
  CHECK_EQ(fi15s("+0.0"), "0.0");
  CHECK_EQ(fi15s("0"), "0.0");
  CHECK_EQ(fi15s("00001.500"), "1.5");
  CHECK_EQ(fi15s("0.0000"), "0.0");
  CHECK_EQ(fi15s("0000000.0000000000000"), "0.0");
  CHECK_EQ(fi15s("-0000000.0000000000000"), "0.0");
  CHECK_EQ(fi15s("+0000000.0000000000000"), "0.0");
  CHECK_EQ(fi15s("00000000001.0000000000000"), "1.0");
  CHECK_EQ(fi15s("-00000000001.0000000000000"), "-1.0");
  CHECK_EQ(fi15s("+00000000001.0000000000000"), "1.0");
  CHECK_EQ(fi15s(".25"), "0.25");
  CHECK_EQ(fi15s("+.25"), "0.25");
  CHECK_EQ(fi15s("-.25"), "-0.25");
  CHECK_EQ(fi15s("1."), "1.0");
  CHECK_EQ(fi15s("-1."), "-1.0");
  CHECK_EQ(fi15s("+1."), "1.0");
  CHECK_EQ(fi15s("-.0"), "0.0");
  CHECK_EQ(fi15s("+.0"), "0.0");

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


BOOST_AUTO_TEST_SUITE(construction_unsigned)
typedef Fi::Fixed<15, 5, Fi::UNSIGNED, Fi::Throw> fi15u;

BOOST_AUTO_TEST_CASE( float_construction_no_overflow )
{

  CHECK_EQ(fi15u(1023.96875), "1023.96875");
  CHECK_EQ(fi15u(511.96875), "511.96875");
  CHECK_EQ(fi15u(9.0), "9.0");
  CHECK_EQ(fi15u(7.9375), "7.9375");
  CHECK_EQ(fi15u(1.0), "1.0");
  CHECK_EQ(fi15u(0.0), "0.0");
  CHECK_EQ(fi15u(-0.0), "0.0");

  CHECK_EQ(fi15u(9.0f), "9.0");
  CHECK_EQ(fi15u(7.9375f), "7.9375");
  CHECK_EQ(fi15u(1.0f), "1.0");
  CHECK_EQ(fi15u(0.0f), "0.0");
  CHECK_EQ(fi15u(-0.0f), "0.0");

}

BOOST_AUTO_TEST_CASE( construction_overflow )
{

  BOOST_CHECK_THROW(fi15u(1024.0), Fi::PositiveOverflow);
  BOOST_CHECK_THROW(fi15u(-0.03125), Fi::NegativeOverflow);

  BOOST_CHECK_THROW(fi15u(1e40), Fi::PositiveOverflow);
  BOOST_CHECK_THROW(fi15u(-1e40), Fi::NegativeOverflow);

  BOOST_CHECK_THROW(fi15u(1e20), Fi::PositiveOverflow);
  BOOST_CHECK_THROW(fi15u(-1e20), Fi::NegativeOverflow);

  BOOST_CHECK_THROW(fi15u(1e20f), Fi::PositiveOverflow);
  BOOST_CHECK_THROW(fi15u(-1e20f), Fi::NegativeOverflow);

  BOOST_CHECK_THROW(fi15u("1000000000000000000000000.0"), Fi::PositiveOverflow);
  BOOST_CHECK_THROW(fi15u("-00000000001.0000000000000"), std::invalid_argument);

  BOOST_CHECK_THROW(fi15u("1024.0"), Fi::PositiveOverflow);

}


BOOST_AUTO_TEST_CASE( string_construction )
{

  CHECK_EQ(fi15u(""), "0.0");
  CHECK_EQ(fi15u("+0.0"), "0.0");
  CHECK_EQ(fi15u("0"), "0.0");
  CHECK_EQ(fi15u("00001.500"), "1.5");
  CHECK_EQ(fi15u("0.0000"), "0.0");
  CHECK_EQ(fi15u("0000000.0000000000000"), "0.0");
  CHECK_EQ(fi15u("+0000000.0000000000000"), "0.0");
  CHECK_EQ(fi15u("00000000001.0000000000000"), "1.0");
  CHECK_EQ(fi15u("+00000000001.0000000000000"), "1.0");
  CHECK_EQ(fi15u(".25"), "0.25");
  CHECK_EQ(fi15u("+.25"), "0.25");
  CHECK_EQ(fi15u("1."), "1.0");
  CHECK_EQ(fi15u("+1."), "1.0");
  CHECK_EQ(fi15u("+.0"), "0.0");

}


BOOST_AUTO_TEST_CASE( faulty_construction )
{

  BOOST_CHECK_THROW(fi15u("abc"), std::invalid_argument);
  BOOST_CHECK_THROW(fi15u("-c"), std::invalid_argument);
  BOOST_CHECK_THROW(fi15u("+c"), std::invalid_argument);
  BOOST_CHECK_THROW(fi15u("1c"), std::invalid_argument);
  BOOST_CHECK_THROW(fi15u("-1c"), std::invalid_argument);
  BOOST_CHECK_THROW(fi15u("8.0.01"), std::invalid_argument);
  BOOST_CHECK_THROW(fi15u("8..0"), std::invalid_argument);
  BOOST_CHECK_THROW(fi15u("8.+1"), std::invalid_argument);
  BOOST_CHECK_THROW(fi15u("+"), std::invalid_argument);
  BOOST_CHECK_THROW(fi15u("-"), std::invalid_argument);
  BOOST_CHECK_THROW(fi15u(" "), std::invalid_argument);
  BOOST_CHECK_THROW(fi15u(" 1"), std::invalid_argument);
  BOOST_CHECK_THROW(fi15u("1 "), std::invalid_argument);
  BOOST_CHECK_THROW(fi15u("0000000-"), std::invalid_argument);
  BOOST_CHECK_THROW(fi15u("0000000+"), std::invalid_argument);
  BOOST_CHECK_THROW(fi15u("9f"), std::invalid_argument);
  BOOST_CHECK_THROW(fi15u("+9f"), std::invalid_argument);
  BOOST_CHECK_THROW(fi15u("-9f"), std::invalid_argument);
  BOOST_CHECK_THROW(fi15u("+."), std::invalid_argument);
  BOOST_CHECK_THROW(fi15u("-."), std::invalid_argument);
  BOOST_CHECK_THROW(fi15u("."), std::invalid_argument);

}


BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////
