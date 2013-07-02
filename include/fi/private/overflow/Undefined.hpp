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

#ifndef FI_PRIVATE_OVERFLOW_UNDEFINED_HPP
#define FI_PRIVATE_OVERFLOW_UNDEFINED_HPP

#include "fi/private/Fi.hpp"
#include "fi/private/Info.hpp"

#include <string>
#include <cmath>

namespace Fi {

  /**
   *\ingroup overflow
   *\brief Optimized for speed, the actual behavior depends on the 
   *compiler and underlying system.

   *\warning The programmer is willing to accept undefined behavior 
   *in the event of an overflow.

   *\note Currently, the only advantage to use using this over other
   *overflow handler is a minor speed improvement.

   *\tparam T Fi::Traits of the fixed-point type.
   */
  template <typename T>
  struct Undefined {

    /**
     *\internal
     *\brief Positive overflow from an integer type representing
     *a fixed-point number.
     *
     *\param n Integer representing a fixed-point number.
     *\return The number.
     *\warning The programmer is willing to accept undefined behavior 
     *in the event of an overflow.
     */
    static typename T::valtype positiveOverflow(const typename T::valtype& n);

    /**
     *\internal
     *\brief Handle negative overflow from an integer type representing
     *a fixed-point number.
     *
     *\param n Integer representing a fixed-point number.
     *\return The number.
     *\warning The programmer is willing to accept undefined behavior 
     *in the event of an overflow.
     */
    static typename T::valtype negativeOverflow(const typename T::valtype& n);

  };

  /**\internal
   *\brief A specialization to retrieve information about the overflow handler.
   */
  template<>
  struct Undefined<Fi::Info> {
    static const std::size_t WIDTH_MULT = 2;
  };

  template<typename T>
  inline typename T::valtype Undefined<T>::
  positiveOverflow(const typename T::valtype& n) {

    return n;

  }

  template<typename T>
  inline typename T::valtype Undefined<T>::
  negativeOverflow(const typename T::valtype& n) {

    return n;

  }

  
}

#endif
