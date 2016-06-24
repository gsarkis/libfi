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
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *GNU General Public License for more details.

 *You should have received a copy of the GNU General Public License
 *along with LibFi.  If not, see <http://www.gnu.org/licenses/>.

 */

#ifndef FI_FIXED_HPP
#define FI_FIXED_HPP

#include "private/Fi.hpp"
#include "private/Traits.hpp"
#include "private/OverflowDetector.hpp"
#include "private/StaticAssert.hpp"

#include "overflow/Throw.hpp"
#include "rounding/Fix.hpp"

#include <string>
#include <ostream>
#include <cstddef>
#include <cmath>

namespace Fi {

	/**\brief Fixed-point data type.
	 *
	 *\tparam W Total word length in bits, including the sign bit.
	 *Must be less than or equal to 32.
	 *\tparam F Number of fractional bits. Must be less than or equal to W.
	 *\tparam S Signedness of the resulting type.
	 *\tparam OF Overflow handling. It defaults to wrap-around.
	 *\tparam R Rounding mode. It defaults to rounding towards zero.

	 *Values for S are: signed (Fi::SIGNED) and unsigned (Fi::UNSIGNED).

	 *Default overflow handler is Throw. Other options are listed in \ref overflow.

	 *Default rounding method is towards zero (Fix). Other options are listed in \ref rounding.

	 *Here is an example of multiplying 8-bit signed fixed-point numbers with
	 *4 fractional bits and wrap-around overflow handling:
	 *\code
	 #include "fi/Fixed.hpp"

	 #include <iostream>

	 int main(int argc, char* argv[]) {
	 Fi::Fixed<8, 4, Fi::SIGNED, Fi::Wrap> a("3.14");
	 Fi::Fixed<8, 4, Fi::SIGNED, Fi::Wrap> b("13.14");

	 std::cout << a*b << std::endl;

	 return 0;
	 }
	 \endcode

	 *Here is the same example, but using saturation overflow handling and
	 *unsigned fixed-point numbers:
	 *\code
	 #include "fi/Fixed.hpp"
	 #include "fi/overflow/Saturate.hpp"

	 #include <iostream>

	 int main(int argc, char* argv[]) {
	 Fi::Fixed<8, 4, Fi::UNSIGNED, Fi::Saturate> a("3.14");
	 Fi::Fixed<8, 4, Fi::UNSIGNED, Fi::Saturate> b("13.14");

	 std::cout << a*b << std::endl;

	 return 0;

	 }
	 \endcode

	 *To display results using the C standard library, the code must still be 
	 *compiled using a C++ compiler, use the following code:
	 *\code
	 #include "fi/Fixed.hpp"

	 #include <stdio.h>

	 int main(int argc, char* argv[]) {
	 Fi::Fixed<8, 4, Fi::SIGNED, Fi::Wrap> a("3.14");
	 Fi::Fixed<8, 4, Fi::SIGNED, Fi::Wrap> b("13.14");

	 printf("%s\n", (a*b).toString().c_str());

	 return 0;
	 }
	 \endcode

	*/
	template<std::size_t W, std::size_t F, Fi::Signedness S, 
	         template <typename> class OF=Fi::Throw,
	         template <typename> class R=Fi::Fix>

	class Fixed {

		//will be replaced with C++11 static_assert
		FI_STATIC_ASSERT_W_0(W > 0);
		FI_STATIC_ASSERT_W_33(W <= 32);
		FI_STATIC_ASSERT_W_F(W >= F);

	public:

		///Total word length in bits, including the sign bit.
		static const std::size_t WORD_LENGTH     = W;
		///Number of fractional bits.
		static const std::size_t FRACTION_LENGTH = F;
		///Signedness of the type.
		static const Fi::Signedness SIGNEDNESS = S;

		typedef Fi::Traits<W, OF<Info>::WIDTH_MULT*W, F, S> TR;
		///Datatype used for storage.
		typedef typename TR::valtype valtype;

		///A mask to obtain the fractional bits only.
		static const valtype F_MASK = TR::F_MASK;
		///A mask to obtain the integer bits only.
		static const valtype I_MASK = TR::I_MASK;
		///A mask to obtain the entire number discarding any padding bits.
		static const valtype T_MASK = TR::T_MASK;
		///A mask to obtain the sign bit.
		static const valtype S_MASK = TR::S_MASK;

		///Overflow handler.
		typedef OverflowDetector< TR, OF > OFH;
		///Rounding handler.
		typedef R<TR> RH;

