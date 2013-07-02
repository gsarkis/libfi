#include "fi/Fixed.hpp"
#include "fi/overflow/Saturate.hpp"

#define BOOST_TEST_DYN_LINK true
#define BOOST_TEST_MODULE to_type
#include <boost/test/unit_test.hpp>

typedef Fi::Fixed<15, 5, Fi::SIGNED, Fi::Saturate> fi15_5ss;
typedef Fi::Fixed<15, 1, Fi::UNSIGNED, Fi::Saturate> fi15_1us;

BOOST_AUTO_TEST_SUITE(to_type)

BOOST_AUTO_TEST_CASE( toFloat )
{

  BOOST_CHECK_EQUAL(fi15_5ss(0.9375).toFloat(), 0.9375);
  BOOST_CHECK_EQUAL(fi15_5ss(-1.0).toFloat(), -1.0);
  BOOST_CHECK_EQUAL(fi15_1us(0.9375).toFloat(), 0.5);
  BOOST_CHECK_EQUAL(fi15_1us(1.0).toFloat(), 1.0);

}

BOOST_AUTO_TEST_CASE( toDouble )
{

  BOOST_CHECK_EQUAL(fi15_5ss(0.9375).toDouble(), 0.9375);
  BOOST_CHECK_EQUAL(fi15_5ss(-1.0).toDouble(), -1.0);
  BOOST_CHECK_EQUAL(fi15_1us(0.9375).toDouble(), 0.5);
  BOOST_CHECK_EQUAL(fi15_1us(1.0).toDouble(), 1.0);

}

BOOST_AUTO_TEST_CASE( toString )
{

  BOOST_CHECK_EQUAL(fi15_5ss(0.9375).toString(), "0.9375");
  BOOST_CHECK_EQUAL(fi15_5ss(-1.0).toString(), "-1.0");
  BOOST_CHECK_EQUAL(fi15_1us(0.9375).toString(), "0.5");
  BOOST_CHECK_EQUAL(fi15_1us(1.0).toString(), "1.0");

}

BOOST_AUTO_TEST_CASE( toBinaryString )
{

  BOOST_CHECK_EQUAL(fi15_5ss(0.9375).toBinaryString(), "000000000011110");
  BOOST_CHECK_EQUAL(fi15_5ss(-1.0).toBinaryString(), "111111111100000");
  BOOST_CHECK_EQUAL(fi15_1us(0.9375).toBinaryString(), "000000000000001");
  BOOST_CHECK_EQUAL(fi15_1us(1.0).toBinaryString(), "000000000000010");

}
BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////
