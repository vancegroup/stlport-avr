// STLport configuration file
// It is internal STLport header - DO NOT include it directly
// Microsoft Visual C++ 4.0, 4.1, 4.2, 5.0, 6.0, 7.0, 7.1, ICL


// Common features for VC++ 4.0 and higher
# ifdef _M_IA64
#  define _STLP_NATIVE_HEADER(x) <../crt/##x>
#  define _STLP_NATIVE_C_HEADER(x) <../crt/##x>
#  define _STLP_NATIVE_CPP_C_HEADER(x) <../crt/##x>
#  define _STLP_NATIVE_OLD_STREAMS_HEADER(x) <../crt/##x>
#  define _STLP_NATIVE_CPP_RUNTIME_HEADER(header) <../crt/##header>
#  define _STLP_GLOBAL_NEW_HANDLER
# else
#  if defined(UNDER_CE) && UNDER_CE >= 400
#   if defined(_X86_)
#       define _STLP_NATIVE_HEADER(x) <../Emulator/##x>
#       define _STLP_NATIVE_C_HEADER(x) <../Emulator/##x>
#       define _STLP_NATIVE_CPP_C_HEADER(x) <../Emulator/##x>
#       define _STLP_NATIVE_OLD_STREAMS_HEADER(x) <../Emulator/##x>
#       define _STLP_NATIVE_CPP_RUNTIME_HEADER(header) <../Emulator/##header>
#   elif defined(_ARM_)
#       define _STLP_NATIVE_HEADER(x) <../Armv4/##x>
#       define _STLP_NATIVE_C_HEADER(x) <../Armv4/##x>
#       define _STLP_NATIVE_CPP_C_HEADER(x) <../Armv4/##x>
#       define _STLP_NATIVE_OLD_STREAMS_HEADER(x) <../Armv4/##x>
#       define _STLP_NATIVE_CPP_RUNTIME_HEADER(header) <../Armv4/##header>
#   endif
#  else
#   define _STLP_NATIVE_HEADER(x) <../include/##x>
#   define _STLP_NATIVE_C_HEADER(x) <../include/##x>
#   define _STLP_NATIVE_CPP_C_HEADER(x) <../include/##x>
#   define _STLP_NATIVE_OLD_STREAMS_HEADER(x) <../include/##x>
#   define _STLP_NATIVE_CPP_RUNTIME_HEADER(header) <../include/##header>
#  endif
# endif

# define _STLP_CALL __cdecl

# ifndef _STLP_LONG_LONG
#  define _STLP_LONG_LONG  __int64
# endif

# define _STLP_PRAGMA_ONCE

// these switches depend on compiler flags
# ifndef _CPPUNWIND
#  define _STLP_HAS_NO_EXCEPTIONS 1
# endif

# define _STLP_VENDOR_UNEXPECTED_STD

# if defined ( _MT ) && !defined (_STLP_NO_THREADS)  && !defined (_REENTRANT)
#   define _REENTRANT 1
# endif

# if !defined (_NATIVE_WCHAR_T_DEFINED)
# define _STLP_WCHAR_T_IS_USHORT 1
# endif

# define _STLP_MINIMUM_IMPORT_STD

# ifdef _STLP_MSVC

# ifndef _CPPRTTI
#   define _STLP_NO_RTTI 1
# endif

# ifndef _STLP_MSVC50_COMPATIBILITY
#  define _STLP_MSVC50_COMPATIBILITY   1
# endif

#  define _STLP_DLLEXPORT_NEEDS_PREDECLARATION 1

// # ifndef __BUILDING_STLPORT
// #  define _STLP_USE_TEMPLATE_EXPORT 1
// # endif

# if (_STLP_MSVC >= 1310)
# define _STLP_NO_METHOD_SPECIALIZATION 1
# define _STLP_FULL_ADL_IMPLEMENTED 1
# endif	//	(_STLP_MSVC >= 1310)

#  if (_STLP_MSVC > 1100)
     typedef char __stl_char;
#   define _STLP_DEFAULTCHAR __stl_char
#  endif /* (_STLP_MSVC < 1100 ) */

# if (_STLP_MSVC <= 1310)
# define _STLP_STATIC_CONST_INIT_BUG   1
# endif	//	(_STLP_MSVC <= 1310)

