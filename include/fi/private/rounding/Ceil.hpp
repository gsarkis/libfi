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

#ifndef FI_PRIVATE_ROUNDING_CEIL_HPP
#define FI_PRIVATE_ROUNDING_CEIL_HPP

#include "fi/private/Fi.hpp"
#include "fi/private/DoubleConversion.hpp"

#include <string>
#include <utility>

namespace Fi {

  /**
   *\ingroup rounding
   *\brief Round towards positive infinity.

   *A value is rounded towards positive infinity. Also known as ceil
   *or positive.

   *Always assumes that T::FRACTION_LENGTH bits will be rounded away.

   *\tparam T Fi::Traits of the fixed-point type.
   */
  template <typename T>
  struct Ceil {

    /**\internal
     *\brief Round a number towards positive infinity.
     *\param n Fixed-point number to be rounded.
     *\return The rounded value and 1 indicating.
     *that numbers can increase in value as a result of rounding,
     *or 0 if the input is 0.
     */
    static std::pair<typename T::valtype, int>
    round(const typename T::valtype& n);

    /**\internal
     *\brief Round a number towards positive infinity.
     *\param fl Original floating-point number.
     *\param n Fixed-point number to be rounded.
     *\return The rounded value and 1 indicating.
     *that numbers can increase in value as a result of rounding,
     *or 0 if the input is 0.
     */
    static std::pair<typename T::valtype, int>
    round(double fl, const typename T::valtype& n);

    /**\internal
     *\brief Round a number towards positive infinity.
     *\param str Original string representation of number.
     *\param n Fixed-point number to be rounded
     *\return The rounded value and 1 indicating
     *that numbers can increase in value as a result of rounding,
     *or 0 if the input is 0.
     */
    static std::pair<typename T::valtype, int>
    round(const std::string& str, const typename T::valtype& n);

  };

}

template <typename T>
inline std::pair<typename T::valtype, int> Fi::Ceil<T>::
round(const typename T::valtype& n) {

	int direction = (n == 0) ? 0 : 1;

  typename T::valtype ret = n >> T::FRACTION_LENGTH;

  if ((n & T::F_MASK) != 0) {
    ret += 1;
  }

  return std::make_pair(ret, direction);

}

template <typename T>
inline std::pair<typename T::valtype, int> Fi::Ceil<T>::
round(double fl, const typename T::valtype& n) {

	int direction = (fl == 0) ? 0 : 1;

  typename T::valtype ret = n >> T::FRACTION_LENGTH;

  if ((n & T::F_MASK) != 0) {
    ret += 1;
  }

  if ((direction == 1) &&
      DoubleConversion::toDouble<T>(ret) < fl) {
	  ret += 1;
  }

  return std::make_pair(ret, direction);

}

template <typename T>
inline std::pair<typename T::valtype, int> Fi::Ceil<T>::
round(const std::string& str, const typename T::valtype& n) {

	int direction = (str == "0.0") ? 0 : 1;

	typename T::valtype ret = n >> T::FRACTION_LENGTH;

  if ((direction == 1) &&
      StringMath::less(StringConversion::toString<T>(ret), str)) {
	  ret += 1;
  }

  return std::make_pair(ret, direction);

}

#endif
