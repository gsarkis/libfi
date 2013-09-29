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

#define BOOST_TEST_DYN_LINK true
#define BOOST_TEST_MODULE overflow_detector
#include <boost/test/unit_test.hpp>

#include <cmath>
#include <iostream>

#define CHECK_EQ(A, E) BOOST_CHECK_EQUAL((A).toString(), (E).toString())

BOOST_AUTO_TEST_SUITE( min_tests )

BOOST_AUTO_TEST_CASE( u_min )
{

	typedef Fi::Fixed<8, 4, Fi::UNSIGNED> fi;

	CHECK_EQ( min(fi(2.5949), fi(0.0)   ), fi(0.0) );
	CHECK_EQ( min(fi(0.0),    fi(0.5093)), fi(0.0) );
	CHECK_EQ( min(fi(15.9375), fi( 4.4308)) , fi(4.4308));
	CHECK_EQ( min(fi( 8.4565), fi(15.9375)) , fi(8.4565));

	CHECK_EQ( min(fi( 2.5949), fi(11.2967)) , fi(std::min( 2.5949, 11.2967)));
	CHECK_EQ( min(fi(12.7086), fi( 0.5093)) , fi(std::min(12.7086,	 0.5093)));
	CHECK_EQ( min(fi( 4.9794), fi( 4.4308)) , fi(std::min( 4.9794,	 4.4308)));
	CHECK_EQ( min(fi( 8.4565), fi( 0.7387)) , fi(std::min( 8.4565,	 0.7387)));
	CHECK_EQ( min(fi( 2.6504), fi( 1.5541)) ,	fi(std::min( 2.6504,	 1.5541)));
	CHECK_EQ( min(fi( 9.6317), fi(13.1753)) , fi(std::min( 9.6317, 13.1753)));
	CHECK_EQ( min(fi( 4.2075), fi(11.1173)) , fi(std::min( 4.2075, 11.1173)));
	CHECK_EQ( min(fi(10.4653), fi( 5.0736)) , fi(std::min(10.4653,	 5.0736)));
	CHECK_EQ( min(fi(11.0274), fi(15.2036)) , fi(std::min(11.0274, 15.2036)));
	CHECK_EQ( min(fi(11.9704), fi( 0.5511)) , fi(std::min(11.9704,	 0.5511)));
	CHECK_EQ( min(fi( 7.2087), fi( 4.4164)) ,	fi(std::min( 7.2087,	 4.4164)));
	CHECK_EQ( min(fi( 1.3411), fi(10.8752)) , fi(std::min( 1.3411, 10.8752)));
	CHECK_EQ( min(fi( 3.6636), fi(10.4816)) ,	fi(std::min( 3.6636, 10.4816)));
	CHECK_EQ( min(fi(14.6134), fi( 2.6018)) , fi(std::min(14.6134,	 2.6018)));
	CHECK_EQ( min(fi( 2.4380), fi( 1.9040)) , fi(std::min( 2.4380,	 1.9040)));

}

