/*
 * Copyright (c) 2003
 * Francois Dumont
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted 
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

#ifndef _STLP_STRING_SUM_H
#define _STLP_STRING_SUM_H

_STLP_BEGIN_NAMESPACE

/*char wrapper to simulate basic_string*/
template <class _CharT>
struct __char_wrapper {
  typedef _CharT char_type;
  typedef const char_type& const_reference;

  __char_wrapper(char_type __val) : 
    _Val(__val) {
  }

  char_type getValue() const {
    return _Val;
  }

  size_t size() const {
    return 1;
  }

  const_reference operator[] (size_t __n) const {
    //To avoid a check on __n we use this strange implementation
    return *((&_Val)[__n]);
  }

private:
  char_type _Val;
};

/*C string wrapper to simulate basic_string*/
template <class _CharT>
struct __cstr_wrapper {
  typedef _CharT char_type;
  typedef const char_type& const_reference;

  __cstr_wrapper(const char_type *__cstr, size_t __size) :
    _CStr(__cstr), _Size(__size) {
  }

  const char_type* c_str() const {
    return _CStr;
  }

  size_t size() const {
    return _Size;
  }

  const_reference operator[] (size_t __n) const {
    return _CStr[__n];
  }

private:
  const char_type *_CStr;
  size_t _Size;
};

/*basic_string wrapper to ensure that we only store a reference to the original string and not copy it*/
template <class _CharT, class _Traits, class _Alloc>
struct __bstr_wrapper {
  typedef _CharT char_type;
  typedef const char_type& const_reference;
  typedef basic_string<_CharT, _Traits, _Alloc> _TString;

  __bstr_wrapper (_TString const& __s) : 
    _BStr(__s) {
  }

  size_t size() const {
    return _BStr.size();
  }

  const_reference operator[] (size_t __n) const {
    return _BStr[__n];
  }

  _TString const& b_str() const {
    return _BStr;
  }

private:
  _TString const& _BStr;
};

template <class _CharT, class _Traits, class _Alloc, class _Left, class _Right>
class __bstr_sum {
public:
  typedef _CharT char_type;
  typedef _Traits traits_type;
  typedef _Alloc allocator_type;
  typedef const char_type& const_reference;

  __bstr_sum (_Left const& lhs, _Right const& rhs) :
    _lhs(lhs), _rhs(rhs) {
  }

  size_t size() const {
    return _lhs.size() + _rhs.size();
  }

  const_reference operator[](size_t __n) const {
    return (__n < _lhs.size())?_lhs[__n]:_rhs[__n - _lhs.size()];
  }

  operator basic_string<char_type, traits_type, allocator_type>() const {
    return basic_string<char_type, traits_type, allocator_type>(*this);
  }

  _Left const& getLhs() const {
    return _lhs;
  }
  _Right const& getRhs() const {
    return _rhs;
  }
private:
  _Left  _lhs;
  _Right _rhs;
};

template <class _CharT, class _Traits, class _Alloc, class _Lh1, class _Rh1, class _Lh2, class _Rh2>
inline __bstr_sum<_CharT, _Traits, _Alloc, __bstr_sum<_CharT, _Traits, _Alloc, _Lh1, _Rh1>, 
                                           __bstr_sum<_CharT, _Traits, _Alloc, _Lh2, _Rh2> > _STLP_CALL 
operator + (const __bstr_sum<_CharT, _Traits, _Alloc, _Lh1, _Rh1> &__lhs,
            const __bstr_sum<_CharT, _Traits, _Alloc, _Lh2, _Rh2> &__rhs) {
  return __bstr_sum<_CharT, _Traits, _Alloc, __bstr_sum<_CharT, _Traits, _Alloc, _Lh1, _Rh1>, 
                                             __bstr_sum<_CharT, _Traits, _Alloc, _Lh2, _Rh2> >(__lhs, __rhs);
}

_STLP_END_NAMESPACE

#endif /*_STLP_STRING_SUM_H*/

