#ifndef __TEST_CONFIG_TEST_H
#define __TEST_CONFIG_TEST_H

#define __FIT_EXAM

#include <exam/suite.h>

class config_test
{
  public:
    int EXAM_DECL(placement_new_bug);
    int EXAM_DECL(endianess);
    int EXAM_DECL(template_function_partial_ordering);
    int EXAM_DECL(new_throw_bad_alloc);
};

#endif // __TEST_CONFIG_TEST_H
