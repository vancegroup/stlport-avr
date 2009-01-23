// -*- C++ -*- Time-stamp: <08/10/26 23:10:12 ptr>

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

#ifndef __TEST_VECTOR_TEST_H
#define __TEST_VECTOR_TEST_H

#define FIT_EXAM

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
