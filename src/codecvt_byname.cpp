/*
 * Copyright (c) 1999
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
# include "stlport_prefix.h"

# ifndef __STL_NO_MBSTATE_T

#include <stl/_codecvt.h>
#include <stl/_algobase.h>
#include "c_locale.h"

__STL_BEGIN_NAMESPACE


//----------------------------------------------------------------------
// codecvt_byname<char>

codecvt_byname<char, char, mbstate_t>
  ::codecvt_byname(const char* /* name */, size_t refs)
    : codecvt<char, char, mbstate_t>(refs)
{}

codecvt_byname<char, char, mbstate_t>::~codecvt_byname() {}


# ifndef __STL_NO_WCHAR_T

//----------------------------------------------------------------------
// codecvt_byname<wchar_t>

_Locale_ctype* __acquire_ctype(const char* name);
void __release_ctype(_Locale_ctype* cat);

codecvt_byname<wchar_t, char, mbstate_t>
  ::codecvt_byname(const char* name, size_t refs)
    : codecvt<wchar_t, char, mbstate_t>(refs),
      _M_ctype(__acquire_ctype(name))
{
  if (!_M_ctype)
    locale::_M_throw_runtime_error();
}

codecvt_byname<wchar_t, char, mbstate_t>::~codecvt_byname()
{
  __release_ctype(_M_ctype);
}

codecvt<wchar_t, char, mbstate_t>::result
codecvt_byname<wchar_t, char, mbstate_t>
  ::do_out(state_type&     state,
           const wchar_t*  from,
           const wchar_t*  from_end,
           const wchar_t*& from_next,
           char*           to,
           char*           to_limit,
           char*&          to_next) const
{
  while (from != from_end) {
    size_t chars_stored = _Locale_wctomb(_M_ctype,
                                         to, to_limit - to, *from,
                                         &state);
    if (chars_stored == (size_t) -1) {
      from_next = from;
      to_next   = to;
      return error;
    }

    else if (chars_stored == (size_t) -2) {
      from_next = from;
      to_next   = to;
      return partial;
    }

    ++from;
    to += chars_stored;
  }

  from_next = from;
  to_next   = to;
  return ok;
}

codecvt<wchar_t, char, mbstate_t>::result
codecvt_byname<wchar_t, char, mbstate_t>
  ::do_in(state_type&         state,
          const extern_type*  from,
          const extern_type*  from_end,
          const extern_type*& from_next,
          intern_type*        to,
          intern_type*        ,
          intern_type*&       to_next) const
{
  while (from != from_end) {
    size_t chars_read = _Locale_mbtowc(_M_ctype,
                                       to, from, from_end - from,
                                       &state);
    if (chars_read == (size_t) -1) {
      from_next = from;
      to_next   = to;
      return error;
    }

    if (chars_read == (size_t) -1) {
      from_next = from;
      to_next   = to;
      return partial;
    }

    from += chars_read;
    to++;
  }

  from_next = from;
  to_next   = to;
  return ok;
}

codecvt<wchar_t, char, mbstate_t>::result
codecvt_byname<wchar_t, char, mbstate_t>
  ::do_unshift(state_type&   state,
               extern_type*  to,
               extern_type*  to_limit,
               extern_type*& to_next) const
{
  to_next = to;
  size_t result = _Locale_unshift(_M_ctype, &state,
                                  to, to_limit - to, &to_next);
  if (result == (size_t) -1)
    return error;
  else if (result == (size_t) -2)
    return partial;
  else
#ifdef __ISCPP__
    return /*to_next == to ? noconv :*/ ok;
#else
    return to_next == to ? noconv : ok;
#endif
}

int
codecvt_byname<wchar_t, char, mbstate_t>::do_encoding() const __STL_NOTHROW
{
  if (_Locale_is_stateless(_M_ctype)) {
    int max_width = _Locale_mb_cur_max(_M_ctype);
    int min_width = _Locale_mb_cur_min(_M_ctype);
    return min_width == max_width ? min_width : 0;
  }
  else
    return -1;
}


bool codecvt_byname<wchar_t, char, mbstate_t>
  ::do_always_noconv() const __STL_NOTHROW
{
  return false;
}

int 
codecvt_byname<wchar_t, char, mbstate_t>::do_length(
                                                    const state_type&,
                                                    const  extern_type* from, const  extern_type* end,
                                                    size_t mx) const 
{
  return (int)__STL_MIN ((size_t) (end - from), mx);
}

int
codecvt_byname<wchar_t, char, mbstate_t>::do_max_length() const __STL_NOTHROW
{
  return _Locale_mb_cur_max(_M_ctype);
}
# endif /* WCHAR_T */

__STL_END_NAMESPACE

# endif /* __STL_NO_MBSTATE_T */

// Local Variables:
// mode:C++
// End:

