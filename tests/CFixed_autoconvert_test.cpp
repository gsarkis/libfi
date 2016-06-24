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

BOOST_AUTO_TEST_SUITE( CFixed_autoconvert )

BOOST_AUTO_TEST_CASE( mult )
{
	typedef Fi::CFixed<9, 4, Fi::SIGNED, Fi::Throw, Fi::Classic> T;
	typedef Fi::CFixed<9, 8, Fi::SIGNED, Fi::Throw, Fi::Classic> T2;

	T xFx(4.5, -3.5);
	std::complex<double> xFP(4.5, -3.5);
	T2 yFx(0.5, 0.5);
	std::complex<double> yFP(0.5, 0.5);

	xFx*= yFx;
	CHECK_CLOSE_R(xFx, xFP*yFP);
	CHECK_CLOSE_I(xFx, xFP*yFP);

	xFx= T(15.0, 0);
	//yFx= T2(0.0, 1/15);
	yFx= T2(0.0, 0.066666666);

	xFx*= yFx;
	std::complex<double> result(0.0, 1.0);
	CHECK_CLOSE_R(xFx, result);
	CHECK_CLOSE_I(xFx, result);
}

BOOST_AUTO_TEST_SUITE_END()