# if (_STLP_MSVC <= 1300) 
#  define _STLP_DEF_CONST_PLCT_NEW_BUG 1
#  define _STLP_HAS_SPECIFIC_PROLOG_EPILOG
#  define _STLP_NO_TYPENAME_IN_TEMPLATE_HEADER
// fails to properly resolve call to sin() from within sin()
#  define _STLP_SAME_FUNCTION_NAME_RESOLUTION_BUG
#  define _STLP_NO_TYPENAME_ON_RETURN_TYPE 1
// boris : not defining this macro for SP5 causes other problems
// #  if !defined (_MSC_FULL_VER) || (_MSC_FULL_VER < 12008804 )
#  define _STLP_NO_USING_FOR_GLOBAL_FUNCTIONS 1
//#  endif
#  define _STLP_NO_FUNCTION_TMPL_PARTIAL_ORDER 1
#  define _STLP_NO_CLASS_PARTIAL_SPECIALIZATION 1
#  define _STLP_NO_FRIEND_TEMPLATES
// VC++ cannot handle default allocator argument in template constructors
#  define _STLP_NEEDS_EXTRA_TEMPLATE_CONSTRUCTORS
// there is no partial spec, and MSVC breaks on simulating it for iterator_traits queries
#  define _STLP_USE_OLD_HP_ITERATOR_QUERIES
// #  define _STLP_NO_EXPLICIT_FUNCTION_TMPL_ARGS 1
#  define _STLP_NO_QUALIFIED_FRIENDS    1
#  define _STLP_DONT_USE_BOOL_TYPEDEF 1
# endif /* _STLP_MSVC <= 1300 */

# if (_STLP_MSVC <= 1200)
// dums: VC6 can't handle correctly member templates of class that are explicitely
// instanciated to be exported
#  ifdef _DLL
#    define _STLP_NO_MEMBER_TEMPLATES 1
#  endif
# endif

# endif /* _STLP_MSVC */

# if (_MSC_VER <= 1310) 
#  define _STLP_VENDOR_GLOBAL_CSTD
#  if !defined(_STLP_WHOLE_NATIVE_STD) && !defined(_STLP_REDEFINE_STD)
/*
 * All VC compilers has a problem with import whole namespace, i.e. sentence
 *   namespace std { uning namespace _STL; }
 * has no effect.
 * The only way is to redefine name 'std'.
 */
#    define _STLP_REDEFINE_STD
#  endif
# endif /* (_MSC_VER <= 1310) */

# if (_MSC_VER <= 1200) || defined(UNDER_CE) // including MSVC 6.0
//  these work, as long they are inline
#  define _STLP_INLINE_MEMBER_TEMPLATES 1
#  define _STLP_NO_MEMBER_TEMPLATE_KEYWORD 1
#  define _STLP_GLOBAL_NEW_HANDLER
#  define _STLP_DONT_RETURN_VOID 1
#  define _STLP_DONT_USE_NESTED_TCLASS_THROUGHT_TPARAM 1
#  define _STLP_NEW_DONT_THROW_BAD_ALLOC 1
#  ifdef _DEBUG
#   define _STLP_USE_ABBREVS
#  endif
# endif /* (_MSC_VER <= 1200) */

# if ( _MSC_VER<=1010 )
// "bool" is reserved in MSVC 4.1 while <yvals.h> absent, so :
// #    define _STLP_USE_ABBREVS           1
#  define _STLP_NO_BAD_ALLOC
#  define _STLP_HAS_NO_NEW_C_HEADERS 1
#  define _STLP_NO_NEW_NEW_HEADER 1
# elif (_MSC_VER < 1100)
// VC++ 4.2 and higher
#  define _STLP_YVALS_H 1
#  define _STLP_HAS_NO_NEW_IOSTREAMS 1
# endif /* 1010 */

# if defined (_STLP_MSVC) && ( _STLP_MSVC < 1200 ) /* before VC++ 6.0 */
// #  define _STLP_NO_MEMBER_TEMPLATES 1
// #  define _STLP_NO_EXPLICIT_FUNCTION_TMPL_ARGS 1
#  define _STLP_NON_TYPE_TMPL_PARAM_BUG 1 
#  define _STLP_THROW_RETURN_BUG 1
#  define _STLP_NO_MEMBER_TEMPLATE_CLASSES 1
#  define _STLP_DEF_CONST_DEF_PARAM_BUG 1
# endif

