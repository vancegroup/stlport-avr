// -*- C++ -*- Time-stamp: <08/12/12 22:28:52 ptr>

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

#ifndef __TEST_FUNCTOR_TEST_H
#define __TEST_FUNCTOR_TEST_H

#define FIT_EXAM

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
