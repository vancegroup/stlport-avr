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

class ostream_iterator_test
{
  public:
    int EXAM_DECL(ostmit0);
};

class ioiter_test
{
  public:
    int EXAM_DECL(ioiterat_test);
    int EXAM_DECL(assign_test);
    int EXAM_DECL(assign2_test);
};

class insert_iter_test
{
  public:
    int EXAM_DECL(insert1);
    int EXAM_DECL(insert2);
};

class binsert_iter_test
{
  public:
    int EXAM_DECL(binsert1);
    int EXAM_DECL(binsert2);
};

class finsert_iter_test
{
  public:
    int EXAM_DECL(finsert1);
    int EXAM_DECL(finsert2);
};

class reviter_test
{
  public:
    int EXAM_DECL(reviter1);
    int EXAM_DECL(reviter2);
    int EXAM_DECL(revbit1);
};

#endif // __TEST_ITER_TEST_H
