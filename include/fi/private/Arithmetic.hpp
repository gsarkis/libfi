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

#ifndef FI_PRIVATE_ARITHMETIC_HPP
#define FI_PRIVATE_ARITHMETIC_HPP

#include "Fi.hpp"

namespace Fi {

  /**\internal
   *\brief Determine whether a fixed-point number is positive or negative 
   *regardless
   *of the sign of the underlying type.
   *\tparam TR Fi::Traits of the fixed-point type.
   */
  template<typename TR>
  bool isNegative(const typename TR::valtype & val) {
    return (((val & TR::S_MASK) >> (TR::WORD_LENGTH-1)) & 0x01) != 0;
  }

}

#endif
