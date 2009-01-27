// -*- C++ -*- Time-stamp: <08/10/27 23:41:57 ptr>

/*
 * Copyright (c) 2004-2008
 * Petr Ovtchenkov
 *
 * Copyright (c) 2004-2008
 * Francois Dumont
 *
 * Licensed under the Academic Free License Version 3.0
 *
 */

#ifndef __TEST_SLIST_TEST_H
#define __TEST_SLIST_TEST_H

#define __FIT_EXAM

#include <exam/suite.h>

class slist_test
{
  public:
    int EXAM_DECL(slist1);
    int EXAM_DECL(erase);
    int EXAM_DECL(insert);
    int EXAM_DECL(splice);
    int EXAM_DECL(allocator_with_state);
};

#endif // __TEST_SLIST_TEST_H
