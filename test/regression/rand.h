#ifndef _rand_h
#define _rand_h
#include <cstdlib>
class MyRandomGenerator
{
  public:
    unsigned long operator()(unsigned long n_)
      {
      return rand() % n_;
      }
};

#endif // _rand_h
