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

#include "fi/Fixed.hpp"
#include "fi/overflow/Throw.hpp"
#include "fi/rounding/Fix.hpp"

#define BOOST_TEST_DYN_LINK true
#define BOOST_TEST_MODULE overflow_detector
#include <boost/test/unit_test.hpp>

#include <iostream>

#define CHECK_EQ(A, E) BOOST_CHECK_EQUAL((A).toString(), E)

BOOST_AUTO_TEST_SUITE( fix_unsigned )

BOOST_AUTO_TEST_CASE( no_overflow_fl )
{

  typedef Fi::Fixed<8, 4, Fi::UNSIGNED, Fi::Throw, Fi::Fix> fix;

  CHECK_EQ( fix( 0.0)   , "0.0");
  CHECK_EQ( fix( 0.001)  , "0.0");
  CHECK_EQ( fix( 0.01)  , "0.0");
  CHECK_EQ( fix( 0.5714),  "0.5625");
  CHECK_EQ( fix(13.5861), "13.5625");
  CHECK_EQ( fix(14.9439), "14.9375");
  CHECK_EQ( fix(10.8598), "10.8125");
  CHECK_EQ( fix(12.1238), "12.0625");
  CHECK_EQ( fix(11.8901), "11.875" );
  CHECK_EQ( fix( 6.2756),  "6.25"  );
  CHECK_EQ( fix(10.4876), "10.4375");
  CHECK_EQ( fix( 2.7390),  "2.6875");
  CHECK_EQ( fix(11.2967), "11.25"  );
  CHECK_EQ( fix(15.9375), "15.9375" );
  CHECK_EQ( fix(15.9475), "15.9375" );
  CHECK_EQ( fix(15.9999), "15.9375" );

}

BOOST_AUTO_TEST_CASE( overflow_fl ) {

  typedef Fi::Fixed<8, 4, Fi::UNSIGNED, Fi::Throw, Fi::Fix> fix;

  BOOST_CHECK_THROW( fix(16.0   ), Fi::PositiveOverflow );
  BOOST_CHECK_THROW( fix(20.123 ), Fi::PositiveOverflow );
  BOOST_CHECK_THROW( fix(31.9375), Fi::PositiveOverflow );
  BOOST_CHECK_THROW( fix(31.9475), Fi::PositiveOverflow );
  BOOST_CHECK_THROW( fix(1e20   ), Fi::PositiveOverflow );

}

BOOST_AUTO_TEST_CASE( no_overflow_string )
{

  typedef Fi::Fixed<8, 4, Fi::UNSIGNED, Fi::Throw, Fi::Fix> fix;

  CHECK_EQ( fix( "0.0")   , "0.0");
  CHECK_EQ( fix( "0.001")  , "0.0");
  CHECK_EQ( fix( "0.01")  , "0.0");
  CHECK_EQ( fix( "0.5714"),  "0.5625");
  CHECK_EQ( fix("13.5861"), "13.5625");
  CHECK_EQ( fix("14.9439"), "14.9375");
  CHECK_EQ( fix("10.8598"), "10.8125");
  CHECK_EQ( fix("12.1238"), "12.0625");
  CHECK_EQ( fix("11.8901"), "11.875" );
  CHECK_EQ( fix( "6.2756"),  "6.25"  );
  CHECK_EQ( fix("10.4876"), "10.4375");
  CHECK_EQ( fix( "2.7390"),  "2.6875");
  CHECK_EQ( fix("11.2967"), "11.25"  );
  CHECK_EQ( fix("15.9375"), "15.9375" );
  CHECK_EQ( fix("15.9475"), "15.9375" );
  CHECK_EQ( fix("15.9999"), "15.9375" );

}

BOOST_AUTO_TEST_CASE( overflow_string ) {

  typedef Fi::Fixed<8, 4, Fi::UNSIGNED, Fi::Throw, Fi::Fix> fix;

  BOOST_CHECK_THROW( fix("16.0"   ), Fi::PositiveOverflow );
  BOOST_CHECK_THROW( fix("20.123" ), Fi::PositiveOverflow );
  BOOST_CHECK_THROW( fix("31.9375"), Fi::PositiveOverflow );
  BOOST_CHECK_THROW( fix("31.9475"), Fi::PositiveOverflow );
  BOOST_CHECK_THROW( fix("100000000.123"), Fi::PositiveOverflow );

}


BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( fix_signed )