BOOST_AUTO_TEST_CASE( u_min_no_i )
{

	typedef Fi::Fixed<4, 4, Fi::UNSIGNED> fi;

	CHECK_EQ( min(fi(0.5949), fi(0.0)   ), fi(0.0) );
	CHECK_EQ( min(fi(0.0),    fi(0.5093)), fi(0.0) );
	CHECK_EQ( min(fi(0.9375), fi(0.4308)) , fi(0.4308));
	CHECK_EQ( min(fi(0.4565), fi(0.9375)) , fi(0.4565));

	CHECK_EQ( min(fi(0.5949), fi(0.2967)) , fi(std::min(0.5949, 0.2967)));
	CHECK_EQ( min(fi(0.7086), fi(0.5093)) , fi(std::min(0.7086,	0.5093)));
	CHECK_EQ( min(fi(0.9794), fi(0.4308)) , fi(std::min(0.9794,	0.4308)));
	CHECK_EQ( min(fi(0.4565), fi(0.7387)) , fi(std::min(0.4565,	0.7387)));
	CHECK_EQ( min(fi(0.6504), fi(0.5541)) ,	fi(std::min(0.6504,	0.5541)));
	CHECK_EQ( min(fi(0.6317), fi(0.1753)) , fi(std::min(0.6317, 0.1753)));
	CHECK_EQ( min(fi(0.2075), fi(0.1173)) , fi(std::min(0.2075, 0.1173)));
	CHECK_EQ( min(fi(0.4653), fi(0.0736)) , fi(std::min(0.4653,	0.0736)));
	CHECK_EQ( min(fi(0.0274), fi(0.2036)) , fi(std::min(0.0274, 0.2036)));
	CHECK_EQ( min(fi(0.9704), fi(0.5511)) , fi(std::min(0.9704,	0.5511)));
	CHECK_EQ( min(fi(0.2087), fi(0.4164)) ,	fi(std::min(0.2087,	0.4164)));
	CHECK_EQ( min(fi(0.3411), fi(0.8752)) , fi(std::min(0.3411, 0.8752)));
	CHECK_EQ( min(fi(0.6636), fi(0.4816)) ,	fi(std::min(0.6636, 0.4816)));
	CHECK_EQ( min(fi(0.6134), fi(0.6018)) , fi(std::min(0.6134,	0.6018)));
	CHECK_EQ( min(fi(0.4380), fi(0.9040)) , fi(std::min(0.4380,	0.9040)));

}

BOOST_AUTO_TEST_CASE( s_min )
{

	typedef Fi::Fixed<8, 4, Fi::SIGNED> fi;

	CHECK_EQ( min(fi(2.5949), fi(-8.0)   ), fi(-8.0) );
	CHECK_EQ( min(fi(-8.0),    fi(0.5093)), fi(-8.0) );
	CHECK_EQ( min(fi(-2.5949), fi(-8.0)   ), fi(-8.0) );
	CHECK_EQ( min(fi(-8.0),    fi(00.5093)), fi(-8.0) );

	CHECK_EQ( min(fi(7.9375), fi(4.4308)) , fi(4.4308));
	CHECK_EQ( min(fi(3.4565), fi(7.9375)) , fi(3.4565));

	CHECK_EQ( min(fi(7.9375), fi(-4.4308)) , fi(-4.4308));
	CHECK_EQ( min(fi(-3.4565), fi(7.9375)) , fi(-3.4565));

	CHECK_EQ( min(fi( 5.2131), fi(-1.0974)) , fi(std::min( 5.2131, -1.0974)));
	CHECK_EQ( min(fi( 0.6135), fi( 6.5704)) , fi(std::min( 0.6135,  6.5704)));
	CHECK_EQ( min(fi( 7.9382), fi(-5.0904)) , fi(std::min( 7.9382, -5.0904)));
	CHECK_EQ( min(fi(-6.7492), fi(-3.7792)) , fi(std::min(-6.7492, -3.7792)));
	CHECK_EQ( min(fi(-0.9171), fi(-5.6714)) , fi(std::min(-0.9171, -5.6714)));
	CHECK_EQ( min(fi(-6.2936), fi(-5.8229)) , fi(std::min(-6.2936, -5.8229)));
	CHECK_EQ( min(fi( 7.3904), fi( 5.9087)) , fi(std::min( 7.3904,  5.9087)));
	CHECK_EQ( min(fi(-7.9259), fi( 1.2753)) , fi(std::min(-7.9259,  1.2753)));
	CHECK_EQ( min(fi( 4.3986), fi( 0.7978)) , fi(std::min( 4.3986,  0.7978)));
	CHECK_EQ( min(fi( 5.0769), fi(-5.6807)) , fi(std::min( 5.0769, -5.6807)));
	CHECK_EQ( min(fi( 5.8991), fi( 5.6485)) , fi(std::min( 5.8991,  5.6485)));
	CHECK_EQ( min(fi(-6.6490), fi( 1.9529)) , fi(std::min(-6.6490,  1.9529)));
	CHECK_EQ( min(fi(-1.6035), fi(-2.3848)) , fi(std::min(-1.6035, -2.3848)));
	CHECK_EQ( min(fi(-3.8421), fi( 0.2120)) , fi(std::min(-3.8421,  0.2120)));
	CHECK_EQ( min(fi( 4.8011), fi(-1.5711)) , fi(std::min( 4.8011, -1.5711)));

}

