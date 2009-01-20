#ifndef __TEST_ADJ_TEST_H
#define __TEST_ADJ_TEST_H

#define FIT_EXAM

#include <exam/suite.h>

class adj_test
{
  public:
    int EXAM_DECL(adjfind0);
    int EXAM_DECL(adjfind1);
    int EXAM_DECL(adjfind2);
    int EXAM_DECL(adjdiff0);
    int EXAM_DECL(adjdiff1);
    int EXAM_DECL(adjdiff2);

  protected:
    static int equal_length(const char* v1_, const char* v2_);
    static int mult(int a_, int b_);
};

#endif // __TEST_ADJ_TEST_H
