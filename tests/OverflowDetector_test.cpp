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
#include "fi/private/OverflowDetector.hpp"

#define BOOST_TEST_DYN_LINK true
#define BOOST_TEST_MODULE overflow_detector
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( overflow_detection_signed )



BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////


BOOST_AUTO_TEST_SUITE( overflow_detection_unsigned )

BOOST_AUTO_TEST_CASE( overflow_double ) {

  typedef Fi::Fixed<8, 4, Fi::UNSIGNED, Fi::Throw> fi;
  typedef Fi::OverflowDetector< fi::TR, Fi::Throw > Det;

  BOOST_CHECK_THROW(Det::fromDouble(1e20, 0xFFF, 0.0), Fi::PositiveOverflow);
  //CHECK_EQ(fi8w(1e20), "0.0");

}

BOOST_AUTO_TEST_SUITE_END()
