#ifndef __TEST_PARTITION_TEST_H
#define __TEST_PARTITION_TEST_H

#define __FIT_EXAM

#include <exam/suite.h>

class partition_test
{
  public:
    int EXAM_DECL(ptition0);
    int EXAM_DECL(ptition1);
    int EXAM_DECL(stblptn0);
    int EXAM_DECL(stblptn1);

  protected:
    struct less_n {
      less_n(int limit, size_t &nb_calls)
        : _limit(limit), _nb_calls(nb_calls) {}

      bool operator() (int a_) const {
        ++_nb_calls;
        return a_ < _limit;
      }

      int _limit;
      size_t &_nb_calls;

    private:
      //explicitely defined as private to avoid warnings:
      less_n& operator = (less_n const&);
    };
};

#endif // __TEST_PARTITION_TEST_H
