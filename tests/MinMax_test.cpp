/*
 *Copyright © 2013 Alexandre Raymond.

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
#define BOOST_TEST_MODULE overflow_detector
#include <boost/test/unit_test.hpp>

#define CHECK_EQ(A, E) BOOST_CHECK_EQUAL((A).toString(), E)

BOOST_AUTO_TEST_SUITE( min_max )

BOOST_AUTO_TEST_CASE( signed_unsigned )
{

	typedef Fi::Fixed<8, 4, Fi::UNSIGNED> fiu;
	typedef Fi::Fixed<8, 4, Fi::SIGNED> fis;

	CHECK_EQ( Fi::max(fiu(1.25), fiu(2.0)), "2.0" );
	CHECK_EQ( Fi::min(fiu(1.25), fiu(2.0)), "1.25" );

	CHECK_EQ( Fi::max(fis(1.25), fis(2.0)), "2.0" );
	CHECK_EQ( Fi::min(fis(-1.25), fis(2.0)), "-1.25" );

	CHECK_EQ( Fi::max(fis(1.25), fis(-2.0)), "1.25" );
	CHECK_EQ( Fi::min(fis(-1.25), fis(-2.0)), "-2.0" );

}

BOOST_AUTO_TEST_CASE( fraction_size )
{

	typedef Fi::Fixed<8, 1, Fi::UNSIGNED> fiu1;

	CHECK_EQ( Fi::max(fiu1(1.5), fiu1(2.0)), "2.0" );
	CHECK_EQ( Fi::min(fiu1(1.5), fiu1(2.0)), "1.5" );

}

BOOST_AUTO_TEST_CASE( total_size )
{

	typedef Fi::Fixed<18, 1, Fi::UNSIGNED> fiu1;

	CHECK_EQ( Fi::max(fiu1(11.5), fiu1(12.0)), "12.0" );
	CHECK_EQ( Fi::min(fiu1(11.5), fiu1(12.0)), "11.5" );

}

BOOST_AUTO_TEST_SUITE_END()
