// -*- C++ -*- Time-stamp: <10/06/02 15:17:35 ptr>

/*
 * Copyright (c) 2004-2008
 * Petr Ovtchenkov
 *
 * Copyright (c) 2004-2008
 * Francois Dumont
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

#ifndef __TEST_STRING_TEST_H
#define __TEST_STRING_TEST_H

#define __FIT_EXAM

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
    int EXAM_DECL(assign_from_char);
};

#endif // __TEST_STRING_TEST_H