BOOST_AUTO_TEST_CASE( s_min_no_i )
{

	typedef Fi::Fixed<4, 4, Fi::SIGNED> fi;

	CHECK_EQ( min(fi(0.3949),  fi(-0.5)  ), fi(-0.5) );
	CHECK_EQ( min(fi(-0.5),    fi(0.3093)), fi(-0.5) );
	CHECK_EQ( min(fi(-0.3949), fi(-0.5)  ), fi(-0.5) );
	CHECK_EQ( min(fi(-0.5),    fi(0.3093)), fi(-0.5) );

	CHECK_EQ( min(fi(0.4375), fi(0.1308)) , fi(0.1308));
	CHECK_EQ( min(fi(0.1565), fi(0.4375)) , fi(0.1565));

	CHECK_EQ( min(fi(0.4375), fi(-0.1308)) , fi(-0.1308));
	CHECK_EQ( min(fi(-0.1565), fi(0.4375)) , fi(-0.1565));

	CHECK_EQ( min(fi( 0.2803), fi(-0.3310)) , fi(std::min( 0.2803,-0.3310)));
	CHECK_EQ( min(fi(-0.1103), fi( 0.1491)) , fi(std::min(-0.1103, 0.1491)));
	CHECK_EQ( min(fi(-0.2583), fi( 0.2317)) , fi(std::min(-0.2583, 0.2317)));
	CHECK_EQ( min(fi(-0.0961), fi( 0.1477)) , fi(std::min(-0.0961, 0.1477)));
	CHECK_EQ( min(fi(-0.4035), fi(-0.0491)) , fi(std::min(-0.4035,-0.0491)));
	CHECK_EQ( min(fi(-0.3680), fi( 0.0470)) , fi(std::min(-0.3680, 0.0470)));
	CHECK_EQ( min(fi( 0.4421), fi(-0.2037)) , fi(std::min( 0.4421,-0.2037)));
	CHECK_EQ( min(fi( 0.4561), fi( 0.2447)) , fi(std::min( 0.4561, 0.2447)));
	CHECK_EQ( min(fi( 0.0752), fi(-0.3110)) , fi(std::min( 0.0752,-0.3110)));
	CHECK_EQ( min(fi(-0.4402), fi( 0.1868)) , fi(std::min(-0.4402, 0.1868)));
	CHECK_EQ( min(fi(-0.2652), fi(-0.3165)) , fi(std::min(-0.2652,-0.3165)));
	CHECK_EQ( min(fi(-0.1468), fi(-0.1315)) , fi(std::min(-0.1468,-0.1315)));
	CHECK_EQ( min(fi( 0.3212), fi( 0.1256)) , fi(std::min( 0.3212, 0.1256)));
	CHECK_EQ( min(fi(-0.4846), fi( 0.2802)) , fi(std::min(-0.4846, 0.2802)));
	CHECK_EQ( min(fi(-0.4570), fi(-0.4189)) , fi(std::min(-0.4570,-0.4189)));

}

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( max_tests )

