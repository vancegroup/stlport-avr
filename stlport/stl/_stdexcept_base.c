/*
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1999
 * Boris Fomitchev
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

__Named_exception::__Named_exception(const string& __str) {
  size_t __size = strlen(__get_c_string(__str)) + 1;
  if (__size > _S_bufsize) {
    _M_name = __STATIC_CAST(char*, malloc(__size * sizeof(char)));
    if (_M_name == 0) {
      __size = _S_bufsize;
      _M_name = _M_static_name;
    }
  }
  else {
    _M_name = _M_static_name;
  }
#if !defined (_STLP_USE_SAFE_STRING_FUNCTIONS)
  strncpy(_M_name, _STLP_PRIV __get_c_string(__str), __size - 1);
  _M_name[__size - 1] = '\0';
#else
  strncpy_s(_M_name, __size, _STLP_PRIV __get_c_string(__str), __size - 1);
#endif
}

__Named_exception::~__Named_exception() _STLP_NOTHROW_INHERENTLY {
  if (_M_name != _M_static_name)
    free(_M_name);
}

const char* __Named_exception::what() const _STLP_NOTHROW_INHERENTLY
{ return _M_name; }
