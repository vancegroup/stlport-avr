// -*- C++ -*- Time-stamp: <08/12/12 22:15:47 ptr>

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

#ifndef __TEST_ALG_TEST_H
#define __TEST_ALG_TEST_H

#define FIT_EXAM

#include <exam/suite.h>

class alg_test
{
  public:
    int EXAM_DECL(remcopy1);
    int EXAM_DECL(remcpif1);
    int EXAM_DECL(remif1);
    int EXAM_DECL(remove1);
    int EXAM_DECL(repcpif1);
    int EXAM_DECL(replace0);
    int EXAM_DECL(replace1);
    int EXAM_DECL(replcpy1);
    int EXAM_DECL(replif1);
    int EXAM_DECL(revcopy1);
    int EXAM_DECL(reverse1);

    int EXAM_DECL(min_max);
    int EXAM_DECL(count_test);
    int EXAM_DECL(sort_test);
    int EXAM_DECL(search_n_test);
    int EXAM_DECL(find_first_of_test);
    int EXAM_DECL(find_first_of_nsc_test);

    int EXAM_DECL(max1);
    int EXAM_DECL(max2);
    int EXAM_DECL(maxelem1);
    int EXAM_DECL(maxelem2);

    int EXAM_DECL(min1);
    int EXAM_DECL(min2);
    int EXAM_DECL(minelem1);
    int EXAM_DECL(minelem2);

    int EXAM_DECL(lwrbnd1);
    int EXAM_DECL(lwrbnd2);
    int EXAM_DECL(uprbnd1);
    int EXAM_DECL(uprbnd2);

    int EXAM_DECL(equal_range0);
    int EXAM_DECL(equal_range1);
    int EXAM_DECL(equal_range2);

  private:
    static bool str_compare( const char*, const char* );

  public:
    int EXAM_DECL(foreach0);
    int EXAM_DECL(foreach1);

  private:
    static void increase( int& a_ );
    static void sqr( int& a_ );

  public:
    int EXAM_DECL(gener1);
    int EXAM_DECL(gener2);
    int EXAM_DECL(genern1);
    int EXAM_DECL(genern2);

};

#endif // __TEST_ALG_TEST_H