BOOST_AUTO_TEST_CASE( u_max )
{

	typedef Fi::Fixed<8, 4, Fi::UNSIGNED> fi;

	CHECK_EQ( max(fi(2.5949), fi(0.0)   ), fi(2.5949) );
	CHECK_EQ( max(fi(0.0),    fi(0.5093)), fi(0.5093) );
	CHECK_EQ( max(fi(15.9375), fi( 4.4308)) , fi(15.9375));
	CHECK_EQ( max(fi( 8.4565), fi(15.9375)) , fi(15.9375));

	CHECK_EQ( max(fi( 2.5949), fi(11.2967)) , fi(std::max( 2.5949, 11.2967)));
	CHECK_EQ( max(fi(12.7086), fi( 0.5093)) , fi(std::max(12.7086,	 0.5093)));
	CHECK_EQ( max(fi( 4.9794), fi( 4.4308)) , fi(std::max( 4.9794,	 4.4308)));
	CHECK_EQ( max(fi( 8.4565), fi( 0.7387)) , fi(std::max( 8.4565,	 0.7387)));
	CHECK_EQ( max(fi( 2.6504), fi( 1.5541)) ,	fi(std::max( 2.6504,	 1.5541)));
	CHECK_EQ( max(fi( 9.6317), fi(13.1753)) , fi(std::max( 9.6317, 13.1753)));
	CHECK_EQ( max(fi( 4.2075), fi(11.1173)) , fi(std::max( 4.2075, 11.1173)));
	CHECK_EQ( max(fi(10.4653), fi( 5.0736)) , fi(std::max(10.4653,	 5.0736)));
	CHECK_EQ( max(fi(11.0274), fi(15.2036)) , fi(std::max(11.0274, 15.2036)));
	CHECK_EQ( max(fi(11.9704), fi( 0.5511)) , fi(std::max(11.9704,	 0.5511)));
	CHECK_EQ( max(fi( 7.2087), fi( 4.4164)) ,	fi(std::max( 7.2087,	 4.4164)));
	CHECK_EQ( max(fi( 1.3411), fi(10.8752)) , fi(std::max( 1.3411, 10.8752)));
	CHECK_EQ( max(fi( 3.6636), fi(10.4816)) ,	fi(std::max( 3.6636, 10.4816)));
	CHECK_EQ( max(fi(14.6134), fi( 2.6018)) , fi(std::max(14.6134,	 2.6018)));
	CHECK_EQ( max(fi( 2.4380), fi( 1.9040)) , fi(std::max( 2.4380,	 1.9040)));

}

BOOST_AUTO_TEST_CASE( u_max_no_i )
{

	typedef Fi::Fixed<4, 4, Fi::UNSIGNED> fi;

	CHECK_EQ( max(fi(0.5949), fi(0.0)   ), fi(0.5949) );
	CHECK_EQ( max(fi(0.0),    fi(0.5093)), fi(0.5093) );
	CHECK_EQ( max(fi(0.9375), fi(0.4308)) , fi(0.9375));
	CHECK_EQ( max(fi(0.4565), fi(0.9375)) , fi(0.9375));

	CHECK_EQ( max(fi(0.5949), fi(0.2967)) , fi(std::max(0.5949, 0.2967)));
	CHECK_EQ( max(fi(0.7086), fi(0.5093)) , fi(std::max(0.7086,	0.5093)));
	CHECK_EQ( max(fi(0.9794), fi(0.4308)) , fi(std::max(0.9794,	0.4308)));
	CHECK_EQ( max(fi(0.4565), fi(0.7387)) , fi(std::max(0.4565,	0.7387)));
	CHECK_EQ( max(fi(0.6504), fi(0.5541)) ,	fi(std::max(0.6504,	0.5541)));
	CHECK_EQ( max(fi(0.6317), fi(0.1753)) , fi(std::max(0.6317, 0.1753)));
	CHECK_EQ( max(fi(0.2075), fi(0.1173)) , fi(std::max(0.2075, 0.1173)));
	CHECK_EQ( max(fi(0.4653), fi(0.0736)) , fi(std::max(0.4653,	0.0736)));
	CHECK_EQ( max(fi(0.0274), fi(0.2036)) , fi(std::max(0.0274, 0.2036)));
	CHECK_EQ( max(fi(0.9704), fi(0.5511)) , fi(std::max(0.9704,	0.5511)));
	CHECK_EQ( max(fi(0.2087), fi(0.4164)) ,	fi(std::max(0.2087,	0.4164)));
	CHECK_EQ( max(fi(0.3411), fi(0.8752)) , fi(std::max(0.3411, 0.8752)));
	CHECK_EQ( max(fi(0.6636), fi(0.4816)) ,	fi(std::max(0.6636, 0.4816)));
	CHECK_EQ( max(fi(0.6134), fi(0.6018)) , fi(std::max(0.6134,	0.6018)));
	CHECK_EQ( max(fi(0.4380), fi(0.9040)) , fi(std::max(0.4380,	0.9040)));

}

