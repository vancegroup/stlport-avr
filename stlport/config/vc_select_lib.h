# if !( defined(__STL_WINCE) )
#  define __STL_EXPORT_DECLSPEC __declspec(dllexport)
#  define __STL_IMPORT_DECLSPEC __declspec(dllimport)
# endif

#  if !( defined(__STL_MSVC) && __STL_MSVC < 1100)
#   define __STL_CLASS_EXPORT_DECLSPEC __declspec(dllexport)
#   define __STL_CLASS_IMPORT_DECLSPEC __declspec(dllimport)
#  endif


#  if !defined (__STL_NO_SGI_IOSTREAMS)

#    if ( defined (__DLL) || defined (_DLL) || defined (_WINDLL) || defined (_RTLDLL) \
     || defined(_AFXDLL) || defined (__STL_USE_DYNAMIC_LIB) ) \
       && ! defined (__STL_USE_STATIC_LIB)
#      undef  __STL_USE_DECLSPEC
#      define __STL_USE_DECLSPEC 1
#    endif

#  ifndef __STL_IMPORT_TEMPLATE_KEYWORD
#   define __STL_IMPORT_TEMPLATE_KEYWORD  extern
#  endif
#  define __STL_EXPORT_TEMPLATE_KEYWORD

#    define __STL_LIB_STATIC_SUFFIX "_static"
#    include <config/stl_select_lib.h>

#  endif /* __SGI_STL_OWN_IOSTREAMS */


