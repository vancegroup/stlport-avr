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

#ifndef __STL_CONFIG_H
# define __STL_CONFIG_H

/*
 * Purpose of this file :
 *
 * Defines all STLport settings.
 * This file is actually a wrapper : it includes compiler-specific
 * settings from <config/stlcomp.h>
 * and user-defined settings from <stl_user_config.h>.
 * See <config/stl_mycomp.h> and <stl_user_config.h> for the description
 * of those macros
 * 
 */

/* Other macros defined by this file:

 * bool, true, and false, if __STL_NO_BOOL is defined.
 * typename, as a null macro if it's not already a keyword.
 * explicit, as a null macro if it's not already a keyword.
 * namespace-related macros (__STLPORT_STD, __STL_BEGIN_NAMESPACE, etc.)
 * exception-related macros (__STL_TRY, __STL_UNWIND, etc.)
 * __STL_ASSERT, either as a test or as a null macro, depending on
   whether or not __STL_ASSERTIONS is defined.
*/

/* SGI basic release */
#   define __SGI_STL                                      0x330

/* Adaptation version */
#   define __SGI_STL_PORT                                 0x410

/* Placeholder for user to override settings.
 * It could be also used to mask settings from 
 * different directories.
 */
# include <stl_user_config.h>

/* Common configuration file for this particular installation. */

# include <stl/_site_config.h>

/* Use per-version compiler recognition */
#  include <config/stlcomp.h>

/* ========================================================= */

/* some fixes to configuration. This also includes modifications
 * of STLport switches depending on compiler flags,
 * or settings applicable to a group of compilers, such as
 * to all who use EDG front-end.
 */
# include <config/stl_confix.h>


/*
 * Performs integrity check on user-specified parameters
 * and site-specific settings.
 */
# include <stl/_check_config.h>


/* SGI terms */

#if !defined(__STL_HAS_NAMESPACES) && !defined(__STL_HAS_NO_NAMESPACES)
# define __STL_HAS_NAMESPACES 1
#endif

# if !defined (__STL_NO_PARTIAL_SPECIALIZATION_SYNTAX) && !defined (__STL_PARTIAL_SPECIALIZATION_SYNTAX)
#  define __STL_PARTIAL_SPECIALIZATION_SYNTAX 1
# endif

# if !defined (__STL_NO_EXPLICIT_FUNCTION_TMPL_ARGS) && !defined(__STL_EXPLICIT_FUNCTION_TMPL_ARGS)
#  define __STL_EXPLICIT_FUNCTION_TMPL_ARGS 1
# endif

# if !defined (__STL_NO_MEMBER_TEMPLATES) && !defined (__STL_MEMBER_TEMPLATES)
#  define __STL_MEMBER_TEMPLATES 1
# endif

# if !defined (__STL_NO_FRIEND_TEMPLATES) && !defined (__STL_FRIEND_TEMPLATES)
#  define __STL_FRIEND_TEMPLATES 1
# endif

# if !defined (__STL_NO_MEMBER_TEMPLATE_CLASSES) && !defined (__STL_MEMBER_TEMPLATE_CLASSES)
#  define __STL_MEMBER_TEMPLATE_CLASSES 1
# endif

#if !defined (__STL_NO_CLASS_PARTIAL_SPECIALIZATION) && !defined (__STL_CLASS_PARTIAL_SPECIALIZATION)
#  define __STL_CLASS_PARTIAL_SPECIALIZATION 1
#endif

#if !defined (__STL_FUNCTION_TMPL_PARTIAL_ORDER) && !defined (__STL_NO_FUNCTION_TMPL_PARTIAL_ORDER)
#  define __STL_FUNCTION_TMPL_PARTIAL_ORDER 1
#endif

#if !defined(__STL_NO_TEMPLATE_CONVERSIONS) && !defined (__SGI_STL_USE_AUTO_PTR_CONVERSIONS)
#  define __SGI_STL_USE_AUTO_PTR_CONVERSIONS
#endif


# if !defined (__STL_BIG_ENDIAN) && ! defined (__STL_LITTLE_ENDIAN)
#  if defined(_MIPSEB) || defined (__sparc) || \
      defined (_AIX) || defined (__hpux) || defined(macintosh) || defined (_MAC)
#   define __STL_BIG_ENDIAN 1
#  elif defined(__i386) || defined(_M_IX86) 
#   define __STL_LITTLE_ENDIAN 1
#  else
#   define __STL_UNKNOWN_ENDIAN 1
#  endif
# endif /* __STL_BIG_ENDIAN */

/* ==========================================================
 * final workaround tuning based on given flags
 * ========================================================== */

# ifndef __STL_MIN 
#  define __STL_MIN (min)
# endif

# ifndef __STL_MAX 
#  define __STL_MAX (max)
# endif

#ifndef __STL_UINT32_T
# define __STL_UINT32_T unsigned long
#endif

# if !defined (__STL_HAS_NO_NAMESPACES)
# if defined __STL_NO_NAMESPACES
#  undef __STL_USE_NAMESPACES
# else
/* assume it as the default, turn it off later if NO_NAMESPACES selected */
#  undef __STL_USE_NAMESPACES
#  define __STL_USE_NAMESPACES 1
# endif
# endif

# if defined (__STL_NO_IOSTREAMS)
#  define __STL_USE_NO_IOSTREAMS
# endif

# if defined (__STL_USE_NO_IOSTREAMS)
#  undef __STL_USE_NEW_IOSTREAMS
# endif


# if ( defined (__SGI_STL_OWN_IOSTREAMS) || \
     ! defined (__STL_HAS_NO_NEW_IOSTREAMS)) \
   && ! defined (__STL_USE_NO_IOSTREAMS) && !defined (__STL_USE_NEW_IOSTREAMS)
#  define __STL_USE_NEW_IOSTREAMS
# endif

# if defined (__STL_NO_NEW_IOSTREAMS)
#  undef __STL_USE_NEW_IOSTREAMS
#  undef __SGI_STL_OWN_IOSTREAMS
# endif

/* Operating system recognition (basic) */
# if defined (__unix) || defined (__linux__) || defined (__QNX__) || defined (_AIX)
#  define __STL_UNIX 1
#  if defined (__linux__) && ! defined (__STL_USE_GLIBC)
#   define __STL_USE_GLIBC 1
#  endif
# elif defined(macintosh) || defined (_MAC)
#  define __STL_MAC  1
# elif defined (_WIN32) || defined (__WIN32) || defined (WIN32) || defined (__WIN32__)
#  define __STL_WIN32 1
# elif defined (__WIN16) || defined (WIN16) || defined (_WIN16)
#  define __STL_WIN16
# endif /* __unix */

# if !defined(__STL_MAKE_HEADER)
#  define __STL_MAKE_HEADER(path, header) <path/header>
# endif

#if !defined (__STL_NATIVE_HEADER)
# if !defined (__STL_NATIVE_INCLUDE_PATH)
#  define __STL_NATIVE_INCLUDE_PATH ../include
# endif
# define __STL_NATIVE_HEADER(header) __STL_MAKE_HEADER(__STL_NATIVE_INCLUDE_PATH,header)
#endif

/* For some compilers, C headers like <stdio.h> are located in separate directory */
#if !defined (__STL_NATIVE_C_HEADER)
# if !defined (__STL_NATIVE_C_INCLUDE_PATH)
#  define __STL_NATIVE_C_INCLUDE_PATH __STL_NATIVE_INCLUDE_PATH
# endif
# define __STL_NATIVE_C_HEADER(header)  __STL_MAKE_HEADER(__STL_NATIVE_C_INCLUDE_PATH,header)
#endif

/* For some compilers, C-library headers like <cstdio> are located in separate directory */
#if !defined (__STL_NATIVE_CPP_C_HEADER)
# if !defined (__STL_NATIVE_CPP_C_INCLUDE_PATH)
#  define __STL_NATIVE_CPP_C_INCLUDE_PATH __STL_NATIVE_INCLUDE_PATH
# endif
# define __STL_NATIVE_CPP_C_HEADER(header)  __STL_MAKE_HEADER(__STL_NATIVE_CPP_C_INCLUDE_PATH,header)
#endif

/* Some compilers have weird placement of old-style iostream headers */
#if !defined ( __STL_NATIVE_OLD_STREAMS_HEADER )
# if !defined (__STL_NATIVE_OLD_STREAMS_INCLUDE_PATH)
#  define __STL_NATIVE_OLD_STREAMS_INCLUDE_PATH __STL_NATIVE_INCLUDE_PATH
# endif
# define __STL_NATIVE_OLD_STREAMS_HEADER(header)  __STL_MAKE_HEADER(__STL_NATIVE_OLD_STREAMS_INCLUDE_PATH,header)
#endif

/* Some compilers locate basic C++ runtime support headers (<new>, <typeinfo>, <exception>) in separate directory */
#if !defined ( __STL_NATIVE_CPP_RUNTIME_HEADER )
# if !defined (__STL_NATIVE_CPP_RUNTIME_INCLUDE_PATH)
#  define __STL_NATIVE_CPP_RUNTIME_INCLUDE_PATH __STL_NATIVE_INCLUDE_PATH
# endif
# define __STL_NATIVE_CPP_RUNTIME_HEADER(header)  __STL_MAKE_HEADER(__STL_NATIVE_CPP_RUNTIME_INCLUDE_PATH,header)
#endif

/*  shared library tune-up */

#if defined (__BUILDING_STLPORT)
/*  if we are rebuilding right now as a DLL, place everything here */
#  undef  __STL_DESIGNATED_DLL
#  define __STL_DESIGNATED_DLL 1
#endif

/* Use own namespace always if possible and not explicitly instructed otherwise */
# if defined (__STL_USE_NAMESPACES) && !defined (__STL_BROKEN_USING_DIRECTIVE) && \
     !defined(__STL_NO_OWN_NAMESPACE)
#  undef  __STL_USE_OWN_NAMESPACE
#  define __STL_USE_OWN_NAMESPACE  1
# else
#  undef __STL_WHOLE_NATIVE_STD
# endif

#  undef __STLPORT_NAMESPACE
#  if defined (__STL_USE_OWN_NAMESPACE)
#   define __STLPORT_NAMESPACE _STL
#   define __STLPORT_DBG_NAMESPACE _STLD
#  else
#   define __STLPORT_NAMESPACE std
#   define __STLPORT_DBG_NAMESPACE stdD
#  endif

# if (defined (__STL_NOTHREADS) || defined (NOTHREADS)) && ! defined (_NOTHREADS)
#  define _NOTHREADS
# endif

# if defined(_PTHREADS) && !defined(_NOTHREADS)
#     define __STL_PTHREADS
# endif
# if defined(_UITHREADS) && !defined(_NOTHREADS)
#     define __STL_UITHREADS
# endif
# ifdef _REENTRANT
#  if !defined(_NOTHREADS)
#   if defined (__sgi)
#    define __STL_SGI_THREADS
#  elif defined(__DECC) || defined(__DECCXX)
#    define __STL_DEC_THREADS
#  elif 0 /* defined (__sun) && defined (__sparc) && defined(__SGI_STL_OWN_IOSTREAMS) */
#    define __STL_SUN_SPARC_THREADS
#  elif (defined (__sun) && defined (__SVR4)) || \
         (defined(_UITHREADS) || defined (__STL_SOLARIS_THREADS) && !defined(_NOTHREADS) && !defined(_PTHREADS))
#     define __STL_UITHREADS
#   elif defined (_WIN32) || defined (WIN32) || defined (__WIN32__)
#     define __STL_WIN32THREADS
#   elif defined (__OS2__)
#     define __STL_OS2THREADS
#   else
#     define __STL_PTHREADS
#   endif /* __sgi */
# endif /* _NOTHREADS */
# endif /* _REENTRANT */

# define _STL_STATIC_MUTEX _STL_mutex_base

# if defined (_MFC_VER) && !defined (__STL_USE_MFC)
#  define __STL_USE_MFC 1
# endif

#if defined(__STL_WIN32THREADS) || defined(__STL_SGI_THREADS) \
    || defined(__STL_PTHREADS) || defined(__STL_UITHREADS) || defined(__STL_OS2THREADS)
#   define __STL_THREADS
#   define __STL_VOLATILE volatile
/* windows.h _MUST be included before bool definition ;( */
# if defined  (__STL_WIN32THREADS) && defined (__STL_NO_BOOL)
#   undef  NOMINMAX
#   define NOMINMAX
#   ifdef __STL_USE_MFC
#    include <afx.h>
#   else
#    include <windows.h>
#   endif
// #   undef min
// #   undef max
#   define __STLPORT_WINDOWS_H_INCLUDED
# endif
#else
#   define __STL_VOLATILE
#endif

# if !defined ( __STL_USE_NEW_C_HEADERS ) && !defined ( __STL_HAS_NO_NEW_C_HEADERS )
#  define __STL_USE_NEW_C_HEADERS
# endif
/* disable new-style headers if requested */
# if defined ( __STL_NO_NEW_C_HEADERS )
#  undef __STL_USE_NEW_C_HEADERS
# endif

# if !defined ( __STL_STATIC_TEMPLATE_DATA )
# define __STL_STATIC_TEMPLATE_DATA 1
# endif

#ifdef __STL_STATIC_CONST_INIT_BUG
# define __STL_INLINE_STATIC_INIT(__x)
# define __STL_OUTLINE_STATIC_INIT(__x) = __x
#else
# define __STL_INLINE_STATIC_INIT(__x) = __x
# define __STL_OUTLINE_STATIC_INIT(__x)
#endif

# if defined (__STL_BASE_TYPEDEF_BUG)
#  undef  __STL_BASE_TYPEDEF_OUTSIDE_BUG
#  define __STL_BASE_TYPEDEF_OUTSIDE_BUG 1
# endif

# if defined ( __STL_NESTED_TYPE_PARAM_BUG ) || (defined (__STL_MSVC) && (__STL_MSVC < 1100))
#  define __STL_GLOBAL_NESTED_RETURN_TYPE_PARAM_BUG
# endif

/* SUNpro 4.2 inline string literal bug */
#ifdef __STL_INLINE_STRING_LITERAL_BUG
# define __STL_FIX_LITERAL_BUG(__x) __x=__x;
#else
# define __STL_FIX_LITERAL_BUG(__x)
#endif

# if defined (__STL_NON_TYPE_TMPL_PARAM_BUG)
#  undef  __STL_NO_DEFAULT_NON_TYPE_PARAM
#  define __STL_NO_DEFAULT_NON_TYPE_PARAM 1
# endif

# define __STL_NEW new
# define __STL_PLACEMENT_NEW new

# ifdef __STL_DEBUG
#  define __STL_ASSERTIONS 1
# endif

/* apple mpw exception handling bug */
#ifndef __STL_MPWFIX_TRY
# define __STL_MPWFIX_TRY
#endif
#ifndef __STL_MPWFIX_CATCH
# define __STL_MPWFIX_CATCH
#endif
#ifndef __STL_MPWFIX_CATCH_ACTION
# define __STL_MPWFIX_CATCH_ACTION(action)
#endif

/* if __STL_DEBUG or __STL_ASSERTIONS are set, stl/debug/_debug.h defines those */

# if !defined( __STL_ASSERTIONS ) && !defined(__STL_DEBUG) && !defined(__STL_DEBUG_ALLOC)
#  define __STL_ASSERT(expr)
# endif

# ifndef __STL_DEBUG
#  define __STL_VERBOSE_ASSERT(expr,diagnostic)
#  define __STL_DEBUG_CHECK(expr)
#  define __STL_DEBUG_DO(expr)
# endif

#  if !defined (__STL_WEAK)
#   define __STL_WEAK 
#  endif

/* default parameters as template types derived from arguments ( not always supported ) */
#  if defined (__STL_LIMITED_DEFAULT_TEMPLATES)
#   define __DFL_TMPL_PARAM( classname, defval ) class classname
#   define __DFL_TMPL_ARG(classname) , classname
#  else
#   define __STL_DEFAULT_TYPE_PARAM 1
#   define __DFL_TMPL_PARAM( classname, defval ) class classname = defval
#   define __DFL_TMPL_ARG(classname)  
#  endif

/* default parameters as complete types */
# if defined ( __STL_DEFAULT_TYPE_PARAM )
#   define __DFL_TYPE_PARAM( classname, defval ) class classname = defval
#   define __DFL_NON_TYPE_PARAM(type,name,val) type name = val
#   define __DFL_TYPE_ARG(classname)
# else
#   define __DFL_TYPE_PARAM( classname, defval ) class classname
#   define __DFL_NON_TYPE_PARAM(type,name,val) type name
#   define __DFL_TYPE_ARG(classname) , classname
# endif

/* SGI compatibility */

#ifdef __STL_NO_WCHAR_T
# ifndef __STL_NO_NATIVE_WIDE_STREAMS
#  define  __STL_NO_NATIVE_WIDE_STREAMS 1
# endif
#else
# define __STL_HAS_WCHAR_T 1
#endif

#if !defined (__STL_NO_AT_MEMBER_FUNCTION)
# define __STL_CAN_THROW_RANGE_ERRORS 1
#endif

/* __STL_USE_SGI_ALLOCATORS is a hook so that users can 
 * disable allocator<_Tp> as default, and continue to use the same kind of
 * allocators as before, without having to edit library headers.
 */

# if !defined (__STL_USE_RAW_SGI_ALLOCATORS)
#   define __STL_DEFAULT_ALLOCATOR(_Tp) allocator< _Tp >
#   define __STL_DEFAULT_ALLOCATOR_SELECT( _Tp ) __DFL_TMPL_PARAM(_Alloc, allocator< _Tp >)
#   define __STL_DEFAULT_PAIR_ALLOCATOR(_Key, _Tp) allocator< pair < _Key, _Tp > >
#   if defined (__STL_LIMITED_DEFAULT_TEMPLATES)
#     define __STL_DEFAULT_PAIR_ALLOCATOR_SELECT(_Key, _Tp ) class _Alloc
#     define __STL_USE_WRAPPER_FOR_ALLOC_PARAM 1
#   else
#     define __STL_DEFAULT_PAIR_ALLOCATOR_SELECT(_Key, _Tp ) \
             class _Alloc = allocator< pair < _Key, _Tp > >
