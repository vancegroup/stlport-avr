// -*- C++ -*- Time-stamp: <08/10/27 09:21:32 ptr>

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

#ifndef __TEST_DEQUE_TEST_H
#define __TEST_DEQUE_TEST_H

#define FIT_EXAM

#include <exam/suite.h>

class deque_test
{
  public:
    int EXAM_DECL(deque1);
    int EXAM_DECL(at);
    int EXAM_DECL(insert);
    int EXAM_DECL(erase);
    int EXAM_DECL(auto_ref);
    int EXAM_DECL(allocator_with_state);
    int EXAM_DECL(optimizations_check);
};

#endif // __TEST_DEQUE_TEST_H
