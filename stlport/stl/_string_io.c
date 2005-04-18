#ifndef _STLP_STRING_IO_C
#define _STLP_STRING_IO_C

#ifndef _STLP_STRING_IO_H
#  include <stl/_string_io.h>
#endif

#ifndef _STLP_INTERNAL_CTYPE_H
#  include <stl/_ctype.h>
#endif

_STLP_BEGIN_NAMESPACE

template <class _CharT, class _Traits>
bool _STLP_CALL
__stlp_string_fill(basic_ostream<_CharT, _Traits>& __os,
                   basic_streambuf<_CharT, _Traits>* __buf,
                   streamsize __n) {
  _CharT __f = __os.fill();
  for (streamsize __i = 0; __i < __n; ++__i) {
    if (_Traits::eq_int_type(__buf->sputc(__f), _Traits::eof()))
      return false;
  }
  return true;
}


template <class _CharT, class _Traits, class _Alloc>
basic_ostream<_CharT, _Traits>& _STLP_CALL
operator << (basic_ostream<_CharT, _Traits>& __os, 
             const basic_string<_CharT,_Traits,_Alloc>& __s) {
  typedef basic_ostream<_CharT, _Traits> __ostream;
  typedef typename basic_string<_CharT, _Traits, _Alloc>::size_type size_type;

  /* The hypothesis of this implementation is that size_type is unsigned
   * and streamsize is at least equal to size_type.
   * It is important in the way we compare it to streamsize.
   */
  typedef char __static_assert_unsigned_size_type[__STATIC_CAST(size_type, -1) > 0];
  typedef char __static_assert_gt_or_eq_size[sizeof(streamsize) >= sizeof(size_type)];

  typename __ostream::sentry __sentry(__os);
  bool __ok = false;

  if (__sentry) {
    __ok = true;
    size_type __n = __s.size();
    streamsize __pad_len = 0;
    const bool __left = (__os.flags() & __ostream::left) != 0;
    const streamsize __w = __os.width(0);
    basic_streambuf<_CharT, _Traits>* __buf = __os.rdbuf();

    /* If __n cast in streamsize is negative the string is already longer
     * than the possible output stream width requested so no need to pad.
     */
    if ((__STATIC_CAST(streamsize, __n) >= 0) && (__w > __STATIC_CAST(streamsize, __n))) {
      __pad_len = __w - __n;
    }
    
    if (!__left)
      __ok = __stlp_string_fill(__os, __buf, __pad_len);    

    __ok = __ok && (__buf->sputn(__s.data(), streamsize(__n)) == streamsize(__n));

    if (__left)
      __ok = __ok && __stlp_string_fill(__os, __buf, __pad_len);
  }

  if (!__ok)
    __os.setstate(__ostream::failbit);

  return __os;
}

template <class _CharT, class _Traits, class _Alloc>
basic_istream<_CharT, _Traits>& _STLP_CALL 
operator >> (basic_istream<_CharT, _Traits>& __is,
             basic_string<_CharT,_Traits, _Alloc>& __s) {
  typedef basic_istream<_CharT, _Traits> __istream;
  typedef typename basic_string<_CharT, _Traits, _Alloc>::size_type size_type;

  /* The hypothesis of this implementation is that size_type is unsigned
   * and streamsize is at least equal to size_type.
   * It is important in the way we compare it to streamsize.
   */
  typedef char __static_assert_unsigned_size_type[__STATIC_CAST(size_type, -1) > 0];
  typedef char __static_assert_gt_or_eq_size[sizeof(streamsize) >= sizeof(size_type)];

  typename __istream::sentry __sentry(__is);

  if (__sentry) {
    basic_streambuf<_CharT, _Traits>* __buf = __is.rdbuf();
    typedef ctype<_CharT> _C_type;

    const locale& __loc = __is.getloc();
    const _C_type& _Ctype = use_facet<_C_type>(__loc);
    __s.clear();
    streamsize __width = __is.width(0);
    size_type __n;
    if (__width <= 0)
      __n = __s.max_size();
    /* If string max_size() cast to streamsize is negative it means that
     * the required extraction size will never exceed the possible string
     * representation.
     */
    else if ((__STATIC_CAST(streamsize, __s.max_size()) >= 0) && 
             (__width > __STATIC_CAST(streamsize, __s.max_size())))
      __n = 0;
    else {
      __n = __STATIC_CAST(size_type, __width);
      __s.reserve(__n);
    }

    while (__n-- > 0) {
      typename _Traits::int_type __c1 = __buf->sbumpc();
      if (_Traits::eq_int_type(__c1, _Traits::eof())) {
        __is.setstate(__istream::eofbit);
        break;
      }
      else {
        _CharT __c = _Traits::to_char_type(__c1);

        if (_Ctype.is(_C_type::space, __c)) {
          if (_Traits::eq_int_type(__buf->sputbackc(__c), _Traits::eof()))
            __is.setstate(__istream::failbit);
          break;
        }
        else
          __s.push_back(__c);
      }
    }
    
    // If we have read no characters, then set failbit.
    if (__s.empty())
      __is.setstate(__istream::failbit);
  }
  else
    __is.setstate(__istream::failbit);

  return __is;
}

template <class _CharT, class _Traits, class _Alloc>    
basic_istream<_CharT, _Traits>& _STLP_CALL 
getline(basic_istream<_CharT, _Traits>& __is,
        basic_string<_CharT,_Traits,_Alloc>& __s,
        _CharT __delim) {
  typedef basic_istream<_CharT, _Traits> __istream;
  typedef typename basic_string<_CharT, _Traits, _Alloc>::size_type size_type;
  size_type __nread = 0;
  typename basic_istream<_CharT, _Traits>::sentry __sentry(__is, true);
  if (__sentry) {
    basic_streambuf<_CharT, _Traits>* __buf = __is.rdbuf();
    __s.clear();

    while (__nread < __s.max_size()) {
      int __c1 = __buf->sbumpc();
      if (_Traits::eq_int_type(__c1, _Traits::eof())) {
        __is.setstate(__istream::eofbit);
        break;
      }
      else {
        ++__nread;
        _CharT __c = _Traits::to_char_type(__c1);
        if (!_Traits::eq(__c, __delim)) 
          __s.push_back(__c);
        else
          break;              // Character is extracted but not appended.
      }
    }
  }
  if (__nread == 0 || __nread >= __s.max_size())
    __is.setstate(__istream::failbit);

  return __is;
}

_STLP_END_NAMESPACE

#endif

// Local Variables:
// mode:C++
// End:
