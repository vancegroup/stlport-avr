// -*- C++ -*- Time-stamp: <09/01/26 23:27:43 ptr>

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

#ifndef __TEST_EXCEPTION_TEST_H
#define __TEST_EXCEPTION_TEST_H

#define FIT_EXAM

#include <exam/suite.h>

class exception_test
{
  public:
    int EXAM_DECL(what);
    int EXAM_DECL(unexpected_except);
    int EXAM_DECL(uncaught_except);
    int EXAM_DECL(exception_emission);
};

#endif // __TEST_EXCEPTION_TEST_H
