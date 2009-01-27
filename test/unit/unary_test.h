#ifndef __TEST_UNARY_TEST_H
#define __TEST_UNARY_TEST_H

#define __FIT_EXAM

#include <exam/suite.h>

class unary_test
{
  public:
    int EXAM_DECL(unegate1);
    int EXAM_DECL(unegate2);
    int EXAM_DECL(unegate3);
    int EXAM_DECL(ucompose1);
    int EXAM_DECL(ucompose2);
};

#endif // __TEST_UNARY_TEST_H
