// -*- C++ -*- Time-stamp: <09/01/23 01:05:20 ptr>

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
