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

#include "fi/private/StringConversion.hpp"
#include "fi/Fixed.hpp"

#define BOOST_TEST_DYN_LINK true
#define BOOST_TEST_MODULE StringConversion
#include <boost/test/unit_test.hpp>

#include <string>

using Fi::StringConversion::fractionalString;
using Fi::StringConversion::fromString;

BOOST_AUTO_TEST_SUITE( to_string )

BOOST_AUTO_TEST_CASE( fractional )
{

	typedef Fi::Traits<8, 8, 8, Fi::UNSIGNED> TR888U;

	BOOST_CHECK_EQUAL( fractionalString<TR888U>(0xFF), "99609375" );
	BOOST_CHECK_EQUAL( fractionalString<TR888U>(0x80), "5" );

	typedef Fi::Traits<8, 8, 8, Fi::SIGNED> TR888S;

	//-1 = 0xFF. GCC was complaining about this.
	BOOST_CHECK_EQUAL( fractionalString<TR888S>(-1), "00390625" );
	//-128 = 0x80. GCC was complaining about this.
	BOOST_CHECK_EQUAL( fractionalString<TR888S>(-128), "5" );

}

BOOST_AUTO_TEST_CASE( from_string )
{

	typedef Fi::Traits<8, 8, 8, Fi::SIGNED> TR888S;

	BOOST_CHECK_EQUAL( (unsigned char)((fromString<TR888S>("-0.5")).first) , 0x80 );
	BOOST_CHECK_EQUAL( (unsigned char)((fromString<TR888S>("7.9375")).first) , 0xF0 );

}

BOOST_AUTO_TEST_SUITE_END()
