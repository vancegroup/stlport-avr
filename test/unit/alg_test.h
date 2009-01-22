// -*- C++ -*- Time-stamp: <09/01/23 02:15:46 ptr>

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

class count_test
{
  public:
    int EXAM_DECL(count0);
    int EXAM_DECL(count1);
    int EXAM_DECL(countif1);
  protected:
    static int odd(int a_);
};

class transform_test
{
  public:
    int EXAM_DECL(trnsfrm1);
    int EXAM_DECL(trnsfrm2);
    int EXAM_DECL(self_str);
};

class neq_test
{
  public:
    int EXAM_DECL(negate0);
    int EXAM_DECL(nequal0);
    int EXAM_DECL(modulus0);
};

class modulus_test
{
  public:
    int EXAM_DECL(modulus0);
};

class copy_test
{
  public:
    int EXAM_DECL(copy_array);
    int EXAM_DECL(copy_volatile);
    int EXAM_DECL(copy_vector);
    int EXAM_DECL(copy_insert);
    int EXAM_DECL(copy_back);
    int EXAM_DECL(copy_back_array);
};

class fill_test
{
  public:
    int EXAM_DECL(fill1);
    int EXAM_DECL(filln1);
};

class search_test
{
  public:
    int EXAM_DECL(search0);
    int EXAM_DECL(search1);
    int EXAM_DECL(search2);

  private:
    static bool str_equal(const char* a_, const char* b_)
    {
      return strcmp(a_, b_) == 0 ? 1 : 0;
    }
};

class mismatch_test
{
  public:
    int EXAM_DECL(mismatch0);
    int EXAM_DECL(mismatch1);
    int EXAM_DECL(mismatch2);
};

class adj_test
{
  public:
    int EXAM_DECL(adjfind0);
    int EXAM_DECL(adjfind1);
    int EXAM_DECL(adjfind2);
    int EXAM_DECL(adjdiff0);
    int EXAM_DECL(adjdiff1);
    int EXAM_DECL(adjdiff2);

  protected:
    static int equal_length(const char* v1_, const char* v2_);
    static int mult(int a_, int b_);
};

class find_test
{
  public:
    int EXAM_DECL(find0);
    int EXAM_DECL(find1);
    int EXAM_DECL(findif0);
    int EXAM_DECL(findif1);
    int EXAM_DECL(find_char);

  protected:
    static bool odd(int a_);
    static bool div_3(int a_);
};

class advance_test
{
  public:
    int EXAM_DECL(adv);
};

class swap_test
{
  public:
    int EXAM_DECL(swap1);
    int EXAM_DECL(swprnge1);
    int EXAM_DECL(swap_container_non_spec);
    int EXAM_DECL(swap_container_spec);
};

#endif // __TEST_ALG_TEST_H
