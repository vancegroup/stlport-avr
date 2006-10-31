#ifndef STLP_DIGITS_H
#define STLP_DIGITS_H

#include <string>
#include <numeric>

template <int N>
struct _Digits
{ enum { dig = _Digits<N / 10>::dig + 1 }; };

#if defined (STLPORT)
_STLP_TEMPLATE_NULL
#else
template <>
#endif
struct _Digits<0>
{ enum { dig = 0 }; };

inline void complete_digits(std::string &digits)
{
#if defined (STLPORT) && !defined (_STLP_NO_LONG_DOUBLE)
  typedef long double longest_float_type;
#else
  typedef double longest_float_type;
#endif
  size_t nbDigits = (size_t)_Digits<std::numeric_limits<longest_float_type>::max_exponent10>::dig;
  while (digits.size() != nbDigits)
  {
    digits.insert(digits.begin(), '0');
  }
}

#endif
