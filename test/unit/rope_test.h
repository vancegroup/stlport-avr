#ifndef __TEST_ROPE_TEST_H
#define __TEST_ROPE_TEST_H

#define __FIT_EXAM

#include <exam/suite.h>

class rope_test
{
  public:
    int EXAM_DECL(io);
    int EXAM_DECL(find1);
    int EXAM_DECL(find2);
    int EXAM_DECL(construct_from_char);
    int EXAM_DECL(bug_report);
    int EXAM_DECL(test_saved_rope_iterators);
};

#endif // __TEST_ROPE_TEST_H
