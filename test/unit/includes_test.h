#ifndef __TEST_INCLUDES_TEST_H
#define __TEST_INCLUDES_TEST_H

#define FIT_EXAM

#include <exam/suite.h>

class includes_test
{
  public:
    int EXAM_DECL(incl0);
    int EXAM_DECL(incl1);
    int EXAM_DECL(incl2);

  protected:
    static bool compare_strings(const char* s1_, const char* s2_)
    {
      return strcmp(s1_, s2_) < 0 ? 1 : 0;
    }
};

#endif // __TEST_INCLUDES_TEST_H