		/**
		 *\brief Creates a new Fixed object initialized to zero.
		 */
		Fixed();

		/**
		 *\brief Copies a Fixed object.
		 */
		Fixed(const Fixed& a);

		/**
		 *\brief Creates a new Fixed object from a double-precision 
		 *floating-point number.
		 *
		 *\param f Floating-point number.
		 */
		explicit Fixed(double f);

		/**
		 *\brief Creates a new Fixed object from a string.
		 *
		 *\param number String representing a fixed-point number.
		 *
		 *Correct format for s is:
		 *\li For unsigned numbers: "d.d" or "+d.d", where "d" is one or many 
		 *numeric digits.
		 *\li For signed number: "d.d", "+d.d", or "-d.d", where "d" is one 
		 *or many numeric digits.

		 *\throw  std::invalid_argument when the provided number is invalid
		 */
		explicit Fixed(const std::string& number);

		/**
		 *\brief Creates a new Fixed object from another.
		 *\param src Source fixed-point number.
		 *\return A fixed-point number.
		 *\tparam W2 Width of source number.
		 *\tparam F2 Number of fractional bits in source number.
		 *\tparam S2 Signedness of source number.
		 *\tparam OF2 Overflow handler of the source number.
		 *\tparam R2 Rounding method of the source number.
		 */
		template<std::size_t W2, std::size_t F2, Fi::Signedness S2, 
		         template <typename> class OF2,
		         template <typename> class R2>
		static Fixed fromFixed(const Fixed<W2, F2, S2, OF2, R2>& src);

		/**
		 *\brief Creates a new Fixed object from a raw binary number.
		 *\param value Raw binary value representing a fixed point number.
		 *\return A fixed-point number.
		 *\note All but the first W bits will be ignored.
		 */
		static Fixed fromBinary(valtype value);

		/**
		 *\brief Assignment operator.
		 *\param that Fixed object to assign from.
		 */
		Fixed& operator=(const Fixed& that);

		/**
		 *\brief Less-than comparison operator.
		 */
		bool operator<(const Fixed& x) const;

		/**
		 *\brief Equality comparison operator
		 */
		bool operator==(const Fixed& x) const;

		/**
		 *\brief Increment operator.

		 *Increments the current value by \c x.

		 *\param x Increment amount.
		 */
		Fixed& operator+=(const Fixed& x);

		/**
		 *\brief Decrement operator.

		 *Decrements the current value by \c x.

		 *\param x Decrement amount.
		 */
		Fixed& operator-=(const Fixed& x);

		/**
		 *\brief Multiply and store operator.

		 *Multiplies the current value by \c x.

		 *\param x Multiplicand.
		 */
		Fixed& operator*=(const Fixed& x);

		/**
		 * Multiply this object by a Fixed object with different width
		 * parameters.
		 *
		 *\param x Multiplicand
		 *\tparam W2 Width of multiplicand.
		 *\tparam F2 Number of fractional bits in multiplicand.
		 *\tparam S2 Signedness of multiplicand.
		 *\tparam OF2 Overflow handler of the multiplicand.
		 *\tparam R2 Rounding method of the multiplicand.
		 */
		template<std::size_t W2, std::size_t F2, Fi::Signedness S2, 
		         template <typename> class OF2,
		         template <typename> class R2>
		Fixed& operator*=(const Fixed<W2, F2, S2, OF2, R2>& x);

		/**
		 *\brief Divide and store operator.

		 *Divides the current value by \c x.

		 *\param x Divisor.
		 */
		Fixed& operator/=(const Fixed& x);

		/**
		 *\brief Bit-wise \c NOT.
		 */
		const Fixed operator~() const;

		/**
		 *\brief Bit-wise \c OR and store.

		 *Performs a bit-wise \c OR between the current value and \c x.

		 *\param x \c OR operand.
		 */
		Fixed& operator|=(const Fixed& x);

		/**
		 *\brief Bit-wise \c AND and store.

		 *Performs a bit-wise \c AND between the current value and \c x.

		 *\param x \c AND operand.
		 */
		Fixed& operator&=(const Fixed& x);

		/**
		 *\brief Bit-wise \c XOR and store.

		 *Performs a bit-wise \c XOR between the current value and \c x.

		 *\param x \c XOR operand.
		 */
		Fixed& operator^=(const Fixed& x);

