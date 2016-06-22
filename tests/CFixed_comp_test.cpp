/*
 *Copyright © 2016 Francois Leduc-Primeau.

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

#include "fi/CFixed.hpp"
#include "fi/overflow/Throw.hpp"
#include "fi/rounding/Classic.hpp"

#define BOOST_TEST_DYN_LINK true
#define BOOST_TEST_MODULE overflow_detector
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include <iostream>
#include <complex>

#define CHECK_TRUE(A) BOOST_CHECK_EQUAL(A, true);
#define CHECK_FALSE(A) BOOST_CHECK_EQUAL(A, false);

BOOST_AUTO_TEST_SUITE( CFixed_comp )

BOOST_AUTO_TEST_CASE( eq )
{
	typedef Fi::CFixed<16, 10, Fi::SIGNED, Fi::Throw, Fi::Classic> T;

	T z1(1.34, 2.25);
	T z2(1.34, 2.25);
	T z3(-15.0, 4.3);
	T z4(-15.0, 4.3);
	
	CHECK_TRUE( z1 == z2 );
	CHECK_TRUE( z3 == z4 );
	CHECK_FALSE( (z1+z2) == z2 );
	CHECK_FALSE( z3 == z1 );
}

BOOST_AUTO_TEST_CASE( noteq )
{
	typedef Fi::CFixed<16, 10, Fi::SIGNED, Fi::Throw, Fi::Classic> T;

	T z1(1.34, 2.25);
	T z2(1.34, 2.25);
	T z3(-15.0, 4.3);
	T z4(-15.0, 4.3);

	CHECK_FALSE( z1 != z2 );
	CHECK_TRUE( (z1+z2) != z2 );
	CHECK_TRUE( z1 != z3 );
	CHECK_FALSE( z3 != z4 );
}

BOOST_AUTO_TEST_SUITE_END()
