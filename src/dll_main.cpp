 /*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1997
 * Moscow Center for SPARC Technology
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
# define __STL_EXPOSE_GLOBALS_IMPLEMENTATION

# include "stlport_prefix.h"

#include <utility>

#include <memory>
#include <vector>
#include <set>
#include <list>
#include <slist>
#include <stl/_hashtable.h>
#include <limits>
#include <string>
#include <stdexcept>

__STL_BEGIN_NAMESPACE

void __STL_DECLSPEC __STL_CALL __stl_throw_range_error(const char* __msg) { 
  __STL_THROW_MSG(range_error, __msg); 
}

void __STL_DECLSPEC __STL_CALL __stl_throw_out_of_range(const char* __msg) { 
  __STL_THROW_MSG(out_of_range, __msg); 
}

void __STL_DECLSPEC __STL_CALL __stl_throw_length_error(const char* __msg) { 
  __STL_THROW_MSG(length_error, __msg); 
}

void __STL_DECLSPEC __STL_CALL __stl_throw_invalid_argument(const char* __msg) { 
  __STL_THROW_MSG(invalid_argument, __msg); 
}

void __STL_DECLSPEC __STL_CALL __stl_throw_overflow_error(const char* __msg) { 
  __STL_THROW_MSG(overflow_error, __msg); 
}

__STL_DECLSPEC const char*  __STL_CALL
__get_c_string(const string& __str) { 
  return __str.c_str(); 
}


# if defined (__STL_NO_EXCEPTION_HEADER)
const char* exception::what() const __STL_NOTHROW {return "class exception";}
const char* bad_exception::what() const __STL_NOTHROW {return "class bad_exception";}
# endif

# ifdef __STL_OWN_STDEXCEPT
__Named_exception::__Named_exception(const string& __str) {
  strncpy(_M_name, __get_c_string(__str), _S_bufsize);
  _M_name[_S_bufsize - 1] = '\0';
}
const char* __Named_exception::what() const __STL_NOTHROW_INHERENTLY { return _M_name; }

// boris : those are needed to force typeinfo nodes to be created in here only
logic_error::~logic_error() __STL_NOTHROW_INHERENTLY {}
runtime_error::~runtime_error() __STL_NOTHROW_INHERENTLY {}
domain_error::~domain_error() __STL_NOTHROW_INHERENTLY {}
invalid_argument::~invalid_argument() __STL_NOTHROW_INHERENTLY {}
length_error::~length_error() __STL_NOTHROW_INHERENTLY {}
out_of_range::~out_of_range() __STL_NOTHROW_INHERENTLY {}
range_error::~range_error() __STL_NOTHROW_INHERENTLY {}
overflow_error::~overflow_error() __STL_NOTHROW_INHERENTLY {}
underflow_error::~underflow_error() __STL_NOTHROW_INHERENTLY {}

# endif

# ifndef __STL_NO_FORCE_INSTANTIATE

# ifdef __STL_DEBUG
template struct __STL_CLASS_DECLSPEC __stl_debug_engine<bool>;
# endif

template class __STL_CLASS_DECLSPEC __node_alloc<false,0>;
template class __STL_CLASS_DECLSPEC __node_alloc<true,0>;
template class __STL_CLASS_DECLSPEC __debug_alloc< __node_alloc<true,0> >;
template class __STL_CLASS_DECLSPEC __debug_alloc< __node_alloc<false,0> >;
template class __STL_CLASS_DECLSPEC __debug_alloc<__new_alloc>;

template class allocator<void*>;
template class _STL_alloc_proxy<void**, void*, allocator<void*> >;
template class _Vector_base<void*,allocator<void*> >;
# if defined (__STL_DEBUG)
template class __WORKAROUND_DBG_RENAME(vector) <void*,allocator<void*> >;
# endif
template class __vector__<void*,allocator<void*> >;

template class _Rb_global<bool>;
template class _List_global<bool>;
template class _Sl_global<bool>;
template class _Stl_prime<bool>;
template class _LimG<bool>;

template class __STL_CLASS_DECLSPEC allocator<char>;
template class __STL_CLASS_DECLSPEC _STL_alloc_proxy<char *,char, allocator<char> >;
template class __STL_CLASS_DECLSPEC _String_base<char, allocator<char> >;

# ifdef __STL_DEBUG
template class __STL_CLASS_DECLSPEC _Nondebug_string<char, char_traits<char>, allocator<char> >;
# endif

template class basic_string<char, char_traits<char>, allocator<char> >;
# endif

__STL_END_NAMESPACE


# if defined (_WIN32) && defined (__STL_USE_DECLSPEC)
// stlportmt.cpp : Defines the entry point for the DLL application.
//
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}
# endif
