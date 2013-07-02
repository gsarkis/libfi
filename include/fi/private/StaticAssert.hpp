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

#ifndef FI_PRIVATE_STATIC_ASSERT_HPP
#define FI_PRIVATE_STATIC_ASSERT_HPP

#define FI_CONC(a, b) a ## b
#define FI_CONC2(a, b) FI_CONC(a, b)

#define FI_STATIC_ASSERT_W_F(x) typename \
	Fi::AssertionFailure<sizeof(Fi::W_Must_Be_Greater_than_or_Equal_to_F<(x)==0?false:true>)> \
	FI_CONC2(AssertionValtype, __LINE__)

#define FI_STATIC_ASSERT_W_33(x) typename \
	Fi::AssertionFailure<sizeof(Fi::W_Must_Be_Less_than_33<(x) == 0 ? false : true>)> \
	FI_CONC2(AssertionValtype, __LINE__)

namespace Fi {

	template<bool B> struct W_Must_Be_Greater_than_or_Equal_to_F;

	template<> struct W_Must_Be_Greater_than_or_Equal_to_F<true> {
		static const int val = 1;
	};

	template<bool B> struct W_Must_Be_Less_than_33;

	template<> struct W_Must_Be_Less_than_33<true> {
		static const int val = 1;
	};

	template<int I> struct AssertionFailure {
		typedef bool valtype;
	};


}

#endif
