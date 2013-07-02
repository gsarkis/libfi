/*
 *Copyright © 2012 Gabi Sarkis.

 *This file is part of the C++ Fixed-Point Library (LibFi).

 *LibFi is free software: you can redistribute it and/or modify
 *it under the terms of the GNU General Public License as published by
 *the Free Software Foundation, either version 3 of the License, or
 *(at your option) any later version.

 *LibFi is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *GNU General Public License for more details.

 *You should have received a copy of the GNU General Public License
 *along with LibFi.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "fi/private/StringMath.hpp"

#define BOOST_TEST_DYN_LINK true
#define BOOST_TEST_MODULE StringMath
#include <boost/test/unit_test.hpp>

#include <string>

BOOST_AUTO_TEST_SUITE( comparison )

BOOST_AUTO_TEST_CASE( less_false )
{

  using Fi::StringMath::less;

  BOOST_CHECK_EQUAL( less("1.0", "1.0"), false );
  BOOST_CHECK_EQUAL( less("0", "-1.123"), false );
  BOOST_CHECK_EQUAL( less("2.1", "2.0"), false );
  BOOST_CHECK_EQUAL( less("12", "2"), false );
  BOOST_CHECK_EQUAL( less(".9", ".5"), false );
  BOOST_CHECK_EQUAL( less("0", "0"), false );
  BOOST_CHECK_EQUAL( less("", ""), false );
  BOOST_CHECK_EQUAL( less("-1.0", "-1.0"), false );
  BOOST_CHECK_EQUAL( less("-0", "-1.123"), false );
  BOOST_CHECK_EQUAL( less("-2.0", "-2.1"), false );
  BOOST_CHECK_EQUAL( less("-2", "-12"), false );
  BOOST_CHECK_EQUAL( less("-.5", "-.9"), false );

}

BOOST_AUTO_TEST_CASE( less_true )
{

  using Fi::StringMath::less;

  BOOST_CHECK_EQUAL( less("-1.123", "1.0"), true );
  BOOST_CHECK_EQUAL( less("2.0", "2.1"), true );
  BOOST_CHECK_EQUAL( less("2", "12"), true );
  BOOST_CHECK_EQUAL( less(".5", ".9"), true );
  BOOST_CHECK_EQUAL( less("-1.123", "-0"), true );
  BOOST_CHECK_EQUAL( less("-2.1", "-2.0"), true );
  BOOST_CHECK_EQUAL( less("-12", "-2"), true );
  BOOST_CHECK_EQUAL( less("-.9", "-.5"), true );

}

BOOST_AUTO_TEST_CASE( greater_false )
{

  using Fi::StringMath::greater;

  BOOST_CHECK_EQUAL( greater("1.0", "1.0"), false );
  BOOST_CHECK_EQUAL( greater("-1.123", "1.0"), false );
  BOOST_CHECK_EQUAL( greater("2.0", "2.1"), false );
  BOOST_CHECK_EQUAL( greater("2", "12"), false );
  BOOST_CHECK_EQUAL( greater(".5", ".9"), false );
  BOOST_CHECK_EQUAL( greater("0", "0"), false );
  BOOST_CHECK_EQUAL( greater("", ""), false );
  BOOST_CHECK_EQUAL( greater("-1.0", "-1.0"), false );
  BOOST_CHECK_EQUAL( greater("-1.123", "-0"), false );
  BOOST_CHECK_EQUAL( greater("-2.1", "-2.0"), false );
  BOOST_CHECK_EQUAL( greater("-12", "-2"), false );
  BOOST_CHECK_EQUAL( greater("-.9", "-.5"), false );

}

BOOST_AUTO_TEST_CASE( greater_true )
{

  using Fi::StringMath::greater;

  BOOST_CHECK_EQUAL( greater("0", "-1.123"), true );
  BOOST_CHECK_EQUAL( greater("2.1", "2.0"), true );
  BOOST_CHECK_EQUAL( greater("12", "2"), true );
  BOOST_CHECK_EQUAL( greater(".9", ".5"), true );
  BOOST_CHECK_EQUAL( greater("-0", "-1.123"), true );
  BOOST_CHECK_EQUAL( greater("-2.0", "-2.1"), true );
  BOOST_CHECK_EQUAL( greater("-2", "-12"), true );
  BOOST_CHECK_EQUAL( greater("-.5", "-.9"), true );
  BOOST_CHECK_EQUAL( greater("1", "-1"), true);

}

BOOST_AUTO_TEST_CASE( equal_false )
{

  using Fi::StringMath::equal;

  BOOST_CHECK_EQUAL( equal("0", "1"), false );
  BOOST_CHECK_EQUAL( equal("0", "-1"), false );
  BOOST_CHECK_EQUAL( equal("-1", "0"), false );
  BOOST_CHECK_EQUAL( equal("1", "-1"), false );
  BOOST_CHECK_EQUAL( equal("-1", "1"), false );
  BOOST_CHECK_EQUAL( equal(".1", "1."), false );
  BOOST_CHECK_EQUAL( equal("1.", ".1"), false );
  BOOST_CHECK_EQUAL( equal("542.1", "543.1"), false );
  BOOST_CHECK_EQUAL( equal("1.123", "1.7435"), false );

}


BOOST_AUTO_TEST_CASE( equal_true )
{

  using Fi::StringMath::equal;

  BOOST_CHECK_EQUAL( equal("", ""), true );
  BOOST_CHECK_EQUAL( equal("0", "0"), true );
  BOOST_CHECK_EQUAL( equal("0.0", "0.0"), true );
  BOOST_CHECK_EQUAL( equal("-0.0", "0.0"), true );
  BOOST_CHECK_EQUAL( equal("0.0", "-0.0"), true );
  BOOST_CHECK_EQUAL( equal("1.123", "1.123"), true );
  BOOST_CHECK_EQUAL( equal(".123", "0.123"), true );
  BOOST_CHECK_EQUAL( equal("0.123", ".123"), true );
  BOOST_CHECK_EQUAL( equal("532.0", "532"), true );
  BOOST_CHECK_EQUAL( equal("532", "532.0"), true );

}


BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( arithmetic )

BOOST_AUTO_TEST_CASE( increment )
{

  using Fi::StringMath::plusOne;

  BOOST_CHECK_EQUAL( plusOne("-123"), "-122");
  BOOST_CHECK_EQUAL( plusOne("-100"), "-99");
  BOOST_CHECK_EQUAL( plusOne("-10"), "-9");
  BOOST_CHECK_EQUAL( plusOne("-3"), "-2");
  
  BOOST_CHECK_EQUAL( plusOne("-1"), "0");
  BOOST_CHECK_EQUAL( plusOne("0"), "1");

  BOOST_CHECK_EQUAL( plusOne("2"), "3");
  BOOST_CHECK_EQUAL( plusOne("9"), "10");
  BOOST_CHECK_EQUAL( plusOne("99"), "100");
  BOOST_CHECK_EQUAL( plusOne("122"), "123");

}

BOOST_AUTO_TEST_SUITE_END()
