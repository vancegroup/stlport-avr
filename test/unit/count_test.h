#ifndef __TEST_COUNT_TEST_H
#define __TEST_COUNT_TEST_H

#define FIT_EXAM

#include <exam/suite.h>

class count_test
{
  public:
    int EXAM_DECL(count0);
    int EXAM_DECL(count1);
    int EXAM_DECL(countif1);
  protected:
    static int odd(int a_);
};

#endif // __TEST_COUNT_TEST_H
