// -*- C++ -*- Time-stamp: <09/01/23 00:52:02 ptr>

/*
 * Copyright (c) 2004-2009
 * Petr Ovtchenkov
 *
 * Copyright (c) 2004-2008
 * Francois Dumont
 *
 * Licensed under the Academic Free License Version 3.0
 *
 */

#ifndef __TEST_BIND_TEST_H
#define __TEST_BIND_TEST_H

#define __FIT_EXAM

#include <exam/suite.h>

class bind_test
{
  public:
    int EXAM_DECL(bind1st1);
    int EXAM_DECL(bind2nd1);
    int EXAM_DECL(bind2nd2);
    int EXAM_DECL(bind2nd3);
    int EXAM_DECL(bind_memfn);
};

#endif // __TEST_BIND_TEST_H
