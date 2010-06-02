// -*- C++ -*- Time-stamp: <10/06/02 15:17:35 ptr>

/*
 * Copyright (c) 2004-2008
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
