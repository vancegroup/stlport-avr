#ifndef __TEST_SWAP_TEST_H
#define __TEST_SWAP_TEST_H

#define FIT_EXAM

#include <exam/suite.h>

class swap_test
{
  public:
    int EXAM_DECL(swap1);
    int EXAM_DECL(swprnge1);
    int EXAM_DECL(swap_container_non_spec);
    int EXAM_DECL(swap_container_spec);
};

#endif // __TEST_SWAP_TEST_H
