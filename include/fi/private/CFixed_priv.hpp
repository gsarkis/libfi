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

#ifndef PRIVATE_FI_CFIXED_PRIV_HPP
#define PRIVATE_FI_CFIXED_PRIV_HPP

#include <cmath>

namespace Fi {

	// ---------- Member functions ----------
	
	template<std::size_t W, std::size_t F, Fi::Signedness S, 
	         template <typename> class OF,
	         template <typename> class R>
	CFixed<W, F, S, OF, R>::CFixed()
		: _real(Fixed<W,F,S,OF,R>()),
		  _imag(Fixed<W,F,S,OF,R>())
	{}

	template<std::size_t W, std::size_t F, Fi::Signedness S, 
	         template <typename> class OF,
	         template <typename> class R>
	CFixed<W, F, S, OF, R>::CFixed(const CFixed<W,F,S,OF,R>& a)
		: _real(a._real),
		  _imag(a._imag)
	{}

	template<std::size_t W, std::size_t F, Fi::Signedness S, 
	         template <typename> class OF,
	         template <typename> class R>
	CFixed<W, F, S, OF, R>::CFixed(double realf, double imagf)
	{
		_real= Fixed<W,F,S,OF,R>(realf);
		_imag= Fixed<W,F,S,OF,R>(imagf);
	}

	template<std::size_t W, std::size_t F, Fi::Signedness S, 
	         template <typename> class OF,
	         template <typename> class R>
	CFixed<W, F, S, OF, R>::CFixed(const Fixed<W,F,S,OF,R>& real,
	                               const Fixed<W,F,S,OF,R>& imag)
		: _real(real),
		  _imag(imag)
	{}

	template<std::size_t W, std::size_t F, Fi::Signedness S, 
	         template <typename> class OF,
	         template <typename> class R>
	CFixed<W, F, S, OF, R>& CFixed<W, F, S, OF, R>::
	operator=(const CFixed<W, F, S, OF, R>& that) {
		this->_real= that._real;
		this->_imag= that._imag;
		return *this;
	}

	template<std::size_t W, std::size_t F, Fi::Signedness S, 
	         template <typename> class OF,
	         template <typename> class R>
	CFixed<W, F, S, OF, R>& CFixed<W, F, S, OF, R>::
	operator+=(const CFixed<W, F, S, OF, R>& that) {
		_real+= that._real;
		_imag+= that._imag;
		return *this;
	}

	template<std::size_t W, std::size_t F, Fi::Signedness S, 
	         template <typename> class OF,
	         template <typename> class R>
	CFixed<W, F, S, OF, R>& CFixed<W, F, S, OF, R>::
	operator-=(const CFixed<W, F, S, OF, R>& that) {
		_real-= that._real;
		_imag-= that._imag;
		return *this;
	}

	template<std::size_t W, std::size_t F, Fi::Signedness S, 
	         template <typename> class OF,
	         template <typename> class R>
	CFixed<W,F,S,OF,R>& CFixed<W, F, S, OF, R>::
	operator*=(const CFixed<W,F,S,OF,R>& that) {
		Fixed<W,F,S,OF,R> newReal= _real * that.real() - _imag * that.imag();
		Fixed<W,F,S,OF,R> newImag= _real * that.imag() + _imag * that.real();
		_real= newReal;
		_imag= newImag;
		return *this;
	}
		
	
	//TODO: multiplication with operands having different widths
	// template<std::size_t W, std::size_t F, Fi::Signedness S, 
	//          template <typename> class OF,
	//          template <typename> class R>
	// template<std::size_t W2, std::size_t F2, Fi::Signedness S2, 
	//          template <typename> class OF2,
	//          template <typename> class R2>
	// CFixed<W,F,S,OF,R>& CFixed<W, F, S, OF, R>::
	// operator*=(const CFixed<W2, F2, S2, OF2, R2>& that) {
	// 	// perform the operation using the maximum width and fractional
	// 	// width of both operands
	// }

	// template<std::size_t W, std::size_t F, Fi::Signedness S, 
	//          template <typename> class OF=Fi::Throw,
	//          template <typename> class R=Fi::Fix>
	// CFixed<W, F, S, OF, R>::operator/=(const CFixed<W, F, S, OF, R>& that) {

	// }

