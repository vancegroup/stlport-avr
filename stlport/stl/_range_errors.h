/*
 * Copyright (c) 1999
 * Silicon Graphics
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 */

#ifndef __STL_RANGE_ERRORS_H
#define __STL_RANGE_ERRORS_H

// A few places in the STL throw range errors, using standard exception
// classes defined in <stdexcept>.  This header file provides functions
// to throw those exception objects.

// __STL_DONT_THROW_RANGE_ERRORS is a hook so that users can disable
// this exception throwing.
#if defined(__STL_CAN_THROW_RANGE_ERRORS) && defined(__STL_USE_EXCEPTIONS) && !defined(__STL_DONT_THROW_RANGE_ERRORS)
# define __STL_THROW_RANGE_ERRORS
#endif

#if defined(__STL_THROW_RANGE_ERRORS)
# ifndef __SGI_STDEXCEPT
#  include <stdexcept>
# endif
# ifndef __SGI_STL_STRING
#  include <string>
# endif
# define __STL_THROW_MSG(ex,msg)  throw ex(string(msg))
#else
# if defined (__STL_WINCE)
#  define __STL_THROW_MSG(ex,msg)  TerminateProcess(GetCurrentProcess(), 0)
# else
#  include <cstdlib>
#  include <cstdio>
#  define __STL_THROW_MSG(ex,msg)  puts(msg),abort()
# endif
#endif

// For the SGI 7.3 compiler, declare these functions here and define them
// elsewhere.
#if defined ( __SGI_STL_OWN_IOSTREAMS  ) && ! defined (__STL_EXTERN_RANGE_ERRORS) 
#  define __STL_EXTERN_RANGE_ERRORS
# endif
__STL_BEGIN_NAMESPACE

#if defined (__STL_EXTERN_RANGE_ERRORS)
void  __STL_DECLSPEC __STL_CALL __stl_throw_range_error(const char* __msg);
void  __STL_DECLSPEC __STL_CALL __stl_throw_out_of_range(const char* __msg);
void  __STL_DECLSPEC __STL_CALL __stl_throw_length_error(const char* __msg);
void  __STL_DECLSPEC __STL_CALL __stl_throw_invalid_argument(const char* __msg);
void  __STL_DECLSPEC __STL_CALL __stl_throw_overflow_error(const char* __msg);
// For other compilers where we're throwing range errors, include the
// stdexcept header and throw the appropriate exceptions directly.
#else
inline void __STL_DECLSPEC __STL_CALL __stl_throw_range_error(const char* __msg) { 
  __STL_THROW_MSG(range_error, __msg); 
}

inline void __STL_DECLSPEC __STL_CALL __stl_throw_out_of_range(const char* __msg) { 
  __STL_THROW_MSG(out_of_range, __msg); 
}

inline void __STL_DECLSPEC __STL_CALL __stl_throw_length_error(const char* __msg) { 
  __STL_THROW_MSG(length_error, __msg); 
}

inline void __STL_DECLSPEC __STL_CALL __stl_throw_invalid_argument(const char* __msg) { 
  __STL_THROW_MSG(invalid_argument, __msg); 
}

inline void __STL_DECLSPEC __STL_CALL __stl_throw_overflow_error(const char* __msg) { 
  __STL_THROW_MSG(overflow_error, __msg); 
}
# endif /* EXTERN_RANGE_ERRORS */

__STL_END_NAMESPACE

#endif /* __STL_RANGE_ERRORS_H */

// Local Variables:
// mode:C++
// End:
