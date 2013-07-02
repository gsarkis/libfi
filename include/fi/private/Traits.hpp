/*

 *Copyright © 2011-2012 Gabi Sarkis.
 *Copyright © 2012 Alexandre Raymond.

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

#ifndef FI_PRIVATE_TRAITS_HPP
#define FI_PRIVATE_TRAITS_HPP

#include "Fi.hpp"
#include "TypeFromRange.hpp"
#include "Limits.hpp"
#include "Masks.hpp"

#include <cstddef>
#include <cmath>

namespace Fi {

  /**
   *\internal
   *\brief Defines traits of a fixed-point type.

   *\tparam W Total word length in bits.
   *\tparam UTL Total number of bits the underlying type must be able to store.
   *\tparam F Length of the fractional part in bits.
   *\tparam S \c true if the number is signed, \c false otherwise.
   */
  template<std::size_t W, std::size_t UTL, std::size_t F, Signedness S>
  struct Traits {
    /**\internal 
     *\brief The total word length including any bits needed to indicate the 
     *sign.
    */
    static const std::size_t WORD_LENGTH     = W;
    /**\internal 
     *\brief The number of bits used to represent the integer part of the 
     *number.
     */
    static const std::size_t INTEGER_LENGTH = W-F;
    /**\internal 
     *\brief The number of bits used to represent the fractional part of the 
     *number.
     */
    static const std::size_t FRACTION_LENGTH = F;

    /**\internal
     *\brief The signedness of the number. Can be Fi::SIGNED or 
     *Fi::UNSIGNED
     */
    static const Signedness SIGNEDNESS = S;

    /**\internal 
     *\brief The smallest C++ built-in type which can store the fixed-point 
     *number.
     */
    typedef typename Fi::TypeFromRange<Range<UTL>::R, S>::valtype valtype;

    /**\internal 
     *\brief The smallest C++ built-in type which can store a signed 
     *fixed-point number of the same width.
     */
    typedef typename Fi::
    TypeFromRange<Range<UTL>::R, SIGNED>::valtype SignedType;

    /**\internal 
     *\brief The smallest C++ built-in type which can store an unsigned
     *fixed-point number of the same width.
     */
    typedef typename Fi::
    TypeFromRange<Range<UTL>::R, UNSIGNED>::valtype UnsignedType;

    ///\internal \brief A mask to select the entire number.
    static const valtype T_MASK = TMask<valtype, W>::value;
    ///\internal \brief A mask to select the sign bits.
    static const valtype S_MASK = SMask<valtype, WORD_LENGTH, S>::value;
	  ///\internal \brief A mask to select the sign bit.
	  static const valtype S_BIT = S_MASK & T_MASK;
    ///\internal \brief A mask to select the fractional bits.
    static const valtype F_MASK = FMask<valtype, W, F>::value;
    ///\internal \brief A mask to select the integer bits.
    static const valtype I_MASK = T_MASK & ~S_MASK & ~F_MASK;

    ///\internal \brief The maximum value that can be represented.
    static const valtype MAX_VAL = MaxVal<valtype, WORD_LENGTH, S>::value;
    ///\internal \brief The minimum value that can be represented.
    static const valtype MIN_VAL = MinVal<valtype, WORD_LENGTH, S>::value;

    ///\internal \brief The maximum double value that can be represented.
    static double minDoubleValue() {
      return static_cast<double>(MIN_VAL)/std::pow(2.0, FRACTION_LENGTH);
    }
    ///\internal \brief The minimum double value that can be represented.
    static double maxDoubleValue() {
      return static_cast<double>(MAX_VAL)/std::pow(2.0, FRACTION_LENGTH);
    }

  };
}

#endif
