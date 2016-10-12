/*

 *Copyright © 2016 Francois Leduc-Primeau

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

#ifndef FI_CFIXED_HPP
#define FI_CFIXED_HPP

#include "fi/Fixed.hpp"

#include "overflow/Throw.hpp"
#include "rounding/Fix.hpp"

#include <cstddef>
#include <cmath>
#include <complex>

namespace Fi {

	/**\brief Complex number composed of two Fi::Fixed values with identical parameters
	 *
	 *\tparam W Total word length in bits, including the sign bit.
	 *Must be less than or equal to 32.
	 *\tparam F Number of fractional bits. Must be less than or equal to W.
	 *\tparam S Signedness of the resulting type.
	 *\tparam OF Overflow handling. It defaults to wrap-around.
	 *\tparam R Rounding mode. It defaults to rounding towards zero.
	 *
	 *\see Fi::Fixed
	 */

	template<std::size_t W, std::size_t F, Fi::Signedness S, 
	         template <typename> class OF=Fi::Throw,
	         template <typename> class R=Fi::Fix>
	class CFixed {
	public:
		/**
		 *\brief Create a new CFixed object initialized to zero.
		 */		
		CFixed();

		/**
		 *\brief Copies a CFixed object.
		 */
		CFixed(const CFixed& a);

		/**
		 *\brief Creates a new CFixed object from a double-precision 
		 *floating-point real part and imaginary part.
		 *
		 *\param realf Floating-point real part.
		 *\param imagf Floating-point imaginary part.
		 */
		CFixed(double realf, double imagf);

		/**
		 * Creates a new CFixed object from a std::complex<double> object.
		 *
		 *\param c  A complex number.
		 */
		CFixed(std::complex<double>& c);

		/**
		 *\brief Creates a new CFixed object from two Fixed objects.
		 */
		CFixed(const Fixed<W,F,S,OF,R>& real, const Fixed<W,F,S,OF,R>& imag);

		/**
		 *\brief Creates a new CFixed object by converting another.
		 *\param src Source complex fixed-point number.
		 *\return A CFixed object.
		 *\tparam W2 Width of source number.
		 *\tparam F2 Number of fractional bits in source number.
		 *\tparam S2 Signedness of source number.
		 *\tparam OF2 Overflow handler of the source number.
		 *\tparam R2 Rounding method of the source number.
		 */
		template<std::size_t W2, std::size_t F2, Fi::Signedness S2, 
		         template <typename> class OF2,
		         template <typename> class R2>
		static CFixed fromCFixed(const CFixed<W2, F2, S2, OF2, R2>& src);
		
		/**
		 *\brief Assignment operator.
		 *\param that CFixed object to assign from.
		 */
		CFixed& operator=(const CFixed& that);

		/**
		 *\brief Equality comparison operator
		 */
		bool operator==(const CFixed& x) const;

		/**
		 *\brief Increment operator.

		 *Increments the current value by \c x.

		 *\param x Increment amount.
		 */
		CFixed& operator+=(const CFixed& x);

		/**
		 *\brief Decrement operator.

		 *Decrements the current value by \c x.

		 *\param x Decrement amount.
		 */
		CFixed& operator-=(const CFixed& x);

		/**
		 *\brief Multiply and store operator.

		 *Multiplies the current value by \c x.

		 *\param x Multiplicand.
		 */
		CFixed& operator*=(const CFixed& x);

		/**
		 * Multiply this object by a CFixed object with different width
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
		CFixed& operator*=(const CFixed<W2,F2,S2,OF2,R2>& x);

		/**
		 *\brief Divide and store operator.

		 *Divides the current value by \c x.

		 *\param x Divisor.
		 */
		// CFixed& operator/=(const CFixed& x);		

		/**
		 *\brief Binary right-shift and store of both the real and imaginary parts.
		 *\param pos Number of positions to shift the bits.

		 *\warning For unsigned numbers, zeros are shifted in.
		 *However, for signed numbers, the behavior is defined by
		 *the compiler.
		 */		
		CFixed& operator>>=(std::size_t pos);

		/**
		 *\brief Binary left-shift and store of both the real and imaginary parts.
		 *\param pos Number of positions to shift the bits.

		 *\note Zeros are shifted in.
		 */		
		CFixed& operator<<=(std::size_t pos);
		
		/**
		 *\brief Convert to \c std::complex<double>.

		 *Converts the fixed-point complex number to std::complex<double>.

		 *\sa CFixed::toString() for a higher-precision display method.
		 *\return floating-point number.
		 */
		std::complex<double> toDouble() const;

		/**
		 * Returns the real part.
		 */
		Fi::Fixed<W,F,S,OF,R> real() const;

		/**
		 * Returns the imaginary part.
		 */
		Fi::Fixed<W,F,S,OF,R> imag() const;

	private:

		Fi::Fixed<W,F,S,OF,R> _real;
		Fi::Fixed<W,F,S,OF,R> _imag;

	}; // end class CFixed

	/** \name Comparison operators */
	//@{
	/**
	 *\relates Fi::CFixed
	 *\brief Equality check operator.
	 */
	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	inline bool operator==(const Fi::CFixed<W, F, S, OF, R>& x, 
	                       const Fi::CFixed<W, F, S, OF, R>& y);

	/**
	 *\relates Fi::CFixed
	 *\brief Inequality check operator.
	 */
	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	inline bool operator!=(const Fi::CFixed<W, F, S, OF, R>& x, 
	                       const Fi::CFixed<W, F, S, OF, R>& y);

	//@}

	/** \name Arithmetic operators */
	//@{

	/**
	 *\relates Fi::CFixed
	 *\brief Addition operator.
	 */
	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fi::CFixed<W, F, S, OF, R> 
	operator+(const Fi::CFixed<W, F, S, OF, R>& x, 
	          const Fi::CFixed<W, F, S, OF, R>& y);

	/**
	 *\relates Fi::CFixed
	 *\brief Subtraction operator.
	 */
	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fi::CFixed<W, F, S, OF, R> 
	operator-(const Fi::CFixed<W, F, S, OF, R>& x, 
	          const Fi::CFixed<W, F, S, OF, R>& y);


	/**
	 *\relates Fi::CFixed
	 *\brief Negation operator.
     
	 *Negates the number.

	 *\return The additive inverse of the number.
	 */
	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fi::CFixed<W, F, S, OF, R> 
	operator-(const Fi::CFixed<W, F, S, OF, R>& a);

	/**
	 *\relates Fi::CFixed
	 *\brief Multiplication operator.
	 */
	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fi::CFixed<W, F, S, OF, R>
	operator*(const Fi::CFixed<W, F, S, OF, R>& x, 
	          const Fi::CFixed<W, F, S, OF, R>& y);

	/**
	 *\relates Fi::CFixed
	 *\brief Division operator.
	 */
	// template<std::size_t W, std::size_t F, Fi::Signedness S,
	//          template <typename> class OF,
	//          template <typename> class R>
	// const Fi::CFixed<W, F, S, OF, R>
	// operator/(const Fi::CFixed<W, F, S, OF, R>& x, 
	//           const Fi::CFixed<W, F, S, OF, R>& y);

	//@}	
}

namespace std {

	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	Fi::Fixed<W, F, S, OF, R> real(const Fi::CFixed<W, F, S, OF, R>& x);

	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	Fi::Fixed<W, F, S, OF, R> imag(const Fi::CFixed<W, F, S, OF, R>& x);
	
	// template<std::size_t W, std::size_t F, Fi::Signedness S,
	//          template <typename> class OF,
	//          template <typename> class R>
	// Fi::Fixed<W, F, S, OF, R> abs(const Fi::CFixed<W, F, S, OF, R>& x);

	// template<std::size_t W, std::size_t F, Fi::Signedness S,
	//          template <typename> class OF,
	//          template <typename> class R>
	// Fi::Fixed<W, F, S, OF, R> arg(const Fi::CFixed<W, F, S, OF, R>& x);

	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	Fi::Fixed<W, F, S, OF, R> norm(const Fi::CFixed<W, F, S, OF, R>& x);

	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	Fi::CFixed<W, F, S, OF, R> conj(const Fi::CFixed<W, F, S, OF, R>& x);	
	
}

#include "private/CFixed_priv.hpp"

#endif
