#include "fi/private/Parser.hpp"

#define BOOST_TEST_DYN_LINK true
#define BOOST_TEST_MODULE construction
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(parsing)

BOOST_AUTO_TEST_CASE( invalid_number )
{

  int s;
  std::string i, f;
  BOOST_CHECK_THROW(Fi::parseNumber("abc", Fi::SIGNED, s, i, f), 
                      std::invalid_argument);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "0");
  BOOST_CHECK_EQUAL(f, "0");

  BOOST_CHECK_THROW(Fi::parseNumber("-c", Fi::SIGNED, s, i, f), 
                      std::invalid_argument);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "0");
  BOOST_CHECK_EQUAL(f, "0");

  BOOST_CHECK_THROW(Fi::parseNumber("+c", Fi::SIGNED, s, i, f), 
                      std::invalid_argument);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "0");
  BOOST_CHECK_EQUAL(f, "0");

  BOOST_CHECK_THROW(Fi::parseNumber("1c", Fi::SIGNED, s, i, f), 
                      std::invalid_argument);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "0");
  BOOST_CHECK_EQUAL(f, "0");

  BOOST_CHECK_THROW(Fi::parseNumber("-1c", Fi::SIGNED, s, i, f), 
                      std::invalid_argument);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "0");
  BOOST_CHECK_EQUAL(f, "0");

  BOOST_CHECK_THROW(Fi::parseNumber("8.0.01", Fi::SIGNED, s, i, f), 
                      std::invalid_argument);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "0");
  BOOST_CHECK_EQUAL(f, "0");

  BOOST_CHECK_THROW(Fi::parseNumber("8.+1", Fi::SIGNED, s, i, f), 
                      std::invalid_argument);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "0");
  BOOST_CHECK_EQUAL(f, "0");

  BOOST_CHECK_THROW(Fi::parseNumber("+", Fi::SIGNED, s, i, f), 
                      std::invalid_argument);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "0");
  BOOST_CHECK_EQUAL(f, "0");

  BOOST_CHECK_THROW(Fi::parseNumber("-", Fi::SIGNED, s, i, f), 
                      std::invalid_argument);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "0");
  BOOST_CHECK_EQUAL(f, "0");

  BOOST_CHECK_THROW(Fi::parseNumber(" ", Fi::SIGNED, s, i, f), 
                      std::invalid_argument);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "0");
  BOOST_CHECK_EQUAL(f, "0");

  BOOST_CHECK_THROW(Fi::parseNumber(" 1", Fi::SIGNED, s, i, f), 
                      std::invalid_argument);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "0");
  BOOST_CHECK_EQUAL(f, "0");

  BOOST_CHECK_THROW(Fi::parseNumber("1 ", Fi::SIGNED, s, i, f), 
                      std::invalid_argument);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "0");
  BOOST_CHECK_EQUAL(f, "0");

  BOOST_CHECK_THROW(Fi::parseNumber("000000-", Fi::SIGNED, s, i, f), 
                      std::invalid_argument);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "0");
  BOOST_CHECK_EQUAL(f, "0");

  BOOST_CHECK_THROW(Fi::parseNumber("000000+", Fi::SIGNED, s, i, f), 
                      std::invalid_argument);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "0");
  BOOST_CHECK_EQUAL(f, "0");

  BOOST_CHECK_THROW(Fi::parseNumber("9f", Fi::SIGNED, s, i, f), 
                      std::invalid_argument);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "0");
  BOOST_CHECK_EQUAL(f, "0");

  BOOST_CHECK_THROW(Fi::parseNumber("+9f", Fi::SIGNED, s, i, f), 
                      std::invalid_argument);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "0");
  BOOST_CHECK_EQUAL(f, "0");

  BOOST_CHECK_THROW(Fi::parseNumber("-9f", Fi::SIGNED, s, i, f), 
                      std::invalid_argument);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "0");
  BOOST_CHECK_EQUAL(f, "0");

  BOOST_CHECK_THROW(Fi::parseNumber("-10.0", Fi::UNSIGNED, s, i, f), 
                      std::invalid_argument);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "0");
  BOOST_CHECK_EQUAL(f, "0");

  BOOST_CHECK_THROW(Fi::parseNumber(".", Fi::UNSIGNED, s, i, f), 
                      std::invalid_argument);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "0");
  BOOST_CHECK_EQUAL(f, "0");

}

