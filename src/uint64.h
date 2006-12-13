//  uint64.h
//  minimal double precision unsigned int arithmetics for numeric_facets support.
//  Written by Tsutomu Yoshida, Minokamo, Japan. 03/25/2000
#ifndef _UINT64_H
#define _UINT64_H

template <class _Tp>
class _compound_int : public _Tp {
public:
  typedef _compound_int<_Tp> _Self;

  // Constructors, destructor, assignment operator.
  _compound_int();                    // platform specific
  _compound_int(unsigned long);              // platform specific
  _compound_int(unsigned long hi, unsigned long lo);  // platform specific
  _compound_int(const _Tp& rhs) : _Tp(rhs) {}

  // Arithmetic op= operations involving two _compound_int.
  _Self& operator+= (const _Self&);            // platform specific
  _Self& operator-= (const _Self&);            // platform specific
  _Self& operator*= (const _Self&);            // platform specific
  _Self& operator/= (const _Self&);            // platform specific
  _Self& operator%= (const _Self&);            // platform specific
  _Self& operator&= (const _Self&);            // platform specific
  _Self& operator|= (const _Self&);            // platform specific
  _Self& operator^= (const _Self&);            // platform specific

  // Arithmetic op= operations involving built-in integer.
  _Self& operator<<= (unsigned int);          // platform specific
  _Self& operator>>= (unsigned int);          // platform specific

  _Self& operator=  (unsigned long rhs) { return *this =  _Self(rhs); }
  _Self& operator+= (unsigned long rhs) { return *this += _Self(rhs); }
  _Self& operator-= (unsigned long rhs) { return *this -= _Self(rhs); }
  _Self& operator*= (unsigned long rhs) { return *this *= _Self(rhs); }
  _Self& operator/= (unsigned long rhs) { return *this /= _Self(rhs); }
  _Self& operator%= (unsigned long rhs) { return *this %= _Self(rhs); }
  _Self& operator&= (unsigned long rhs) { return *this &= _Self(rhs); }
  _Self& operator|= (unsigned long rhs) { return *this |= _Self(rhs); }
  _Self& operator^= (unsigned long rhs) { return *this ^= _Self(rhs); }

  // Increment and decrement
  _Self& operator++() { return (*this) += 1; }
  _Self& operator--() { return (*this) -= 1; }
  _Self operator++(int) { _Self temp(*this); ++(*this); return temp; }
  _Self operator--(int) { _Self temp(*this); --(*this); return temp; }
};

// Comparison operators.
template <class _Tp> bool operator==(const _compound_int<_Tp>&, const _compound_int<_Tp>&);  // platform specific
template <class _Tp> bool operator<(const _compound_int<_Tp>&, const _compound_int<_Tp>&);  // platform specific

template <class _Tp> inline bool operator==(const _compound_int<_Tp>& lhs, unsigned long rhs) { return lhs == _compound_int<_Tp>(rhs); }
template <class _Tp> inline bool operator==(unsigned long lhs, const _compound_int<_Tp>& rhs) { return rhs == lhs; }

template <class _Tp> inline bool operator< (const _compound_int<_Tp>& lhs, unsigned long rhs) { return lhs < _compound_int<_Tp>(rhs); }
template <class _Tp> inline bool operator< (unsigned long lhs, const _compound_int<_Tp>& rhs) { return _compound_int<_Tp>(lhs) < rhs; }

template <class _Tp> inline bool operator!=(const _compound_int<_Tp>& lhs, unsigned long rhs) { return !(lhs == rhs); }
template <class _Tp> inline bool operator!=(unsigned long lhs, const _compound_int<_Tp>& rhs) { return !(lhs == rhs); }

template <class _Tp> inline bool operator> (const _compound_int<_Tp>& lhs, unsigned long rhs) { return rhs < lhs; }
template <class _Tp> inline bool operator> (unsigned long lhs, const _compound_int<_Tp>& rhs) { return rhs < lhs; }

template <class _Tp> inline bool operator<=(const _compound_int<_Tp>& lhs, unsigned long rhs) { return !(lhs > rhs); }
template <class _Tp> inline bool operator<=(unsigned long lhs, const _compound_int<_Tp>& rhs) { return !(lhs > rhs); }

template <class _Tp> inline bool operator>=(const _compound_int<_Tp>& lhs, unsigned long rhs) { return !(lhs < rhs); }
template <class _Tp> inline bool operator>=(unsigned long lhs, const _compound_int<_Tp>& rhs) { return !(lhs < rhs); }

// Unary non-member arithmetic operators.
template <class _Tp> unsigned long to_ulong(const _compound_int<_Tp>&);      // platform specific
template <class _Tp> _compound_int<_Tp> operator~(const _compound_int<_Tp>&);  // platform specific

template <class _Tp> inline _compound_int<_Tp> operator+(const _compound_int<_Tp>& val) {return val;}
template <class _Tp> inline _compound_int<_Tp> operator-(const _compound_int<_Tp>& val) {return 0 - val;}
template <class _Tp> inline bool operator!(const _compound_int<_Tp>& val) {return val==0;}

