// -*- C++ -*- Time-stamp: <09/01/27 12:59:29 ptr>

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

#ifndef __TEST_LIMITS_TEST_H
#define __TEST_LIMITS_TEST_H

#define __FIT_EXAM

#include <exam/suite.h>

class limits_test
{
  public:
    int EXAM_DECL(limits);
    int EXAM_DECL(qnan_test);
};

#endif // __TEST_LIMITS_TEST_H
