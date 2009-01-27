#ifndef __TEST_ALLOCATOR_TEST_H
#define __TEST_ALLOCATOR_TEST_H

#define __FIT_EXAM

#include <exam/suite.h>

class allocator_test
{
  public:
    int EXAM_DECL(zero_allocation);
    int EXAM_DECL(bad_alloc_test);
    int EXAM_DECL(per_thread_alloc);
};

class memory_test
{
  public:
    int EXAM_DECL(auto_ptr_test);
};

class rawriter_test
{
  public:
    int EXAM_DECL(rawiter1);
};

#endif // __TEST_ALLOCATOR_TEST_H
