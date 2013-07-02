/*

 *Copyright © 2012 Gabi Sarkis.

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

#ifndef FI_PRIVATE_OVERFLOW_DETECTOR_HPP
#define FI_PRIVATE_OVERFLOW_DETECTOR_HPP

#include "Parser.hpp"
#include "StringConversion.hpp"
#include "StringMath.hpp"

#include <string>
#include <cstddef>
#include <cmath>

namespace Fi {

  /**
   *\internal
   *\brief An overflow detector.

   *Converts from different types to a Fixed number,
   *detects overflow, and applies the handler \c OFH

   *\tparam T Traits of the fixed-point number.
   *\tparam OFH Overflow handler.
   */
  template<typename T, template <typename> class OFH>
  class OverflowDetector {

  public:

    /**
     *\internal
     *\brief Detect overflow in conversion from another fixed-point number.
     *\param n Integer representing a fixed-point number.
     *\return An integer representing the fixed-point number after
     *overflow has been handled.
     */
    static typename T::valtype fromFixedPoint(const typename T::valtype& n);

    /**
     *\internal
     *\brief Detect overflow in conversion from a floating-point number.
     *\param f Source floating-point number.
     *\param n Fixed-point result of conversion.
     *\param maxRoundChange Maximum possible amount the number was 
     *adjust by due to rounding.
     *\return An integer representing the fixed-point number after
     *overflow has been handled.
     */
    static typename T::valtype fromDouble(double f,
                                          const typename T::valtype& n,
                                          double maxRoundChange);

    /**
     *\internal
     *\brief Detect overflow in conversion from a string.
     *\param str String representing a number. \c str must
     *not be an empty string.
     *\param n Fixed-point result of conversion.
     *\param roundingDirection Whether the value of the number increased 
     *(+1), decreased (-1), or did not change (0) as a result of rounding.
     *\return An integer representing the fixed-point number after
     *overflow has been handled.
     */
    static typename T::valtype fromString(const std::string& str,
                                          const typename T::valtype& n,
                                          int roundingDirection);

  };

  template<typename T,  template <typename> class OFH>
  inline typename T::valtype OverflowDetector<T, OFH>::
  fromFixedPoint(const typename T::valtype& n) {

    //Cannot use ternary operator due to n being const.

    typename T::valtype ret(n);

    //Casting to signed to detect negative overflow as a result of
    //subtracting two unsigned numbers.
    if (static_cast<typename T::SignedType>(n) < T::MIN_VAL) {
      ret = OFH<T>::negativeOverflow(n);
    }
    else if (static_cast<typename T::SignedType>(n) > T::MAX_VAL) {
      ret = OFH<T>::positiveOverflow(n);
    }

    return ret;

  }

  template<typename T, template <typename> class OFH>
  inline typename T::valtype OverflowDetector<T, OFH>::
  fromDouble(double f, const typename T::valtype& n, double maxRoundChange) {

    typename T::valtype ret = n;
    double minimum = T::minDoubleValue();
    double maximum = T::maxDoubleValue();

    //Cannot simplify to (f <= (minimum - r)).
    //Consider minimum = 0, r = -0.1 (rounding down), and f = 0.05.
    if ((f < minimum) && ((minimum - f) >= maxRoundChange)) {
      ret = OFH<T>::negativeOverflow(ret);
    }
    else if ((f > maximum) && ((f - maximum) >= -maxRoundChange)) {
      ret = OFH<T>::positiveOverflow(ret);
    }

    return ret;

  }

  template<typename T, template <typename> class OFH>
  inline typename T::valtype OverflowDetector<T, OFH>::
  fromString(const std::string& fStr, const typename T::valtype& res,
             int roundingDirection) {

    typename T::valtype ret = res;

    std::string convRes = StringConversion::toString<T>(ret);

    bool negative = (fStr[0] == '-');
    bool overflow = false;

    if (negative && (convRes[0] != '-') && (convRes != "0.0")) {
      overflow = true;
    }
    else if (!negative && (convRes[0] == '-') && (convRes != "0.0")) {
      overflow = true;
    }
    else {

      std::string minimum = StringConversion::toString<T>(+T::MIN_VAL);
      std::string maximum = StringConversion::toString<T>(+T::MAX_VAL);

      if (StringMath::greater(fStr, maximum)) {

        overflow = true;

        if (roundingDirection == -1) {
          std::string integer;
          std::string fractional;
          typename T::valtype sign;
          parseNumber(maximum, T::SIGNEDNESS, sign, integer, fractional);
          std::string limit = StringMath::plusOne(integer) + ".0";
          if (StringMath::less(fStr, limit)) {
            overflow = false;
          }
        }

      }
      else if (StringMath::less(fStr, minimum)) {

        overflow = true;

        if (roundingDirection == 1) {
          std::string integer;
          std::string fractional;
          typename T::valtype sign;
          parseNumber(minimum, T::SIGNEDNESS, sign, integer, fractional);
          std::string limit = "-" + integer + "."
            + StringConversion::unsignedFractionalString<T>(typename T::valtype(1));
          if (StringMath::greater(fStr, limit)) {
            overflow = false;
          }
        }

      }

    }

    if (overflow && negative) {
      ret = OFH<T>::negativeOverflow(ret);
    }
    else if (overflow && !negative) {
      ret = OFH<T>::positiveOverflow(ret);
    }

    return ret;

  }

}
#endif
