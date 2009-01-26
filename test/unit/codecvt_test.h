#ifndef __TEST_CODECVT_TEST_H
#define __TEST_CODECVT_TEST_H

#define FIT_EXAM

#include <exam/suite.h>

class codecvt_test
{
  public:
    int EXAM_DECL(variable_encoding);
    int EXAM_DECL(in_out_test);
    int EXAM_DECL(length_test);
    int EXAM_DECL(imbue_while_reading);
    int EXAM_DECL(special_encodings);
};

#endif // __TEST_CODECVT_H
