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
#include "fi/rounding/Ceil.hpp"

#define BOOST_TEST_DYN_LINK true
#define BOOST_TEST_MODULE overflow_detector
#include <boost/test/unit_test.hpp>

#include <iostream>

#define CHECK_EQ(A, E) BOOST_CHECK_EQUAL((A).toString(), E)

BOOST_AUTO_TEST_SUITE( ceil_unsigned )

BOOST_AUTO_TEST_CASE( no_overflow_fl )
{

	typedef Fi::Fixed<8, 4, Fi::UNSIGNED, Fi::Throw, Fi::Ceil> fic;

	CHECK_EQ( fic( 0.0)   , "0.0"    );
	CHECK_EQ( fic( 0.001) , "0.0625" );
	CHECK_EQ( fic( 0.01)  , "0.0625" );
	CHECK_EQ( fic( 0.1)   , "0.125"  );
	CHECK_EQ( fic( 0.5714),  "0.625" );
	CHECK_EQ( fic(13.5861), "13.625" );
	CHECK_EQ( fic(14.9439), "15.0"   );
	CHECK_EQ( fic(10.8598), "10.875" );
	CHECK_EQ( fic(12.1238), "12.125" );
	CHECK_EQ( fic(11.8901), "11.9375");
	CHECK_EQ( fic( 6.2756),  "6.3125");
	CHECK_EQ( fic(10.4876), "10.5"   );
	CHECK_EQ( fic( 2.7390),  "2.75"  );
	CHECK_EQ( fic(11.2967), "11.3125");
	CHECK_EQ( fic(15.9375), "15.9375");

}

BOOST_AUTO_TEST_CASE( overflow_fl ) {

	typedef Fi::Fixed<8, 4, Fi::UNSIGNED, Fi::Throw, Fi::Ceil> fic;

	BOOST_CHECK_THROW( fic(15.9376), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic(15.9475), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic(15.9999), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic(16.0   ), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic(20.123 ), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic(31.9375), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic(31.9475), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic(1e20   ), Fi::PositiveOverflow );

}

BOOST_AUTO_TEST_CASE( no_overflow_string )
{

	typedef Fi::Fixed<8, 4, Fi::UNSIGNED, Fi::Throw, Fi::Ceil> fic;

	CHECK_EQ( fic( "0.0")   , "0.0"    );
	CHECK_EQ( fic( "0.001") , "0.0625" );
	CHECK_EQ( fic( "0.01")  , "0.0625" );
	CHECK_EQ( fic( "0.1")   , "0.125"  );
	CHECK_EQ( fic( "0.5714"),  "0.625" );
	CHECK_EQ( fic("13.5861"), "13.625" );
	CHECK_EQ( fic("14.9439"), "15.0"   );
	CHECK_EQ( fic("10.8598"), "10.875" );
	CHECK_EQ( fic("12.1238"), "12.125" );
	CHECK_EQ( fic("11.8901"), "11.9375");
	CHECK_EQ( fic( "6.2756"),  "6.3125");
	CHECK_EQ( fic("10.4876"), "10.5"   );
	CHECK_EQ( fic( "2.7390"),  "2.75"  );
	CHECK_EQ( fic("11.2967"), "11.3125");
	CHECK_EQ( fic("15.9375"), "15.9375");

}

BOOST_AUTO_TEST_CASE( overflow_string ) {

	typedef Fi::Fixed<8, 4, Fi::UNSIGNED, Fi::Throw, Fi::Ceil> fic;

	BOOST_CHECK_THROW( fic("15.9376"), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic("15.9475"), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic("15.9999"), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic("16.0"   ), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic("20.123" ), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic("31.9375"), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic("31.9475"), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic("1000000000.123"), Fi::PositiveOverflow );

}

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( ceil_unsigned )

