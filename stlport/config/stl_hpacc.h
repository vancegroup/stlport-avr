// STLport configuration file
// It is internal STLport header - DO NOT include it directly

// system C-library dependent
#  define __STL_RAND48 1
#  define __STL_NO_NATIVE_MBSTATE_T      1
#  define __STL_HPACC_BROKEN_BUFEND       1
#  define __STL_WCHAR_HPACC_EXCLUDE      1

// this was reported to help, just as with SUN CC 4.2
# define __STL_INLINE_STRING_LITERAL_BUG


// specific prolog is needed to select correct threads impl
#  define __STL_HAS_SPECIFIC_PROLOG_EPILOG

// HP aCC with +noeh
#  ifdef __HPACC_NOEH
#   define __STL_HAS_NO_EXCEPTIONS 1
#  endif

// HP compilers
// At that point, we only know we are on HP (and _not_ using gcc,
// according to "stlcomp.h"

// __HP_aCC indicate HP ANSI C++, but not always (03.xx does not
// define it before 3.13, for example).
//
#  if defined(__HP_aCC)

#   define __STL_NATIVE_OLD_STREAMS_INCLUDE_PATH ../iostream
#   define __STL_LONG_LONG long long

#if (__HP_aCC <= 30000 && __HP_aCC >= 12300)

//Special kludge to workaround bug in aCC A.01.23, CR JAGac40634
#ifdef __STL_DEBUG
static void __STL_dummy_literal() { const char *p = "x";}
static void __STL_dummy_literal_2() { const char *p = "123456789"; }
static void __STL_dummy_literal_3() { const char *p = "123456700000000000000089";}
#endif

#     define __STL_HP_ACC                   0123
#     define __STL_NATIVE_INCLUDE_PATH       ../include
#     define __STL_NATIVE_C_INCLUDE_PATH     ../include
#     define __STL_NATIVE_CPP_C_INCLUDE_PATH ../include
#     define __STL_VENDOR_GLOBAL_STD         1
#     define __STL_VENDOR_GLOBAL_CSTD        1
#     define __STL_HAS_NO_NEW_IOSTREAMS      1
#     define __STL_DONT_THROW_RANGE_ERRORS   1
#     define __STL_STATIC_CONST_INIT_BUG 1
//new flag: on most HP compilers cwchar is missing
#     define __STL_NO_CWCHAR
#   endif /* 123 */

// latest version and up
#   if (__HP_aCC >= 32500 )
#     define __STL_HP_ACC                   0325
#    if defined(_HP_NAMESPACE_STD) // option -AA
// Not tested this option. Just copied stuff from 314
// from now, we have a full standard lib in namespace std
#      define __STL_NATIVE_INCLUDE_PATH       ../include_std
#      define __STL_NATIVE_C_INCLUDE_PATH     ../include_std
#      define __STL_NATIVE_CPP_C_INCLUDE_PATH ../include_std
#      define __STL_HPACC_ONLY_NATIVE_STRING 1 // STLPort _string.c includes <locale>
// fbp : what are exact problems - we may add those headers to IMPORT_NATIVE_STD
#     define __STL_WHOLE_NATIVE_STD         1 // rw needs to acces to it's own components
// fbp : why is that ?
#     define __STL_DONT_REDEFINE_STD        1
#     define __STL_HP_ACC_COMPAT            -1
#    else // option -Aa
#     define __STL_NATIVE_INCLUDE_PATH       ../include
#     define __STL_NATIVE_C_INCLUDE_PATH     ../include
#     define __STL_NATIVE_CPP_C_INCLUDE_PATH ../include
#     define __STL_VENDOR_GLOBAL_STD         1
#     define __STL_VENDOR_GLOBAL_CSTD        1
#     define __STL_HAS_NO_NEW_IOSTREAMS      1
// Add the following in _site_config.h if "-Wc,-koenig_lookup,on" not used
//#     define __STL_NO_KOENIG_LOOKUP          1
#     define __STL_DONT_THROW_RANGE_ERRORS   1
#    endif /* _NAMESPACE_STD */
#   endif

#   if (__HP_aCC >= 31400 && __HP_aCC < 32500)
#     define __STL_HP_ACC                   0314
#     define __STL_NO_CWCHAR
#    if defined(_NAMESPACE_STD) // option -AA
// from now, we have a full standard lib in namespace std
#      define __STL_NATIVE_INCLUDE_PATH       ../include_std
#      define __STL_NATIVE_C_INCLUDE_PATH     ../include_std
#      define __STL_NATIVE_CPP_C_INCLUDE_PATH ../include_std
#      define __STL_HPACC_ONLY_NATIVE_STRING 1 // STLPort _string.c includes <locale>
// fbp : what are exact problems - we may add those headers to IMPORT_NATIVE_STD
#     define __STL_WHOLE_NATIVE_STD         1 // rw needs to acces to it's own components
// fbp : why is that ?
#     define __STL_DONT_REDEFINE_STD        1
#     define __STL_HP_ACC_COMPAT            -1
#    else // kind of compatibility mode
#     define __STL_NATIVE_INCLUDE_PATH       ../include
#     define __STL_NATIVE_C_INCLUDE_PATH     ../include
#     define __STL_NATIVE_CPP_C_INCLUDE_PATH ../include
#     define __STL_VENDOR_GLOBAL_STD         1
#     define __STL_VENDOR_GLOBAL_CSTD        1
#     define __STL_HAS_NO_NEW_IOSTREAMS      1
// comment if  "-Wc,-koenig_lookup,on" id used
#     define __STL_NO_KOENIG_LOOKUP          1
#     define __STL_DONT_THROW_RANGE_ERRORS   1
#     define __STL_NO_ROPE                   1
#    endif /* _NAMESPACE_STD */
#   endif /* 314 */

#  if (__HP_aCC >= 30000 && __HP_aCC < 31400)

// the folllowing was true for version A03.10
// #   define __STL_PARTIAL_SPECIALIZATION_BUG 1

#   define __STL_HAS_NO_NEW_C_HEADERS 1

#   define __STL_HAS_NO_NEW_IOSTREAMS
#   define __STL_NO_QUALIFIED_FRIENDS       1
// aCC bug ? need explicit args on constructors of partial specialized
// classes
#   define __STL_PARTIAL_SPEC_NEEDS_TEMPLATE_ARGS 1
// ?? fbp: really needed ?
#   define __STL_STATIC_ARRAY_BUG 1
// ?? fbp : maybe present in some versions ?
#   define __STL_NO_MEMBER_TEMPLATE_CLASSES 1
#   define __STL_NO_MEMBER_TEMPLATE_KEYWORD 1
// <exception> and stuff is in global namespace
#   define __STL_VENDOR_GLOBAL_EXCEPT_STD
// fbp : moved here
#     define __STL_VENDOR_GLOBAL_CSTD        1
// #     define _INCLUDE_HPUX_SOURCE
#   define _XPG4
#   define _INCLUDE_XOPEN_SOURCE
#   define _INCLUDE_AES_SOURCE
#  endif /* < 314 */

# endif /* HP_ACC */

// 
# ifndef __HP_aCC
#  define __STL_NATIVE_INCLUDE_PATH ../CC
#  define __STL_NATIVE_C_INCLUDE_PATH ../include
// it is HP's old cfront-based compiler.
#  define __STL_NO_BOOL 1
// #  define __STL_DONT_USE_BOOL_TYPEDEF 1
#  define __STL_NO_NEW_NEW_HEADER 1 
#  define __STL_HAS_NO_NEW_IOSTREAMS 1
#  define __STL_LIMITED_DEFAULT_TEMPLATES 1
#  define __STL_NO_SIGNED_BUILTINS
#  define __STL_HAS_NO_NAMESPACES 1
#  define __STL_NEED_TYPENAME 1
#  define __STL_NEED_EXPLICIT 1
#  define __STL_NO_EXCEPTION_SPEC 1
#  define __STL_NONTEMPL_BASE_MATCH_BUG 1
#  define __SGI_STL_NO_ARROW_OPERATOR 1
#  define __STL_BASE_MATCH_BUG
#  define __STL_BASE_TYPEDEF_OUTSIDE_BUG 1
#  define __STL_NO_NEW_STYLE_CASTS 1
// #  define __STL_NO_WCHAR_T 1
// #  define __STL_LONG_LONG long long
#  define __STL_NEED_MUTABLE 1
#  define __STL_NO_PARTIAL_SPECIALIZATION_SYNTAX 1
#  define __STL_NO_BAD_ALLOC 1
#  define __STL_NO_MEMBER_TEMPLATES 1
#  define __STL_NO_MEMBER_TEMPLATE_CLASSES 1
#  define __STL_NO_MEMBER_TEMPLATE_KEYWORD 1
#  define __STL_NO_FRIEND_TEMPLATES 1
#  define __STL_NO_QUALIFIED_FRIENDS 1
#  define __STL_NO_CLASS_PARTIAL_SPECIALIZATION 1
#  define __STL_NO_FUNCTION_TMPL_PARTIAL_ORDER 1
#  define __STL_MEMBER_POINTER_PARAM_BUG 1
#  define __STL_NON_TYPE_TMPL_PARAM_BUG 1
#  define __STL_NO_DEFAULT_NON_TYPE_PARAM 1
// #  define __STL_NO_METHOD_SPECIALIZATION 1
#  define __STL_NO_EXPLICIT_FUNCTION_TMPL_ARGS 1
#  define __STL_NO_EXCEPTION_HEADER 1
#  define __STL_DEFAULT_CONSTRUCTOR_BUG 1
#  define __STL_HAS_NO_NEW_C_HEADERS 1
// #  define __STL_STATIC_CONST_INIT_BUG 1
// #  define __STL_THROW_RETURN_BUG 1
// #  define __STL_LINK_TIME_INSTANTIATION 1
// #  define __STL_NO_TEMPLATE_CONVERSIONS 1
#  define __STL_NO_TYPEINFO 1
#  define __STL_WCHAR_T_IS_USHORT 1
#  define __STL_NO_PROXY_ARROW_OPERATOR 1
# endif /* cfront */

