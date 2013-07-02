/*
 *Copyright © 2013 Gabi Sarkis.

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

#define CHECK_EQ(A, E) BOOST_CHECK_EQUAL((A).toString(), E)

BOOST_AUTO_TEST_SUITE( unsigned_binary_convesion )

BOOST_AUTO_TEST_CASE( u_from_binary_8_4 )
{

  typedef Fi::Fixed<8, 4, Fi::UNSIGNED> fi;

  CHECK_EQ( fi::fromBinary(0), "0.0" );
  CHECK_EQ( fi::fromBinary(1), "0.0625" );
  CHECK_EQ( fi::fromBinary(20), "1.25" );
  CHECK_EQ( fi::fromBinary(40), "2.5" );
  CHECK_EQ( fi::fromBinary(76), "4.75" );
  CHECK_EQ( fi::fromBinary(127), "7.9375" );
  CHECK_EQ( fi::fromBinary(240), "15.0" );
  CHECK_EQ( fi::fromBinary(243), "15.1875" );
  CHECK_EQ( fi::fromBinary(255), "15.9375" );

}

BOOST_AUTO_TEST_CASE( u_to_binary_8_4 )
{

  typedef Fi::Fixed<8, 4, Fi::UNSIGNED> fi;

  BOOST_CHECK_EQUAL( fi("0.0"		).toBinary(), 0		);
	BOOST_CHECK_EQUAL( fi("0.0625" ).toBinary(), 1		);
	BOOST_CHECK_EQUAL( fi("1.25"		).toBinary(), 20	);
	BOOST_CHECK_EQUAL( fi("2.5"		).toBinary(), 40	);
	BOOST_CHECK_EQUAL( fi("4.75"		).toBinary(), 76	);
	BOOST_CHECK_EQUAL( fi("7.9375" ).toBinary(), 127 );
	BOOST_CHECK_EQUAL( fi("15.0"		).toBinary(), 240 );
	BOOST_CHECK_EQUAL( fi("15.1875").toBinary(), 243 );
	BOOST_CHECK_EQUAL( fi("15.9375").toBinary(), 255 );

}

BOOST_AUTO_TEST_CASE( u_from_binary_5_3 )
{

  typedef Fi::Fixed<5, 3, Fi::UNSIGNED> fi;

	CHECK_EQ( fi::fromBinary(0), "0.0" );
	CHECK_EQ( fi::fromBinary(1), "0.125" );
	CHECK_EQ( fi::fromBinary(6), "0.75" );
	CHECK_EQ( fi::fromBinary(10), "1.25" );
	CHECK_EQ( fi::fromBinary(20), "2.5" );
	CHECK_EQ( fi::fromBinary(24), "3.0" );
	CHECK_EQ( fi::fromBinary(25), "3.125" );
	CHECK_EQ( fi::fromBinary(31), "3.875" );

}

BOOST_AUTO_TEST_CASE( u_to_binary_5_3 )
{

  typedef Fi::Fixed<5, 3, Fi::UNSIGNED> fi;

  BOOST_CHECK_EQUAL( fi("0.0").toBinary(), 0);
	BOOST_CHECK_EQUAL( fi("0.125").toBinary(), 1);
	BOOST_CHECK_EQUAL( fi("0.75").toBinary(), 6);
	BOOST_CHECK_EQUAL( fi("1.25").toBinary(), 10);
	BOOST_CHECK_EQUAL( fi("2.5").toBinary(), 20);
	BOOST_CHECK_EQUAL( fi("3.0").toBinary(), 24);
	BOOST_CHECK_EQUAL( fi("3.125").toBinary(), 25);
	BOOST_CHECK_EQUAL( fi("3.875").toBinary(), 31);

}

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( signed_binary_convesion )

BOOST_AUTO_TEST_CASE( s_from_binary_8_4 )
{

  typedef Fi::Fixed<8, 4, Fi::SIGNED> fi;

  CHECK_EQ( fi::fromBinary(128), "-8.0");
	CHECK_EQ( fi::fromBinary(141), "-7.1875");
	CHECK_EQ( fi::fromBinary(160), "-6.0"		);
	CHECK_EQ( fi::fromBinary(180), "-4.75"	);
	CHECK_EQ( fi::fromBinary(216), "-2.5"		);
	CHECK_EQ( fi::fromBinary(236), "-1.25"	);
	CHECK_EQ( fi::fromBinary(255), "-0.0625");
	CHECK_EQ( fi::fromBinary( 0 ),  "0.0"	  );
	CHECK_EQ( fi::fromBinary( 1 ),  "0.0625");
	CHECK_EQ( fi::fromBinary(20 ),  "1.25"  );
	CHECK_EQ( fi::fromBinary(40 ),  "2.5"	  );
	CHECK_EQ( fi::fromBinary(76 ),  "4.75"  );
	CHECK_EQ( fi::fromBinary(96 ),  "6.0"   );
	CHECK_EQ( fi::fromBinary(115),  "7.1875");
	CHECK_EQ( fi::fromBinary(127),  "7.9375");

}

BOOST_AUTO_TEST_CASE( s_to_binary_8_4 )
{

  typedef Fi::Fixed<8, 4, Fi::SIGNED> fi;

  BOOST_CHECK_EQUAL( fi("-8.0").toBinary(), 128);
	BOOST_CHECK_EQUAL( fi("-7.1875").toBinary(), 141);
	BOOST_CHECK_EQUAL( fi("-6.0"		).toBinary(), 160);
	BOOST_CHECK_EQUAL( fi("-4.75"	).toBinary(), 180);
	BOOST_CHECK_EQUAL( fi("-2.5"		).toBinary(), 216);
	BOOST_CHECK_EQUAL( fi("-1.25"	).toBinary(), 236);
	BOOST_CHECK_EQUAL( fi("-0.0625").toBinary(), 255);
	BOOST_CHECK_EQUAL( fi( "0.0"		).toBinary(),	 0);
	BOOST_CHECK_EQUAL( fi( "0.0625").toBinary(),	 1);
	BOOST_CHECK_EQUAL( fi( "1.25"	).toBinary(),	20);
	BOOST_CHECK_EQUAL( fi( "2.5"		).toBinary(),	40);
	BOOST_CHECK_EQUAL( fi( "4.75"	).toBinary(),	76);
	BOOST_CHECK_EQUAL( fi( "6.0"		).toBinary(),	96);
	BOOST_CHECK_EQUAL( fi( "7.1875").toBinary(), 115);
	BOOST_CHECK_EQUAL( fi( "7.9375").toBinary(), 127);

}

BOOST_AUTO_TEST_CASE( s_from_binary_5_3 )
{

  typedef Fi::Fixed<5, 3, Fi::SIGNED> fi;

  CHECK_EQ( fi::fromBinary(16), "-2.0"  );
  CHECK_EQ( fi::fromBinary(23), "-1.125");
  CHECK_EQ( fi::fromBinary(24), "-1.0"  );
  CHECK_EQ( fi::fromBinary(28), "-0.5"  );
  CHECK_EQ( fi::fromBinary(30), "-0.25" );
  CHECK_EQ( fi::fromBinary(31), "-0.125");
  CHECK_EQ( fi::fromBinary( 0),	 "0.0"  );
  CHECK_EQ( fi::fromBinary( 1),	 "0.125");
  CHECK_EQ( fi::fromBinary( 2),	 "0.25" );
  CHECK_EQ( fi::fromBinary( 4),	 "0.5"  );
  CHECK_EQ( fi::fromBinary( 8),	 "1.0"  );
  CHECK_EQ( fi::fromBinary( 9),	 "1.125");
  CHECK_EQ( fi::fromBinary(15),  "1.875");

}

BOOST_AUTO_TEST_CASE( s_to_binary_5_3 )
{

  typedef Fi::Fixed<5, 3, Fi::SIGNED> fi;

  BOOST_CHECK_EQUAL( fi("-2.0"	).toBinary(), 16);
	BOOST_CHECK_EQUAL( fi("-1.125").toBinary(), 23);
	BOOST_CHECK_EQUAL( fi("-1.0"	).toBinary(), 24);
	BOOST_CHECK_EQUAL( fi("-0.5"	).toBinary(), 28);
	BOOST_CHECK_EQUAL( fi("-0.25" ).toBinary(), 30);
	BOOST_CHECK_EQUAL( fi("-0.125").toBinary(), 31);
	BOOST_CHECK_EQUAL( fi( "0.0"	).toBinary(),	 0);
	BOOST_CHECK_EQUAL( fi( "0.125").toBinary(),	 1);
	BOOST_CHECK_EQUAL( fi( "0.25" ).toBinary(),	 2);
	BOOST_CHECK_EQUAL( fi( "0.5"	).toBinary(),	 4);
	BOOST_CHECK_EQUAL( fi( "1.0"	).toBinary(),	 8);
	BOOST_CHECK_EQUAL( fi( "1.125").toBinary(),	 9);
	BOOST_CHECK_EQUAL( fi( "1.875").toBinary(),	15);


}

BOOST_AUTO_TEST_SUITE_END()
