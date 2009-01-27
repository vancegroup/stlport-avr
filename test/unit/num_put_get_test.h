#ifndef __TEST_NUM_PUT_GET_TEST_H
#define __TEST_NUM_PUT_GET_TEST_H

#define __FIT_EXAM

#include <exam/suite.h>

class num_put_get_test
{
  public:
    int EXAM_DECL(num_put_float);
    int EXAM_DECL(num_put_integer);
    int EXAM_DECL(num_get_float);
    int EXAM_DECL(num_get_integer);
    int EXAM_DECL(inhex);
    int EXAM_DECL(pointer);
    int EXAM_DECL(fix_float_long);
    int EXAM_DECL(custom_numpunct);
};

#endif // __TEST_NUM_PUT_GET_TEST_H
