// -*- C++ -*- Time-stamp: <08/10/27 10:02:15 ptr>

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

#ifndef __TEST_LIST_TEST_H
#define __TEST_LIST_TEST_H

#define __FIT_EXAM

#include <exam/suite.h>

class list_test
{
  public:
    int EXAM_DECL(list1);
    int EXAM_DECL(list2);
    int EXAM_DECL(list3);
    int EXAM_DECL(list4);
    int EXAM_DECL(erase);
    int EXAM_DECL(resize);
    int EXAM_DECL(push_back);
    int EXAM_DECL(push_front);
    int EXAM_DECL(allocator_with_state);
    int EXAM_DECL(swap);
    int EXAM_DECL(adl);
    //int EXAM_DECL(const_list);
};

#endif // __TEST_LIST_TEST_H
