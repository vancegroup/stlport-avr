#ifndef __TEST_CODECVT_TEST_H
#define __TEST_CODECVT_TEST_H

#define __FIT_EXAM

#include <exam/suite.h>

class codecvt_test
{
  public:
    int EXAM_DECL(variable_encoding);
    int EXAM_DECL(in_out_test);
    int EXAM_DECL(length_test);
    int EXAM_DECL(imbue_while_reading);

    int EXAM_DECL(partial_conversion);
    int EXAM_DECL(eol);
    int EXAM_DECL(_936_to_wchar);
    int EXAM_DECL(utf8_to_wchar);
    int EXAM_DECL(bad_utf8);
};

#endif // __TEST_CODECVT_H
