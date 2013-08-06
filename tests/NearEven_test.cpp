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
#include "fi/overflow/Throw.hpp"
#include "fi/rounding/NearEven.hpp"

#define BOOST_TEST_DYN_LINK true
#define BOOST_TEST_MODULE overflow_detector
#include <boost/test/unit_test.hpp>

#include <iostream>

#define CHECK_EQ(A, E) BOOST_CHECK_EQUAL((A).toString(), E)

BOOST_AUTO_TEST_SUITE( neareven_unsigned )
BOOST_AUTO_TEST_CASE( no_overflow_fl )
{

	typedef Fi::Fixed<4, 2, Fi::UNSIGNED, Fi::Throw, Fi::NearEven> fic;

	CHECK_EQ( fic( 0.0000),  "0.0");
	CHECK_EQ( fic( 0.0625),  "0.0");
	CHECK_EQ( fic( 0.1250),  "0.0");
	CHECK_EQ( fic( 0.1875),  "0.25");

	CHECK_EQ( fic( 0.2500),  "0.25");
	CHECK_EQ( fic( 0.3125),  "0.25");
	CHECK_EQ( fic( 0.3750),  "0.5");
	CHECK_EQ( fic( 0.4375),  "0.5");

	CHECK_EQ( fic( 0.500),   "0.5");
	CHECK_EQ( fic( 0.5625),  "0.5");
	CHECK_EQ( fic( 0.6250),  "0.5");
	CHECK_EQ( fic( 0.6875),  "0.75");

	CHECK_EQ( fic( 0.7500),  "0.75");
	CHECK_EQ( fic( 0.8125),  "0.75");
	CHECK_EQ( fic( 0.8750),  "1.0");
	CHECK_EQ( fic( 0.9375),  "1.0");

	CHECK_EQ( fic( 3.75),    "3.75");
	CHECK_EQ( fic( 3.85),    "3.75");

}

BOOST_AUTO_TEST_CASE( overflow_fl ) {
	typedef Fi::Fixed<4, 2, Fi::UNSIGNED, Fi::Throw, Fi::NearEven> fic;

	BOOST_CHECK_THROW( fic(3.875),   Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic(3.9),     Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic(3.9),     Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic(16.0   ), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic(1e20   ), Fi::PositiveOverflow );
}

BOOST_AUTO_TEST_CASE( no_overflow_string )
{

	typedef Fi::Fixed<4, 2, Fi::UNSIGNED, Fi::Throw, Fi::NearEven> fic;

	CHECK_EQ( fic( "0.0000"),  "0.0");
	CHECK_EQ( fic( "0.0625"),  "0.0");
	CHECK_EQ( fic( "0.1250"),  "0.0");
	CHECK_EQ( fic( "0.1875"),  "0.25");

	CHECK_EQ( fic( "0.2500"),  "0.25");
	CHECK_EQ( fic( "0.3125"),  "0.25");
	CHECK_EQ( fic( "0.3750"),  "0.5");
	CHECK_EQ( fic( "0.4375"),  "0.5");

	CHECK_EQ( fic( "0.5000"),  "0.5");
	CHECK_EQ( fic( "0.5625"),  "0.5");
	CHECK_EQ( fic( "0.6250"),  "0.5");
	CHECK_EQ( fic( "0.6875"),  "0.75");

	CHECK_EQ( fic( "0.7500"),  "0.75");
	CHECK_EQ( fic( "0.8125"),  "0.75");
	CHECK_EQ( fic( "0.8750"),  "1.0");
	CHECK_EQ( fic( "0.9375"),  "1.0");

	CHECK_EQ( fic( 3.75),      "3.75");
	CHECK_EQ( fic( 3.85),      "3.75");

}

BOOST_AUTO_TEST_CASE( overflow_string ) {

	typedef Fi::Fixed<4, 2, Fi::UNSIGNED, Fi::Throw, Fi::NearEven> fic;

	BOOST_CHECK_THROW( fic("3.875"),   Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic("3.9"),     Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic("3.9"),     Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic("16.0"),    Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic("1000000000.123"), Fi::PositiveOverflow );

}

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( neareven_signed )

