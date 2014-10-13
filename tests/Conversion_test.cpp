/*

 *Copyright © 2013 Gabi Sarkis.

 *This file is part of the C++ Fixed-Point Library (LibFi).

 *LibFi is free software: you can redistribute it and/or modify
 *it under the terms of the GNU General Public License as published by
 *the Free Software Foundation, either version 3 of the License, or
 *(at your option) any later version.

 *LibFi is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *GNU General Public License for more details.

 *You should have received a copy of the GNU General Public License
 *along with LibFi.  If not, see <http://www.gnu.org/licenses/>.

 */

#include "fi/Fixed.hpp"
#include "fi/overflow/Saturate.hpp"
#include "fi/overflow/Throw.hpp"
#include "fi/overflow/Wrap.hpp"

#include "fi/rounding/Classic.hpp"
#include "fi/rounding/Ceil.hpp"
#include "fi/rounding/Floor.hpp"

#define BOOST_TEST_DYN_LINK true
#define BOOST_TEST_MODULE overflow_detector
#include <boost/test/unit_test.hpp>

#include <iostream>

#define CHECK_EQ(A, E) BOOST_CHECK_EQUAL((A).toString(), E)

BOOST_AUTO_TEST_SUITE( conversion_unsigned )

BOOST_AUTO_TEST_CASE( u_up_throw )
{

	typedef Fi::Fixed<10, 5, Fi::UNSIGNED, Fi::Throw> fi1;
	typedef Fi::Fixed<8, 4, Fi::UNSIGNED, Fi::Throw> fi2;

	CHECK_EQ( fi1::fromFixed(fi2("15.9375")), "15.9375" );
	CHECK_EQ( fi1::fromFixed(fi2("15.0")), "15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("4.75")), "4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("2.5")), "2.5");
	CHECK_EQ( fi1::fromFixed(fi2("1.25")), "1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0625")), "0.0625" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0")), "0.0" );

}

BOOST_AUTO_TEST_CASE( u_up_sat )
{

	typedef Fi::Fixed<10, 5, Fi::UNSIGNED, Fi::Saturate> fi1;
	typedef Fi::Fixed<8, 4, Fi::UNSIGNED, Fi::Saturate> fi2;

	CHECK_EQ( fi1::fromFixed(fi2("15.9375")), "15.9375" );
	CHECK_EQ( fi1::fromFixed(fi2("15.0")), "15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("4.75")), "4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("2.5")), "2.5");
	CHECK_EQ( fi1::fromFixed(fi2("1.25")), "1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0625")), "0.0625" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0")), "0.0" );

}

BOOST_AUTO_TEST_CASE( u_up_wrap )
{

	typedef Fi::Fixed<10, 5, Fi::UNSIGNED, Fi::Saturate> fi1;
	typedef Fi::Fixed<8, 4, Fi::UNSIGNED, Fi::Saturate> fi2;

	CHECK_EQ( fi1::fromFixed(fi2("15.9375")), "15.9375" );
	CHECK_EQ( fi1::fromFixed(fi2("15.0")), "15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("4.75")), "4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("2.5")), "2.5");
	CHECK_EQ( fi1::fromFixed(fi2("1.25")), "1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0625")), "0.0625" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0")), "0.0" );

}

BOOST_AUTO_TEST_CASE( u_up_wrap_2 )
{

	typedef Fi::Fixed<9, 5, Fi::SIGNED, Fi::Wrap> fi1;
	typedef Fi::Fixed<10, 5, Fi::SIGNED, Fi::Wrap> fi2;

	CHECK_EQ( fi2::fromFixed(fi1("-0.15625")), "-0.15625" );

}

BOOST_AUTO_TEST_CASE( u_up_ceil )
{

	typedef Fi::Fixed<10, 5, Fi::UNSIGNED, Fi::Throw, Fi::Ceil> fi1;
	typedef Fi::Fixed<8, 4, Fi::UNSIGNED, Fi::Throw, Fi::Ceil> fi2;

	CHECK_EQ( fi1::fromFixed(fi2("15.9375")), "15.9375" );
	CHECK_EQ( fi1::fromFixed(fi2("15.0")), "15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("4.75")), "4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("2.5")), "2.5");
	CHECK_EQ( fi1::fromFixed(fi2("1.25")), "1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0625")), "0.0625" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0")), "0.0" );

}

