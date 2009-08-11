/*
 * Copyright (c) 2009
 * Petr Ovtchenkov
 *
 * Licensed under the Academic Free License version 3.0
 *
 */

#ifndef _STLP_OUTERMOST_HEADER_ID
#  define _STLP_OUTERMOST_HEADER_ID 0x263
#  include <stl/_cprolog.h>
#elif (_STLP_OUTERMOST_HEADER_ID == 0x263) && !defined(_STLP_DONT_POP_HEADER_ID)
#  define _STLP_DONT_POP_HEADER_ID
#endif

#ifdef _MSC_VER
#  include "stl/msc_stdint.h"
#else /* _MSC_VER */
#  ifdef _STLP_HAS_INCLUDE_NEXT
#   include_next <stdint.h>
#  else
#   include _STLP_NATIVE_C_HEADER(stdint.h)
#  endif
#endif /* _MSC_VER */

#if (_STLP_OUTERMOST_HEADER_ID == 0x263)
#  ifndef _STLP_DONT_POP_HEADER_ID
#    include <stl/_epilog.h>
#    undef _STLP_OUTERMOST_HEADER_ID
#  else
#    undef _STLP_DONT_POP_HEADER_ID
#  endif
#endif
