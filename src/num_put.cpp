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

# include "num_put.h"

__STL_BEGIN_NAMESPACE

//----------------------------------------------------------------------
// num_put

extern const char __hex_char_table_lo[];
extern const char __hex_char_table_hi[];

const char __hex_char_table_lo[18] = "0123456789abcdefx"; 
const char __hex_char_table_hi[18] = "0123456789ABCDEFX";

char* __STL_CALL
__write_integer(char* buf, ios_base::fmtflags flags, long x)
{
  char tmp[64];
  char* bufend = tmp+64;
  char* beg = __write_integer_backward(bufend, flags, x);
  return copy(beg, bufend, buf);
}

///-------------------------------------

ptrdiff_t __STL_CALL
__insert_grouping(char * first, char * last, const string& grouping,
		  char separator, char Plus, char Minus, int basechars)
{
  return __insert_grouping_aux(first, last, grouping, 
			       separator, Plus, Minus, basechars);
}

# ifndef __STL_NO_WCHAR_T

ptrdiff_t __STL_CALL
__insert_grouping(wchar_t* first, wchar_t* last, const string& grouping,
                  wchar_t separator, wchar_t Plus, wchar_t Minus,
		  int basechars)
{
  return __insert_grouping_aux(first, last, grouping, separator, 
			       Plus, Minus, basechars);
}

# endif


//----------------------------------------------------------------------
// Force instantiation of num_put<>
#if !defined(__STL_NO_FORCE_INSTANTIATE)
template class __STL_CLASS_DECLSPEC ostreambuf_iterator<char, char_traits<char> >;
// template class num_put<char, char*>;
template class num_put<char, ostreambuf_iterator<char, char_traits<char> > >;
# ifndef __STL_NO_WCHAR_T
template class ostreambuf_iterator<wchar_t, char_traits<wchar_t> >;
template class num_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >;
// template class num_put<wchar_t, wchar_t*>;
# endif /* INSTANTIATE_WIDE_STREAMS */
#endif

__STL_END_NAMESPACE

// Local Variables:
// mode:C++
// End:
