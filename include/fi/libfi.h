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

/**
 *\defgroup overflow Overflow
 *\brief Different mechanisms for handling overflow.

 *The library will support most of the overflow handling mechanisms proposed for TR2:
 *\li "impossible," the programmer has determined that overflow cannot occur: will be supported by Fi::Undefined.
 *\li "modulus," the assigned value is the dynamic value mod the range of the variable: supported by Fi::Wrap.
 *\li "saturate," if the dynamic value exceeds the range of the variable, assign the nearest representable value: supported by Fi::Saturate.
 *\li "exception," if the dynamic value exceeds the range of the variable, throw an exception of type std::overflow_error: supported by Fi::Throw.

 * If overflow occurs in "impossible" mode, the behavior will be undefined.
 */

/**
 *\defgroup rounding Rounding
 *\brief Different mechanisms for rounding numbers.
 */

/**
 *\mainpage LibFi User Documentation

 LibFi is a fixed-point arithmetic library for C++, focusing on flexibility and 
 correctness, not speed. It is intended to be used for modeling hardware systems.

 Unlike most other C and C++ fixed-point libraries, the word length in LibFi does not have 
 to be a multiple of 8, and the overflow behavior and rounding method are customizable.

 LibFi provides the fixed-point type Fi::Fixed and is header only.

 */
