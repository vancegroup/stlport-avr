// -*- C++ -*- Time-stamp: <10/06/02 15:17:35 ptr>

/*
 * Copyright (c) 2004-2009
 * Petr Ovtchenkov
 *
 * Copyright (c) 2004-2008
 * Francois Dumont
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

#ifndef __TEST_PERM_TEST_H
#define __TEST_PERM_TEST_H

#define __FIT_EXAM

#include <exam/suite.h>

class perm_test
{
  public:
    int EXAM_DECL(nextprm0);
    int EXAM_DECL(nextprm1);
    int EXAM_DECL(nextprm2);
    int EXAM_DECL(prevprm0);
    int EXAM_DECL(prevprm1);
    int EXAM_DECL(prevprm2);
};

#endif // __TEST_PERM_TEST_H
