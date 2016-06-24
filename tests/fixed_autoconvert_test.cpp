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

#include "fi/Fixed.hpp"
#include "fi/overflow/Throw.hpp"
#include "fi/rounding/Classic.hpp"

#define BOOST_TEST_DYN_LINK true
#define BOOST_TEST_MODULE Fixed
#include <boost/test/unit_test.hpp>

#define CHECK_EQ(A, E) BOOST_CHECK_EQUAL((A).toString(), E)
#define CHECK_NOTEQ(A, E) BOOST_CHECK((A).toString() != E)

typedef Fi::Fixed<9,4, Fi::SIGNED, Fi::Throw, Fi::Classic> fi9_4s;
typedef Fi::Fixed<9,8, Fi::SIGNED, Fi::Throw, Fi::Classic> fi9_8s;

BOOST_AUTO_TEST_SUITE(Fi_autoconvert)

BOOST_AUTO_TEST_CASE( mult )
{
	fi9_4s a("4.5");
	fi9_8s b("0.5");

	a*= b;
	CHECK_EQ(a, "2.25");

	a= fi9_4s("-3.25");
	a*= b;
	CHECK_EQ(a, "-1.625");

	a= fi9_4s("15");
	b= fi9_8s("0.066666666"); // \approx 1/15
	a*= b;
	CHECK_EQ(a, "1.0");

	a= fi9_4s("15");
	fi9_4s c= fi9_4s("0.066666666");
	a*= c;
	CHECK_NOTEQ(a, "1.0");
	
}

BOOST_AUTO_TEST_SUITE_END()