		/**
		 *\brief Binary right-shift and store.
		 *\param pos Number of positions to shift the bits.

		 *\warning For unsigned numbers, zeros are shifted in.
		 *However, for signed numbers, the behavior is defined by
		 *the compiler.
		 */
		Fixed& operator>>=(std::size_t pos);

		/**
		 *\brief Binary left-shift and store.
		 *\param pos Number of positions to shift the bits.

		 *\note Zeros are shifted in.
		 */
		Fixed& operator<<=(std::size_t pos);

		/**
		 *\brief Convert to \c float.

		 *Converts the fixed-point value to a single-precision floating-point 
		 *number.

		 *\sa Fixed::toString() for a higher-precision display method.
		 *\return floating-point number.
		 */
		float toFloat() const;

		/**
		 *\brief Convert to \c double.

		 *Converts the fixed-point value to a double-precision floating-point 
		 *number.

		 *\sa Fixed::toString() for a higher-precision display method.
		 *\return floating-point number.
		 */
		double toDouble() const;

		/**
		 *\brief Integer part of number.

		 *Returns the integer part of the fixed-point number, e.g. the integer 
		 *part of 3.14 is 3.

		 *\return The integer part.
		 */
		std::string integer() const;

		/**
		 *\brief Fractional part of number.

		 *Returns the fractional part of the fixed-point number, e.g. the 
		 *fractional part of 3.14 is 14.

		 *\return The fractional part.
		 */
		std::string fraction() const;

		/**
		 *\brief String representation of number.

		 *Returns the fixed-point number represented as a string.
		 *\note This is the most accurate method of displaying a fixed-point
		 *since its precision might exceed that provided by the float and double
		 *data types returned by Fixed::toFloat, and Fixed::toDouble,
		 *respectively
		 *\returns string representation.
		 */
		std::string toString() const;

		/**
		 *\brief Returns a string containing the binary representation of number.

		 *\return Binary representation of number.
		 */
		std::string toBinaryString() const;

		/**
		 *\brief Returns the raw binary representation of the number.
		 *\param extendSign Extend the sign bit and maintain sign.
		 *\return Raw binary representation.
		 *\warning The returned value does not have its sign extended
		 *by default, i.e.
		 *negative numbers might appear to the compiler as positive if
		 *W < sizeof(valtype)
		 */
		valtype toBinary(bool extendSign=false) const;

		/**
		 *\brief Maximum possible value.

		 *Returns the largest value that can be stored in this Fixed class.

		 *\return Maximum possible value.
		 */
		static Fixed MaxVal();

		/**
		 *\brief Minimum possible value.

		 *Returns the smallest value that can be stored in this Fixed class.

		 *\return Minimum possible value.
		 */
		static Fixed MinVal();

	private:

		valtype _val;

	};


	/** \name Comparison operators */
	//@{
	/**
	 *\relates Fi::Fixed
	 *\brief Equality check operator.
	 */
	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	inline bool operator==(const Fi::Fixed<W, F, S, OF, R>& x, 
	                       const Fi::Fixed<W, F, S, OF, R>& y);

	/**
	 *\relates Fi::Fixed
	 *\brief Inequality check operator.
	 */
	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	inline bool operator!=(const Fi::Fixed<W, F, S, OF, R>& x, 
	                       const Fi::Fixed<W, F, S, OF, R>& y);

	/**
	 *\relates Fi::Fixed
	 *\brief Less than operator.
	 */
	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	inline bool operator<(const Fi::Fixed<W, F, S, OF, R>& x, 
	                      const Fi::Fixed<W, F, S, OF, R>& y);

	/**
	 *\relates Fi::Fixed
	 *\brief Less than or equals operator.
	 */
	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	inline bool operator<=(const Fi::Fixed<W, F, S, OF, R>& x, 
	                       const Fi::Fixed<W, F, S, OF, R>& y);

	/**
	 *\relates Fi::Fixed
	 *\brief Greater than operator.
	 */
	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	inline bool operator>(const Fi::Fixed<W, F, S, OF, R>& x, 
	                      const Fi::Fixed<W, F, S, OF, R>& y);

	/**
	 *\relates Fi::Fixed
	 *\brief Greater than or equals operator.
	 */
	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>

	inline bool operator>=(const Fi::Fixed<W, F, S, OF, R>& x, 
	                       const Fi::Fixed<W, F, S, OF, R>& y);

	//@}

	/** \name Arithmetic operators */
	//@{

