#ifndef __TEST_COPY_TEST_H
#define __TEST_COPY_TEST_H

#define FIT_EXAM

#include <exam/suite.h>

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

#endif // __TEST_COPY_TEST_H
