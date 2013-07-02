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

#include "fi/private/DoubleConversion.hpp"

#define BOOST_TEST_DYN_LINK true
#define BOOST_TEST_MODULE double_conversion
#include <boost/test/unit_test.hpp>

using Fi::DoubleConversion::limitToRange;

BOOST_AUTO_TEST_SUITE( double_conversion )

BOOST_AUTO_TEST_CASE( in_range )
{

  BOOST_CHECK_EQUAL( limitToRange(-7, -8, 8), -7 );
  BOOST_CHECK_EQUAL( limitToRange(-7.99999, -8, 8), -7.99999 );
  BOOST_CHECK_EQUAL( limitToRange(-3, -8, 8), -3 );
  BOOST_CHECK_EQUAL( limitToRange(3, -8, 8), 3 );
  BOOST_CHECK_EQUAL( limitToRange(7, -8, 8), 7 );

}


BOOST_AUTO_TEST_CASE( out_of_range )
{

  BOOST_CHECK_EQUAL( limitToRange(-40.0, -8, 8), -8.0 );
  BOOST_CHECK_EQUAL( limitToRange(-32.0, -8, 8), 0.0 );
  BOOST_CHECK_EQUAL( limitToRange(-24.0, -8, 8), -8.0 );
  BOOST_CHECK_EQUAL( limitToRange(-16.0, -8, 8), 0.0 );
  BOOST_CHECK_EQUAL( limitToRange(-8.0, -8, 8), -8.0 );
  BOOST_CHECK_EQUAL( limitToRange(0.0, -8, 8), 0.0 );
  BOOST_CHECK_EQUAL( limitToRange(8.0, -8, 8), -8.0 );
  BOOST_CHECK_EQUAL( limitToRange(16.0, -8, 8), 0.0 );
  BOOST_CHECK_EQUAL( limitToRange(24.0, -8, 8), -8.0 );
  BOOST_CHECK_EQUAL( limitToRange(32.0, -8, 8), 0.0 );

}

BOOST_AUTO_TEST_CASE( out_of_range_1 )
{

  
  BOOST_CHECK_EQUAL( limitToRange(-31.0, -8, 8), 1.0 );
  BOOST_CHECK_EQUAL( limitToRange(-23.0, -8, 8), -7.0 );
  BOOST_CHECK_EQUAL( limitToRange(-15.0, -8, 8), 1.0 );
  BOOST_CHECK_EQUAL( limitToRange(-7.0, -8, 8), -7.0 );
  BOOST_CHECK_EQUAL( limitToRange(1.0, -8, 8), 1.0 );
  BOOST_CHECK_EQUAL( limitToRange(9.0, -8, 8), -7.0 );
  BOOST_CHECK_EQUAL( limitToRange(17.0, -8, 8), 1.0 );
  BOOST_CHECK_EQUAL( limitToRange(25.0, -8, 8), -7.0 );
  BOOST_CHECK_EQUAL( limitToRange(33.0, -8, 8), 1.0 );

}

BOOST_AUTO_TEST_CASE( out_of_range_large ) {

  BOOST_CHECK_EQUAL( limitToRange(1e20, -8, 8), 0.0 );
  BOOST_CHECK_EQUAL( limitToRange(-1e20, -8, 8), 0.0 );

}

BOOST_AUTO_TEST_SUITE_END()