	/**
	 *\relates Fi::Fixed
	 *\brief Addition operator.
	 */
	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fi::Fixed<W, F, S, OF, R> 
	operator+(const Fi::Fixed<W, F, S, OF, R>& x, 
	          const Fi::Fixed<W, F, S, OF, R>& y);

	/**
	 *\relates Fi::Fixed
	 *\brief Subtraction operator.
	 */
	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fi::Fixed<W, F, S, OF, R> 
	operator-(const Fi::Fixed<W, F, S, OF, R>& x, 
	          const Fi::Fixed<W, F, S, OF, R>& y);


	/**
	 *\relates Fi::Fixed
	 *\brief Negation operator.
     
	 *Negates the number.

	 *\return The additive inverse of the number.
	 */
	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fi::Fixed<W, F, S, OF, R> 
	operator-(const Fi::Fixed<W, F, S, OF, R>& a);

	/**
	 *\relates Fi::Fixed
	 *\brief Multiplication operator.
	 */
	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fi::Fixed<W, F, S, OF, R>
	operator*(const Fi::Fixed<W, F, S, OF, R>& x, 
	          const Fi::Fixed<W, F, S, OF, R>& y);

	/**
	 *\relates Fi::Fixed
	 *\brief Division operator.
	 */
	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fi::Fixed<W, F, S, OF, R>
	operator/(const Fi::Fixed<W, F, S, OF, R>& x, 
	          const Fi::Fixed<W, F, S, OF, R>& y);

	/**
	 *\relates Fi::Fixed
	 *\brief Returns the smaller of two values
	 */
	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fi::Fixed<W, F, S, OF, R>
	min(const Fi::Fixed<W, F, S, OF, R>& x, 
	    const Fi::Fixed<W, F, S, OF, R>& y);

	/**
	 *\relates Fi::Fixed
	 *\brief Returns the greater of two values
	 */
	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fi::Fixed<W, F, S, OF, R>
	max(const Fi::Fixed<W, F, S, OF, R>& x, 
	    const Fi::Fixed<W, F, S, OF, R>& y);
	
	//@}

	/**\name Bit-wise manipulation */
	//@{

	/**
	 *\brief Bit-wise \c NOT
	 *\relates Fi::Fixed
	 */
	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fi::Fixed<W, F, S, OF, R> 
	operator~(const Fi::Fixed<W, F, S, OF, R>& x);

	/**
	 *\brief Bit-wise \c OR
	 *\relates Fi::Fixed
	 */
	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fi::Fixed<W, F, S, OF, R> 
	operator|(const Fi::Fixed<W, F, S, OF, R>& x, 
	          const Fi::Fixed<W, F, S, OF, R>& y);

	/**
	 *\brief Bit-wise \c AND
	 *\relates Fi::Fixed
	 */
	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fi::Fixed<W, F, S, OF, R> 
	operator&(const Fi::Fixed<W, F, S, OF, R>& x, 
	          const Fi::Fixed<W, F, S, OF, R>& y);

	/**
	 *\brief Bit-wise \c XOR
	 *\relates Fi::Fixed
	 */
	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fi::Fixed<W, F, S, OF, R> 
	operator^(const Fi::Fixed<W, F, S, OF, R>& x, 
	          const Fi::Fixed<W, F, S, OF, R>& y);

	/**
	 *\brief Binary left-shift.
	 *\param x Fixed-point number to shift.
	 *\param pos Number of positions to shift the bits.

	 *\note Zeros are shifted in.

	 *\relates Fi::Fixed
	 */
	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fi::Fixed<W, F, S, OF, R> 
	operator<<(const Fi::Fixed<W, F, S, OF, R>& x, std::size_t pos);

	/**
	 *\brief Binary right-shift.
	 *\param x Fixed-point number to shift.
	 *\param pos Number of positions to shift the bits.

	 *\warning For unsigned numbers, zeros are shifted in.
	 *However, for signed numbers, the behavior is defined by
	 *the compiler.

	 *\relates Fi::Fixed
	 */
	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fi::Fixed<W, F, S, OF, R>
	operator>>(const Fi::Fixed<W, F, S, OF, R>& x, std::size_t pos);
	//@}

	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	std::ostream& 
	operator<<(std::ostream& os, const Fi::Fixed<W, F, S, OF, R>& x);
}

namespace std {
	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	Fi::Fixed<W, F, S, OF, R> abs(const Fi::Fixed<W, F, S, OF, R>& x);
}

#include "private/Fixed_priv.hpp"


#endif
