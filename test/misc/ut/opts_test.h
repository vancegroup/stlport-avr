// -*- C++ -*- Time-stamp: <09/06/06 00:36:12 ptr>

/*
 * Copyright (c) 2008
 * Petr Ovtchenkov
 *
 * Licensed under the Academic Free License Version 3.0
 *
 */

#ifndef __OPTS_TEST_H
#define __OPTS_TEST_H

#define FIT_EXAM

#include <exam/suite.h>

class opts_test
{
  public:
    // implementation
    int EXAM_DECL(flag_option);
    int EXAM_DECL(flag_option_long);
    int EXAM_DECL(int_option);
    int EXAM_DECL(int_option_long);
    int EXAM_DECL(add_check_flag);
    int EXAM_DECL(add_get_opt);
    int EXAM_DECL(option_position);
    int EXAM_DECL(defaults);
    int EXAM_DECL(bad_option);
    int EXAM_DECL(bad_argument);
    int EXAM_DECL(unexpected_argument);
    int EXAM_DECL(missing_argument);
    int EXAM_DECL(multiple);
    int EXAM_DECL(compound);
    int EXAM_DECL(multiple_compound);
    int EXAM_DECL(args);
    int EXAM_DECL(stop);
    int EXAM_DECL(user_defined);
    int EXAM_DECL(autocomplement);
    int EXAM_DECL(autocomplement_failure);
    int EXAM_DECL(multiple_args);
    int EXAM_DECL(help);
    int EXAM_DECL(long_string);
    int EXAM_DECL(named_param);
    int EXAM_DECL(z_bug);
    int EXAM_DECL(z_bug_reorder);
};

#endif // __MISC_TEST_H
