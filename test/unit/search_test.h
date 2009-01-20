#ifndef __TEST_SEARCH_TEST_H
#define __TEST_SEARCH_TEST_H

#define FIT_EXAM

#include <exam/suite.h>

class search_test
{
  public:
    int EXAM_DECL(search0);
    int EXAM_DECL(search1);
    int EXAM_DECL(search2);

  private:
    static bool str_equal(const char* a_, const char* b_)
    {
      return strcmp(a_, b_) == 0 ? 1 : 0;
    }
};

#endif // __TEST_SEARCH_TEST_H