# if defined (_STLP_MSVC) && ( _STLP_MSVC < 1100 )
#  ifndef _STLP_NO_OWN_IOSTREAMS
#   define _STLP_NO_OWN_IOSTREAMS
#   undef  _STLP_OWN_IOSTREAMS
#  endif
// #  define _STLP_NESTED_TYPE_PARAM_BUG 1
// Debug mode does not work for 4.2
#  ifdef _STLP_DEBUG
#   pragma message ("STLport debug mode does not work for VC++ 4.2, turning _STLP_DEBUG off ...")
#    undef _STLP_DEBUG
#  endif
#  define _STLP_NO_BOOL            1
#  define _STLP_NEED_TYPENAME      1
#  define _STLP_NEED_EXPLICIT      1
#   define _STLP_NEED_MUTABLE       1
#   define _STLP_NO_PARTIAL_SPECIALIZATION_SYNTAX
#   define _STLP_LIMITED_DEFAULT_TEMPLATES 1

// up to 4.2, library is in global namespace
#   define _STLP_VENDOR_GLOBAL_STD
#   define _STLP_NONTEMPL_BASE_MATCH_BUG 1
#   define _STLP_BROKEN_USING_DIRECTIVE  1
#   define _STLP_NO_ARROW_OPERATOR
#   define _STLP_NO_SIGNED_BUILTINS 1
#   define _STLP_NO_EXCEPTION_SPEC 1
#   undef  _STLP_DEFAULT_TYPE_PARAM
#   undef  _STLP_HAS_NO_NAMESPACES
#   undef  _STLP_NO_AT_MEMBER_FUNCTION
#   undef  _STLP_NO_MEMBER_TEMPLATES
#   undef  _STLP_NO_MEMBER_TEMPLATE_CLASSES
#   define  _STLP_HAS_NO_NAMESPACES 1
#   define  _STLP_NO_AT_MEMBER_FUNCTION 1
#  define  _STLP_NO_MEMBER_TEMPLATES
#  define  _STLP_NO_MEMBER_TEMPLATE_CLASSES
# endif /* 1100 */

// If we are under Windows CE, include appropriate config

# if defined(UNDER_CE)
#  if _MSC_VER < 1200
    // Microsoft Visual C++ 5 with Windows CE Toolkit;
    // could also be Visual C++ 6 with toolkit, but we can't detect that.
    // the Windows CE Toolkit is obsolete, anyway
#   include <config/stl_wince.h>
#  else
    // common header for eMbedded Visual C++ 3 and .NET
#   include <config/stl_evc.h>
#  endif
# endif /* UNDER_CE */

# if !( defined(_STLP_WINCE) )
#  define _STLP_EXPORT_DECLSPEC __declspec(dllexport)
#  define _STLP_IMPORT_DECLSPEC __declspec(dllimport)
# endif

# if !( defined(_STLP_MSVC) && _STLP_MSVC < 1100)
#  define _STLP_CLASS_EXPORT_DECLSPEC __declspec(dllexport)
#  define _STLP_CLASS_IMPORT_DECLSPEC __declspec(dllimport)
# endif

# if ( defined (__DLL) || defined (_DLL) || defined (_WINDLL) || defined (_RTLDLL) || \
       defined(_AFXDLL) || defined (_STLP_USE_DYNAMIC_LIB) ) && \
       !(defined(_STLP_USE_STATIC_LIB) || defined(_STLP_USE_STATICX_LIB))
#  undef  _STLP_USE_DECLSPEC
#  define _STLP_USE_DECLSPEC 1
# endif

# ifndef _STLP_IMPORT_TEMPLATE_KEYWORD
#  if defined(_STLP_MSVC) && _STLP_MSVC > 1300
#   define _STLP_IMPORT_TEMPLATE_KEYWORD
#  else
#   define _STLP_IMPORT_TEMPLATE_KEYWORD  extern
#  endif
# endif
# define _STLP_EXPORT_TEMPLATE_KEYWORD


