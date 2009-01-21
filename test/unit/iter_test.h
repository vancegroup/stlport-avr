#ifndef __TEST_ITER_TEST_H
#define __TEST_ITER_TEST_H

#define FIT_EXAM

#include <exam/suite.h>

class iter_test
{
  public:
    int EXAM_DECL(iter1);
    int EXAM_DECL(iter2);
    int EXAM_DECL(iter3);
    int EXAM_DECL(iterswp0);
    int EXAM_DECL(iterswp1);
    int EXAM_DECL(iterswp2);
    int EXAM_DECL(iterswp3);
};

class istream_iterator_test
{
  public:
    int EXAM_DECL(istmit1);
    int EXAM_DECL(copy_n_test);
};

class ioiter_test
{
  public:
    int EXAM_DECL(ioiterat_test);
    int EXAM_DECL(assign_test);
    int EXAM_DECL(assign2_test);
};

#endif // __TEST_ITER_TEST_H
