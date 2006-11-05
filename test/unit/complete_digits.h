#ifndef STLP_DIGITS_H
#define STLP_DIGITS_H

#include <string>

inline void complete_digits(std::string &digits)
{
  while (digits.size() < 2)
  {
    digits.insert(digits.begin(), '0');
  }
}

#endif