BOOST_AUTO_TEST_CASE( u_up_classic )
{

	typedef Fi::Fixed<10, 5, Fi::UNSIGNED, Fi::Throw, Fi::Classic> fi1;
	typedef Fi::Fixed<8, 4, Fi::UNSIGNED, Fi::Throw, Fi::Classic> fi2;

	CHECK_EQ( fi1::fromFixed(fi2("15.9375")), "15.9375" );
	CHECK_EQ( fi1::fromFixed(fi2("15.0")), "15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("4.75")), "4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("2.5")), "2.5");
	CHECK_EQ( fi1::fromFixed(fi2("1.25")), "1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0625")), "0.0625" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0")), "0.0" );

}

BOOST_AUTO_TEST_CASE( u_up_fix )
{

	typedef Fi::Fixed<10, 5, Fi::UNSIGNED, Fi::Throw, Fi::Fix> fi1;
	typedef Fi::Fixed<8, 4, Fi::UNSIGNED, Fi::Throw, Fi::Fix> fi2;

	CHECK_EQ( fi1::fromFixed(fi2("15.9375")), "15.9375" );
	CHECK_EQ( fi1::fromFixed(fi2("15.0")), "15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("4.75")), "4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("2.5")), "2.5");
	CHECK_EQ( fi1::fromFixed(fi2("1.25")), "1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0625")), "0.0625" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0")), "0.0" );

}

BOOST_AUTO_TEST_CASE( u_up_floor )
{

	typedef Fi::Fixed<10, 5, Fi::UNSIGNED, Fi::Throw, Fi::Floor> fi1;
	typedef Fi::Fixed<8, 4, Fi::UNSIGNED, Fi::Throw, Fi::Floor> fi2;

	CHECK_EQ( fi1::fromFixed(fi2("15.9375")), "15.9375" );
	CHECK_EQ( fi1::fromFixed(fi2("15.0")), "15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("4.75")), "4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("2.5")), "2.5");
	CHECK_EQ( fi1::fromFixed(fi2("1.25")), "1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0625")), "0.0625" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0")), "0.0" );

}


BOOST_AUTO_TEST_CASE( u_down_throw )
{

	typedef Fi::Fixed<8, 4, Fi::UNSIGNED, Fi::Throw> fi1;
	typedef Fi::Fixed<10, 5, Fi::UNSIGNED, Fi::Throw> fi2;

	CHECK_EQ( fi1::fromFixed(fi2("15.9375")), "15.9375" );
	CHECK_EQ( fi1::fromFixed(fi2("15.0")), "15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("4.75")), "4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("2.5")), "2.5");
	CHECK_EQ( fi1::fromFixed(fi2("1.25")), "1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0625")), "0.0625" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0")), "0.0" );

}

BOOST_AUTO_TEST_CASE( u_down_sat )
{

	typedef Fi::Fixed<7, 4, Fi::UNSIGNED, Fi::Saturate> fi1;
	typedef Fi::Fixed<8, 4, Fi::UNSIGNED, Fi::Saturate> fi2;

	CHECK_EQ( fi1::fromFixed(fi2("15.9375")), "7.9375" );
	CHECK_EQ( fi1::fromFixed(fi2("15.0")), "7.9375" );
	CHECK_EQ( fi1::fromFixed(fi2("7.95")), "7.9375" );
	CHECK_EQ( fi1::fromFixed(fi2("4.75")), "4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("2.5")), "2.5");
	CHECK_EQ( fi1::fromFixed(fi2("1.25")), "1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0625")), "0.0625" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0")), "0.0" );

}

