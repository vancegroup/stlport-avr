// STLport configuration file
// It is internal STLport header - DO NOT include it directly
// Microsoft Visual C++ 4.0, 4.1, 4.2, 5.0, ICL

// Common features for VC++ 4.0 and higher
# define __STL_NATIVE_HEADER(x) <../include/##x>
# define __STL_NATIVE_C_HEADER(x) <../include/##x>
# define __STL_NATIVE_CPP_C_HEADER(x) <../include/##x>
# define __STL_NATIVE_OLD_STREAMS_HEADER(x) <../include/##x>
# define __STL_NATIVE_CPP_RUNTIME_HEADER(header) <../include/##header>

# define __STL_MSVC50_COMPATIBILITY   1
# define __STL_MINIMUM_IMPORT_STD

# define __STL_CALL __cdecl

# ifndef __STL_LONG_LONG
#  define __STL_LONG_LONG  __int64
# endif

// these switches depend on compiler flags
# ifndef _CPPUNWIND
#  define __STL_HAS_NO_EXCEPTIONS 1
# endif

# define __STL_VENDOR_UNEXPECTED_STD

# if defined ( _MT ) && !defined (_NOTHREADS) && !defined (_REENTRANT)
#   define _REENTRANT 1
# endif

# define __STL_WCHAR_T_IS_USHORT      1

// common for VC++ and ICL
# if ! defined (__ICL) || (__ICL > 0x400)
#  define __STL_STATIC_CONST_INIT_BUG   1
#  define __STL_DEFAULT_CONSTRUCTOR_BUG 1
# endif

# ifdef __STL_MSVC
#  define __STL_DLLEXPORT_NEEDS_PREDECLARATION 1

# ifndef __BUILDING_STLPORT
#  define __STL_USE_TEMPLATE_EXPORT 1
# endif

#  define __STL_HAS_SPECIFIC_PROLOG_EPILOG
#  define __STL_NO_TYPENAME_IN_TEMPLATE_HEADER
// fails to properly resolve call to sin() from within sin()
#  define __STL_SAME_FUNCTION_NAME_RESOLUTION_BUG

#  if (__STL_MSVC > 1100)
     typedef char __stl_char;
#   define __STL_DEFAULTCHAR __stl_char
#  endif /* (__STL_MSVC < 1100 ) */

#  define __STL_NO_TYPENAME_ON_RETURN_TYPE 1 
//  using ::func_name results in ambiguity

# if (__STL_MSVC <= 1300) 
#  define __STL_NO_USING_FOR_GLOBAL_FUNCTIONS 1
#  define __STL_NO_FUNCTION_TMPL_PARTIAL_ORDER 1
#  define __STL_NO_CLASS_PARTIAL_SPECIALIZATION 1
#  define __STL_NO_FRIEND_TEMPLATES
#  define __STL_STATIC_CONST_INIT_BUG   1
# endif

#  define __STL_NO_EXPLICIT_FUNCTION_TMPL_ARGS 1
#  define __STL_NO_MEMBER_TEMPLATE_KEYWORD 1
#  define __STL_NO_MEMBER_TEMPLATE_CLASSES 1

#  define __STL_NO_QUALIFIED_FRIENDS    1
#  define __STL_DONT_USE_BOOL_TYPEDEF 1

# endif /* __STL_MSVC */


# if (_MSC_VER <= 1300) 
#  define __STL_VENDOR_GLOBAL_CSTD
// They included the necessary coding,
// but the beta still has an issue with template classes
// ok:    class a { static const int v = 2; };
// error: template &lt;class _Tp> class a { static const int v = 2; };
# endif /* (_MSC_VER <= 1300) */

# if (_MSC_VER <= 1200)  // including MSVC 6.0

// there is no partial spec, and MSVC breaks on simulating it for iterator_traits queries
# define __STL_USE_OLD_HP_ITERATOR_QUERIES

#  define __STL_GLOBAL_NEW_HANDLER

#  ifdef __STL_MSVC
//  these work, as long they are inline
#   define __STL_INLINE_MEMBER_TEMPLATES 1
#  endif
# endif /* (_MSC_VER <= 1200) */

