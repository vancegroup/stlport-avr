#ifndef __TEST_FIND_TEST_H
#define __TEST_FIND_TEST_H

#define FIT_EXAM

#include <exam/suite.h>

class find_test
{
  public:
    int EXAM_DECL(find0);
    int EXAM_DECL(find1);
    int EXAM_DECL(findif0);
    int EXAM_DECL(findif1);
    int EXAM_DECL(find_char);

  protected:
    static bool odd(int a_);
    static bool div_3(int a_);
};

class advance_test
{
  public:
    int EXAM_DECL(adv);
};

#endif // __TEST_FIND_TEST_H
