/*
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

/*
 * STLport configuration file
 * It is internal STLport header - DO NOT include it directly
 * Purpose of this file : to define STLport settings that depend on
 * compiler flags or can be otherwise missed
 *
 */

#ifndef __STL_CONFIX_H
# define __STL_CONFIX_H

/* If, by any chance, C compiler get there, try to help it to pass smoothly */
# if ! defined (__cplusplus) && ! defined (__STL_HAS_NO_NAMESPACES)
#  define __STL_HAS_NO_NAMESPACES
# endif

/* list of compilers to use SGI string */
# if (defined (__sgi) || defined (__GNUC__)) 
# if !defined (__STL_USE_SGI_STRING)
#  define __STL_USE_SGI_STRING         1
# endif
#  undef  __STL_USE_OWN_NAMESPACE 
# endif

# if defined(__MINGW32__)
#   define __STL_NO_DRAND48
# endif

/* Modena C++ library  */
#if defined (__MWERKS__) && __MWERKS__ <= 0x2303 || defined (__KCC)
# include <mcompile.h>
# define __STL_USE_MSIPL 1
# if defined (__KCC) || (defined(__MSL_CPP__) && \
       ( (__MSL_CPP__ >= 0x5000 && defined( _MSL_NO_MESSAGE_FACET )) || \
	 (__MSL_CPP__ < 0x5000 && defined( MSIPL_NL_TYPES )))  \
	 )
#  define __STL_NO_NATIVE_MESSAGE_FACET 1
# endif
#endif

/* common switches for EDG front-end */
# if defined (__EDG_SWITCHES)
#   if !(defined(_TYPENAME) || defined (_TYPENAME_IS_KEYWORD))
#     undef  __STL_NEED_TYPENAME
#     define __STL_NEED_TYPENAME 1
#   endif
#   if !defined(_WCHAR_T_IS_KEYWORD)
#     undef __STL_NO_WCHAR_T 
#     define __STL_NO_WCHAR_T 1
#   endif
#   ifndef _PARTIAL_SPECIALIZATION_OF_CLASS_TEMPLATES
#     undef __STL_NO_CLASS_PARTIAL_SPECIALIZATION
#     define __STL_NO_CLASS_PARTIAL_SPECIALIZATION 1
#   endif
#   ifndef _MEMBER_TEMPLATES
#     undef __STL_NO_MEMBER_TEMPLATES
#     define __STL_NO_MEMBER_TEMPLATES 1
#     undef __STL_NO_MEMBER_TEMPLATE_CLASSES
#     define __STL_NO_MEMBER_TEMPLATE_CLASSES 1
#   endif
#   if !defined(_MEMBER_TEMPLATE_KEYWORD)
#     undef  __STL_NO_MEMBER_TEMPLATE_KEYWORD
#     define __STL_NO_MEMBER_TEMPLATE_KEYWORD 1
#   endif
#   if !defined (__EXCEPTIONS) && ! defined (_EXCEPTIONS)
#     undef  __STL_HAS_NO_EXCEPTIONS
#     define __STL_HAS_NO_EXCEPTIONS
#   endif
#   undef __EDG_SWITCHES
# endif /* EDG */
#endif
