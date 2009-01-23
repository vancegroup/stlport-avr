#ifndef __TEST_UNINITIALIZED_TEST_H
#define __TEST_UNINITIALIZED_TEST_H

#define FIT_EXAM

#include <exam/suite.h>

class uninitialized_test
{
  public:
    int EXAM_DECL(copy_test);
    int EXAM_DECL(fill_test);
    int EXAM_DECL(fill_n_test);
};

#endif // __TEST_UNINITIALIZED_TEST_H