BOOST_AUTO_TEST_CASE( u_down_wrap )
{

	typedef Fi::Fixed<7, 4, Fi::UNSIGNED, Fi::Wrap> fi1;
	typedef Fi::Fixed<8, 4, Fi::UNSIGNED, Fi::Wrap> fi2;

	CHECK_EQ( fi1::fromFixed(fi2("15.9375")), "7.9375" );
	CHECK_EQ( fi1::fromFixed(fi2("15.0")), "7.0" );
	CHECK_EQ( fi1::fromFixed(fi2("7.95")), "7.9375" );
	CHECK_EQ( fi1::fromFixed(fi2("4.75")), "4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("2.5")), "2.5");
	CHECK_EQ( fi1::fromFixed(fi2("1.25")), "1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0625")), "0.0625" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0")), "0.0" );

}

BOOST_AUTO_TEST_CASE( u_down_ceil )
{

	typedef Fi::Fixed<8, 3, Fi::UNSIGNED, Fi::Wrap, Fi::Ceil> fi1;
	typedef Fi::Fixed<8, 4, Fi::UNSIGNED, Fi::Wrap, Fi::Ceil> fi2;

	CHECK_EQ( fi1::fromFixed(fi2("15.1875")), "15.25" );
	CHECK_EQ( fi1::fromFixed(fi2("15.0")), "15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("7.95")), "8.0" );
	CHECK_EQ( fi1::fromFixed(fi2("4.75")), "4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("2.5")), "2.5");
	CHECK_EQ( fi1::fromFixed(fi2("1.25")), "1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0625")), "0.125" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0")), "0.0" );

}

BOOST_AUTO_TEST_CASE( u_down_classic )
{

	typedef Fi::Fixed<8, 3, Fi::UNSIGNED, Fi::Wrap, Fi::Classic> fi1;
	typedef Fi::Fixed<8, 4, Fi::UNSIGNED, Fi::Wrap, Fi::Classic> fi2;

	CHECK_EQ( fi1::fromFixed(fi2("15.1875")), "15.25" );
	CHECK_EQ( fi1::fromFixed(fi2("15.0")), "15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("7.95")), "8.0" );
	CHECK_EQ( fi1::fromFixed(fi2("4.75")), "4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("2.5")), "2.5");
	CHECK_EQ( fi1::fromFixed(fi2("1.25")), "1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0625")), "0.125" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0")), "0.0" );

}

BOOST_AUTO_TEST_CASE( u_down_fix )
{

	typedef Fi::Fixed<8, 3, Fi::UNSIGNED, Fi::Wrap, Fi::Fix> fi1;
	typedef Fi::Fixed<8, 4, Fi::UNSIGNED, Fi::Wrap, Fi::Fix> fi2;

	CHECK_EQ( fi1::fromFixed(fi2("15.9375")), "15.875" );
	CHECK_EQ( fi1::fromFixed(fi2("15.0")), "15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("7.95")), "7.875" );
	CHECK_EQ( fi1::fromFixed(fi2("4.75")), "4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("2.5")), "2.5");
	CHECK_EQ( fi1::fromFixed(fi2("1.25")), "1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0625")), "0.0" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0")), "0.0" );

}

BOOST_AUTO_TEST_CASE( u_down_floor )
{

	typedef Fi::Fixed<8, 3, Fi::UNSIGNED, Fi::Wrap, Fi::Floor> fi1;
	typedef Fi::Fixed<8, 4, Fi::UNSIGNED, Fi::Wrap, Fi::Floor> fi2;

	CHECK_EQ( fi1::fromFixed(fi2("15.9375")), "15.875" );
	CHECK_EQ( fi1::fromFixed(fi2("15.0")), "15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("7.95")), "7.875" );
	CHECK_EQ( fi1::fromFixed(fi2("4.75")), "4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("2.5")), "2.5");
	CHECK_EQ( fi1::fromFixed(fi2("1.25")), "1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0625")), "0.0" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0")), "0.0" );

}


BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( conversion_signed )

BOOST_AUTO_TEST_CASE( s_up_throw )
{

	typedef Fi::Fixed<10, 5, Fi::SIGNED, Fi::Throw> fi1;
	typedef Fi::Fixed<9, 4, Fi::SIGNED, Fi::Throw> fi2;

	CHECK_EQ( fi1::fromFixed(fi2("15.9375")), "15.9375" );
	CHECK_EQ( fi1::fromFixed(fi2("15.0")), "15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("4.75")), "4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("2.5")), "2.5");
	CHECK_EQ( fi1::fromFixed(fi2("1.25")), "1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0625")), "0.0625" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0")), "0.0" );

	CHECK_EQ( fi1::fromFixed(fi2("-0.0625")), "-0.0625" );
	CHECK_EQ( fi1::fromFixed(fi2("-1.25")), "-1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("-2.5")), "-2.5");
	CHECK_EQ( fi1::fromFixed(fi2("-4.75")), "-4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("-15.0")), "-15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("-15.9375")), "-15.9375" );

}

BOOST_AUTO_TEST_CASE( s_up_sat )
{

	typedef Fi::Fixed<10, 5, Fi::SIGNED, Fi::Saturate> fi1;
	typedef Fi::Fixed<9, 4, Fi::SIGNED, Fi::Saturate> fi2;

	CHECK_EQ( fi1::fromFixed(fi2("15.9375")), "15.9375" );
	CHECK_EQ( fi1::fromFixed(fi2("15.0")), "15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("4.75")), "4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("2.5")), "2.5");
	CHECK_EQ( fi1::fromFixed(fi2("1.25")), "1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0625")), "0.0625" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0")), "0.0" );

	CHECK_EQ( fi1::fromFixed(fi2("-0.0625")), "-0.0625" );
	CHECK_EQ( fi1::fromFixed(fi2("-1.25")), "-1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("-2.5")), "-2.5");
	CHECK_EQ( fi1::fromFixed(fi2("-4.75")), "-4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("-15.0")), "-15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("-15.9375")), "-15.9375" );

}

