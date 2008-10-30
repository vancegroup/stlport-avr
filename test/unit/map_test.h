// -*- C++ -*- Time-stamp: <08/10/30 23:09:27 ptr>

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

#ifndef __TEST_MAP_TEST_H
#define __TEST_MAP_TEST_H

#define FIT_EXAM

#include <exam/suite.h>

class map_test
{
  public:
    int EXAM_DECL(map1);
    int EXAM_DECL(mmap1);
    int EXAM_DECL(mmap2);
    int EXAM_DECL(iterators);
    int EXAM_DECL(equal_range);
    int EXAM_DECL(allocator_with_state);
    int EXAM_DECL(template_methods);
};

class set_test
{
  public:
    int EXAM_DECL(set1);
    int EXAM_DECL(set2);
    int EXAM_DECL(erase);
    int EXAM_DECL(insert);
    int EXAM_DECL(find);
    int EXAM_DECL(bounds);
    int EXAM_DECL(specialized_less);
    int EXAM_DECL(implementation_check);
    int EXAM_DECL(allocator_with_state);
    int EXAM_DECL(reverse_iterator_test);
    int EXAM_DECL(template_methods);
};

class multiset_test
{
  public:
    int EXAM_DECL(mset1);
    int EXAM_DECL(mset3);
    int EXAM_DECL(mset5);
};

class hash_test
{
  public:
    int EXAM_DECL(hmap1);
    int EXAM_DECL(hmmap1);
    int EXAM_DECL(hmmap2);
    int EXAM_DECL(hmset1);
    int EXAM_DECL(hset2);
    int EXAM_DECL(insert_erase);
    int EXAM_DECL(allocator_with_state);
    // int EXAM_DECL(equality);
};

class unordered_test
{
  public:
    int EXAM_DECL(uset);
    int EXAM_DECL(umultiset);
    int EXAM_DECL(umap);
    int EXAM_DECL(umultimap);
    int EXAM_DECL(user_case);
    int EXAM_DECL(hash_policy);
    int EXAM_DECL(buckets);
    int EXAM_DECL(equal_range);
    // (benchmark1);
    // (benchmark2);
    int EXAM_DECL(template_methods);
};

#endif // __TEST_MAP_TEST_H
