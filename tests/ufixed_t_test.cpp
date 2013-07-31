/*
 *
 *Copyright © 2011 Gabi Sarkis.

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
#include "fi/overflow/Saturate.hpp"
#include "fi/overflow/Throw.hpp"
#include "fi/overflow/Wrap.hpp"

#define BOOST_TEST_DYN_LINK true
#define BOOST_TEST_MODULE uFixed
#include <boost/test/unit_test.hpp>

#define CHECK_EQ(A, E) BOOST_CHECK_EQUAL((A).toString(), E)

typedef Fi::Fixed<8, 4, Fi::UNSIGNED, Fi::Saturate> fi8s;

BOOST_AUTO_TEST_SUITE(Saturate)
BOOST_AUTO_TEST_CASE( saturate_flp_construction )
{

	CHECK_EQ(fi8s(1e20), "15.9375");
	CHECK_EQ(fi8s(16.0), "15.9375" );
	CHECK_EQ(fi8s(15.9375f), "15.9375" );
	CHECK_EQ(fi8s(7.9375), "7.9375");
	CHECK_EQ(fi8s(4.123), "4.0625");
	CHECK_EQ(fi8s(1.0f), "1.0");
	CHECK_EQ(fi8s(0.0), "0.0");
	CHECK_EQ(fi8s(-1.123), "0.0");
	CHECK_EQ(fi8s(-19.0), "0.0");

}

BOOST_AUTO_TEST_CASE( saturate_str_construction )
{

	CHECK_EQ(fi8s("1000000000000000000000000.0"), "15.9375");
	CHECK_EQ(fi8s("16.0"), "15.9375" );
	CHECK_EQ(fi8s("15.9375"), "15.9375" );
	CHECK_EQ(fi8s("9.0"), "9.0" );
	CHECK_EQ(fi8s("7.9375"), "7.9375");
	CHECK_EQ(fi8s("4.123"), "4.0625");
	CHECK_EQ(fi8s("1.0"), "1.0");
	CHECK_EQ(fi8s("0.0"), "0.0");

	CHECK_EQ(fi8s("000004.123"), "4.0625");

	BOOST_CHECK_THROW(fi8s("-9.0"), std::invalid_argument);
	BOOST_CHECK_THROW(fi8s("abc"), std::invalid_argument);
	BOOST_CHECK_THROW(fi8s("8.0.01"), std::invalid_argument);

}

BOOST_AUTO_TEST_CASE( saturate_add )
{

	CHECK_EQ(fi8s("0.0") + fi8s("14.123"), "14.0625");
	CHECK_EQ(fi8s("3.123") + fi8s("0.0"), "3.0625");
	CHECK_EQ(fi8s("1.0") + fi8s("3.0"), "4.0");
	CHECK_EQ(fi8s("6.0") + fi8s("10.0"), "15.9375");

	CHECK_EQ(fi8s( "8.166706486120111") + fi8s("10.675027211092726"), "15.9375");
	CHECK_EQ(fi8s( "0.507730321101910") + fi8s( "4.750194427708022"), "5.25");
	CHECK_EQ(fi8s("12.358953766892963") + fi8s("11.006365423173214"), "15.9375");
	CHECK_EQ(fi8s( "7.200477333276465") + fi8s( "7.071570706397456"), "14.25");
	CHECK_EQ(fi8s( "8.804272635917481") + fi8s( "3.759932265267421"), "12.5");
	CHECK_EQ(fi8s( "3.392959193571562") + fi8s( "4.173940158067184"), "7.5");
	CHECK_EQ(fi8s( "7.757061016729224") + fi8s("14.215592535930147"), "15.9375");
	CHECK_EQ(fi8s("14.623593317803982") + fi8s( "7.811197271925399"), "15.9375");
	CHECK_EQ(fi8s( "8.071375895442914") + fi8s( "1.604623251593447"), "9.625");
	CHECK_EQ(fi8s( "5.791169538438560") + fi8s( "9.684914136531665"), "15.375");

}

BOOST_AUTO_TEST_CASE( saturate_sub )
{

	CHECK_EQ(fi8s("0.0") - fi8s("14.123"), "0.0");
	CHECK_EQ(fi8s("3.123") - fi8s("0.0"), "3.0625");
	CHECK_EQ(fi8s("6.0") - fi8s("10.0"), "0.0");

	CHECK_EQ(fi8s( "8.166706486120111") - fi8s("10.675027211092726"), "0.0");
	CHECK_EQ(fi8s( "0.507730321101910") - fi8s( "4.750194427708022"), "0.0");
	CHECK_EQ(fi8s("12.358953766892963") - fi8s("11.006365423173214"), "1.3125");
	CHECK_EQ(fi8s( "7.200477333276465") - fi8s( "7.071570706397456"), "0.125");
	CHECK_EQ(fi8s( "8.804272635917481") - fi8s( "3.759932265267421"), "5.0");
	CHECK_EQ(fi8s( "3.392959193571562") - fi8s( "4.173940158067184"), "0.0");
	CHECK_EQ(fi8s( "7.757061016729224") - fi8s("14.215592535930147"), "0.0");
	CHECK_EQ(fi8s("14.623593317803982") - fi8s( "7.811197271925399"), "6.8125");
	CHECK_EQ(fi8s( "8.071375895442914") - fi8s( "1.604623251593447"), "6.5");
	CHECK_EQ(fi8s( "5.791169538438560") - fi8s( "9.684914136531665"), "0.0");

}

BOOST_AUTO_TEST_CASE( saturate_mul )
{
	//Directed
	CHECK_EQ(fi8s("0") * fi8s("6.234"), "0.0");
	CHECK_EQ(fi8s("1.234") * fi8s("0.0"), "0.0");
	CHECK_EQ(fi8s("1.125") * fi8s("1.0"), "1.125");
	CHECK_EQ(fi8s("1.0") * fi8s("1.125"), "1.125");
	//Random
	CHECK_EQ(fi8s( "8.166706486120111") * fi8s("10.675027211092726"), "15.9375");
	CHECK_EQ(fi8s( "0.507730321101910") * fi8s( "4.750194427708022"), "2.375");
	CHECK_EQ(fi8s("12.358953766892963") * fi8s("11.006365423173214"), "15.9375");
	CHECK_EQ(fi8s( "7.200477333276465") * fi8s( "7.071570706397456"), "15.9375");
	CHECK_EQ(fi8s( "8.804272635917481") * fi8s( "3.759932265267421"), "15.9375");
	CHECK_EQ(fi8s( "3.392959193571562") * fi8s( "4.173940158067184"), "13.875");
	CHECK_EQ(fi8s( "7.757061016729224") * fi8s("14.215592535930147"), "15.9375");
	CHECK_EQ(fi8s("14.623593317803982") * fi8s( "7.811197271925399"), "15.9375");
	CHECK_EQ(fi8s( "8.071375895442914") * fi8s( "1.604623251593447"), "12.5625");
	CHECK_EQ(fi8s( "5.791169538438560") * fi8s( "9.684914136531665"), "15.9375");

}

BOOST_AUTO_TEST_CASE( saturate_div ) {

	//Directed
	CHECK_EQ(fi8s("0") / fi8s("6.234"), "0.0");
	CHECK_EQ(fi8s("1.125") / fi8s("1.0"), "1.125");
	CHECK_EQ(fi8s("1.0") / fi8s("1.125"), "0.875");
	//Random
	CHECK_EQ(fi8s( "8.166706486120111") / fi8s("10.675027211092726"), "0.75");
	CHECK_EQ(fi8s( "0.507730321101910") / fi8s( "4.750194427708022"), "0.0625");
	CHECK_EQ(fi8s("12.358953766892963") / fi8s("11.006365423173214"), "1.0625");
	CHECK_EQ(fi8s( "7.200477333276465") / fi8s( "7.071570706397456"), "1.0");
	CHECK_EQ(fi8s( "8.804272635917481") / fi8s( "3.759932265267421"), "2.3125");
	CHECK_EQ(fi8s( "3.392959193571562") / fi8s( "4.173940158067184"), "0.8125");
	CHECK_EQ(fi8s( "7.757061016729224") / fi8s("14.215592535930147"), "0.5");
	CHECK_EQ(fi8s("14.623593317803982") / fi8s( "7.811197271925399"), "1.875");
	CHECK_EQ(fi8s( "8.071375895442914") / fi8s( "1.604623251593447"), "5.125");
	CHECK_EQ(fi8s( "5.791169538438560") / fi8s( "9.684914136531665"), "0.5625");

	CHECK_EQ(fi8s("13.329528734447672") / fi8s("0.702582514675030"),  "15.9375");
	CHECK_EQ(fi8s( "4.209521444258016") / fi8s("5.646696541209569"),  "0.6875");
	CHECK_EQ(fi8s( "4.708846376190046") / fi8s("6.343968266867194"),  "0.6875");
	CHECK_EQ(fi8s("13.255598133088446") / fi8s("6.668712941371484"),  "2.0");
	CHECK_EQ(fi8s( "0.330151768675361") / fi8s("0.148657609474102"),  "2.5");
	CHECK_EQ(fi8s("13.564899245972654") / fi8s("5.579927923473343"),  "2.4375");
	CHECK_EQ(fi8s( "6.577733241138658") / fi8s("7.372743473296302"),  "0.875");
	CHECK_EQ(fi8s( "7.320401340687432") / fi8s("6.537891962177564"),  "1.125");
	CHECK_EQ(fi8s("12.554209689821736") / fi8s("0.382952038033004"),  "15.9375");
	CHECK_EQ(fi8s( "7.150780532966863") / fi8s("2.948953122635400"),  "2.375");

}

BOOST_AUTO_TEST_CASE( saturate_comp_lt ) {

	BOOST_CHECK(fi8s(0.14) < fi8s(0.9567));
	BOOST_CHECK(!(fi8s(3.14) < fi8s(0.9567)));
	BOOST_CHECK(!(fi8s(3.14) < fi8s(3.14)));

}

BOOST_AUTO_TEST_CASE( saturate_comp_eq ) {

	BOOST_CHECK(fi8s(0.14) == fi8s(0.14));
	BOOST_CHECK(!(fi8s(0.14) == fi8s(0.24)));
	BOOST_CHECK(!(fi8s(10.14) == fi8s(0.24)));

}

BOOST_AUTO_TEST_CASE( saturate_comp_neq ) {

	BOOST_CHECK(fi8s(0.14) != fi8s(10.14));
	BOOST_CHECK(!(fi8s(0.14) != fi8s(0.14)));
	BOOST_CHECK(fi8s(0.14) != fi8s(0.24));

}

BOOST_AUTO_TEST_CASE( saturate_comp_gt ) {

	BOOST_CHECK(fi8s(1.54) > fi8s(0.9567));
	BOOST_CHECK(!(fi8s(3.14) > fi8s(10.9567)));
	BOOST_CHECK(!(fi8s(3.14) > fi8s(3.14)));

}

BOOST_AUTO_TEST_CASE( saturate_comp_lte ) {

	BOOST_CHECK(fi8s(0.14) <= fi8s(0.9567));
	BOOST_CHECK(!(fi8s(3.14) <= fi8s(0.9567)));
	BOOST_CHECK(fi8s(3.14) <= fi8s(3.14));

}

BOOST_AUTO_TEST_CASE( saturate_comp_gte ) {

	BOOST_CHECK(fi8s(1.54) >= fi8s(0.9567));
	BOOST_CHECK(!(fi8s(3.14) >= fi8s(10.9567)));
	BOOST_CHECK(fi8s(3.14) >= fi8s(3.14));

}

BOOST_AUTO_TEST_CASE( saturate_shift ) {

	fi8s b("0.9375");

	b = ~b;
	CHECK_EQ(b, "15.0");

	b >>= 1;
	CHECK_EQ(b, "7.5");

	b <<= 1;
	CHECK_EQ(b, "15.0");

	b >>= 1;
	b <<= 2;
	CHECK_EQ(b, "15.9375");

	CHECK_EQ(b>>1, "7.9375");
	CHECK_EQ(b, "15.9375");

	CHECK_EQ(b<<1, "15.9375");
	CHECK_EQ(b<<2, "15.9375");

}


BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////

typedef Fi::Fixed<8, 4, Fi::UNSIGNED, Fi::Wrap> fi8w;

BOOST_AUTO_TEST_SUITE(Wrap)

BOOST_AUTO_TEST_CASE( wrap_flp_construction )
{

	CHECK_EQ(fi8w(1e20), "0.0");
	CHECK_EQ(fi8w(17.125), "1.125");
	CHECK_EQ(fi8w(16.0f), "0.0");
	CHECK_EQ(fi8w(15.9375), "15.9375");
	CHECK_EQ(fi8w(4.123), "4.0625");
	CHECK_EQ(fi8w(1.0f), "1.0");
	CHECK_EQ(fi8w(0.0), "0.0");
	CHECK_EQ(fi8w(-0.0), "0.0");
	CHECK_EQ(fi8w(-1.0), "15.0");
	CHECK_EQ(fi8w(-1.25), "14.75");
	CHECK_EQ(fi8w(-9.0), "7.0");
	CHECK_EQ(fi8w(-19.0), "13.0");

}

BOOST_AUTO_TEST_CASE( wrap_str_construction )
{

	CHECK_EQ(fi8w("1000000000000000000000000.0"), "0.0");
	CHECK_EQ(fi8w("17.125"), "1.125");
	CHECK_EQ(fi8w("16.0"), "0.0");
	CHECK_EQ(fi8w("15.9375"), "15.9375");
	CHECK_EQ(fi8w("4.123"), "4.0625");
	CHECK_EQ(fi8w("1.0"), "1.0");
	CHECK_EQ(fi8w("0.0"), "0.0");

	CHECK_EQ(fi8w("000004.123"), "4.0625");
	BOOST_CHECK_THROW(fi8s("-9.0"), std::invalid_argument);
	BOOST_CHECK_THROW(fi8s("abc"), std::invalid_argument);
	BOOST_CHECK_THROW(fi8s("8.0.01"), std::invalid_argument);

}

BOOST_AUTO_TEST_CASE( wrap_add )
{

	CHECK_EQ(fi8w("2.75") + fi8w("0.0"), "2.75");
	CHECK_EQ(fi8w("0.0") + fi8w("14.0625"), "14.0625");

	CHECK_EQ(fi8w( "8.166706486120111") + fi8w("10.675027211092726"), "2.75");
	CHECK_EQ(fi8w( "0.507730321101910") + fi8w( "4.750194427708022"), "5.25");
	CHECK_EQ(fi8w("12.358953766892963") + fi8w("11.006365423173214"), "7.3125");
	CHECK_EQ(fi8w( "7.200477333276465") + fi8w( "7.071570706397456"), "14.25");
	CHECK_EQ(fi8w( "8.804272635917481") + fi8w( "3.759932265267421"), "12.5");
	CHECK_EQ(fi8w( "3.392959193571562") + fi8w( "4.173940158067184"), "7.5");
	CHECK_EQ(fi8w( "7.757061016729224") + fi8w("14.215592535930147"), "5.9375");
	CHECK_EQ(fi8w("14.623593317803982") + fi8w( "7.811197271925399"), "6.3125");
	CHECK_EQ(fi8w( "8.071375895442914") + fi8w( "1.604623251593447"), "9.625");
	CHECK_EQ(fi8w( "5.791169538438560") + fi8w( "9.684914136531665"), "15.375");

}

BOOST_AUTO_TEST_CASE( wrap_sub )
{

	CHECK_EQ(fi8w("2.75") - fi8w("0.0"), "2.75");
	CHECK_EQ(fi8w("0.0") - fi8w("14.0625"), "1.9375");

	CHECK_EQ(fi8w( "8.166706486120111") - fi8w("10.675027211092726"), "13.5");
	CHECK_EQ(fi8w( "0.507730321101910") - fi8w( "4.750194427708022"), "11.75");
	CHECK_EQ(fi8w("12.358953766892963") - fi8w("11.006365423173214"), "1.3125");
	CHECK_EQ(fi8w( "7.200477333276465") - fi8w( "7.071570706397456"), "0.125");
	CHECK_EQ(fi8w( "8.804272635917481") - fi8w( "3.759932265267421"), "5.0");
	CHECK_EQ(fi8w( "3.392959193571562") - fi8w( "4.173940158067184"), "15.25");
	CHECK_EQ(fi8w( "7.757061016729224") - fi8w("14.215592535930147"), "9.5625");
	CHECK_EQ(fi8w("14.623593317803982") - fi8w( "7.811197271925399"), "6.8125");
	CHECK_EQ(fi8w( "8.071375895442914") - fi8w( "1.604623251593447"), "6.5");
	CHECK_EQ(fi8w( "5.791169538438560") - fi8w( "9.684914136531665"), "12.125");

}

BOOST_AUTO_TEST_CASE( wrap_mul )
{

	CHECK_EQ(fi8w("2.75") * fi8w("0.0"), "0.0");
	CHECK_EQ(fi8w("0.0") * fi8w("14.0625"), "0.0");
	CHECK_EQ(fi8w("2.75") * fi8w("1.0"), "2.75");
	CHECK_EQ(fi8w("1.0") * fi8w("14.0625"), "14.0625");

	CHECK_EQ(fi8w( "8.166706486120111") * fi8w("10.675027211092726"), "6.3125");
	CHECK_EQ(fi8w( "0.507730321101910") * fi8w( "4.750194427708022"), "2.375");
	CHECK_EQ(fi8w("12.358953766892963") * fi8w("11.006365423173214"), "7.4375");
	CHECK_EQ(fi8w( "7.200477333276465") * fi8w( "7.071570706397456"), "2.75");
	CHECK_EQ(fi8w( "8.804272635917481") * fi8w( "3.759932265267421"), "0.8125");
	CHECK_EQ(fi8w( "3.392959193571562") * fi8w( "4.173940158067184"), "13.875");
	CHECK_EQ(fi8w( "7.757061016729224") * fi8w("14.215592535930147"), "13.9375");
	CHECK_EQ(fi8w("14.623593317803982") * fi8w( "7.811197271925399"), "0.8125");
	CHECK_EQ(fi8w( "8.071375895442914") * fi8w( "1.604623251593447"), "12.5625");
	CHECK_EQ(fi8w( "5.791169538438560") * fi8w( "9.684914136531665"), "7.3125");

}

BOOST_AUTO_TEST_CASE( wrap_div ) {

	//Directed
	CHECK_EQ(fi8w("0") / fi8w("6.234"), "0.0");
	CHECK_EQ(fi8w("1.125") / fi8w("1.0"), "1.125");
	CHECK_EQ(fi8w("1.0") / fi8w("1.125"), "0.875");
	//Random
	CHECK_EQ(fi8w( "8.166706486120111") / fi8w("10.675027211092726"), "0.75");
	CHECK_EQ(fi8w( "0.507730321101910") / fi8w( "4.750194427708022"), "0.0625");
	CHECK_EQ(fi8w("12.358953766892963") / fi8w("11.006365423173214"), "1.0625");
	CHECK_EQ(fi8w( "7.200477333276465") / fi8w( "7.071570706397456"), "1.0");
	CHECK_EQ(fi8w( "8.804272635917481") / fi8w( "3.759932265267421"), "2.3125");
	CHECK_EQ(fi8w( "3.392959193571562") / fi8w( "4.173940158067184"), "0.8125");
	CHECK_EQ(fi8w( "7.757061016729224") / fi8w("14.215592535930147"), "0.5");
	CHECK_EQ(fi8w("14.623593317803982") / fi8w( "7.811197271925399"), "1.875");
	CHECK_EQ(fi8w( "8.071375895442914") / fi8w( "1.604623251593447"), "5.125");
	CHECK_EQ(fi8w( "5.791169538438560") / fi8w( "9.684914136531665"), "0.5625");

	CHECK_EQ(fi8w("13.329528734447672") / fi8w("0.702582514675030"),  "3.3125");
	CHECK_EQ(fi8w( "4.209521444258016") / fi8w("5.646696541209569"),  "0.6875");
	CHECK_EQ(fi8w( "4.708846376190046") / fi8w("6.343968266867194"),  "0.6875");
	CHECK_EQ(fi8w("13.255598133088446") / fi8w("6.668712941371484"),  "2.0");
	CHECK_EQ(fi8w( "0.330151768675361") / fi8w("0.148657609474102"),  "2.5");
	CHECK_EQ(fi8w("13.564899245972654") / fi8w("5.579927923473343"),  "2.4375");
	CHECK_EQ(fi8w( "6.577733241138658") / fi8w("7.372743473296302"),  "0.875");
	CHECK_EQ(fi8w( "7.320401340687432") / fi8w("6.537891962177564"),  "1.125");
	CHECK_EQ(fi8w("12.554209689821736") / fi8w("0.382952038033004"),  "1.3125");
	CHECK_EQ(fi8w( "7.150780532966863") / fi8w("2.948953122635400"),  "2.375");

}

BOOST_AUTO_TEST_CASE( wrap_comp_lt ) {

	BOOST_CHECK(fi8w(0.14) < fi8w(0.9567));
	BOOST_CHECK(!(fi8w(3.14) < fi8w(0.9567)));
	BOOST_CHECK(!(fi8w(3.14) < fi8w(3.14)));

}

BOOST_AUTO_TEST_CASE( wrap_comp_eq ) {

	BOOST_CHECK(fi8w(0.14) == fi8w(0.14));
	BOOST_CHECK(!(fi8w(0.14) == fi8w(0.24)));
	BOOST_CHECK(!(fi8w(10.14) == fi8w(0.24)));

}

BOOST_AUTO_TEST_CASE( wrap_comp_neq ) {

	BOOST_CHECK(fi8w(0.14) != fi8w(10.14));
	BOOST_CHECK(!(fi8w(0.14) != fi8w(0.14)));
	BOOST_CHECK(fi8w(0.14) != fi8w(0.24));

}

BOOST_AUTO_TEST_CASE( wrap_comp_gt ) {

	BOOST_CHECK(fi8w(1.54) > fi8w(0.9567));
	BOOST_CHECK(!(fi8w(3.14) > fi8w(10.9567)));
	BOOST_CHECK(!(fi8w(3.14) > fi8w(3.14)));

}

BOOST_AUTO_TEST_CASE( wrap_comp_lte ) {

	BOOST_CHECK(fi8w(0.14) <= fi8w(0.9567));
	BOOST_CHECK(!(fi8w(3.14) <= fi8w(0.9567)));
	BOOST_CHECK(fi8w(3.14) <= fi8w(3.14));

}

BOOST_AUTO_TEST_CASE( wrap_comp_gte ) {

	BOOST_CHECK(fi8w(1.54) >= fi8w(0.9567));
	BOOST_CHECK(!(fi8w(3.14) >= fi8w(10.9567)));
	BOOST_CHECK(fi8w(3.14) >= fi8w(3.14));

}

BOOST_AUTO_TEST_CASE( wrap_shift ) {

	fi8w b("0.9375");

	b = ~b;
	CHECK_EQ(b, "15.0");

	b >>= 1;
	CHECK_EQ(b, "7.5");

	b <<= 1;
	CHECK_EQ(b, "15.0");

	b >>= 1;
	b <<= 2;
	CHECK_EQ(b, "14.0");

	CHECK_EQ(b>>1, "7.0");
	CHECK_EQ(b, "14.0");

	CHECK_EQ(b<<1, "12.0");
	CHECK_EQ(b<<2, "8.0");

}

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////

typedef Fi::Fixed<8, 4, Fi::UNSIGNED, Fi::Throw> fi8of;

BOOST_AUTO_TEST_SUITE(Throw)
BOOST_AUTO_TEST_CASE( overflowexception_flp_construction )
{

	BOOST_CHECK_THROW(fi8of(1e20), std::overflow_error);
	BOOST_CHECK_THROW(fi8of(16.0), std::overflow_error);
	CHECK_EQ(fi8of(15.9375f), "15.9375");
	CHECK_EQ(fi8of(7.9375), "7.9375");
	CHECK_EQ(fi8of(4.123), "4.0625");
	CHECK_EQ(fi8of(1.0f), "1.0");
	CHECK_EQ(fi8of(0.0), "0.0");
	BOOST_CHECK_THROW(fi8of(-1.123), std::overflow_error);
	BOOST_CHECK_THROW(fi8of(-19.0), std::overflow_error);

}

BOOST_AUTO_TEST_CASE( overflowexception_str_construction )
{

	BOOST_CHECK_THROW(fi8of("1000000000000000000000000.0"), std::overflow_error);
	BOOST_CHECK_THROW(fi8of("16.0"), std::overflow_error);
	CHECK_EQ(fi8of("15.9375"), "15.9375");
	CHECK_EQ(fi8of("9.0"), "9.0" );
	CHECK_EQ(fi8of("7.9375"), "7.9375");
	CHECK_EQ(fi8of("4.123"), "4.0625");
	CHECK_EQ(fi8of("1.0"), "1.0");
	CHECK_EQ(fi8of("0.0"), "0.0");

	CHECK_EQ(fi8of("000004.123"), "4.0625");

	BOOST_CHECK_THROW(fi8of("-9.0"), std::invalid_argument);
	BOOST_CHECK_THROW(fi8of("abc"), std::invalid_argument);
	BOOST_CHECK_THROW(fi8of("8.0.01"), std::invalid_argument);

}

BOOST_AUTO_TEST_CASE( overflowexception_add )
{

	CHECK_EQ(fi8of("0.0") + fi8of("14.123"), "14.0625");
	CHECK_EQ(fi8of("3.123") + fi8of("0.0"), "3.0625");
	CHECK_EQ(fi8of("1.0") + fi8of("3.0"), "4.0");
	BOOST_CHECK_THROW(fi8of("6.0") + fi8of("10.0"), std::overflow_error);

	BOOST_CHECK_THROW(fi8of( "8.166706486120111") + fi8of("10.675027211092726"), std::overflow_error);
	CHECK_EQ(fi8of( "0.507730321101910") + fi8of( "4.750194427708022"), "5.25");
	BOOST_CHECK_THROW(fi8of("12.358953766892963") + fi8of("11.006365423173214"), std::overflow_error);
	CHECK_EQ(fi8of( "7.200477333276465") + fi8of( "7.071570706397456"), "14.25");
	CHECK_EQ(fi8of( "8.804272635917481") + fi8of( "3.759932265267421"), "12.5");
	CHECK_EQ(fi8of( "3.392959193571562") + fi8of( "4.173940158067184"), "7.5");
	BOOST_CHECK_THROW(fi8of( "7.757061016729224") + fi8of("14.215592535930147"), std::overflow_error);
	BOOST_CHECK_THROW(fi8of("14.623593317803982") + fi8of( "7.811197271925399"), std::overflow_error);
	CHECK_EQ(fi8of( "8.071375895442914") + fi8of( "1.604623251593447"), "9.625");
	CHECK_EQ(fi8of( "5.791169538438560") + fi8of( "9.684914136531665"), "15.375");

}

BOOST_AUTO_TEST_CASE( overflowexception_sub )
{

	BOOST_CHECK_THROW(fi8of("0.0") - fi8of("14.123"),  std::overflow_error);
	CHECK_EQ(fi8of("3.123") - fi8of("0.0"), "3.0625");
	BOOST_CHECK_THROW(fi8of("6.0") - fi8of("10.0"),  std::overflow_error);

	BOOST_CHECK_THROW(fi8of( "8.166706486120111") - fi8of("10.675027211092726"),  std::overflow_error);
	BOOST_CHECK_THROW(fi8of( "0.507730321101910") - fi8of( "4.750194427708022"),  std::overflow_error);
	CHECK_EQ(fi8of("12.358953766892963") - fi8of("11.006365423173214"), "1.3125");
	CHECK_EQ(fi8of( "7.200477333276465") - fi8of( "7.071570706397456"), "0.125");
	CHECK_EQ(fi8of( "8.804272635917481") - fi8of( "3.759932265267421"), "5.0");
	BOOST_CHECK_THROW(fi8of( "3.392959193571562") - fi8of( "4.173940158067184"),  std::overflow_error);
	BOOST_CHECK_THROW(fi8of( "7.757061016729224") - fi8of("14.215592535930147"),  std::overflow_error);
	CHECK_EQ(fi8of("14.623593317803982") - fi8of( "7.811197271925399"), "6.8125");
	CHECK_EQ(fi8of( "8.071375895442914") - fi8of( "1.604623251593447"), "6.5");
	BOOST_CHECK_THROW(fi8of( "5.791169538438560") - fi8of( "9.684914136531665"),  std::overflow_error);

}

BOOST_AUTO_TEST_CASE( overflowexception_mul )
{
	//Directed
	CHECK_EQ(fi8of("0") * fi8of("6.234"), "0.0");
	CHECK_EQ(fi8of("1.234") * fi8of("0.0"), "0.0");
	CHECK_EQ(fi8of("1.125") * fi8of("1.0"), "1.125");
	CHECK_EQ(fi8of("1.0") * fi8of("1.125"), "1.125");
	//Random
	BOOST_CHECK_THROW(fi8of( "8.166706486120111") * fi8of("10.675027211092726"), std::overflow_error);
	CHECK_EQ(fi8of( "0.507730321101910") * fi8of( "4.750194427708022"), "2.375");
	BOOST_CHECK_THROW(fi8of("12.358953766892963") * fi8of("11.006365423173214"), std::overflow_error);
	BOOST_CHECK_THROW(fi8of( "7.200477333276465") * fi8of( "7.071570706397456"), std::overflow_error);
	BOOST_CHECK_THROW(fi8of( "8.804272635917481") * fi8of( "3.759932265267421"), std::overflow_error);
	CHECK_EQ(fi8of( "3.392959193571562") * fi8of( "4.173940158067184"), "13.875");
	BOOST_CHECK_THROW(fi8of( "7.757061016729224") * fi8of("14.215592535930147"), std::overflow_error);
	BOOST_CHECK_THROW(fi8of("14.623593317803982") * fi8of( "7.811197271925399"), std::overflow_error);
	CHECK_EQ(fi8of( "8.071375895442914") * fi8of( "1.604623251593447"), "12.5625");
	BOOST_CHECK_THROW(fi8of( "5.791169538438560") * fi8of( "9.684914136531665"), std::overflow_error);

}

BOOST_AUTO_TEST_CASE( overflowexception_div ) {

	//Directed
	CHECK_EQ(fi8of("0") / fi8of("6.234"), "0.0");
	CHECK_EQ(fi8of("1.125") / fi8of("1.0"), "1.125");
	CHECK_EQ(fi8of("1.0") / fi8of("1.125"), "0.875");
	//Random
	CHECK_EQ(fi8of( "8.166706486120111") / fi8of("10.675027211092726"), "0.75");
	CHECK_EQ(fi8of( "0.507730321101910") / fi8of( "4.750194427708022"), "0.0625");
	CHECK_EQ(fi8of("12.358953766892963") / fi8of("11.006365423173214"), "1.0625");
	CHECK_EQ(fi8of( "7.200477333276465") / fi8of( "7.071570706397456"), "1.0");
	CHECK_EQ(fi8of( "8.804272635917481") / fi8of( "3.759932265267421"), "2.3125");
	CHECK_EQ(fi8of( "3.392959193571562") / fi8of( "4.173940158067184"), "0.8125");
	CHECK_EQ(fi8of( "7.757061016729224") / fi8of("14.215592535930147"), "0.5");
	CHECK_EQ(fi8of("14.623593317803982") / fi8of( "7.811197271925399"), "1.875");
	CHECK_EQ(fi8of( "8.071375895442914") / fi8of( "1.604623251593447"), "5.125");
	CHECK_EQ(fi8of( "5.791169538438560") / fi8of( "9.684914136531665"), "0.5625");

	BOOST_CHECK_THROW(fi8of("13.329528734447672") / fi8of("0.702582514675030"),  std::overflow_error);
	CHECK_EQ(fi8of( "4.209521444258016") / fi8of("5.646696541209569"),  "0.6875");
	CHECK_EQ(fi8of( "4.708846376190046") / fi8of("6.343968266867194"),  "0.6875");
	CHECK_EQ(fi8of("13.255598133088446") / fi8of("6.668712941371484"),  "2.0");
	CHECK_EQ(fi8of( "0.330151768675361") / fi8of("0.148657609474102"),  "2.5");
	CHECK_EQ(fi8of("13.564899245972654") / fi8of("5.579927923473343"),  "2.4375");
	CHECK_EQ(fi8of( "6.577733241138658") / fi8of("7.372743473296302"),  "0.875");
	CHECK_EQ(fi8of( "7.320401340687432") / fi8of("6.537891962177564"),  "1.125");
	BOOST_CHECK_THROW(fi8of("12.554209689821736") / fi8of("0.382952038033004"),  std::overflow_error);
	CHECK_EQ(fi8of( "7.150780532966863") / fi8of("2.948953122635400"),  "2.375");

}

BOOST_AUTO_TEST_CASE( overflowexception_comp_lt ) {

	BOOST_CHECK(fi8of(0.14) < fi8of(0.9567));
	BOOST_CHECK(!(fi8of(3.14) < fi8of(0.9567)));
	BOOST_CHECK(!(fi8of(3.14) < fi8of(3.14)));

}

BOOST_AUTO_TEST_CASE( overflowexception_comp_eq ) {

	BOOST_CHECK(fi8of(0.14) == fi8of(0.14));
	BOOST_CHECK(!(fi8of(0.14) == fi8of(0.24)));
	BOOST_CHECK(!(fi8of(10.14) == fi8of(0.24)));

}

BOOST_AUTO_TEST_CASE( overflowexception_comp_neq ) {

	BOOST_CHECK(fi8of(0.14) != fi8of(10.14));
	BOOST_CHECK(!(fi8of(0.14) != fi8of(0.14)));
	BOOST_CHECK(fi8of(0.14) != fi8of(0.24));

}

BOOST_AUTO_TEST_CASE( overflowexception_comp_gt ) {

	BOOST_CHECK(fi8of(1.54) > fi8of(0.9567));
	BOOST_CHECK(!(fi8of(3.14) > fi8of(10.9567)));
	BOOST_CHECK(!(fi8of(3.14) > fi8of(3.14)));

}

BOOST_AUTO_TEST_CASE( overflowexception_comp_lte ) {

	BOOST_CHECK(fi8of(0.14) <= fi8of(0.9567));
	BOOST_CHECK(!(fi8of(3.14) <= fi8of(0.9567)));
	BOOST_CHECK(fi8of(3.14) <= fi8of(3.14));

}

BOOST_AUTO_TEST_CASE( overflowexception_comp_gte ) {

	BOOST_CHECK(fi8of(1.54) >= fi8of(0.9567));
	BOOST_CHECK(!(fi8of(3.14) >= fi8of(10.9567)));
	BOOST_CHECK(fi8of(3.14) >= fi8of(3.14));

}

BOOST_AUTO_TEST_CASE( overflowexception_shift ) {

	fi8of b("0.9375");

	b = ~b;
	CHECK_EQ(b, "15.0");

	b >>= 1;
	CHECK_EQ(b, "7.5");

	b <<= 1;
	CHECK_EQ(b, "15.0");

	BOOST_CHECK_THROW(b << 2, Fi::PositiveOverflow);
	CHECK_EQ(b, "15.0");

	CHECK_EQ(b>>1, "7.5");
	CHECK_EQ(b, "15.0");

}


BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////