// Non-member arithmetic operations involving two _compound_int arguments
template <class _Tp>
inline _compound_int<_Tp> operator+(const _compound_int<_Tp>& lhs, const _compound_int<_Tp>& rhs)
{ _compound_int<_Tp> temp(lhs); return temp += rhs; }
template <class _Tp>
inline _compound_int<_Tp> operator-(const _compound_int<_Tp>& lhs, const _compound_int<_Tp>& rhs)
{ _compound_int<_Tp> temp(lhs); return temp -= rhs; }
template <class _Tp>
inline _compound_int<_Tp> operator*(const _compound_int<_Tp>& lhs, const _compound_int<_Tp>& rhs)
{ _compound_int<_Tp> temp(lhs); return temp *= rhs; }
template <class _Tp>
inline _compound_int<_Tp> operator/(const _compound_int<_Tp>& lhs, const _compound_int<_Tp>& rhs)
{ _compound_int<_Tp> temp(lhs); return temp /= rhs; }
template <class _Tp>
inline _compound_int<_Tp> operator%(const _compound_int<_Tp>& lhs, const _compound_int<_Tp>& rhs)
{ _compound_int<_Tp> temp(lhs); return temp %= rhs; }
template <class _Tp>
inline _compound_int<_Tp> operator&(const _compound_int<_Tp>& lhs, const _compound_int<_Tp>& rhs)
{ _compound_int<_Tp> temp(lhs); return temp &= rhs; }
template <class _Tp>
inline _compound_int<_Tp> operator|(const _compound_int<_Tp>& lhs, const _compound_int<_Tp>& rhs)
{ _compound_int<_Tp> temp(lhs); return temp |= rhs; }
template <class _Tp>
inline _compound_int<_Tp> operator^(const _compound_int<_Tp>& lhs, const _compound_int<_Tp>& rhs)
{ _compound_int<_Tp> temp(lhs); return temp ^= rhs; }

// Non-member arithmetic operations involving one built-in integer argument.
template <class _Tp>
inline _compound_int<_Tp> operator+(const _compound_int<_Tp>& lhs, unsigned long rhs) { return lhs + _compound_int<_Tp>(rhs); }
template <class _Tp>
inline _compound_int<_Tp> operator+(unsigned long lhs, const _compound_int<_Tp>& rhs) { return _compound_int<_Tp>(lhs) + rhs; }

template <class _Tp>
inline _compound_int<_Tp> operator-(const _compound_int<_Tp>& lhs, unsigned long rhs) { return lhs - _compound_int<_Tp>(rhs); }
template <class _Tp>
inline _compound_int<_Tp> operator-(unsigned long lhs, const _compound_int<_Tp>& rhs) { return _compound_int<_Tp>(lhs) - rhs; }

template <class _Tp>
inline _compound_int<_Tp> operator*(const _compound_int<_Tp>& lhs, unsigned long rhs) { return lhs * _compound_int<_Tp>(rhs); }
template <class _Tp>
inline _compound_int<_Tp> operator*(unsigned long lhs, const _compound_int<_Tp>& rhs) { return _compound_int<_Tp>(lhs) * rhs; }

template <class _Tp>
inline _compound_int<_Tp> operator/(const _compound_int<_Tp>& lhs, unsigned long rhs) { return lhs / _compound_int<_Tp>(rhs); }
template <class _Tp>
inline _compound_int<_Tp> operator/(unsigned long lhs, const _compound_int<_Tp>& rhs) { return _compound_int<_Tp>(lhs) / rhs; }

template <class _Tp>
inline _compound_int<_Tp> operator%(const _compound_int<_Tp>& lhs, unsigned long rhs) { return lhs % _compound_int<_Tp>(rhs); }
template <class _Tp>
inline _compound_int<_Tp> operator%(unsigned long lhs, const _compound_int<_Tp>& rhs) { return _compound_int<_Tp>(lhs) % rhs; }

template <class _Tp>
inline _compound_int<_Tp> operator&(const _compound_int<_Tp>& lhs, unsigned long rhs) { return lhs & _compound_int<_Tp>(rhs); }
template <class _Tp>
inline _compound_int<_Tp> operator&(unsigned long lhs, const _compound_int<_Tp>& rhs) { return _compound_int<_Tp>(lhs) & rhs; }

template <class _Tp>
inline _compound_int<_Tp> operator|(const _compound_int<_Tp>& lhs, unsigned long rhs) { return lhs | _compound_int<_Tp>(rhs); }
template <class _Tp>
inline _compound_int<_Tp> operator|(unsigned long lhs, const _compound_int<_Tp>& rhs) { return _compound_int<_Tp>(lhs) | rhs; }

template <class _Tp>
inline _compound_int<_Tp> operator^(const _compound_int<_Tp>& lhs, unsigned long rhs) { return lhs ^ _compound_int<_Tp>(rhs); }
template <class _Tp>
inline _compound_int<_Tp> operator^(unsigned long lhs, const _compound_int<_Tp>& rhs) { return _compound_int<_Tp>(lhs) ^ rhs; }

template <class _Tp>
inline _compound_int<_Tp> operator<<(const _compound_int<_Tp>& lhs, unsigned int rhs) { _compound_int<_Tp> temp(lhs); return temp <<= rhs; }
template <class _Tp>
inline _compound_int<_Tp> operator>>(const _compound_int<_Tp>& lhs, unsigned int rhs) { _compound_int<_Tp> temp(lhs); return temp >>= rhs; }

#endif // _UINT64_H