BOOST_AUTO_TEST_CASE( s_up_wrap )
{

	typedef Fi::Fixed<10, 5, Fi::SIGNED, Fi::Saturate> fi1;
	typedef Fi::Fixed<9, 4, Fi::SIGNED, Fi::Saturate> fi2;

	CHECK_EQ( fi1::fromFixed(fi2("15.9375")), "15.9375" );
	CHECK_EQ( fi1::fromFixed(fi2("15.0")), "15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("4.75")), "4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("2.5")), "2.5");
	CHECK_EQ( fi1::fromFixed(fi2("1.25")), "1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0625")), "0.0625" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0")), "0.0" );

	CHECK_EQ( fi1::fromFixed(fi2("-0.0625")), "-0.0625" );
	CHECK_EQ( fi1::fromFixed(fi2("-1.25")), "-1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("-2.5")), "-2.5");
	CHECK_EQ( fi1::fromFixed(fi2("-4.75")), "-4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("-15.0")), "-15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("-15.9375")), "-15.9375" );

}

BOOST_AUTO_TEST_CASE( s_up_ceil )
{

	typedef Fi::Fixed<10, 5, Fi::SIGNED, Fi::Throw, Fi::Ceil> fi1;
	typedef Fi::Fixed<9, 4, Fi::SIGNED, Fi::Throw, Fi::Ceil> fi2;

	CHECK_EQ( fi1::fromFixed(fi2("15.9375")), "15.9375" );
	CHECK_EQ( fi1::fromFixed(fi2("15.0")), "15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("4.75")), "4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("2.5")), "2.5");
	CHECK_EQ( fi1::fromFixed(fi2("1.25")), "1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0625")), "0.0625" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0")), "0.0" );

	CHECK_EQ( fi1::fromFixed(fi2("-0.0625")), "-0.0625" );
	CHECK_EQ( fi1::fromFixed(fi2("-1.25")), "-1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("-2.5")), "-2.5");
	CHECK_EQ( fi1::fromFixed(fi2("-4.75")), "-4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("-15.0")), "-15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("-15.9375")), "-15.9375" );

}

BOOST_AUTO_TEST_CASE( s_up_classic )
{

	typedef Fi::Fixed<10, 5, Fi::SIGNED, Fi::Throw, Fi::Classic> fi1;
	typedef Fi::Fixed<9, 4, Fi::SIGNED, Fi::Throw, Fi::Classic> fi2;

	CHECK_EQ( fi1::fromFixed(fi2("15.9375")), "15.9375" );
	CHECK_EQ( fi1::fromFixed(fi2("15.0")), "15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("4.75")), "4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("2.5")), "2.5");
	CHECK_EQ( fi1::fromFixed(fi2("1.25")), "1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0625")), "0.0625" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0")), "0.0" );

	CHECK_EQ( fi1::fromFixed(fi2("-0.0625")), "-0.0625" );
	CHECK_EQ( fi1::fromFixed(fi2("-1.25")), "-1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("-2.5")), "-2.5");
	CHECK_EQ( fi1::fromFixed(fi2("-4.75")), "-4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("-15.0")), "-15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("-15.9375")), "-15.9375" );

}

BOOST_AUTO_TEST_CASE( s_up_fix )
{

	typedef Fi::Fixed<10, 5, Fi::SIGNED, Fi::Throw, Fi::Fix> fi1;
	typedef Fi::Fixed<9, 4, Fi::SIGNED, Fi::Throw, Fi::Fix> fi2;

	CHECK_EQ( fi1::fromFixed(fi2("15.9375")), "15.9375" );
	CHECK_EQ( fi1::fromFixed(fi2("15.0")), "15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("4.75")), "4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("2.5")), "2.5");
	CHECK_EQ( fi1::fromFixed(fi2("1.25")), "1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0625")), "0.0625" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0")), "0.0" );

	CHECK_EQ( fi1::fromFixed(fi2("-0.0625")), "-0.0625" );
	CHECK_EQ( fi1::fromFixed(fi2("-1.25")), "-1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("-2.5")), "-2.5");
	CHECK_EQ( fi1::fromFixed(fi2("-4.75")), "-4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("-15.0")), "-15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("-15.9375")), "-15.9375" );

}

BOOST_AUTO_TEST_CASE( s_up_floor )
{

	typedef Fi::Fixed<10, 5, Fi::SIGNED, Fi::Throw, Fi::Floor> fi1;
	typedef Fi::Fixed<9, 4, Fi::SIGNED, Fi::Throw, Fi::Floor> fi2;

	CHECK_EQ( fi1::fromFixed(fi2("15.9375")), "15.9375" );
	CHECK_EQ( fi1::fromFixed(fi2("15.0")), "15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("4.75")), "4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("2.5")), "2.5");
	CHECK_EQ( fi1::fromFixed(fi2("1.25")), "1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0625")), "0.0625" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0")), "0.0" );

	CHECK_EQ( fi1::fromFixed(fi2("-0.0625")), "-0.0625" );
	CHECK_EQ( fi1::fromFixed(fi2("-1.25")), "-1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("-2.5")), "-2.5");
	CHECK_EQ( fi1::fromFixed(fi2("-4.75")), "-4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("-15.0")), "-15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("-15.9375")), "-15.9375" );

}


BOOST_AUTO_TEST_CASE( s_down_throw )
{

	typedef Fi::Fixed<9, 4, Fi::SIGNED, Fi::Throw> fi1;
	typedef Fi::Fixed<10, 5, Fi::SIGNED, Fi::Throw> fi2;

	CHECK_EQ( fi1::fromFixed(fi2("15.9375")), "15.9375" );
	CHECK_EQ( fi1::fromFixed(fi2("15.0")), "15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("4.75")), "4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("2.5")), "2.5");
	CHECK_EQ( fi1::fromFixed(fi2("1.25")), "1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0625")), "0.0625" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0")), "0.0" );

	CHECK_EQ( fi1::fromFixed(fi2("-0.0625")), "-0.0625" );
	CHECK_EQ( fi1::fromFixed(fi2("-1.25")), "-1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("-2.5")), "-2.5");
	CHECK_EQ( fi1::fromFixed(fi2("-4.75")), "-4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("-15.0")), "-15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("-15.9375")), "-15.9375" );

}

