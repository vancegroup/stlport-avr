// STLport config file for KAI C++ compiler

#  define __STL_RAND48 1

#  define __STL_VENDOR_MB_NAMESPACE __STL_VENDOR_STD

#  ifndef __KAI_STRICT /* _NO_LONGLONG */
#   define __STL_LONG_LONG long long
#  endif

#  if !defined (__EXCEPTIONS) && ! defined (_EXCEPTIONS)
#    define __STL_HAS_NO_EXCEPTIONS
#  endif

// #  define __STL_LINK_TIME_INSTANTIATION 1
#  define __STL_VENDOR_GLOBAL_CSTD 1
#  define __STL_NO_NATIVE_WIDE_STREAMS 1

// two levels of macros do not work good with kcc.
#   define __STL_NATIVE_HEADER(header)    <../include/##header> 
#   define __STL_NATIVE_C_HEADER(header)    <../include/##header> 
#   define __STL_NATIVE_CPP_C_HEADER(header)    <../include/##header> 
#   define __STL_NATIVE_CPP_RUNTIME_HEADER(header) <../include/##header>

# ifdef _WIN32
#  define __STL_MINIMUM_IMPORT_STD
# endif

// KAI C++ uses EDG front-end, but apparently different switches
// #  define __EDG_SWITCHES 1

