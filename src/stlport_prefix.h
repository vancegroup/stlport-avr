#ifndef STLPORT_PREFIX_H
# define STLPORT_PREFIX_H

# define __BUILDING_STLPORT 1

# if defined (_WIN32) || defined (WIN32)
#  ifdef __cplusplus
#   define WIN32_LEAN_AND_MEAN
#   define NOSERVICE
#  endif
#  if ! defined (__CYGWIN__)
#   define __STL_REAL_LOCALE_IMPLEMENTED
#  endif
# endif

#   undef __STL_NO_FORCE_INSTANTIATE

/* Please add extra compilation switches for particular compilers here */

# include <stl/_config.h>

# if defined (__STL_USE_TEMPLATE_EXPORT) && defined (__STL_USE_DECLSPEC)
#  define __STL_EXPOSE_GLOBALS_IMPLEMENTATION
# endif

# ifdef __cplusplus
// This section is only for compilers that support precompiled headers !
// Currently there are : Visual C++
// Please remember to make sure to turn on precompiled header option in
// the platform makefile when addinf compilers to this list, otherwise 
// this will result in worse build performance.

# if defined (__STL_MSVC)
# ifndef __STL_USE_DECLSPEC
# include <climits>
# include <cmath>
# include <cstdlib>
# include <cstring>
# include <ctime>
# include <new>
# include <exception>
# include <functional>
# include <memory>
# include <utility>
# include <limits>
# include <algorithm>
# include <iosfwd>
# include <ios>

# include <stdexcept>
# include <string>
// # include <locale>

# ifdef __STL_MSVC
#  pragma hdrstop
# endif

# endif

# endif /* precompiler headers */

# if defined (__STL_FUNCTION_TMPL_PARTIAL_ORDER) || defined (__BORLANDC__)
#  define __STL_OPERATOR_SPEC __STL_DECLSPEC 
# else
#  define __STL_OPERATOR_SPEC __STL_TEMPLATE_NULL __STL_DECLSPEC
# endif

# endif /* __cplusplus */

#endif /* PREFIX */