BOOST_AUTO_TEST_CASE( s_down_sat )
{

	typedef Fi::Fixed<8, 4, Fi::SIGNED, Fi::Saturate> fi1;
	typedef Fi::Fixed<9, 4, Fi::SIGNED, Fi::Saturate> fi2;

	CHECK_EQ( fi1::fromFixed(fi2("15.9375")), "7.9375" );
	CHECK_EQ( fi1::fromFixed(fi2("15.0")), "7.9375" );
	CHECK_EQ( fi1::fromFixed(fi2("7.95")), "7.9375" );
	CHECK_EQ( fi1::fromFixed(fi2("4.75")), "4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("2.5")), "2.5");
	CHECK_EQ( fi1::fromFixed(fi2("1.25")), "1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0625")), "0.0625" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0")), "0.0" );

	CHECK_EQ( fi1::fromFixed(fi2("-0.0625")), "-0.0625" );
	CHECK_EQ( fi1::fromFixed(fi2("-1.25")), "-1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("-2.5")), "-2.5");
	CHECK_EQ( fi1::fromFixed(fi2("-4.75")), "-4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("-7.9375")), "-7.9375" );
	CHECK_EQ( fi1::fromFixed(fi2("-15.0")), "-8.0" );
	CHECK_EQ( fi1::fromFixed(fi2("-15.9375")), "-8.0" );

}

BOOST_AUTO_TEST_CASE( s_down_wrap )
{

	typedef Fi::Fixed<8, 4, Fi::SIGNED, Fi::Wrap> fi1;
	typedef Fi::Fixed<9, 4, Fi::SIGNED, Fi::Wrap> fi2;

	CHECK_EQ( fi1::fromFixed(fi2("15.9375")), "-0.0625" );
	CHECK_EQ( fi1::fromFixed(fi2("15.0")), "-1.0" );
	CHECK_EQ( fi1::fromFixed(fi2("7.95")), "7.9375" );
	CHECK_EQ( fi1::fromFixed(fi2("4.75")), "4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("2.5")), "2.5");
	CHECK_EQ( fi1::fromFixed(fi2("1.25")), "1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0625")), "0.0625" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0")), "0.0" );

	CHECK_EQ( fi1::fromFixed(fi2("-0.0625")), "-0.0625" );
	CHECK_EQ( fi1::fromFixed(fi2("-1.25")), "-1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("-2.5")), "-2.5");
	CHECK_EQ( fi1::fromFixed(fi2("-4.75")), "-4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("-7.9375")), "-7.9375" );
	CHECK_EQ( fi1::fromFixed(fi2("-15.0")), "1.0" );
	CHECK_EQ( fi1::fromFixed(fi2("-15.9375")), "0.0625" );

}

BOOST_AUTO_TEST_CASE( s_down_ceil )
{

	typedef Fi::Fixed<9, 3, Fi::SIGNED, Fi::Wrap, Fi::Ceil> fi1;
	typedef Fi::Fixed<9, 4, Fi::SIGNED, Fi::Wrap, Fi::Ceil> fi2;

	CHECK_EQ( fi1::fromFixed(fi2("15.1875")), "15.25" );
	CHECK_EQ( fi1::fromFixed(fi2("15.0")), "15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("7.95")), "8.0" );
	CHECK_EQ( fi1::fromFixed(fi2("4.75")), "4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("2.5")), "2.5");
	CHECK_EQ( fi1::fromFixed(fi2("1.25")), "1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0625")), "0.125" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0")), "0.0" );

	CHECK_EQ( fi1::fromFixed(fi2("-0.0625")), "0.0" );
	CHECK_EQ( fi1::fromFixed(fi2("-1.25")), "-1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("-2.5")), "-2.5");
	CHECK_EQ( fi1::fromFixed(fi2("-4.75")), "-4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("-7.95")), "-7.875" );
	CHECK_EQ( fi1::fromFixed(fi2("-15.0")), "-15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("-15.1875")), "-15.125" );

}

BOOST_AUTO_TEST_CASE( s_down_classic )
{

	typedef Fi::Fixed<9, 3, Fi::SIGNED, Fi::Wrap, Fi::Classic> fi1;
	typedef Fi::Fixed<9, 4, Fi::SIGNED, Fi::Wrap, Fi::Classic> fi2;

	CHECK_EQ( fi1::fromFixed(fi2("15.1875")), "15.25" );
	CHECK_EQ( fi1::fromFixed(fi2("15.0")), "15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("7.95")), "8.0" );
	CHECK_EQ( fi1::fromFixed(fi2("4.75")), "4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("2.5")), "2.5");
	CHECK_EQ( fi1::fromFixed(fi2("1.25")), "1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0625")), "0.125" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0")), "0.0" );

	CHECK_EQ( fi1::fromFixed(fi2("-0.0625")), "-0.125" );
	CHECK_EQ( fi1::fromFixed(fi2("-1.25")), "-1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("-2.5")), "-2.5");
	CHECK_EQ( fi1::fromFixed(fi2("-4.75")), "-4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("-7.95")), "-8.0" );
	CHECK_EQ( fi1::fromFixed(fi2("-15.0")), "-15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("-15.1875")), "-15.25" );

}

BOOST_AUTO_TEST_CASE( s_down_fix )
{

	typedef Fi::Fixed<9, 3, Fi::SIGNED, Fi::Wrap, Fi::Fix> fi1;
	typedef Fi::Fixed<9, 4, Fi::SIGNED, Fi::Wrap, Fi::Fix> fi2;

	CHECK_EQ( fi1::fromFixed(fi2("15.9375")), "15.875" );
	CHECK_EQ( fi1::fromFixed(fi2("15.0")), "15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("7.95")), "7.875" );
	CHECK_EQ( fi1::fromFixed(fi2("4.75")), "4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("2.5")), "2.5");
	CHECK_EQ( fi1::fromFixed(fi2("1.25")), "1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0625")), "0.0" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0")), "0.0" );

	CHECK_EQ( fi1::fromFixed(fi2("-0.0625")), "0.0" );
	CHECK_EQ( fi1::fromFixed(fi2("-1.25")), "-1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("-2.5")), "-2.5");
	CHECK_EQ( fi1::fromFixed(fi2("-4.75")), "-4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("-7.95")), "-7.875" );
	CHECK_EQ( fi1::fromFixed(fi2("-15.0")), "-15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("-15.1875")), "-15.125" );

}

BOOST_AUTO_TEST_CASE( s_down_floor )
{

	typedef Fi::Fixed<9, 3, Fi::SIGNED, Fi::Wrap, Fi::Floor> fi1;
	typedef Fi::Fixed<9, 4, Fi::SIGNED, Fi::Wrap, Fi::Floor> fi2;

	CHECK_EQ( fi1::fromFixed(fi2("15.9375")), "15.875" );
	CHECK_EQ( fi1::fromFixed(fi2("15.0")), "15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("7.95")), "7.875" );
	CHECK_EQ( fi1::fromFixed(fi2("4.75")), "4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("2.5")), "2.5");
	CHECK_EQ( fi1::fromFixed(fi2("1.25")), "1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0625")), "0.0" );
	CHECK_EQ( fi1::fromFixed(fi2("0.0")), "0.0" );

	CHECK_EQ( fi1::fromFixed(fi2("-0.0625")), "-0.125" );
	CHECK_EQ( fi1::fromFixed(fi2("-1.25")), "-1.25" );
	CHECK_EQ( fi1::fromFixed(fi2("-2.5")), "-2.5");
	CHECK_EQ( fi1::fromFixed(fi2("-4.75")), "-4.75" );
	CHECK_EQ( fi1::fromFixed(fi2("-7.95")), "-8.0" );
	CHECK_EQ( fi1::fromFixed(fi2("-15.0")), "-15.0" );
	CHECK_EQ( fi1::fromFixed(fi2("-15.1875")), "-15.25" );

}


BOOST_AUTO_TEST_SUITE_END()
