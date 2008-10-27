// -*- C++ -*- Time-stamp: <08/10/28 00:09:34 ptr>

/*
 * Copyright (c) 2004-2008
 * Petr Ovtchenkov
 *
 * Copyright (c) 2004-2008
 * Francois Dumont
 *
 * Licensed under the Academic Free License Version 3.0
 *
 */

#ifndef __TEST_STRING_TEST_H
#define __TEST_STRING_TEST_H

#define FIT_EXAM

#include <exam/suite.h>

class string_test
{
  public:
    int EXAM_DECL(constructor);
    int EXAM_DECL(trivial_char_compare);
    int EXAM_DECL(reserve);
    int EXAM_DECL(assign);
    int EXAM_DECL(erase);
    int EXAM_DECL(data);
    int EXAM_DECL(c_str);
    int EXAM_DECL(null_char);
    int EXAM_DECL(insert);
    int EXAM_DECL(replace);
    int EXAM_DECL(resize);
    int EXAM_DECL(short_string);
    int EXAM_DECL(find);
    int EXAM_DECL(bogus_edge_find);
    int EXAM_DECL(rfind);
    int EXAM_DECL(find_last_of);
    int EXAM_DECL(find_last_not_of);
    int EXAM_DECL(copy);
    int EXAM_DECL(mt);
    int EXAM_DECL(short_string_optim_bug);
    int EXAM_DECL(compare);
    int EXAM_DECL(template_expression);
    int EXAM_DECL(te_tmp);
    int EXAM_DECL(oper_tmp);
    int EXAM_DECL(template_wexpression);
    int EXAM_DECL(io);
    int EXAM_DECL(allocator_with_state);
    int EXAM_DECL(capacity);
    int EXAM_DECL(concat24);
};

#endif // __TEST_STRING_TEST_H