# if ( _MSC_VER<=1010 )
// "bool" is reserved in MSVC 4.1 while <yvals.h> absent, so :
// #    define __STL_USE_ABBREVS           1
#  define __STL_NO_BAD_ALLOC
#  define __STL_HAS_NO_NEW_C_HEADERS 1
#  define __STL_NO_NEW_NEW_HEADER 1
# elif (_MSC_VER < 1100)
// VC++ 4.2 and higher
#  define __STL_YVALS_H 1
#  define __STL_HAS_NO_NEW_IOSTREAMS 1
# endif /* 1010 */

# if defined (__STL_MSVC) && ( __STL_MSVC < 1200 ) /* VC++ 6.0 */
// #  define __STL_NO_MEMBER_TEMPLATES 1
#  define __STL_NON_TYPE_TMPL_PARAM_BUG 1 
#  define __STL_THROW_RETURN_BUG 1
# endif

# if defined (__STL_MSVC) && ( __STL_MSVC < 1100 )
#  ifndef __STL_NO_SGI_IOSTREAMS
#   define __STL_NO_SGI_IOSTREAMS
#   undef  __SGI_STL_OWN_IOSTREAMS
#  endif
// #  define __STL_NESTED_TYPE_PARAM_BUG 1
// Debug mode does not work for 4.2
#  ifdef __STL_DEBUG
#   pragma message ("STLport debug mode does not work for VC++ 4.2, turning __STL_DEBUG off ...")
#    undef __STL_DEBUG
#  endif
#  define __STL_NO_BOOL            1
#  define __STL_NEED_TYPENAME      1
#  define __STL_NEED_EXPLICIT      1
#   define __STL_NEED_MUTABLE       1
#   define __STL_NO_PARTIAL_SPECIALIZATION_SYNTAX
#   define __STL_LIMITED_DEFAULT_TEMPLATES 1

// up to 4.2, library is in global namespace
#   define __STL_VENDOR_GLOBAL_STD
#   define __STL_NONTEMPL_BASE_MATCH_BUG 1
#   define __STL_BROKEN_USING_DIRECTIVE  1
#   define __SGI_STL_NO_ARROW_OPERATOR
#   define __STL_NO_SIGNED_BUILTINS 1
#   define __STL_NO_EXCEPTION_SPEC 1
#   undef  __STL_DEFAULT_TYPE_PARAM
#   undef  __STL_HAS_NO_NAMESPACES
#   undef  __STL_NO_AT_MEMBER_FUNCTION
#   undef  __STL_NO_MEMBER_TEMPLATES
#   undef  __STL_NO_MEMBER_TEMPLATE_CLASSES
#   define  __STL_HAS_NO_NAMESPACES 1
#   define  __STL_NO_AT_MEMBER_FUNCTION 1
#  define  __STL_NO_MEMBER_TEMPLATES
#  define  __STL_NO_MEMBER_TEMPLATE_CLASSES
# endif /* 1100 */

// If we are under Windows CE, include appropriate config

# ifdef UNDER_CE
#   include <config/stl_wince.h>
# endif

# ifdef __ICL
#  define __STL_LIB_BASENAME "stlport_icl"
# else
#  if (_MSC_VER >= 1200)
#   ifdef _UNICODE
#    define __STL_LIB_BASENAME "stlport_vc6_unicode"
#   else
#    define __STL_LIB_BASENAME "stlport_vc6"
#   endif
#  elif (_MSC_VER >= 1100)
#   ifdef _UNICODE
#    define __STL_LIB_BASENAME "stlport_vc5_unicode"
#   else
#    define __STL_LIB_BASENAME "stlport_vc5"
#   endif
#  endif /* (_MSC_VER >= 1200) */
# endif /* __ICL */


#    if defined (__ICL) || (_MSC_VER < 1200) && ! defined (__BUILDING_STLPORT)
//    only static SGI lib now works for ICL and VC 5.0
#     undef  __STL_USE_STATIC_LIB
#     define __STL_USE_STATIC_LIB
//    disable hook which makes template symbols to be searched for in the library
#     undef __STL_NO_CUSTOM_IO
#    endif

#   include <config/vc_select_lib.h>




