// STLport config file for KAI C++ compiler

#if defined(_XOPEN_SOURCE) && (_XOPEN_VERSION - 0 >= 4)
# define _STLP_RAND48 1
#endif
// #  define _STLP_RAND48 1

#  define _STLP_VENDOR_MB_NAMESPACE _STLP_VENDOR_STD

#  ifndef __KAI_STRICT /* _NO_LONGLONG */
#   define _STLP_LONG_LONG long long
#  endif

#  if !defined (__EXCEPTIONS) && ! defined (_EXCEPTIONS)
#    define _STLP_HAS_NO_EXCEPTIONS
#  endif

// #  define _STLP_LINK_TIME_INSTANTIATION 1
#  define _STLP_VENDOR_GLOBAL_CSTD 1
#  define _STLP_VENDOR_GLOBAL_EXCEPT_STD 1
#  define _STLP_NO_NATIVE_WIDE_STREAMS 1

// two levels of macros do not work good with kcc.
#   define _STLP_NATIVE_HEADER(header)    <../include/##header> 
#   define _STLP_NATIVE_C_HEADER(header)    <../include/##header> 
#   define _STLP_NATIVE_CPP_C_HEADER(header)    <../include/##header> 
#   define _STLP_NATIVE_CPP_RUNTIME_HEADER(header) <../include/##header>

# ifdef _WIN32
#  define _STLP_MINIMUM_IMPORT_STD
# endif

// KAI C++ uses EDG front-end, but apparently different switches
// #  define __EDG_SWITCHES 1