#   endif
# else
#   define __STL_DEFAULT_ALLOCATOR( _Tp ) __sgi_alloc
#   define __STL_DEFAULT_ALLOCATOR_SELECT( _Tp ) __DFL_TYPE_PARAM(_Alloc,__sgi_alloc)
#   define __STL_DEFAULT_PAIR_ALLOCATOR( _Key, _Tp ) __sgi_alloc
#   define __STL_DEFAULT_PAIR_ALLOCATOR_SELECT(_Key, _Tp ) __DFL_TYPE_PARAM(_Alloc,__sgi_alloc)
#   if defined (__STL_LIMITED_DEFAULT_TEMPLATES) && !defined (__STL_DEFAULT_TYPE_PARAM)
#    define __STL_USE_WRAPPER_FOR_ALLOC_PARAM 1
#   endif
# endif

/* default parameters workaround tuning */
#  if defined ( __STL_USE_WRAPPER_FOR_ALLOC_PARAM )
#    define __WORKAROUND_RENAME(X) __##X
#  else
#    define __WORKAROUND_RENAME(X) X
#  endif
#  if defined ( __STL_DEBUG )
#    define __WORKAROUND_DBG_RENAME(X) __##X
#  else
#    define __WORKAROUND_DBG_RENAME(X) __WORKAROUND_RENAME(X)
#  endif
#  define __FULL_NAME(X) __WORKAROUND_RENAME(X)

/* macro to convert the allocator for initialization
 * not using MEMBER_TEMPLATE_CLASSES as it should work given template constructor  */
#if defined (__STL_MEMBER_TEMPLATES) || ! defined (__STL_CLASS_PARTIAL_SPECIALIZATION)

/* if __STL_NO_TEMPLATE_CONVERSIONS is set, the member template constructor is
 * not used implicitly to convert allocator parameter, so let us do it explicitly */
# if defined (__STL_MEMBER_TEMPLATE_CLASSES) && defined (__STL_NO_TEMPLATE_CONVERSIONS)
#  define __STL_CONVERT_ALLOCATOR(__a, _Tp) __a.rebind<_Tp>::other(__a)
# else
#  define __STL_CONVERT_ALLOCATOR(__a, _Tp) __a
# endif

/* else convert, but only if partial specialization works, since else
 * Container::allocator_type won't be different */
#else 
#  define __STL_CONVERT_ALLOCATOR(__a, _Tp) __stl_alloc_create(__a,(_Tp*)0)
#endif

#ifdef __STL_MEMBER_TEMPLATE_CLASSES
#  define __STL_REBIND_ALLOCATOR(__a, _Tp) __a
#else
#  define __STL_REBIND_ALLOCATOR(__a, _Tp) __stl_alloc_rebind(__a,(_Tp*)0)
#endif

/* namespace stuff adjustment */
# if defined (__STL_USE_NAMESPACES) && defined (__cplusplus)
#  ifdef __STL_DEBUG
#   define __STLPORT_NONDBG_STD     __STLPORT_DBG_NAMESPACE
#   define __STLPORT_DBG_STD        __STLPORT_DBG_NAMESPACE
#  else
#   define __STLPORT_NONDBG_STD     __STLPORT_NAMESPACE
#   define __STLPORT_DBG_STD        __STLPORT_NAMESPACE
#  endif
# endif

/* provide a mechanism to redefine std:: namespace in a way that is transparent to the 
 * user. __STL_REDEFINE_STD is being used for wrapper files that include native headers
 * to temporary undef the std macro. */
#  if defined ( __STL_USE_NAMESPACES ) && defined ( __STL_USE_OWN_NAMESPACE ) &&  \
   ! defined ( __STL_DONT_REDEFINE_STD )
#   define __STL_REDEFINE_STD 1
#  else
#   undef  __STL_REDEFINE_STD
#  endif

/* this always mean the C library is in global namespace */
# if defined (__STL_HAS_NO_NEW_C_HEADERS) && ! defined (__STL_VENDOR_GLOBAL_CSTD)
#  define __STL_VENDOR_GLOBAL_CSTD 1
# endif

/* Depending of whether compiler supports namespaces,
 * tune the parameters for vendor-supplied libraries.
 * This section is guarded by __STL_HAS_NO_NAMESPACES, not by __STL_USE_NAMESPACES,
 * since it depends only on the native features, not on user's preference whether
 * to use namespace for STLport or not.
 */
# if !defined (__STL_HAS_NO_NAMESPACES)
/* Import some vendor's headers into corresponding STLport ones if they might be needed
 * (if we wrap native iostreams and use namepace other than std::) */
#  if ( defined (__STL_USE_OWN_NAMESPACE) || ( defined (__STL_DEBUG) && defined (__STL_USE_NAMESPACES) ) ) \
       && defined (__STL_USE_NEW_IOSTREAMS) && ! defined (__SGI_STL_OWN_IOSTREAMS)
#    define  __STL_IMPORT_VENDOR_STD 1
#  endif

/* if using stlport:: namespace or if C library stuff is not in vendor's std::,
 * try importing 'em.
 * MSVC has ambiguity problem when we try to import C-style std:: stuff back into global namespace */
#  if defined (__STL_USE_NAMESPACES) && \
   ( defined(__STL_USE_OWN_NAMESPACE) || defined (__STL_DEBUG) || defined (__STL_VENDOR_GLOBAL_CSTD))
#    define  __STL_IMPORT_VENDOR_CSTD 1
#  endif

# if defined (__STL_NO_USING_FOR_GLOBAL_FUNCTIONS) && ! defined (__STL_DO_IMPORT_CSTD_FUNCTIONS)
#  define __STL_NO_CSTD_FUNCTION_IMPORTS
# endif

#  define  __STL_USING_NAMESPACE(x) using namespace x ;

namespace std { }
namespace __std_alias = std;

/* assume std:: namespace for C++ std library if not being told otherwise */
#  ifdef __STL_VENDOR_GLOBAL_STD
#   define __STL_VENDOR_STD
#   define __STL_USING_VENDOR_STD
#  else
#   define __STL_VENDOR_STD __std_alias
#   define __STL_USING_VENDOR_STD __STL_USING_NAMESPACE(__STL_VENDOR_STD)
#  endif