BOOST_AUTO_TEST_CASE( s_no_overflow_fl ) {

	typedef Fi::Fixed<8, 4, Fi::SIGNED, Fi::Throw, Fi::Ceil> fic;

	CHECK_EQ( fic(-8.0624), "-8.0");
	CHECK_EQ( fic(-8.01), "-8.0");
	CHECK_EQ( fic(-8.0), "-8.0");

	CHECK_EQ( fic(7.9375), "7.9375");

	CHECK_EQ( fic(-7.4907), "-7.4375");
	CHECK_EQ( fic(-3.5692), "-3.5625");
	CHECK_EQ( fic(-7.2613), "-7.25");
	CHECK_EQ( fic(-6.4459), "-6.4375");
	CHECK_EQ( fic( 5.1753),  "5.1875");
	CHECK_EQ( fic( 3.1173),  "3.125");
	CHECK_EQ( fic(-2.9264), "-2.875");
	CHECK_EQ( fic( 7.2036),  "7.25");
	CHECK_EQ( fic(-7.4489), "-7.4375");
	CHECK_EQ( fic(-0.9801), "-0.9375");

	CHECK_EQ( fic( 0.0)   , "0.0"    );
	CHECK_EQ( fic( 0.001) , "0.0625" );
	CHECK_EQ( fic( 0.01)  , "0.0625" );
	CHECK_EQ( fic( 0.1)   , "0.125"  );

	CHECK_EQ( fic( -0.0)   , "0.0"    );
	CHECK_EQ( fic( -0.001) , "0.0" );
	CHECK_EQ( fic( -0.01)  , "0.0" );
	CHECK_EQ( fic( -0.1)   , "-0.0625"  );

}

BOOST_AUTO_TEST_CASE( s_overflow_fl ) {

	typedef Fi::Fixed<8, 4, Fi::SIGNED, Fi::Throw, Fi::Ceil> fic;

	BOOST_CHECK_THROW( fic(-8.0625 ), Fi::NegativeOverflow );
	BOOST_CHECK_THROW( fic(-10.1298 ), Fi::NegativeOverflow );
	BOOST_CHECK_THROW( fic(-16.0625 ), Fi::NegativeOverflow );
	BOOST_CHECK_THROW( fic(-1e20 ), Fi::NegativeOverflow );

	BOOST_CHECK_THROW( fic(7.93751 ), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic(7.99  ), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic(7.95  ), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic(8.0   ), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic(16.123 ), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic(31.9375), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic(31.9475), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic(1e20   ), Fi::PositiveOverflow );


}

BOOST_AUTO_TEST_CASE( s_no_overflow_string ) {

	typedef Fi::Fixed<8, 4, Fi::SIGNED, Fi::Throw, Fi::Ceil> fic;

	CHECK_EQ( fic("-8.0624"), "-8.0");
	CHECK_EQ( fic("-8.01"), "-8.0");
	CHECK_EQ( fic("-8.0"), "-8.0");

	CHECK_EQ( fic("7.9375"), "7.9375");

	CHECK_EQ( fic("-7.4907"), "-7.4375");
	CHECK_EQ( fic("-3.5692"), "-3.5625");
	CHECK_EQ( fic("-7.2613"), "-7.25");
	CHECK_EQ( fic("-6.4459"), "-6.4375");
	CHECK_EQ( fic( "5.1753"),  "5.1875");
	CHECK_EQ( fic( "3.1173"),  "3.125");
	CHECK_EQ( fic("-2.9264"), "-2.875");
	CHECK_EQ( fic( "7.2036"),  "7.25");
	CHECK_EQ( fic("-7.4489"), "-7.4375");
	CHECK_EQ( fic("-0.9801"), "-0.9375");

	CHECK_EQ( fic( "0.0")   , "0.0"    );
	CHECK_EQ( fic( "0.001") , "0.0625" );
	CHECK_EQ( fic( "0.01")  , "0.0625" );
	CHECK_EQ( fic( "0.1")   , "0.125"  );

	CHECK_EQ( fic( "-0.0")   , "0.0"    );
	CHECK_EQ( fic( "-0.001") , "0.0" );
	CHECK_EQ( fic( "-0.01")  , "0.0" );
	CHECK_EQ( fic( "-0.1")   , "-0.0625"  );

}

BOOST_AUTO_TEST_CASE( s_overflow_string ) {

	typedef Fi::Fixed<8, 4, Fi::SIGNED, Fi::Throw, Fi::Ceil> fic;

	BOOST_CHECK_THROW( fic("-8.0625"), Fi::NegativeOverflow );
	BOOST_CHECK_THROW( fic("-10.1298"), Fi::NegativeOverflow );
	BOOST_CHECK_THROW( fic("-16.0625"), Fi::NegativeOverflow );
	BOOST_CHECK_THROW( fic("-1000000"), Fi::NegativeOverflow );

	BOOST_CHECK_THROW( fic("7.93751" ), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic("7.99"  ), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic("7.95"  ), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic("8.0"   ), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic("16.123" ), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic("31.9375"), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic("31.9475"), Fi::PositiveOverflow );
	BOOST_CHECK_THROW( fic("10000000"), Fi::PositiveOverflow );


}

BOOST_AUTO_TEST_SUITE_END()
