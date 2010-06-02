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

#ifndef __TEST_FUNCTOR_TEST_H
#define __TEST_FUNCTOR_TEST_H

#define __FIT_EXAM

#include <exam/suite.h>

class functor_test
{
  public:
    int EXAM_DECL(equal0);
    int EXAM_DECL(equal1);
    int EXAM_DECL(equal2);
    int EXAM_DECL(equalto);

  private:
    static bool values_squared( int a_, int b_ );

  public:
    int EXAM_DECL(bnegate1);
    int EXAM_DECL(bnegate2);

    int EXAM_DECL(logicand);
    int EXAM_DECL(logicnot);
    int EXAM_DECL(logicor);

    int EXAM_DECL(lesst);
    int EXAM_DECL(lesseqt);

    int EXAM_DECL(greatert);
    int EXAM_DECL(greatereq);

    int EXAM_DECL(func1);
    int EXAM_DECL(func2);
    int EXAM_DECL(func3);

  private:
    static bool bigger(int i_);
    static bool bigger_than(int x_, int y_);

  public:
    int EXAM_DECL(plus0);
    int EXAM_DECL(minus0);
};

#endif // __TEST_FUNCTOR_TEST_H