BOOST_AUTO_TEST_CASE( s_no_overflow_fl ) {

  typedef Fi::Fixed<8, 4, Fi::SIGNED, Fi::Throw, Fi::Fix> fix;

  CHECK_EQ( fix(-8.0624), "-8.0");
  CHECK_EQ( fix(-8.01), "-8.0");
  CHECK_EQ( fix(-8.0), "-8.0");

  CHECK_EQ( fix(7.99), "7.9375");
  CHECK_EQ( fix(7.95), "7.9375");
  CHECK_EQ( fix(7.9375), "7.9375");

  CHECK_EQ( fix(-7.4907), "-7.4375");
  CHECK_EQ( fix(-3.5692), "-3.5625");
  CHECK_EQ( fix(-7.2613), "-7.25");
  CHECK_EQ( fix(-6.4459), "-6.4375");
  CHECK_EQ( fix( 5.1753),  "5.125");
  CHECK_EQ( fix( 3.1173),  "3.0625");
  CHECK_EQ( fix(-2.9264), "-2.875");
  CHECK_EQ( fix( 7.2036),  "7.1875");
  CHECK_EQ( fix(-7.4489), "-7.4375");
  CHECK_EQ( fix(-0.9801), "-0.9375");

  CHECK_EQ( fix(-0.01), "0.0");
  CHECK_EQ( fix(-0.001), "0.0");
  CHECK_EQ( fix(0.0)  , "0.0");
  CHECK_EQ( fix(0.001) , "0.0");
  CHECK_EQ( fix(0.01) , "0.0");

}

BOOST_AUTO_TEST_CASE( s_overflow_fl ) {

  typedef Fi::Fixed<8, 4, Fi::SIGNED, Fi::Throw, Fi::Fix> fix;

  BOOST_CHECK_THROW( fix(-8.0625 ), Fi::NegativeOverflow );
  BOOST_CHECK_THROW( fix(-10.1298 ), Fi::NegativeOverflow );
  BOOST_CHECK_THROW( fix(-16.0625 ), Fi::NegativeOverflow );
  BOOST_CHECK_THROW( fix(-1e20 ), Fi::NegativeOverflow );

  BOOST_CHECK_THROW( fix(8.0   ), Fi::PositiveOverflow );
  BOOST_CHECK_THROW( fix(16.123 ), Fi::PositiveOverflow );
  BOOST_CHECK_THROW( fix(31.9375), Fi::PositiveOverflow );
  BOOST_CHECK_THROW( fix(31.9475), Fi::PositiveOverflow );
  BOOST_CHECK_THROW( fix(1e20   ), Fi::PositiveOverflow );


}

BOOST_AUTO_TEST_CASE( s_no_overflow_string ) {

  typedef Fi::Fixed<8, 4, Fi::SIGNED, Fi::Throw, Fi::Fix> fix;

  CHECK_EQ( fix("-8.0624"), "-8.0");
  CHECK_EQ( fix("-8.01"), "-8.0");
  CHECK_EQ( fix("-8.0"), "-8.0");

  CHECK_EQ( fix("7.99"), "7.9375");
  CHECK_EQ( fix("7.95"), "7.9375");
  CHECK_EQ( fix("7.9375"), "7.9375");

  CHECK_EQ( fix("-7.4907"), "-7.4375");
  CHECK_EQ( fix("-3.5692"), "-3.5625");
  CHECK_EQ( fix("-7.2613"), "-7.25");
  CHECK_EQ( fix("-6.4459"), "-6.4375");
  CHECK_EQ( fix( "5.1753"),  "5.125");
  CHECK_EQ( fix( "3.1173"),  "3.0625");
  CHECK_EQ( fix("-2.9264"), "-2.875");
  CHECK_EQ( fix( "7.2036"),  "7.1875");
  CHECK_EQ( fix("-7.4489"), "-7.4375");
  CHECK_EQ( fix("-0.9801"), "-0.9375");

  CHECK_EQ( fix("-0.01"), "0.0");
  CHECK_EQ( fix("-0.001"), "0.0");
  CHECK_EQ( fix("0.0")  , "0.0");
  CHECK_EQ( fix("0.001") , "0.0");
  CHECK_EQ( fix("0.01") , "0.0");

}

BOOST_AUTO_TEST_CASE( s_overflow_string ) {

  typedef Fi::Fixed<8, 4, Fi::SIGNED, Fi::Throw, Fi::Fix> fix;

  BOOST_CHECK_THROW( fix("-8.0625"), Fi::NegativeOverflow );
  BOOST_CHECK_THROW( fix("-10.1298"), Fi::NegativeOverflow );
  BOOST_CHECK_THROW( fix("-16.0625"), Fi::NegativeOverflow );
  BOOST_CHECK_THROW( fix("-1000000"), Fi::NegativeOverflow );

  BOOST_CHECK_THROW( fix("8.0"   ), Fi::PositiveOverflow );
  BOOST_CHECK_THROW( fix("16.123" ), Fi::PositiveOverflow );
  BOOST_CHECK_THROW( fix("31.9375"), Fi::PositiveOverflow );
  BOOST_CHECK_THROW( fix("31.9475"), Fi::PositiveOverflow );
  BOOST_CHECK_THROW( fix("10000000"), Fi::PositiveOverflow );


}

BOOST_AUTO_TEST_SUITE_END()