BOOST_AUTO_TEST_CASE( signed_parsing )
{

  int s;
  std::string i, f;

  Fi::parseNumber("1", Fi::SIGNED, s, i, f);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "1");
  BOOST_CHECK_EQUAL(f, "0");

  Fi::parseNumber("1.", Fi::SIGNED, s, i, f);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "1");
  BOOST_CHECK_EQUAL(f, "0");

  Fi::parseNumber("1.0", Fi::SIGNED, s, i, f);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "1");
  BOOST_CHECK_EQUAL(f, "0");

  Fi::parseNumber("-1", Fi::SIGNED, s, i, f);
  BOOST_CHECK_EQUAL(s, -1);
  BOOST_CHECK_EQUAL(i, "1");
  BOOST_CHECK_EQUAL(f, "0");

  Fi::parseNumber("-1.", Fi::SIGNED, s, i, f);
  BOOST_CHECK_EQUAL(s, -1);
  BOOST_CHECK_EQUAL(i, "1");
  BOOST_CHECK_EQUAL(f, "0");

  Fi::parseNumber("-1.0", Fi::SIGNED, s, i, f);
  BOOST_CHECK_EQUAL(s, -1);
  BOOST_CHECK_EQUAL(i, "1");
  BOOST_CHECK_EQUAL(f, "0");

  Fi::parseNumber("0", Fi::SIGNED, s, i, f);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "0");
  BOOST_CHECK_EQUAL(f, "0");

  Fi::parseNumber("0.0", Fi::SIGNED, s, i, f);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "0");
  BOOST_CHECK_EQUAL(f, "0");

  Fi::parseNumber("-0.0", Fi::SIGNED, s, i, f);
  BOOST_CHECK_EQUAL(s, -1);
  BOOST_CHECK_EQUAL(i, "0");
  BOOST_CHECK_EQUAL(f, "0");

  Fi::parseNumber(".0", Fi::SIGNED, s, i, f);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "0");
  BOOST_CHECK_EQUAL(f, "0");

  Fi::parseNumber("-.0", Fi::SIGNED, s, i, f);
  BOOST_CHECK_EQUAL(s, -1);
  BOOST_CHECK_EQUAL(i, "0");
  BOOST_CHECK_EQUAL(f, "0");

  Fi::parseNumber("+1.1234", Fi::SIGNED, s, i, f);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "1");
  BOOST_CHECK_EQUAL(f, "1234");

  Fi::parseNumber("-1.1234", Fi::SIGNED, s, i, f);
  BOOST_CHECK_EQUAL(s, -1);
  BOOST_CHECK_EQUAL(i, "1");
  BOOST_CHECK_EQUAL(f, "1234");

  Fi::parseNumber("001129.00123900", Fi::SIGNED, s, i, f);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "1129");
  BOOST_CHECK_EQUAL(f, "001239");

  Fi::parseNumber(".9123", Fi::SIGNED, s, i, f);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "0");
  BOOST_CHECK_EQUAL(f, "9123");

  Fi::parseNumber("-.9123", Fi::SIGNED, s, i, f);
  BOOST_CHECK_EQUAL(s, -1);
  BOOST_CHECK_EQUAL(i, "0");
  BOOST_CHECK_EQUAL(f, "9123");

  Fi::parseNumber("9822.", Fi::SIGNED, s, i, f);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "9822");
  BOOST_CHECK_EQUAL(f, "0");

  Fi::parseNumber("-9822.", Fi::SIGNED, s, i, f);
  BOOST_CHECK_EQUAL(s, -1);
  BOOST_CHECK_EQUAL(i, "9822");
  BOOST_CHECK_EQUAL(f, "0");

  Fi::parseNumber("", Fi::SIGNED, s, i, f);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "0");
  BOOST_CHECK_EQUAL(f, "0");

}

BOOST_AUTO_TEST_CASE( unsigned_parsing )
{

  int s;
  std::string i, f;

  Fi::parseNumber("1", Fi::UNSIGNED, s, i, f);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "1");
  BOOST_CHECK_EQUAL(f, "0");

  Fi::parseNumber("1.", Fi::UNSIGNED, s, i, f);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "1");
  BOOST_CHECK_EQUAL(f, "0");

  Fi::parseNumber("1.0", Fi::UNSIGNED, s, i, f);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "1");
  BOOST_CHECK_EQUAL(f, "0");

  Fi::parseNumber("0", Fi::UNSIGNED, s, i, f);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "0");
  BOOST_CHECK_EQUAL(f, "0");

  Fi::parseNumber("0.0", Fi::UNSIGNED, s, i, f);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "0");
  BOOST_CHECK_EQUAL(f, "0");

  Fi::parseNumber(".0", Fi::UNSIGNED, s, i, f);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "0");
  BOOST_CHECK_EQUAL(f, "0");

  Fi::parseNumber("+1.1234", Fi::UNSIGNED, s, i, f);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "1");
  BOOST_CHECK_EQUAL(f, "1234");

  Fi::parseNumber("001129.00123900", Fi::UNSIGNED, s, i, f);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "1129");
  BOOST_CHECK_EQUAL(f, "001239");

  Fi::parseNumber(".9123", Fi::UNSIGNED, s, i, f);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "0");
  BOOST_CHECK_EQUAL(f, "9123");

  Fi::parseNumber("9822.", Fi::UNSIGNED, s, i, f);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "9822");
  BOOST_CHECK_EQUAL(f, "0");

  Fi::parseNumber("", Fi::UNSIGNED, s, i, f);
  BOOST_CHECK_EQUAL(s, 1);
  BOOST_CHECK_EQUAL(i, "0");
  BOOST_CHECK_EQUAL(f, "0");

}

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////