BOOST_AUTO_TEST_CASE( s_max )
{

	typedef Fi::Fixed<8, 4, Fi::SIGNED> fi;

	CHECK_EQ( max(fi(2.5949), fi(-8.0)   ), fi(2.5949) );
	CHECK_EQ( max(fi(-8.0),    fi(0.5093)), fi(0.5093) );
	CHECK_EQ( max(fi(-2.5949), fi(-8.0)  ), fi(-2.5949) );
	CHECK_EQ( max(fi(-8.0),    fi(0.5093)), fi(0.5093) );

	CHECK_EQ( max(fi(7.9375), fi(4.4308)) , fi(7.9375));
	CHECK_EQ( max(fi(3.4565), fi(7.9375)) , fi(7.9375));

	CHECK_EQ( max(fi(7.9375), fi(-4.4308)) , fi(7.9375));
	CHECK_EQ( max(fi(-3.4565), fi(7.9375)) , fi(7.9375));

	CHECK_EQ( max(fi( 5.2131), fi(-1.0974)) , fi(std::max( 5.2131, -1.0974)));
	CHECK_EQ( max(fi( 0.6135), fi( 6.5704)) , fi(std::max( 0.6135,  6.5704)));
	CHECK_EQ( max(fi( 7.9382), fi(-5.0904)) , fi(std::max( 7.9382, -5.0904)));
	CHECK_EQ( max(fi(-6.7492), fi(-3.7792)) , fi(std::max(-6.7492, -3.7792)));
	CHECK_EQ( max(fi(-0.9171), fi(-5.6714)) , fi(std::max(-0.9171, -5.6714)));
	CHECK_EQ( max(fi(-6.2936), fi(-5.8229)) , fi(std::max(-6.2936, -5.8229)));
	CHECK_EQ( max(fi( 7.3904), fi( 5.9087)) , fi(std::max( 7.3904,  5.9087)));
	CHECK_EQ( max(fi(-7.9259), fi( 1.2753)) , fi(std::max(-7.9259,  1.2753)));
	CHECK_EQ( max(fi( 4.3986), fi( 0.7978)) , fi(std::max( 4.3986,  0.7978)));
	CHECK_EQ( max(fi( 5.0769), fi(-5.6807)) , fi(std::max( 5.0769, -5.6807)));
	CHECK_EQ( max(fi( 5.8991), fi( 5.6485)) , fi(std::max( 5.8991,  5.6485)));
	CHECK_EQ( max(fi(-6.6490), fi( 1.9529)) , fi(std::max(-6.6490,  1.9529)));
	CHECK_EQ( max(fi(-1.6035), fi(-2.3848)) , fi(std::max(-1.6035, -2.3848)));
	CHECK_EQ( max(fi(-3.8421), fi( 0.2120)) , fi(std::max(-3.8421,  0.2120)));
	CHECK_EQ( max(fi( 4.8011), fi(-1.5711)) , fi(std::max( 4.8011, -1.5711)));

}