/* tune things that come from C library */
#  if  defined (__STL_VENDOR_GLOBAL_CSTD) || !defined(__STL_USE_NEW_C_HEADERS)
/*  in old-style headers, C functions go to global scope. */
#   define __STL_VENDOR_CSTD
#   define __STL_USING_VENDOR_CSTD
#  else
#   define __STL_VENDOR_CSTD  __STL_VENDOR_STD
#   define __STL_USING_VENDOR_CSTD __STL_USING_NAMESPACE(__STL_VENDOR_CSTD)
#  endif /* __STL_VENDOR_CSTD */
/* exception, typeinfo, new - always come from the vendor */
#  ifdef __STL_VENDOR_GLOBAL_EXCEPT_STD
#   define __STL_VENDOR_EXCEPT_STD
#  else
#   define __STL_VENDOR_EXCEPT_STD __STL_VENDOR_STD
#  endif
# define __STL_OLD_IO_NAMESPACE
# ifndef __STL_VENDOR_MB_NAMESPACE
#  define __STL_VENDOR_MB_NAMESPACE __STL_VENDOR_CSTD
# endif
# else 
/* compiler has no namespace support */
#  define __STL_VENDOR_STD 
#  define __STL_VENDOR_CSTD
#  define __STL_USING_NAMESPACE(x)
#  define __STL_USING_VENDOR_CSTD
#  define __STL_USING_VENDOR_STD 
#  define __STL_VENDOR_EXCEPT_STD
# endif

# if defined (__STL_USE_NAMESPACES)
/* SGI terms */
/* user level defines for STLport stuff and C-related stuff. */
# ifdef __STL_DEBUG
#  define __STLPORT_STD      __STLPORT_DBG_STD
# else
#  define __STLPORT_STD      __STLPORT_NONDBG_STD
# endif
#  define __STL_BEGIN_NAMESPACE namespace __STLPORT_STD {
#  define __STL_END_NAMESPACE }
__STL_BEGIN_NAMESPACE __STL_END_NAMESPACE
namespace stlport = __STLPORT_STD;

#   define  __STL_USE_NAMESPACE_FOR_RELOPS
/* decide whether or not we use separate namespace for rel ops */
#   if defined(__STL_NO_RELOPS_NAMESPACE)
#     define __STL_BEGIN_RELOPS_NAMESPACE __STL_BEGIN_NAMESPACE namespace rel_ops {}
#     define __STL_END_RELOPS_NAMESPACE }
#     define __STLPORT_STD_RELOPS STLPORT
#   else
/* Use std::rel_ops namespace */
#     define __STLPORT_STD_RELOPS STLPORT::rel_ops
#     define __STL_BEGIN_RELOPS_NAMESPACE __STL_BEGIN_NAMESPACE namespace rel_ops {
#     define __STL_END_RELOPS_NAMESPACE } }
#     define __STL_USE_SEPARATE_RELOPS_NAMESPACE
#   endif /* Use std::rel_ops namespace */

# else /* __STL_USE_NAMESPACES */
/* STLport is being put into global namespace */
#  define __STLPORT_STD
#  define __STLPORT_DBG_STD
#  define __STL_BEGIN_NAMESPACE
#  define __STL_END_NAMESPACE
#  undef  __STL_USE_NAMESPACE_FOR_RELOPS
/* boris : it was found out that __STL_USE_SEPARATE_RELOPS_NAMESPACE 
   causes less problems than having relational operator templetes in global namespace
   Please define __STL_NO_RELOPS_NAMESPACE in stl_user_config.h if your code rely on them. */
#  ifndef __STL_NO_RELOPS_NAMESPACE
#   define __STL_USE_SEPARATE_RELOPS_NAMESPACE
#  endif
#  define __STL_BEGIN_RELOPS_NAMESPACE 
#  define __STL_END_RELOPS_NAMESPACE 
#  define __STLPORT_STD_RELOPS 
#  undef  __STL_USE_OWN_NAMESPACE
# endif  /* __STL_USE_NAMESPACES */

# define STLPORT_CSTD __STL_VENDOR_CSTD
# define STLPORT      __STLPORT_STD

#if defined(__STL_BOGUS_TEMPLATE_TYPE_MATCHING_BUG)
#  define __STL_SIMPLE_TYPE(T) _stl_trivial_proxy<T>
#else
#  define __STL_SIMPLE_TYPE(T) T
#endif

/* if we are going to use native new iostreams, use native <string> and <stdexcept> */
#  if defined (__STL_USE_NEW_IOSTREAMS) &&  \
   !defined (__STL_USE_SGI_STRING) && !defined (__SGI_STL_OWN_IOSTREAMS)
#   define __STL_USE_NATIVE_STRING      1
#   define __STL_USE_NATIVE_STDEXCEPT   1
# endif /* __STL_USE_NEW_IOSTREAMS */

# if defined(__STL_MSVC) && defined (__STL_USE_NEW_IOSTREAMS) && ! defined (__SGI_STL_OWN_IOSTREAMS) && \
     !defined (__STL_USE_OWN_NAMESPACE) && ! defined (__STL_STD_REBUILD) && defined (__STL_USE_SGI_STRING)
#   if !defined (CRTDLL2)
#    error "You have to #define CRTDLL2, and to link dynamically to work with <iostream> and SGI <string>, or to #define __STL_OWN_NAMESPACE. Read README.VC++"
#   endif /* CRTDLL2 */
# endif /* __STL_MSVC */

# ifndef __STL_RAND48
# define __STL_NO_DRAND48
# endif

/* backwards compatibility */
# define __STL_NAMESPACE __STLPORT_NAMESPACE
# define __STL_NAME(name) __STLPORT_NAMESPACE::name  /* Lo Russo Graziano <Graziano.LoRusso@CSELT.IT> */

