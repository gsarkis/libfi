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

#ifndef FI_PRIVATE_FI_HPP
#define FI_PRIVATE_FI_HPP

//#include <cmath>

/**
 *\brief Top-level namespace.

 *Includes all the datatypes provided by the library.
 */
namespace Fi {

  /**\internal 
     \brief The ability of the fixed-point type to store positive numbers
     *only or both positive and negative numbers.
     */
  enum Signedness {
    /**\internal
     *A signed fixed-point number that can represent both positive
     *and negative numbers.
     */
    SIGNED,
    /**\internal
     *An unsigned fixed-point number that can only represent positive
     *numbers.
     */
    UNSIGNED};




}

#endif
