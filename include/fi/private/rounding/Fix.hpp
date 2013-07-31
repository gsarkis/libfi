/*

 *Copyright © 2011-2012 Gabi Sarkis.

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

#ifndef FI_PRIVATE_ROUNDING_FIX_HPP
#define FI_PRIVATE_ROUNDING_FIX_HPP

#include "fi/private/Fi.hpp"
#include "fi/private/DoubleConversion.hpp"

#include <string>
#include <utility>

namespace Fi {

	/**
	 *\ingroup rounding
	 *\brief Round towards zero.

	 *A value is rounded towards zero. Also known as fix
	 *or away from infinity.

	 *Always assumes that T::FRACTION_LENGTH bits will be rounded away.

	 *\tparam T Fi::Traits of the fixed-point type.
	 */
	template <typename T>
	struct Fix {

		/**\internal
		 *\brief Round a number towards zero.
		 *\param n Fixed-point number to be rounded.
		 *\return The rounded value and -1 (+1) indicating that
		 *positive (negative) numbers can decrease (increase) in value
		 *as a result of rounding, or 0 if the input \c n is zero.
		 */
		static std::pair<typename T::valtype, int>
		round(const typename T::valtype& n);

		/**\internal
		 *\brief Round a number towards zero.
		 *\param fl Original floating-point number.
		 *\param n Fixed-point number to be rounded.
		 *\return The rounded value and -1 (+1) indicating that
		 *positive (negative) numbers can decrease (increase) in value
		 *as a result of rounding, or 0 if the input \c fl is zero.
		 */
		static std::pair<typename T::valtype, int>
		round(double fl, const typename T::valtype& n);

		/**\internal
		 *\brief Round a number towards zero.
		 *\param str Original string representation of number.
		 *\param n Fixed-point number to be rounded.
		 *\return The rounded value and -1 (+1) indicating that
		 *positive (negative) numbers can decrease (increase) in value
		 *as a result of rounding, or 0 if the input \c str is zero.
		 */
		static std::pair<typename T::valtype, int>
		round(const std::string& str, const typename T::valtype& n);

	};

}

template <typename T>
inline std::pair<typename T::valtype, int> Fi::Fix<T>::
round(const typename T::valtype& n) {

	int direction = 0;
	typename T::valtype ret = n & ~T::F_MASK;

	if (n != 0) {
		direction = -1;
		ret >>= T::FRACTION_LENGTH;

		//use n <= instead of < to suppress a warning (not an issue
		//because of the above if (n != 0)
		if ((T::SIGNEDNESS == SIGNED) && (n <= 0)) {
			direction = +1;
			if ((T::F_MASK & n) != typename T::valtype(0)) {
				ret += typename T::valtype(1);
			}
		}
	}

	return std::make_pair(ret, direction);

}

template <typename T>
inline std::pair<typename T::valtype, int> Fi::Fix<T>::
round(double fl, const typename T::valtype& n) {

	int direction = 0;

	typename T::valtype ret = n & ~T::F_MASK;

	if (fl != 0.0) {
		direction = -1;
		ret >>= T::FRACTION_LENGTH;

		if ((T::SIGNEDNESS == SIGNED) && (fl < 0.0)) {
			direction = +1;
			if ((T::F_MASK & n) != typename T::valtype(0)) {
				ret += typename T::valtype(1);
			}
		}
	}

	return std::make_pair(ret, direction);

}

template <typename T>
inline std::pair<typename T::valtype, int> Fi::Fix<T>::
round(const std::string& /*str*/, const typename T::valtype& n) {

	return round(n);

}

#endif
