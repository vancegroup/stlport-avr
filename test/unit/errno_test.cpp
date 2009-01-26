// -*- C++ -*- Time-stamp: <09/01/26 23:26:39 ptr>

/*
 * Copyright (c) 2004-2009
 * Petr Ovtchenkov
 *
 * Copyright (c) 2004-2008
 * Francois Dumont
 *
 * Licensed under the Academic Free License Version 3.0
 *
 */

/*
  We are including stdlib.h and stddef.h first because under MSVC
  those headers contains a errno macro definition without
  the underlying value definition.
*/

#include <stdlib.h>
#include <stddef.h>

#include <errno.h>
#include <errno.h> // not typo, check errno def/undef/redef

#include "errno_test.h"

int EXAM_IMPL(errno_test::check)
{
#ifndef _STLP_WCE
  /*
    We are using ERANGE as it is part of the C++ ISO (see Table 26
    in section 19.3). Using ERANGE improve the test as it means that
    the native errno.h file has really been included.
  */
  errno = ERANGE;

  EXAM_CHECK( errno == ERANGE );
  errno = 0;

/* Note: in common, you can't write ::errno or std::errno,
 * due to errno in most cases is just a macro, that frequently
 * (in MT environment errno is a per-thread value) expand to something like
 * (*__errno_location()). I don't know way how masquerade such
 * things: name of macro can't include ::.
 *
 *                - ptr, 2005-03-30
 */
# if 0
  if ( ::errno != 0 ) {
    return 1;
  }
  if ( std::errno != 0 ) {
    return 1;
  }
# endif
#else
  throw exam::skip_exception();
#endif // _STLP_WCE

  return EXAM_RESULT;
}
