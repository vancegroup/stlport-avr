// -*- C++ -*- Time-stamp: <2011-11-19 01:24:30 ptr>

/*
 * Copyright (c) 2011
 * Petr Ovtchenkov
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

#ifndef __TEST_SHARED_PTR_TEST_H
#define __TEST_SHARED_PTR_TEST_H

#define __FIT_EXAM

#include <exam/suite.h>

class memory1_test
{
  public:
    int EXAM_DECL(align);
    int EXAM_DECL(uses_allocator);
    int EXAM_DECL(pointer_traits);
};

class unique_ptr_test
{
  public:
    int EXAM_DECL(base);
    int EXAM_DECL(array);
};

class shared_ptr_test
{
  public:
    int EXAM_DECL(shared_ptr_base);
    int EXAM_DECL(shared_from_this);
    int EXAM_DECL(alias);
    int EXAM_DECL(convert);
    int EXAM_DECL(move);
    int EXAM_DECL(make);
    int EXAM_DECL(allocate);
    int EXAM_DECL(unique_ptr);
    int EXAM_DECL(assign);
};

class weak_ptr_test
{
  public:
    int EXAM_DECL(base);
};

#endif // __TEST_SHARED_PTR_TEST_H
