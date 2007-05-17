/* NOTE : this header has no guards and is MEANT for multiple inclusion!
 * If you are using "header protection" option with your compiler,
 * please also find #pragma which disables it and put it here, to
 * allow reentrancy of this header.
 */

#ifdef std
#  undef std /* We undef "std" on entry , as STLport headers may include native ones. */
#endif

#ifdef _STLP_PROLOG_HEADER_INCLUDED
#  error STlport prolog header can not be reincluded as long as epilog has not be included.
#endif

#define _STLP_PROLOG_HEADER_INCLUDED

#ifndef _STLP_FEATURES_H
#  include <stl/config/features.h>
#endif

/* If the platform provides any specific prolog actions,
 * like #pragmas, do include platform-specific prolog file */
#if defined (_STLP_HAS_SPECIFIC_PROLOG_EPILOG)
#  include <stl/config/_prolog.h>
#endif

/* Get all debug things, potentially only empty macros if none of
 * the debug features available in user config file is activated. */
 /* Thanks to _STLP_OUTERMOST_HEADER_ID we hide _debug.h when C standard
  * headers are included as some platforms (Win32) include C standard headers
  * in an 'extern "C"' scope which do not accept the templates exposed
  * in _debug.h. */
#if defined (__cplusplus) && !defined (_STLP_DEBUG_H) && \
   !((_STLP_OUTERMOST_HEADER_ID >= 0x200) && (_STLP_OUTERMOST_HEADER_ID <= 0x300))
#  include <stl/debug/_debug.h>
#endif