/* advanced keywords usage */
#  ifndef  __STL_NO_NEW_STYLE_CASTS
#   define __CONST_CAST(__x,__y) const_cast<__x>(__y)
#   define __STATIC_CAST(__x,__y) static_cast<__x>(__y)
#   define __REINTERPRET_CAST(__x,__y) reinterpret_cast<__x>(__y)
#   define __DYNAMIC_CAST(__x,__y) dynamic_cast<__x>(__y)
#  else
#   define __STATIC_CAST(__x,__y) ((__x)(__y))
#   define __CONST_CAST(__x,__y) ((__x)(__y))
#   define __REINTERPRET_CAST(__x,__y) ((__x)(__y))
#   define __DYNAMIC_CAST(__x,__y) ((__x)(__y))
#  endif
#  ifdef __STL_NEED_TYPENAME
#   define typename
#  endif
#  if defined (__STL_NEED_TYPENAME) || defined (__STL_NO_TYPENAME_ON_RETURN_TYPE )
#    define __STL_TYPENAME_ON_RETURN_TYPE
#  else
#    define __STL_TYPENAME_ON_RETURN_TYPE typename
#  endif
# ifdef __STL_NO_TYPENAME_IN_TEMPLATE_HEADER
#  define __STL_HEADER_TYPENAME
# else
#  define __STL_HEADER_TYPENAME typename
# endif
# ifndef __STL_NO_MEMBER_TEMPLATE_KEYWORD
#   define __STL_TEMPLATE template
# else
#   define __STL_TEMPLATE
# endif
#  ifdef __STL_NEED_EXPLICIT
#   define explicit
#  endif
#  ifndef __STL_NEED_MUTABLE
#   define __ASSIGN_MUTABLE(type,x,y) x=y
#  else
#   define __ASSIGN_MUTABLE(type,x,y) __CONST_CAST(type,x)=y
#   define mutable
#  endif
# if defined (__STL_NO_SIGNED_BUILTINS)
/* old HP-UX doesn't understand "signed" keyword */
#  define signed
# endif

#  if defined (__STL_LOOP_INLINE_PROBLEMS)
#   define __STL_INLINE_LOOP
#  else
#   define __STL_INLINE_LOOP inline 
#  endif

#  define __PRIVATE public
#  define __PROTECTED public

#  ifndef __STL_NO_PARTIAL_SPECIALIZATION_SYNTAX
#   define __STL_TEMPLATE_NULL template<>
#  else
#   define __STL_TEMPLATE_NULL
#  endif

#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER
#  define __STL_OPERATOR_TEMPLATE
# else 
#  define __STL_OPERATOR_TEMPLATE __STL_TEMPLATE_NULL
#endif

# ifdef __STL_CLASS_PARTIAL_SPECIALIZATION
# else
/* unless we have other compiler problem, try simulating partial spec here */
# if ! defined (__STL_DONT_SIMULATE_PARTIAL_SPEC_FOR_TYPE_TRAITS)
#  define  __STL_SIMULATE_PARTIAL_SPEC_FOR_TYPE_TRAITS
# endif
/* For your own iterators, please use inheritance from iterator<> instead of these obsolete queries. */
#  if  ( defined (__STL_NESTED_TYPE_PARAM_BUG) || !defined (__STL_SIMULATE_PARTIAL_SPEC_FOR_TYPE_TRAITS))
#   if ! defined ( __STL_USE_OLD_HP_ITERATOR_QUERIES )
#    define __STL_USE_OLD_HP_ITERATOR_QUERIES
#   endif
#  elif defined ( __STL_NO_ANACHRONISMS )
#   undef __STL_USE_OLD_HP_ITERATOR_QUERIES
#  endif
# endif

# ifndef __STL_NO_EXPLICIT_FUNCTION_TMPL_ARGS
#   define __STL_NULL_TMPL_ARGS <>
# else
#   define __STL_NULL_TMPL_ARGS
# endif

# if !defined (__STL_CLASS_PARTIAL_SPECIALIZATION)
#  if !( defined (__SGI_STL_NO_ARROW_OPERATOR) &&  defined (__STL_NO_PROXY_ARROW_OPERATOR)) \
      && !defined (__STL_NO_MSVC50_COMPATIBILITY) && !defined (__STL_MSVC50_COMPATIBILITY)
/* this one is needed for proper reverse_iterator<> operator ->() handling */
#   define __STL_MSVC50_COMPATIBILITY 1
#  endif
# endif

#if defined ( __STL_CLASS_PARTIAL_SPECIALIZATION ) && ! defined (__STL_PARTIAL_SPECIALIZATION_BUG)
# ifdef __sgi
#  define __STL_DECLARE_REVERSE_ITERATORS(__reverse_iterator) \
   typedef __STLPORT_STD:: __STL_TEMPLATE reverse_iterator<const_iterator> const_reverse_iterator; \
   typedef __STLPORT_STD:: __STL_TEMPLATE reverse_iterator<iterator> reverse_iterator
# else
#  define __STL_DECLARE_REVERSE_ITERATORS(__reverse_iterator) \
   typedef __STLPORT_STD::reverse_iterator<const_iterator> const_reverse_iterator; \
   typedef __STLPORT_STD::reverse_iterator<iterator> reverse_iterator
# endif
#else /* __STL_CLASS_PARTIAL_SPECIALIZATION */
# if defined (__STL_MSVC50_COMPATIBILITY)
# define __STL_DECLARE_REVERSE_ITERATORS(__reverse_iterator) \
  typedef __STLPORT_STD::__reverse_iterator<const_iterator, value_type, const_reference, \
    const_pointer, difference_type>  const_reverse_iterator; \
  typedef __STLPORT_STD::__reverse_iterator<iterator, value_type, reference, pointer, difference_type> \
    reverse_iterator
# else
# define __STL_DECLARE_REVERSE_ITERATORS(__reverse_iterator) \
  typedef __STLPORT_STD::__reverse_iterator<const_iterator, value_type, const_reference, \
    difference_type>  const_reverse_iterator; \
  typedef __STLPORT_STD::__reverse_iterator<iterator, value_type, \
    reference, difference_type> \
    reverse_iterator
# endif
#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

# define __STL_DECLARE_BIDIRECTIONAL_REVERSE_ITERATORS \
         __STL_DECLARE_REVERSE_ITERATORS(reverse_bidirectional_iterator)
# define __STL_DECLARE_RANDOM_ACCESS_REVERSE_ITERATORS \
         __STL_DECLARE_REVERSE_ITERATORS(reverse_iterator)

#  define __IMPORT_CONTAINER_TYPEDEFS(_Super)                            \
    typedef typename _Super::value_type value_type;                      \
    typedef typename _Super::size_type size_type;                        \
    typedef typename _Super::difference_type difference_type;            \
    typedef typename _Super::reference reference;                        \
    typedef typename _Super::const_reference const_reference;            \
    typedef typename _Super::pointer pointer;                            \
    typedef typename _Super::const_pointer const_pointer;                \
    typedef typename _Super::allocator_type allocator_type;


#  define __IMPORT_ITERATORS(_Super)                                     \
    typedef typename _Super::iterator iterator;                                   \
    typedef typename _Super::const_iterator const_iterator; 

#  define __IMPORT_REVERSE_ITERATORS(_Super)                             \
    typedef typename _Super::const_reverse_iterator  const_reverse_iterator;      \
    typedef typename _Super::reverse_iterator reverse_iterator;

#  define  __IMPORT_SUPER_COPY_ASSIGNMENT(__derived_name, _Self, _SUPER)         \
    __derived_name(const _Super& __x) : _SUPER(__x) {}          \
    _Self& operator=(const _Super& __x) {                       \
        *(_Super*)this = __x;                                   \
        return *this;                                           \
    }  \
    __derived_name(const _Self& __x) : _SUPER(__x) {}          \
    _Self& operator=(const _Self& __x) {                       \
        *(_Super*)this = __x;                                   \
        return *this;                                           \
    }

# define __IMPORT_WITH_ITERATORS(_Super) \
__IMPORT_CONTAINER_TYPEDEFS(_Super) __IMPORT_ITERATORS(_Super)

# define __IMPORT_WITH_REVERSE_ITERATORS(_Super) \
__IMPORT_WITH_ITERATORS(_Super) __IMPORT_REVERSE_ITERATORS(_Super)

# if defined (__STL_TRIVIAL_CONSTRUCTOR_BUG) 
#  define __TRIVIAL_CONSTRUCTOR(__type) __type() {}  
# else
#  define __TRIVIAL_CONSTRUCTOR(__type)
# endif
# if defined (__STL_TRIVIAL_DESTRUCTOR_BUG)
#  define __TRIVIAL_DESTRUCTOR(__type) ~__type() {}  
# else
#  define __TRIVIAL_DESTRUCTOR(__type) 
# endif

#  define __TRIVIAL_STUFF(__type)  \
  __TRIVIAL_CONSTRUCTOR(__type) __TRIVIAL_DESTRUCTOR(__type)

# if ! (defined ( __STL_NO_EXCEPTIONS ) || defined (__STL_HAS_NO_EXCEPTIONS) \
	|| defined ( __STL_USE_EXCEPTIONS ))
#  define __STL_USE_EXCEPTIONS
# endif 

# ifdef __STL_USE_EXCEPTIONS
#   define __STL_TRY try
#   define __STL_CATCH_ALL catch(...)
#   ifndef __STL_THROW
#    define __STL_THROW(x) throw x
#   endif
#   define __STL_RETHROW throw
#   define __STL_UNWIND(action) catch(...) { action; throw; }

#   if !defined ( __STL_NO_EXCEPTION_SPEC )
#    define __STL_THROWS_INHERENTLY(x) throw x
#    define __STL_NOTHROW_INHERENTLY throw()
#   else
#    define __STL_THROWS_INHERENTLY(x)
#    define __STL_NOTHROW_INHERENTLY 
#   endif
/* We do not use exception throw specifications unless we are forced to */
#   define __STL_THROWS(x)
#   define __STL_NOTHROW 
# else
#   define __STL_TRY 
#   define __STL_CATCH_ALL if (false)
#   ifndef __STL_THROW
#    define __STL_THROW(x)
#   endif
#   define __STL_RETHROW 
#   define __STL_UNWIND(action) 
#   define __STL_THROWS(x)
#   define __STL_NOTHROW 
#   define __STL_THROWS_INHERENTLY(x)
#   define __STL_NOTHROW_INHERENTLY 
# endif

#if defined(__STL_NO_BOOL)
# if (defined (__IBMCPP__) && (__IBMCPP__ < 400)) && ! defined (_AIX)
#  include <isynonym.hpp>
#  if defined (__OS400__)
    typedef int bool;
#  elif !( defined (__xlC__) || defined (_AIX))
    typedef Boolean bool;
#  endif
# else
#  if defined(__STL_YVALS_H)
#   include <yvals.h>
#  else
#    if defined (__STL_DONT_USE_BOOL_TYPEDEF)
#     define bool int
#    else
      typedef int bool;
#    endif
#    define true 1
#    define false 0
#  endif
# endif /* __IBMCPP__ */
#else
#    define __STL_BOOL_KEYWORD 1
#endif /* __STL_NO_BOOL */

# ifndef __STL_MPW_EXTRA_CONST
#  define __STL_MPW_EXTRA_CONST
# endif

# ifndef __STL_DEFAULTCHAR
#  define __STL_DEFAULTCHAR char
# endif

# if defined (__STL_DEBUG_ALLOC) && ! defined (__STL_ASSERTIONS)
#  define __STL_ASSERTIONS 1
# endif

/* uninitialized value filler */
# ifndef __STL_SHRED_BYTE
/* This value is designed to cause problems if an error occurs */
#   define __STL_SHRED_BYTE 0xA3
# endif /* __STL_SHRED_BYTE */

/* shared library tune-up */
# ifndef __STL_IMPORT_DECLSPEC
#  define __STL_IMPORT_DECLSPEC
# endif

/* a keyword used to instantiate export template */
#  ifndef __STL_EXPORT_TEMPLATE_KEYWORD
#   define __STL_EXPORT_TEMPLATE_KEYWORD
#  endif
# ifndef __STL_IMPORT_TEMPLATE_KEYWORD
#  define __STL_IMPORT_TEMPLATE_KEYWORD
# endif


# if  defined (__STL_DLLEXPORT_NEEDS_PREDECLARATION) && defined (__STL_USE_DECLSPEC)
#  if ! defined (__STL_USE_TEMPLATE_EXPORT)
/* this setting turns on "extern template" extension use */
#   define __STL_USE_TEMPLATE_EXPORT
#  endif
#  if defined (__STL_DESIGNATED_DLL) && ! defined (__STL_NO_FORCE_INSTANTIATE)
#   define __STL_NO_FORCE_INSTANTIATE
#  endif
# endif

#   if defined (__STL_DESIGNATED_DLL) /* This is a lib which will contain STLport exports */
#    define  __STL_EXPORT          __STL_EXPORT_TEMPLATE_KEYWORD
#   else
#    define  __STL_EXPORT          __STL_IMPORT_TEMPLATE_KEYWORD
#  endif

# ifndef __STL_EXPORT_TEMPLATE
#  define  __STL_EXPORT_TEMPLATE __STL_EXPORT template
# endif

# if defined (__STL_USE_DECLSPEC) /* using export/import technique */

