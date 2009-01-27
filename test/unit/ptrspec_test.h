#ifndef __TEST_PTRSPEC_TEST_H
#define __TEST_PTRSPEC_TEST_H

#define __FIT_EXAM

#include <exam/suite.h>

class ptrspec_test
{
  public:
  /// this seems to be compile only test but...
    int EXAM_DECL(ptr_specialization_test);
    int EXAM_DECL(function_pointer);

  protected:
    template <class _Tp>
    struct unary_pred {
      bool operator () (_Tp *__ptr) const {
       return *__ptr == 0;
      }
    };

    template <class _Tp>
    struct binary_pred {
      bool operator () (_Tp *__first, _Tp *__second) const {
        return *__first < *__second;
      }
    };
};

#endif // __TEST_PTRSPEC_TEST_H
