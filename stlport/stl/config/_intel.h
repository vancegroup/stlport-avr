// STLport configuration file
// It is internal STLport header - DO NOT include it directly

#if (__ICL >= 450)
#  define _STLP_DLLEXPORT_NEEDS_PREDECLARATION 1
#endif

#define _STLP_IMPORT_TEMPLATE_KEYWORD extern

#include <stl/config/_msvc.h>

#if defined (_STLP_DONT_RETURN_VOID)
#  undef _STLP_DONT_RETURN_VOID
#endif

#if (__ICL >= 900)
#  undef _STLP_NO_UNEXPECTED_EXCEPT_SUPPORT
#  if !defined (_STLP_DONT_USE_EXCEPTIONS)
#    define _STLP_NOTHROW throw()
#  endif
#endif

#if (__ICL < 450)
/*    only static STLport lib works for ICL */
#  undef  _STLP_USE_STATIC_LIB
#  undef  _STLP_USE_DYNAMIC_LIB
#  define _STLP_USE_STATIC_LIB
/*    disable hook which makes template symbols to be searched for in the library */
#  undef _STLP_NO_CUSTOM_IO
#endif

#undef  _STLP_LONG_LONG
#define _STLP_LONG_LONG long long

#if (__ICL >= 800)
#  define _STLP_STATIC_CONST_INIT_BUG 1
#endif

#if defined (__cplusplus) && (__ICL >= 900) && (_MSC_VER < 1300)
namespace std
{
  void _STLP_CALL unexpected();
}
#endif