#  ifndef __STL_EXPORT_DECLSPEC
#   define __STL_EXPORT_DECLSPEC
#  endif
#  ifndef __STL_IMPORT_DECLSPEC
#   define __STL_IMPORT_DECLSPEC
#  endif
#  ifndef __STL_CLASS_EXPORT_DECLSPEC
#   define __STL_CLASS_EXPORT_DECLSPEC
#  endif
#  ifndef __STL_CLASS_IMPORT_DECLSPEC
#   define __STL_CLASS_IMPORT_DECLSPEC
#  endif
#  if defined (__STL_DESIGNATED_DLL) /* This is a lib which will contain STLport exports */
#   define  __STL_DECLSPEC        __STL_EXPORT_DECLSPEC 
#   define  __STL_CLASS_DECLSPEC  __STL_CLASS_EXPORT_DECLSPEC 
#  else
#   define  __STL_DECLSPEC        __STL_IMPORT_DECLSPEC   /* Other modules, importing STLport exports */
#   define  __STL_CLASS_DECLSPEC  __STL_CLASS_IMPORT_DECLSPEC
#  endif

# else /* Not using DLL export/import specifications */

#  define __STL_DECLSPEC
#  define __STL_CLASS_DECLSPEC

# endif

#  define __STL_EXPORT_TEMPLATE_CLASS __STL_EXPORT template class __STL_CLASS_DECLSPEC

#  if defined (__STL_MSVC) || defined (__ICL)
#   define __STL_STATIC_MEMBER_DECLSPEC
#  else
#   define __STL_STATIC_MEMBER_DECLSPEC __STL_DECLSPEC
#  endif

# if !defined (__STL_CALL)
#   define __STL_CALL
# endif

#ifdef __SGI_STL_OWN_IOSTREAMS

#  undef  __STL_WHOLE_NATIVE_STD

/* tell everybody we are using new iostreams */
#  if defined (__DECCXX) && ! defined (__USE_STD_IOSTREAM)
#   define __USE_STD_IOSTREAM
#  endif

/* We only need to expose details of streams implementation 
   if we cannot tell if we are using static or dynamic lib and 
   if we use non-standard i/o or are building STLport*/
# if defined (__BUILDING_STLPORT) || !(defined (__STL_USE_DECLSPEC) && defined (__STL_NO_CUSTOM_IO))
#  define __STL_EXPOSE_STREAM_IMPLEMENTATION 1
# endif

/* We only need to expose details of global implementation if we are building STLport 
   or have not instantiated everything in the lib */
# if defined (__BUILDING_STLPORT) || defined (__STL_NO_FORCE_INSTANTIATE)
#  undef  __STL_EXPOSE_STREAM_IMPLEMENTATION
#  define __STL_EXPOSE_STREAM_IMPLEMENTATION 1
# endif

#else
/* when we are not using SGI iostreams, we must expose globals, but not streams implementation */
#  define __STL_EXPOSE_GLOBALS_IMPLEMENTATION
#endif

# ifdef __STL_PARTIAL_SPEC_NEEDS_TEMPLATE_ARGS
#  define __STL_PSPEC2(t1,t2) < t1,t2 >
#  define __STL_PSPEC3(t1,t2,t3) < t1,t2,t3 >
# else
#  define __STL_PSPEC2(t1,t2)	/* nothing */
#  define __STL_PSPEC3(t1,t2,t3)	/* nothing */
# endif

# ifdef __STL_OPERATOR_SPEC_NEEDS_TEMPLATE_ARGS
#  define __STL_OPSPEC2(t1,t2) < t1,t2 >
# else
#  define __STL_OPSPEC2(t1,t2)	/* nothing */
# endif

# if defined (__SGI_STL_OWN_IOSTREAMS)
#  define __STL_NEW_IO_NAMESPACE __STLPORT_STD
#  define __STL_NO_WIDE_STREAMS  __STL_NO_WCHAR_T
# else
#  ifdef __STL_USE_NEW_IOSTREAMS
#   define __STL_NEW_IO_NAMESPACE __STL_VENDOR_STD
#   ifdef __STL_NO_NATIVE_WIDE_STREAMS
#    define __STL_NO_WIDE_STREAMS __STL_NO_NATIVE_WIDE_STREAMS
#   endif /* __STL_NO_NATIVE_WIDE_STREAMS */
#  else
#   define __STL_NO_WIDE_STREAMS
#   define __STL_NEW_IO_NAMESPACE
#  endif
# endif

/* We disable link-time instantiation of RW library because
 * it is not compatible with std renaming */
#if 0 /* !(defined(__STL_DONT_RENAME_STD) || defined(__BORLANDC__) || defined(_RWSTD_COMPILE_INSTANTIATE)) */
#  define _RWSTD_COMPILE_INSTANTIATE
#endif

#ifdef __STL_USE_SEPARATE_RELOPS_NAMESPACE
# define __STL_RELOPS_OPERATORS(_TMPL, _TP) \
_TMPL \
inline bool __STL_CALL operator!=(const _TP& __x, const _TP& __y) {return !(__x == __y);}\
_TMPL \
inline bool __STL_CALL operator>(const _TP& __x, const _TP& __y)  {return __y < __x;}\
_TMPL \
inline bool __STL_CALL operator<=(const _TP& __x, const _TP& __y) { return !(__y < __x);}\
_TMPL \
inline bool __STL_CALL operator>=(const _TP& __x, const _TP& __y) { return !(__x < __y);}
# else
#  define __STL_RELOPS_OPERATORS(_TMPL, _TP)
# endif

# if defined ( __STL_USE_ABBREVS )
#  include <stl/_abbrevs.h>
# endif

/* some cleanup */
# undef __STL_PARTIAL_SPECIALIZATION_SYNTAX
# undef __STL_DONT_USE_BOOL_TYPEDEF
# undef __STL_YVALS_H
# undef __STL_LOOP_INLINE_PROBLEMS
# undef __STL_NEED_EXPLICIT
# undef __STL_NEED_TYPENAME
# undef __STL_NO_NEW_STYLE_CASTS
# undef __AUTO_CONFIGURED

# define __STL_CONFIG_H_DONE 1

#endif /* __STL_CONFIG_H */

/* Local Variables:
 * mode:C++
 * End:
 */
