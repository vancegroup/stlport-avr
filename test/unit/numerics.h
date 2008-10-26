// -*- C++ -*- Time-stamp: <08/10/26 22:26:08 ptr>

/*
 * Copyright (c) 2008
 * Petr Ovtchenkov
 *
 * Licensed under the Academic Free License Version 3.0
 *
 */

#ifndef __TEST_NUMERICS_H
#define __TEST_NUMERICS_H

#define FIT_EXAM

#include <exam/suite.h>

class numerics
{
  public:
    int EXAM_DECL(accum1);
    int EXAM_DECL(accum2);
    int EXAM_DECL(times);
    int EXAM_DECL(partsum0);
    int EXAM_DECL(partsum1);
    int EXAM_DECL(partsum2);
    int EXAM_DECL(innprod0);
    int EXAM_DECL(innprod1);
    int EXAM_DECL(innprod2);
};

#endif // __TEST_NUMERICS_H
