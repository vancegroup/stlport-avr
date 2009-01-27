#ifndef __TEST_RNDSHF_TEST_H
#define __TEST_RNDSHF_TEST_H

#define __FIT_EXAM

#include <exam/suite.h>

class rnd_shuffle_test
{
  class MyRandomGenerator
  {
    public:
      unsigned long operator()(unsigned long n_)
      {
        return rand() % n_;
      }
  };

  public:
    int EXAM_DECL(rndshuf0);
    int EXAM_DECL(rndshuf1);
};

#endif // __TEST_RNDSHF_TEST_H
