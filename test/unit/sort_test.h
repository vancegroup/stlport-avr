#ifndef __TEST_SORT_TEST_H
#define __TEST_SORT_TEST_H

#define __FIT_EXAM

#include <exam/suite.h>

class sort_test
{
  public:
    int EXAM_DECL(sort1);
    int EXAM_DECL(sort2);
    int EXAM_DECL(sort3);
    int EXAM_DECL(sort4);
    int EXAM_DECL(stblsrt1);
    int EXAM_DECL(stblsrt2);
    int EXAM_DECL(bad_predicate_detected);

  private:
    static bool string_less(const char* a_, const char* b_)
    {
      return strcmp(a_, b_) < 0 ? 1 : 0;
    }
};

#endif // __TEST_SORT_TEST_H
