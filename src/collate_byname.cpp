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

#include "stl/_collate.h"
#include "c_locale.h"

__STL_BEGIN_NAMESPACE

// collate_byname<char>
_Locale_collate* __acquire_collate(const char* name);
void __release_collate(_Locale_collate* cat);

collate_byname<char>::collate_byname(const char* name, size_t refs)
  : collate<char>(refs),
    _M_collate(__acquire_collate(name))
{
  if (!_M_collate)
    locale::_M_throw_runtime_error();
}

collate_byname<char>::~collate_byname()
{
  __release_collate(_M_collate);
}

int collate_byname<char>::do_compare(const char* __low1,
                                     const char* __high1,
                                     const char* __low2,
                                     const char* __high2) const {
  return _Locale_strcmp(_M_collate,
                        __low1, __high1 - __low1, 
                        __low2, __high2 - __low2);
}

collate_byname<char>::string_type
collate_byname<char>::do_transform(const char* low, const char* high) const {
  size_t n = _Locale_strxfrm(_M_collate,
                             NULL, 0,
                             low, high - low);

  __vector__<char, allocator<char> > buf(n);
  _Locale_strxfrm(_M_collate, &buf.front(), n,
                              low, high - low);

   char& __c1 = *(buf.begin());
   char& __c2 = (n == (size_t)-1) ? *(buf.begin() + (high-low-1)) : *(buf.begin() + n);
   //   char& __c2 = *(buf.begin() + n);
   return string_type( &__c1, &__c2 );
}


# ifndef __STL_NO_WCHAR_T

// collate_byname<wchar_t>

collate_byname<wchar_t>::collate_byname(const char* name, size_t refs)
  : collate<wchar_t>(refs),
    _M_collate(__acquire_collate(name))
{
  if (!_M_collate)
    locale::_M_throw_runtime_error();
}

collate_byname<wchar_t>::~collate_byname() 
{
  __release_collate(_M_collate);
}

int collate_byname<wchar_t>::do_compare(const wchar_t* low1,
                                        const wchar_t* high1,
                                        const wchar_t* low2,
                                        const wchar_t* high2) const
{
  return _Locale_strwcmp(_M_collate,
                         low1, high1 - low1, 
                         low2, high2 - low2);
}

collate_byname<wchar_t>::string_type
collate_byname<wchar_t>
  ::do_transform(const wchar_t* low, const wchar_t* high) const
{
  size_t n = _Locale_strwxfrm(_M_collate,
                              NULL, 0,
                              low, high - low);

  __vector__<wchar_t, allocator<wchar_t> > buf(high - low);
  _Locale_strwxfrm(_M_collate, &buf.front(), n,
                               low, high - low);
  wchar_t& __c1 = *(buf.begin());
  wchar_t& __c2 = (n == (size_t)-1) ? *(buf.begin() + (high-low-1)) : *(buf.begin() + n);
  // wchar_t& __c2 = *(buf.begin() + n);
  return string_type( &__c1, &__c2 );
}

# endif /*  __STL_NO_WCHAR_T */

__STL_END_NAMESPACE


// Local Variables:
// mode:C++
// End:

