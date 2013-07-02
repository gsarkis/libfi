/*
 * 
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

#define BOOST_TEST_DYN_LINK true
#define BOOST_TEST_MODULE min_max_val
#include <boost/test/unit_test.hpp>

#define CHECK_EQ(A, E) BOOST_CHECK_EQUAL((A).toString(), E)

BOOST_AUTO_TEST_CASE( unsigned_min_val ) {

  typedef Fi::Fixed<4, 4, Fi::UNSIGNED> fi4;
  CHECK_EQ( (fi4::MinVal()), "0.0");

  typedef Fi::Fixed<6, 3, Fi::UNSIGNED> fi63;
  CHECK_EQ( (fi63::MinVal()), "0.0");

  typedef Fi::Fixed<7, 3, Fi::UNSIGNED> fi73;
  CHECK_EQ( (fi73::MinVal()), "0.0");

  typedef Fi::Fixed<8, 4, Fi::UNSIGNED> fi84;
  CHECK_EQ( (fi84::MinVal()), "0.0");

}

BOOST_AUTO_TEST_CASE( unsigned_max_val ) {

  typedef Fi::Fixed<4, 4, Fi::UNSIGNED> fi4;
  CHECK_EQ( (fi4::MaxVal()), "0.9375");

  typedef Fi::Fixed<6, 3, Fi::UNSIGNED> fi63;
  CHECK_EQ( (fi63::MaxVal()), "7.875");

  typedef Fi::Fixed<7, 3, Fi::UNSIGNED> fi73;
  CHECK_EQ( (fi73::MaxVal()), "15.875");

  typedef Fi::Fixed<8, 4, Fi::UNSIGNED> fi84;
  CHECK_EQ( (fi84::MaxVal()), "15.9375");

}

BOOST_AUTO_TEST_CASE( signed_min_val ) {

  typedef Fi::Fixed<4, 4, Fi::SIGNED> fi4;
  CHECK_EQ( (fi4::MinVal()), "-0.5");

  typedef Fi::Fixed<6, 3, Fi::SIGNED> fi63;
  CHECK_EQ( (fi63::MinVal()), "-4.0");

  typedef Fi::Fixed<7, 3, Fi::SIGNED> fi73;
  CHECK_EQ( (fi73::MinVal()), "-8.0");

  typedef Fi::Fixed<8, 4, Fi::SIGNED> fi84;
  CHECK_EQ( (fi84::MinVal()), "-8.0");

}

BOOST_AUTO_TEST_CASE( signed_max_val ) {

  typedef Fi::Fixed<4, 4, Fi::SIGNED> fi4;
  CHECK_EQ( (fi4::MaxVal()), "0.4375");

  typedef Fi::Fixed<6, 3, Fi::SIGNED> fi63;
  CHECK_EQ( (fi63::MaxVal()), "3.875");

  typedef Fi::Fixed<7, 3, Fi::SIGNED> fi73;
  CHECK_EQ( (fi73::MaxVal()), "7.875");

  typedef Fi::Fixed<8, 4, Fi::SIGNED> fi84;
  CHECK_EQ( (fi84::MaxVal()), "7.9375");

}