# if !defined(_STLP_DONT_FORCE_MSVC_LIB_NAME) && !defined(_STLP_NO_OWN_IOSTREAMS)
#  ifdef __ICL
#   define _STLP_LIB_BASENAME "stlport_icl"
#  elif defined(_STLP_WCE_EVC3)
#   if defined(_X86_)
#    define _STLP_LIB_BASENAME "stlport_evc3-x86"
#   elif defined(_ARM_)
#    define _STLP_LIB_BASENAME "stlport_evc3-arm"
#   endif /* _STLP_WCE_EVC3 */
#  elif defined(_STLP_WCE_NET)
#   if defined(_X86_)
#    define _STLP_LIB_BASENAME "stlport_evc4-x86"
#   elif defined(_ARM_)
#    define _STLP_LIB_BASENAME "stlport_evc4-arm"
#   else
#    define _STLP_LIB_BASENAME "stlport_wce4"
#   endif
#  else
#   if (_MSC_VER >= 1310) 
#    define _STLP_LIB_BASENAME "stlport_vc71"
#   elif (_MSC_VER >= 1300) 
#    define _STLP_LIB_BASENAME "stlport_vc70"
#   elif (_MSC_VER >= 1200)
#    define _STLP_LIB_BASENAME "stlport_vc6"
#   elif (_MSC_VER >= 1100)
#    define _STLP_LIB_BASENAME "stlport_vc5"
#   endif /* (_MSC_VER >= 1200) */
#  endif /* __ICL */


#  if (defined (__ICL) && (__ICL < 450)) || (_MSC_VER < 1200)
//    only static STLport lib now works for ICL and VC 5.0
#   undef  _STLP_USE_STATIC_LIB
#   define _STLP_USE_STATIC_LIB
//    disable hook which makes template symbols to be searched for in the library
#   undef _STLP_NO_CUSTOM_IO
#  endif

#  if (defined(_RTLDLL) && defined(_STLP_USE_STATIC_LIB)) || defined(_STLP_USE_STATICX_LIB)
#   define _STLP_LIB_STATIC_SUFFIX "_staticx"
#  else
#   define _STLP_LIB_STATIC_SUFFIX "_static"
#  endif

#  if !defined (_STLP_LIB_STATIC_SUFFIX)
#   define _STLP_LIB_STATIC_SUFFIX ""
#  endif

// Note : the code below is intended to make use of compiled
// STLport iostreams easier. If you are with to change names used for
// STLport libraries , please also change RELEASE_NAME and DEBUG_NAME
// macros in makefile ../../src/vc6.mak (or whatever .mak you are using to build
// STLport). If you are using binaries, you may just rename the binaries.
#  if !defined (__BUILDING_STLPORT)
#   if defined (_STLP_USE_DECLSPEC)
#    ifdef _STLP_DEBUG
#     pragma comment(lib, _STLP_LIB_BASENAME"_stldebug.lib")
#    elif (defined (_DEBUG) || defined (__DEBUG)) && defined (_STLP_USE_DEBUG_LIB)
#     pragma comment(lib, _STLP_LIB_BASENAME"_debug.lib")
#    else
#     pragma comment(lib, _STLP_LIB_BASENAME".lib")
#    endif
#   else /* _STLP_USE_DECLSPEC */
// fbp : for static linking, debug setting _MUST_ correspond to what
// has been compiled into binary lib
#    ifdef _STLP_DEBUG
#     if (! defined (_DEBUG))
#      error "For static link with STLport library, _DEBUG setting MUST be on when _STLP_DEBUG is on. (/MTd forces _DEBUG)"
#     endif
#     pragma comment(lib, _STLP_LIB_BASENAME"_stldebug"_STLP_LIB_STATIC_SUFFIX".lib")
#    elif (defined (_DEBUG) || defined (__DEBUG)) && defined (_STLP_USE_DEBUG_LIB)
#     pragma comment(lib, _STLP_LIB_BASENAME"_debug"_STLP_LIB_STATIC_SUFFIX".lib")
#    else
#     pragma comment(lib, _STLP_LIB_BASENAME""_STLP_LIB_STATIC_SUFFIX".lib")
#    endif
#   endif /* _STLP_USE_DECLSPEC */
#  endif /* __BUILDING_STLPORT */
# endif // !_STLP_DONT_FORCE_MSVC_LIB_NAME) && !_STLP_NO_OWN_IOSTREAMS

// Local Variables:
// mode:C++
// End:
