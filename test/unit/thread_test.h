// -*- C++ -*- Time-stamp: <2012-03-02 01:02:32 ptr>

/*
 * Copyright (c) 2006-2012
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

#ifndef __TEST_THREAD_H
#define __TEST_THREAD_H

#define __FIT_EXAM

#include <exam/suite.h>

class thread_test
{
  public:
    int EXAM_DECL(thread_call);
    int EXAM_DECL(mutex_test);
    int EXAM_DECL(mutex_rw_test);
    int EXAM_DECL(barrier);
    int EXAM_DECL(semaphore);
    int EXAM_DECL(condition_var);
    int EXAM_DECL(timed_mutex);
    int EXAM_DECL(try_lock);
};

#endif // __TEST_THREAD_H