	template<std::size_t W, std::size_t F, Fi::Signedness S, 
	         template <typename> class OF,
	         template <typename> class R>
	std::complex<double> CFixed<W, F, S, OF, R>::toDouble() const {
		std::complex<double> cdbl(_real.toDouble(), _imag.toDouble());
		return cdbl;
	}

	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	Fixed<W,F,S,OF,R> CFixed<W, F, S, OF, R>::real() const {
		return _real;
	}

	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	Fixed<W,F,S,OF,R> CFixed<W, F, S, OF, R>::imag() const {
		return _imag;
	}		


	// ---------- Non-member function ----------

	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	inline bool operator==(const Fi::CFixed<W, F, S, OF, R>& x, 
	                       const Fi::CFixed<W, F, S, OF, R>& y)
	{
		return x.operator==(y);
	}

	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	inline bool operator!=(const Fi::CFixed<W, F, S, OF, R>& x, 
	                       const Fi::CFixed<W, F, S, OF, R>& y)
	{
		return !(x==y);
	}

	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fi::CFixed<W, F, S, OF, R> 
	operator+(const Fi::CFixed<W, F, S, OF, R>& x, 
	          const Fi::CFixed<W, F, S, OF, R>& y)
	{
		CFixed<W,F,S,OF,R> ret(x);
		ret+= y;
		return ret;
	}

	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fi::CFixed<W, F, S, OF, R> 
	operator-(const Fi::CFixed<W, F, S, OF, R>& x, 
	          const Fi::CFixed<W, F, S, OF, R>& y)
	{
		CFixed<W,F,S,OF,R> ret(x);
		ret-= y;
		return ret;
	}

	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fi::CFixed<W, F, S, OF, R> 
	operator-(const Fi::CFixed<W, F, S, OF, R>& a)	{
		CFixed<W,F,S,OF,R> ret;
		ret._real-= a._real;
		ret._imag-= a._imag;
		return ret;
	}

	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	const Fi::CFixed<W, F, S, OF, R>
	operator*(const Fi::CFixed<W, F, S, OF, R>& x, 
	          const Fi::CFixed<W, F, S, OF, R>& y) {
		CFixed<W,F,S,OF,R> ret(x);
		ret*= y;
		return ret;
	}

	// template<std::size_t W, std::size_t F, Fi::Signedness S,
	//          template <typename> class OF,
	//          template <typename> class R>
	// const Fi::CFixed<W, F, S, OF, R>
	// operator/(const Fi::CFixed<W, F, S, OF, R>& x, 
	//           const Fi::CFixed<W, F, S, OF, R>& y) {
	// 	CFixed<W,F,S,OF,R> ret(x);
	// 	ret/= y;
	// 	return ret;
	// }
	
} // end namespace Fi

	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	Fi::Fixed<W, F, S, OF, R> std::real(const Fi::CFixed<W, F, S, OF, R>& x)
	{
		return x.real();
	}

	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	Fi::Fixed<W, F, S, OF, R> std::imag(const Fi::CFixed<W, F, S, OF, R>& x)
	{
		return x.imag();
	}
	
	// template<std::size_t W, std::size_t F, Fi::Signedness S,
	//          template <typename> class OF,
	//          template <typename> class R>
	// Fi::Fixed<W, F, S, OF, R> std::abs(const Fi::CFixed<W, F, S, OF, R>& x)
	// {
	// 	double result= std::abs(x.toDouble());
	// 	return Fi::Fixed<W,F,S,OF,R>(result);
	// }

	// template<std::size_t W, std::size_t F, Fi::Signedness S,
	//          template <typename> class OF,
	//          template <typename> class R>
	// Fi::Fixed<W, F, S, OF, R> std::arg(const Fi::CFixed<W, F, S, OF, R>& x)
	// {
	// 	double result= atan2(x.imag().toDouble(), x.real().toDouble());
	// 	return Fi::Fixed<W,F,S,OF,R>(result);
	// }

	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	Fi::Fixed<W, F, S, OF, R> std::norm(const Fi::CFixed<W, F, S, OF, R>& x)
	{
		return x.real() * x.real() + x.imag() * x.imag();
	}

	template<std::size_t W, std::size_t F, Fi::Signedness S,
	         template <typename> class OF,
	         template <typename> class R>
	Fi::CFixed<W, F, S, OF, R> std::conj(const Fi::CFixed<W, F, S, OF, R>& x)
	{
		return Fi::CFixed<W,F,S,OF,R>(x.real(), -x.imag());
	}

#endif
