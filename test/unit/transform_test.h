// -*- C++ -*- Time-stamp: <09/01/23 00:39:22 ptr>

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

#ifndef __TEST_TRANSFORM_TEST_H
#define __TEST_TRANSFORM_TEST_H

#define FIT_EXAM

#include <exam/suite.h>

class transform_test
{
  public:
    int EXAM_DECL(trnsfrm1);
    int EXAM_DECL(trnsfrm2);
    int EXAM_DECL(self_str);
};

class neq_test
{
  public:
    int EXAM_DECL(negate0);
    int EXAM_DECL(nequal0);
    int EXAM_DECL(modulus0);
};

class modulus_test
{
  public:
    int EXAM_DECL(modulus0);
};

#endif // __TEST_TRANSFORM_TEST_H
