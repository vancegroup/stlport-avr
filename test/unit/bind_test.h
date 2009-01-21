#ifndef __TEST_BIND_TEST_H
#define __TEST_BIND_TEST_H

#define FIT_EXAM

#include <exam/suite.h>

class bind_test
{
  public:
    int EXAM_DECL(bind1st1);
    int EXAM_DECL(bind2nd1);
    int EXAM_DECL(bind2nd2);
    int EXAM_DECL(bind2nd3);
    int EXAM_DECL(bind_memfn);
};

#endif // __TEST_BIND_TEST_H
