// STLport configuration file
// It is internal STLport header - DO NOT include it directly


// versions ?
# define  __STL_CALL __cdecl
# define __STL_DLLEXPORT_NEEDS_PREDECLARATION
# define __STL_OPERATOR_SPEC_NEEDS_TEMPLATE_ARGS

// most of <exception> contents is still in global namespace
# define __STL_VENDOR_UNEXPECTED_STD

// cannot work with dynamic lib as for now - locale initialization problems 
#ifndef __STL_USE_STATIC_LIB
# define __STL_USE_STATIC_LIB
#endif

// <limits> problem
# define __STL_STATIC_CONST_INIT_BUG

// <bitset> problems
# define __STL_MEMBER_SPECIALIZATION_BUG
# define  __STL_HAS_SPECIFIC_PROLOG_EPILOG 1

#if ( __BORLANDC__ < 0x540 )
// Borland C++ Builder 3 (?)
// those are assumptions, if some of them actually work, please let me know
#  define __STL_STATIC_CONST_INIT_BUG 1
// #  define __STL_THROW_RETURN_BUG 1
#  define __STL_NO_TEMPLATE_CONVERSIONS 1
#  define __STL_DEFAULT_CONSTRUCTOR_BUG 1
#  define __STL_NO_TYPENAME_ON_RETURN_TYPE
#else
#  define __STL_LONG_LONG  __int64
#endif

// BCB 2 or less (Borland 5.02)
#if ( __BORLANDC__ < 0x530 )

#  define __STL_NO_SGI_IOSTREAMS
#  undef  __SGI_STL_OWN_IOSTREAMS

#  define __STL_GLOBAL_VENDOR_CSTD 1
#  define __STL_HAS_NO_NEW_IOSTREAMS 1
#  define __STL_HAS_NO_NEW_C_HEADERS 1

#  define __STL_NO_MEMBER_TEMPLATES 1
#  define __STL_NO_MEMBER_TEMPLATE_CLASSES 1
#  define __STL_NO_MEMBER_TEMPLATE_KEYWORD 1
#  define __STL_NO_FRIEND_TEMPLATES 1
#  define __STL_NO_QUALIFIED_FRIENDS 1
#  define __STL_NO_CLASS_PARTIAL_SPECIALIZATION 1
#  define __STL_NO_FUNCTION_TMPL_PARTIAL_ORDER 1
#  define __STL_NO_EXPLICIT_FUNCTION_TMPL_ARGS 1

#  define __STL_NO_PARTIAL_SPECIALIZATION_SYNTAX 1

#  define __STL_NO_DEFAULT_NON_TYPE_PARAM 1
#  define __STL_NON_TYPE_TMPL_PARAM_BUG 1
#  define __STL_MEMBER_SPECIALIZATION_BUG
#  define __STL_NO_EXCEPTION_HEADER 1
#  define __STL_NO_EXCEPTION_SPEC 1

#  define __STL_NO_BAD_ALLOC 1
#  define __SGI_STL_NO_ARROW_OPERATOR 1
#  define __STL_NO_PROXY_ARROW_OPERATOR 1


typedef char    mbstate_t;

#  define __STL_LIMITED_DEFAULT_TEMPLATES 1
#  define __STL_NO_TYPEINFO
#  define __STL_NO_METHOD_SPECIALIZATION

#endif

// Borland 5.0x
#if ( __BORLANDC__ < 0x520 )

#  define __STL_BROKEN_USING_DIRECTIVE 1
#  define __STLPORT_EXPORT_KEYWORD _export
#  define __STLPORT_IMPORT_KEYWORD _import
#  define __STLPORT_EXPORT_TEMPLATE_KEYWORD _export
#  define __STLPORT_IMPORT_TEMPLATE_KEYWORD _import
#endif

#if ( __BORLANDC__ < 0x501 )
#   define  __STL_NONTEMPL_BASE_MATCH_BUG 1
#   define  __STL_NO_WCHAR_T 1
#endif

// 4.x
#if ( __BORLANDC__ < 0x500 )
#   define __STL_NESTED_TYPE_PARAM_BUG 1
#   define __STL_STATIC_ARRAY_BUG 1
#   define __STL_NO_BOOL 1
#   define __STL_HAS_NO_NAMESPACES 1
#   define __STL_NEED_TYPENAME 1
#   define __STL_NEED_EXPLICIT 1
#   define __STL_NEED_MUTABLE 1
#   define __STL_NO_WCHAR_T 1
#endif

// auto enable thread safety and exceptions:
#   ifndef _CPPUNWIND
#     define __STL_HAS_NO_EXCEPTIONS
#   endif

#   if defined ( __MT__ ) && !defined (_NOTHREADS) && !defined (_REENTRANT)
#     define _REENTRANT 1
#   endif

#  if defined ( __DEBUG ) && ( __DEBUG > 1 )
#   define __STL_DEBUG
#  endif

// Stop complaints about functions not inlined
#  pragma option -w-inl
// Stop complaints about significant digits
#  pragma option -w-sig
// Stop complaint about constant being long
#  pragma option -w-cln

# if (__BORLANDC__ < 0x550)
#  define __STL_LIB_BASENAME "stlport_bcc"
# else
#  define __STL_LIB_BASENAME "stlport_bcb55"
# endif

# if (__BORLANDC__ < 0x540)

#  define __STL_EXPORT_DECLSPEC __declspec(dllexport)
#  define __STL_IMPORT_DECLSPEC __declspec(dllimport)
#  define __STL_IMPORT_TEMPLATE_KEYWORD  extern
#  define __STL_EXPORT_TEMPLATE_KEYWORD

#  define __STL_CLASS_EXPORT_DECLSPEC __declspec(dllexport)
#  define __STL_CLASS_IMPORT_DECLSPEC __declspec(dllimport)

#   if !defined (__STL_NO_SGI_IOSTREAMS)

#    if ( defined (__DLL) || defined (_DLL) || defined (_WINDLL) || defined (_RTLDLL) \
     || defined (__STL_USE_DYNAMIC_LIB) ) \
       && ! defined (__STL_USE_STATIC_LIB)
#      undef  __STL_USE_DECLSPEC
#      define __STL_USE_DECLSPEC
#     endif
#   endif

# else
#  include <config/vc_select_lib.h>
# endif
