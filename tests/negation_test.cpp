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
#include "fi/overflow/Saturate.hpp"
#include "fi/overflow/Wrap.hpp"

#define BOOST_TEST_DYN_LINK true
#define BOOST_TEST_MODULE negation
#include <boost/test/unit_test.hpp>

#define CHECK_EQ(A, E) BOOST_CHECK_EQUAL((A).toString(), E)

BOOST_AUTO_TEST_SUITE( negation_unsigned )

BOOST_AUTO_TEST_CASE( unsigned_8_4_detection )
{

	typedef Fi::Fixed<8, 4, Fi::UNSIGNED, Fi::Throw> fi84t;

	CHECK_EQ( (-fi84t("0.0")), "0.0");
	BOOST_CHECK_THROW( (-fi84t("1.0")), Fi::NegativeOverflow );
	BOOST_CHECK_THROW( (-fi84t("3.125")), Fi::NegativeOverflow );
	BOOST_CHECK_THROW( (-fi84t("15.9375")), Fi::NegativeOverflow );

}

BOOST_AUTO_TEST_CASE( unsigned_8_4_saturate )
{

	typedef Fi::Fixed<8, 4, Fi::UNSIGNED, Fi::Saturate> fi84s;

	CHECK_EQ( (-fi84s("0.0")), "0.0");
	CHECK_EQ( (-fi84s("1.0")), "0.0");
	CHECK_EQ( (-fi84s("3.125")), "0.0");
	CHECK_EQ( (-fi84s("15.9375")), "0.0");

}

BOOST_AUTO_TEST_CASE( unsigned_8_4_wrap )
{

	typedef Fi::Fixed<8, 4, Fi::UNSIGNED, Fi::Wrap> fi84w;

	CHECK_EQ( (-fi84w("0.0")), "0.0");
	CHECK_EQ( (-fi84w("1.0")), "15.0");
	CHECK_EQ( (-fi84w("3.125")), "12.875");
	CHECK_EQ( (-fi84w("15.9375")), "0.0625");

}

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////


BOOST_AUTO_TEST_SUITE( negation_signed )

BOOST_AUTO_TEST_CASE( signed_8_4_detection )
{

	typedef Fi::Fixed<8, 4, Fi::SIGNED, Fi::Throw> fi84t;

	BOOST_CHECK_THROW( (-fi84t("-8.0")), Fi::PositiveOverflow);
	CHECK_EQ( (-fi84t("-1.125")), "1.125");
	CHECK_EQ( (-fi84t("0.0")), "0.0");
	CHECK_EQ( (-fi84t("1.0")), "-1.0");
	CHECK_EQ( (-fi84t("7.9375")), "-7.9375");
}

BOOST_AUTO_TEST_CASE( signed_8_4_saturation )
{

	typedef Fi::Fixed<8, 4, Fi::SIGNED, Fi::Saturate> fi84s;

	CHECK_EQ( (-fi84s("-8.0")), "7.9375");
	CHECK_EQ( (-fi84s("-1.125")), "1.125");
	CHECK_EQ( (-fi84s("0.0")), "0.0");
	CHECK_EQ( (-fi84s("1.0")), "-1.0");
	CHECK_EQ( (-fi84s("7.9375")), "-7.9375");
}

BOOST_AUTO_TEST_CASE( signed_8_4_wrap )
{

	typedef Fi::Fixed<8, 4, Fi::SIGNED, Fi::Wrap> fi84w;

	CHECK_EQ( (-fi84w("-8.0")), "-8.0");
	CHECK_EQ( (-fi84w("-1.125")), "1.125");
	CHECK_EQ( (-fi84w("0.0")), "0.0");
	CHECK_EQ( (-fi84w("1.0")), "-1.0");
	CHECK_EQ( (-fi84w("7.9375")), "-7.9375");
}

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( negation_unsigned_eq )

BOOST_AUTO_TEST_CASE( unsigned_4_4_detection )
{

	typedef Fi::Fixed<4, 4, Fi::UNSIGNED, Fi::Throw> fi4t;

	CHECK_EQ( (-fi4t("0.0")), "0.0");
	BOOST_CHECK_THROW( (-fi4t("0.125")), Fi::NegativeOverflow );
	BOOST_CHECK_THROW( (-fi4t("0.5")), Fi::NegativeOverflow );
	BOOST_CHECK_THROW( (-fi4t("0.9375")), Fi::NegativeOverflow );

}

BOOST_AUTO_TEST_CASE( unsigned_4_4_saturate )
{

	typedef Fi::Fixed<4, 4, Fi::UNSIGNED, Fi::Saturate> fi4s;

	CHECK_EQ( (-fi4s("0.0")), "0.0");
	CHECK_EQ( (-fi4s("0.125")), "0.0");
	CHECK_EQ( (-fi4s("0.5")), "0.0");
	CHECK_EQ( (-fi4s("0.9375")), "0.0");

}

BOOST_AUTO_TEST_CASE( unsigned_4_4_wrap )
{

	typedef Fi::Fixed<4, 4, Fi::UNSIGNED, Fi::Wrap> fi4w;

	CHECK_EQ( (-fi4w("0.0")), "0.0");
	CHECK_EQ( (-fi4w("0.125")), "0.875");
	CHECK_EQ( (-fi4w("0.5")), "0.5");
	CHECK_EQ( (-fi4w("0.9375")), "0.0625");

}

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////


BOOST_AUTO_TEST_SUITE( negation_signed_eq )

BOOST_AUTO_TEST_CASE( signed_4_4_detection )
{

	typedef Fi::Fixed<4, 4, Fi::SIGNED, Fi::Throw> fi4t;

	BOOST_CHECK_THROW( (-fi4t("-0.5")), Fi::PositiveOverflow);
	CHECK_EQ( (-fi4t("-0.125")), "0.125");
	CHECK_EQ( (-fi4t("0.0")), "0.0");
	CHECK_EQ( (-fi4t("0.125")), "-0.125");
	CHECK_EQ( (-fi4t("0.4375")), "-0.4375");
}

BOOST_AUTO_TEST_CASE( signed_4_4_saturation )
{

	typedef Fi::Fixed<4, 4, Fi::SIGNED, Fi::Saturate> fi4s;

	CHECK_EQ( (-fi4s("-0.5")), "0.4375");
	CHECK_EQ( (-fi4s("-0.125")), "0.125");
	CHECK_EQ( (-fi4s("0.0")), "0.0");
	CHECK_EQ( (-fi4s("0.125")), "-0.125");
	CHECK_EQ( (-fi4s("0.4375")), "-0.4375");

}

BOOST_AUTO_TEST_CASE( signed_4_4_wrap )
{

	typedef Fi::Fixed<4, 4, Fi::SIGNED, Fi::Wrap> fi4w;

	CHECK_EQ( (-fi4w("-0.5")), "-0.5");
	CHECK_EQ( (-fi4w("-0.125")), "0.125");
	CHECK_EQ( (-fi4w("0.0")), "0.0");
	CHECK_EQ( (-fi4w("0.125")), "-0.125");
	CHECK_EQ( (-fi4w("0.4375")), "-0.4375");
}

BOOST_AUTO_TEST_SUITE_END()
