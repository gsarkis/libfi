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

#define CHECK_CLOSE_R(A, E) BOOST_CHECK_CLOSE((A).real().toDouble(), (E).real(), 0.0001)
#define CHECK_CLOSE_I(A, E) BOOST_CHECK_CLOSE((A).imag().toDouble(), (E).imag(), 0.0001)
#define CHECK_CLOSE_REAL(A, E) BOOST_CHECK_CLOSE((A).toDouble(), E, 0.0001)

// (to be used in the appropriate context)
#define ROUND_EXPECTED(R) C(round((R).real()*16)/16, round((R).imag()*16)/16);

BOOST_AUTO_TEST_SUITE( CFixed_arith )

BOOST_AUTO_TEST_CASE( addsub )
{
	typedef Fi::CFixed<16, 10, Fi::SIGNED, Fi::Throw, Fi::Classic> T;
	typedef std::complex<double> C;

	C z1(29.0185546875, 1);
	C z2(2.0, -30.5);
	T z1fx(z1.real(), z1.imag());
	T z2fx(z2.real(), z2.imag());

	CHECK_CLOSE_R( z1fx+z2fx, z1+z2 );
	CHECK_CLOSE_I( z1fx+z2fx, z1+z2 );
	CHECK_CLOSE_R( z1fx-z2fx, z1-z2 );
	CHECK_CLOSE_I( z1fx-z2fx, z1-z2 );
	CHECK_CLOSE_R( z2fx-z1fx, z2-z1 );
	CHECK_CLOSE_I( z2fx-z1fx, z2-z1 );	
}

BOOST_AUTO_TEST_CASE( mult )
{
	typedef Fi::CFixed<9, 4, Fi::SIGNED, Fi::Throw, Fi::Classic> T;
	typedef std::complex<double> C;

	C z1(0.5625, 13.5625);
	C z2(1.0, 1.0);
	T z1fx(z1.real(), z1.imag());
	T z2fx(z2.real(), z2.imag());

	CHECK_CLOSE_R( z1fx*z2fx, z1*z2 );
	CHECK_CLOSE_I( z1fx*z2fx, z1*z2 );

	z1= C(2.0, 2.0);
	z2= C(4.5, -3.0);
	z1fx= T(z1.real(), z1.imag());
	z2fx= T(z2.real(), z2.imag());
	std::complex<double> result= z1 * z2;
	result= ROUND_EXPECTED(result);
	CHECK_CLOSE_R( z1fx*z2fx, result);
	CHECK_CLOSE_I( z1fx*z2fx, result);
	
	z1= C(0.5, 13.5);
	z2= C(0.5, 0.25);
	z1fx= T(z1.real(), z1.imag());
	z2fx= T(z2.real(), z2.imag());
	result= z1 * z2;
	result= ROUND_EXPECTED(result);
	CHECK_CLOSE_R( z1fx*z2fx, result);
	CHECK_CLOSE_I( z1fx*z2fx, result);
}

BOOST_AUTO_TEST_CASE( norm )
{
	typedef Fi::CFixed<9, 4, Fi::SIGNED, Fi::Throw, Fi::Classic> T;
	typedef std::complex<double> C;

	C z1= C(0.5, 1.5);
	T z1fx= T(z1.real(), z1.imag());

	CHECK_CLOSE_REAL( std::norm(z1fx), std::norm(z1) );
}

// BOOST_AUTO_TEST_CASE( abs )
// {
// 	typedef Fi::CFixed<9, 4, Fi::SIGNED, Fi::Throw, Fi::Classic> T;
// 	typedef std::complex<double> C;

// 	C z1= C(0.5, 1.5);
// 	T z1fx= T(z1.real(), z1.imag());

// 	double expected= round(std::abs(z1)*16)/16;
// 	CHECK_CLOSE_REAL( std::abs(z1fx), expected );
// }

// BOOST_AUTO_TEST_CASE( arg )
// {
// 	typedef Fi::CFixed<9, 4, Fi::SIGNED, Fi::Throw, Fi::Classic> T;
// 	typedef std::complex<double> C;

// 	C z1= C(0.5, 1.5);
// 	T z1fx= T(z1.real(), z1.imag());

// 	double expected= round(std::arg(z1)*16)/16;
// 	CHECK_CLOSE_REAL( std::arg(z1fx), expected );
// }

BOOST_AUTO_TEST_SUITE_END()
