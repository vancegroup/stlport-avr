#ifndef __TEST_SET_OPERATIONS_TEST_H
#define __TEST_SET_OPERATIONS_TEST_H

#define FIT_EXAM

#include <exam/suite.h>

class set_union_test
{
  public:
    int EXAM_DECL(setunon0);
    int EXAM_DECL(setunon1);
    int EXAM_DECL(setunon2);
};

class set_intersection_test
{
  public:
    int EXAM_DECL(setintr0);
    int EXAM_DECL(setintr1);
    int EXAM_DECL(setintr2);
};

class set_difference_test
{
  public:
    int EXAM_DECL(setdiff0);
    int EXAM_DECL(setdiff1);
    int EXAM_DECL(setdiff2);
    int EXAM_DECL(setsymd0);
    int EXAM_DECL(setsymd1);
    int EXAM_DECL(setsymd2);
};

#endif // __TEST_SET_OPERATIONS_TEST_H
