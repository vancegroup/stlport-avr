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

#ifndef __TEST_VECTOR_TEST_H
#define __TEST_VECTOR_TEST_H

#define __FIT_EXAM

#include <exam/suite.h>

class vector_test
{
  public:
    int EXAM_DECL(vec_test_1);
    int EXAM_DECL(vec_test_2);
    int EXAM_DECL(vec_test_3);
    int EXAM_DECL(vec_test_4);
    int EXAM_DECL(vec_test_5);
    int EXAM_DECL(vec_test_6);
    int EXAM_DECL(vec_test_7);
    int EXAM_DECL(capacity);
    int EXAM_DECL(at);
    int EXAM_DECL(pointer);
    int EXAM_DECL(auto_ref);
    int EXAM_DECL(allocator_with_state);
    int EXAM_DECL(iterators);
    int EXAM_DECL(optimizations_check);
    int EXAM_DECL(assign_check);
    int EXAM_DECL(ebo);
};

class bvector_test
{
  public:
    int EXAM_DECL(bvec1);
};

#endif // __TEST_VECTOR_TEST_H
