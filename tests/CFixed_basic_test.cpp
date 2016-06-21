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

#define CHECK_CLOSE_R(A, E) BOOST_CHECK_CLOSE((A).real().toDouble(), (E).real(), 0.001)
#define CHECK_CLOSE_I(A, E) BOOST_CHECK_CLOSE((A).imag().toDouble(), (E).imag(), 0.001)

BOOST_AUTO_TEST_SUITE( CFixed_basic )

BOOST_AUTO_TEST_CASE( no_overflow )
{
	typedef Fi::CFixed<9, 4, Fi::SIGNED, Fi::Throw, Fi::Classic> T;
	typedef std::complex<double> C;

	CHECK_CLOSE_R( T(0.5714, 13.5861), C(0.5625, 13.5625) );
	CHECK_CLOSE_R( T(-0.5714, 13.5861), C(-0.5625, 13.5625) );
	CHECK_CLOSE_R( T(0.5714, -13.5861), C(0.5625, -13.5625) );
	CHECK_CLOSE_R( T(-0.5714, -13.5861), C(-0.5625, -13.5625) );
	CHECK_CLOSE_R( T(15.94, 15.96874), C(15.9375, 15.9375) );
	CHECK_CLOSE_R( T(-15.94, 15.96874), C(-15.9375, 15.9375) );
	CHECK_CLOSE_R( T(15.94, -15.96874), C(15.9375, -15.9375) );
	CHECK_CLOSE_R( T(-15.94, -15.96874), C(-15.9375, -15.9375) );

	CHECK_CLOSE_I( T(0.5714, 13.5861), C(0.5625, 13.5625) );
	CHECK_CLOSE_I( T(-0.5714, 13.5861), C(-0.5625, 13.5625) );
	CHECK_CLOSE_I( T(0.5714, -13.5861), C(0.5625, -13.5625) );
	CHECK_CLOSE_I( T(-0.5714, -13.5861), C(-0.5625, -13.5625) );
	CHECK_CLOSE_I( T(15.94, 15.96874), C(15.9375, 15.9375) );
	CHECK_CLOSE_I( T(-15.94, 15.96874), C(-15.9375, 15.9375) );
	CHECK_CLOSE_I( T(15.94, -15.96874), C(15.9375, -15.9375) );
	CHECK_CLOSE_I( T(-15.94, -15.96874), C(-15.9375, -15.9375) );
}

BOOST_AUTO_TEST_CASE( overflow_pos )
{
	typedef Fi::CFixed<9, 4, Fi::SIGNED, Fi::Throw, Fi::Classic> T;

	BOOST_CHECK_THROW( T(15.96875, 0), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( T(15.9999, 0), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( T(16.0   , 0), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( T(20.123 , 0), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( T(31.9375, 0), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( T(31.9475, 0), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( T(31.96875, 0), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( T(1e20   , 0), Fi::PositiveOverflow );

	BOOST_CHECK_THROW( T(0, 15.96875), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( T(0, 15.9999), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( T(0, 16.0   ), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( T(0, 20.123 ), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( T(0, 31.9375), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( T(0, 31.9475), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( T(0, 31.96875), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( T(0, 1e20   ), Fi::PositiveOverflow );
}

BOOST_AUTO_TEST_CASE( overflow_pos_2 )
{
	typedef Fi::CFixed<8, 4, Fi::SIGNED, Fi::Throw, Fi::Classic> T;

	BOOST_CHECK_THROW( T(7.96875 , 0), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( T(7.96999 , 0), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( T(8.0     , 0), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( T(16.123  , 0), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( T(31.96875, 0), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( T(31.96877, 0), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( T(1e20    , 0), Fi::PositiveOverflow );	

}

BOOST_AUTO_TEST_CASE( overflow_neg )
{
	typedef Fi::CFixed<8, 4, Fi::SIGNED, Fi::Throw, Fi::Classic> T;

	BOOST_CHECK_THROW( T(-8.0625 , 0), Fi::NegativeOverflow );
	BOOST_CHECK_THROW( T(-8.0001 , 0), Fi::NegativeOverflow );
	BOOST_CHECK_THROW( T(-8.01 , 0), Fi::NegativeOverflow );
	BOOST_CHECK_THROW( T(-10.1298 , 0), Fi::NegativeOverflow );
	BOOST_CHECK_THROW( T(-16.0625 , 0), Fi::NegativeOverflow );
	BOOST_CHECK_THROW( T(-16.96875 , 0), Fi::NegativeOverflow );
	BOOST_CHECK_THROW( T(-1e20 , 0), Fi::NegativeOverflow );

	BOOST_CHECK_THROW( T(0, -8.0625 ), Fi::NegativeOverflow );
	BOOST_CHECK_THROW( T(0, -8.0001 ), Fi::NegativeOverflow );
	BOOST_CHECK_THROW( T(0, -8.01 ), Fi::NegativeOverflow );
	BOOST_CHECK_THROW( T(0, -10.1298 ), Fi::NegativeOverflow );
	BOOST_CHECK_THROW( T(0, -16.0625 ), Fi::NegativeOverflow );
	BOOST_CHECK_THROW( T(0, -16.96875 ), Fi::NegativeOverflow );
	BOOST_CHECK_THROW( T(0, -1e20 ), Fi::NegativeOverflow );	
}

BOOST_AUTO_TEST_SUITE_END()