BOOST_AUTO_TEST_CASE( s_no_overflow_fl )
{

	typedef Fi::Fixed<4, 2, Fi::SIGNED, Fi::Throw, Fi::NearEven> fic;

	//same as above
	CHECK_EQ( fic( 0.0000),  "0.0");
	CHECK_EQ( fic( 0.0625),  "0.0");
	CHECK_EQ( fic( 0.1250),  "0.0");
	CHECK_EQ( fic( 0.1875),  "0.25");

	CHECK_EQ( fic( 0.2500),  "0.25");
	CHECK_EQ( fic( 0.3125),  "0.25");
	CHECK_EQ( fic( 0.3750),  "0.5");
	CHECK_EQ( fic( 0.4375),  "0.5");

	CHECK_EQ( fic( 0.5000),  "0.5");
	CHECK_EQ( fic( 0.5625),  "0.5");
	CHECK_EQ( fic( 0.6250),  "0.5");
	CHECK_EQ( fic( 0.6875),  "0.75");

	CHECK_EQ( fic( 0.7500),  "0.75");
	CHECK_EQ( fic( 0.8125),  "0.75");
	CHECK_EQ( fic( 0.8750),  "1.0");
	CHECK_EQ( fic( 0.9375),  "1.0");

	//custom for signed
	CHECK_EQ( fic( -0.000),   "0.0");
	CHECK_EQ( fic( -0.0625),  "0.0");
	CHECK_EQ( fic( -0.1250),  "0.0");
	CHECK_EQ( fic( -0.1875),  "-0.25");
	CHECK_EQ( fic( -0.2500),  "-0.25");

	CHECK_EQ( fic( -0.3125),  "-0.25");
	CHECK_EQ( fic( -0.3750),  "-0.5");
	CHECK_EQ( fic( -0.4375),  "-0.5");
	CHECK_EQ( fic( -0.5000),  "-0.5");

	CHECK_EQ( fic( -0.5625),  "-0.5");
	CHECK_EQ( fic( -0.6250),  "-0.5");
	CHECK_EQ( fic( -0.6875),  "-0.75");
	CHECK_EQ( fic( -0.7500),  "-0.75");

	CHECK_EQ( fic( -0.8125),  "-0.75");
	CHECK_EQ( fic( -0.8750),  "-1.0");
	CHECK_EQ( fic( -0.9375),  "-1.0");
	CHECK_EQ( fic( -1.0000),  "-1.0");

	CHECK_EQ( fic(-2.0625),   "-2.0");
	CHECK_EQ( fic(-2.1250),   "-2.0");

}

BOOST_AUTO_TEST_CASE( s_overflow_fl ) {

	typedef Fi::Fixed<4, 2, Fi::SIGNED, Fi::Throw, Fi::NearEven> fic;

	BOOST_CHECK_THROW( fic(1.875),     Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic(1.9),       Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic(1.9),       Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic(16.0   ),   Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic(1e20   ),   Fi::PositiveOverflow );

	BOOST_CHECK_THROW( fic(-2.24),     Fi::NegativeOverflow );
	BOOST_CHECK_THROW( fic(-2.25),     Fi::NegativeOverflow );
	BOOST_CHECK_THROW( fic(-16.0   ),  Fi::NegativeOverflow );
	BOOST_CHECK_THROW( fic(-1e20   ),  Fi::NegativeOverflow );

}

BOOST_AUTO_TEST_CASE( s_no_overflow_string )
{

	typedef Fi::Fixed<4, 2, Fi::SIGNED, Fi::Throw, Fi::NearEven> fic;

	//same as above
	CHECK_EQ( fic( "0.0000"),  "0.0");
	CHECK_EQ( fic( "0.0625"),  "0.0");
	CHECK_EQ( fic( "0.1250"),  "0.0");
	CHECK_EQ( fic( "0.1875"),  "0.25");

	CHECK_EQ( fic( "0.2500"),  "0.25");
	CHECK_EQ( fic( "0.3125"),  "0.25");
	CHECK_EQ( fic( "0.3750"),  "0.5");
	CHECK_EQ( fic( "0.4375"),  "0.5");

	CHECK_EQ( fic( "0.5000"),  "0.5");
	CHECK_EQ( fic( "0.5625"),  "0.5");
	CHECK_EQ( fic( "0.6250"),  "0.5");
	CHECK_EQ( fic( "0.6875"),  "0.75");

	CHECK_EQ( fic( "0.7500"),  "0.75");
	CHECK_EQ( fic( "0.8125"),  "0.75");
	CHECK_EQ( fic( "0.8750"),  "1.0");
	CHECK_EQ( fic( "0.9375"),  "1.0");

	//custom for signed
	CHECK_EQ( fic( "-0.0000"),  "0.0");
	CHECK_EQ( fic( "-0.0625"),  "0.0");
	CHECK_EQ( fic( "-0.1250"),  "0.0");
	CHECK_EQ( fic( "-0.1875"),  "-0.25");
	CHECK_EQ( fic( "-0.2500"),  "-0.25");

	CHECK_EQ( fic( "-0.3125"),  "-0.25");
	CHECK_EQ( fic( "-0.3750"),  "-0.5");
	CHECK_EQ( fic( "-0.4375"),  "-0.5");
	CHECK_EQ( fic( "-0.5000"),  "-0.5");

	CHECK_EQ( fic( "-0.5625"),  "-0.5");
	CHECK_EQ( fic( "-0.6250"),  "-0.5");
	CHECK_EQ( fic( "-0.6875"),  "-0.75");
	CHECK_EQ( fic( "-0.7500"),  "-0.75");

	CHECK_EQ( fic( "-0.8125"),  "-0.75");
	CHECK_EQ( fic( "-0.8750"),  "-1.0");
	CHECK_EQ( fic( "-0.9375"),  "-1.0");
	CHECK_EQ( fic( "-1.0000"),  "-1.0");

}

BOOST_AUTO_TEST_CASE( s_overflow_string ) {

	typedef Fi::Fixed<4, 2, Fi::SIGNED, Fi::Throw, Fi::NearEven> fic;

	BOOST_CHECK_THROW( fic("1.875"),     Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic("1.9"),       Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic("1.9"),       Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic("16.0"   ),   Fi::PositiveOverflow );

	BOOST_CHECK_THROW( fic("-2.24"),      Fi::NegativeOverflow );
	BOOST_CHECK_THROW( fic("-2.25"),     Fi::NegativeOverflow );
	BOOST_CHECK_THROW( fic("-16.0"   ),  Fi::NegativeOverflow );

}

BOOST_AUTO_TEST_SUITE_END()