BOOST_AUTO_TEST_CASE( s_max_no_i )
{

	typedef Fi::Fixed<4, 4, Fi::SIGNED> fi;

	CHECK_EQ( max(fi(0.3949),  fi(-0.5)  ), fi(0.3949) );
	CHECK_EQ( max(fi(-0.5),		 fi(0.3093)), fi(0.3093) );
	CHECK_EQ( max(fi(-0.3949), fi(-0.5)	 ), fi(-0.3949) );
	CHECK_EQ( max(fi(-0.5),		 fi(-0.3093)), fi(-0.3093) );

	CHECK_EQ( max(fi(0.4375), fi(0.1308)) , fi(0.4375));
	CHECK_EQ( max(fi(0.1565), fi(0.4375)) , fi(0.4375));

	CHECK_EQ( max(fi(0.4375), fi(-0.1308)) , fi(0.4375));
	CHECK_EQ( max(fi(-0.1565), fi(0.4375)) , fi(0.4375));

	CHECK_EQ( max(fi( 0.2803), fi(-0.3310)) , fi(std::max( 0.2803,-0.3310)));
	CHECK_EQ( max(fi(-0.1103), fi( 0.1491)) , fi(std::max(-0.1103, 0.1491)));
	CHECK_EQ( max(fi(-0.2583), fi( 0.2317)) , fi(std::max(-0.2583, 0.2317)));
	CHECK_EQ( max(fi(-0.0961), fi( 0.1477)) , fi(std::max(-0.0961, 0.1477)));
	CHECK_EQ( max(fi(-0.4035), fi(-0.0491)) , fi(std::max(-0.4035,-0.0491)));
	CHECK_EQ( max(fi(-0.3680), fi( 0.0470)) , fi(std::max(-0.3680, 0.0470)));
	CHECK_EQ( max(fi( 0.4421), fi(-0.2037)) , fi(std::max( 0.4421,-0.2037)));
	CHECK_EQ( max(fi( 0.4561), fi( 0.2447)) , fi(std::max( 0.4561, 0.2447)));
	CHECK_EQ( max(fi( 0.0752), fi(-0.3110)) , fi(std::max( 0.0752,-0.3110)));
	CHECK_EQ( max(fi(-0.4402), fi( 0.1868)) , fi(std::max(-0.4402, 0.1868)));
	CHECK_EQ( max(fi(-0.2652), fi(-0.3165)) , fi(std::max(-0.2652,-0.3165)));
	CHECK_EQ( max(fi(-0.1468), fi(-0.1315)) , fi(std::max(-0.1468,-0.1315)));
	CHECK_EQ( max(fi( 0.3212), fi( 0.1256)) , fi(std::max( 0.3212, 0.1256)));
	CHECK_EQ( max(fi(-0.4846), fi( 0.2802)) , fi(std::max(-0.4846, 0.2802)));
	CHECK_EQ( max(fi(-0.4570), fi(-0.4189)) , fi(std::max(-0.4570,-0.4189)));

}

BOOST_AUTO_TEST_SUITE_END()

#define L_CHECK_EQ(A, E) BOOST_CHECK_EQUAL((A).toString(), E)

BOOST_AUTO_TEST_SUITE( min_max )

BOOST_AUTO_TEST_CASE( signed_unsigned )
{

	typedef Fi::Fixed<8, 4, Fi::UNSIGNED> fiu;
	typedef Fi::Fixed<8, 4, Fi::SIGNED> fis;

	L_CHECK_EQ( Fi::max(fiu(1.25), fiu(2.0)), "2.0" );
	L_CHECK_EQ( Fi::min(fiu(1.25), fiu(2.0)), "1.25" );

	L_CHECK_EQ( Fi::max(fis(1.25), fis(2.0)), "2.0" );
	L_CHECK_EQ( Fi::min(fis(-1.25), fis(2.0)), "-1.25" );

	L_CHECK_EQ( Fi::max(fis(1.25), fis(-2.0)), "1.25" );
	L_CHECK_EQ( Fi::min(fis(-1.25), fis(-2.0)), "-2.0" );

}

BOOST_AUTO_TEST_CASE( fraction_size )
{

	typedef Fi::Fixed<8, 1, Fi::UNSIGNED> fiu1;

	L_CHECK_EQ( Fi::max(fiu1(1.5), fiu1(2.0)), "2.0" );
	L_CHECK_EQ( Fi::min(fiu1(1.5), fiu1(2.0)), "1.5" );

}

BOOST_AUTO_TEST_CASE( total_size )
{

	typedef Fi::Fixed<18, 1, Fi::UNSIGNED> fiu1;

	L_CHECK_EQ( Fi::max(fiu1(11.5), fiu1(12.0)), "12.0" );
	L_CHECK_EQ( Fi::min(fiu1(11.5), fiu1(12.0)), "11.5" );

}

BOOST_AUTO_TEST_SUITE_END()
