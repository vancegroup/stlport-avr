// -*- C++ -*- Time-stamp: <2010-12-13 20:41:53 ptr>

/*
 * Copyright (c) 2007, 2008, 2010
 * Petr Ovtchenkov
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

#ifndef __TEST_TYPE_TRAITS_TEST_H
#define __TEST_TYPE_TRAITS_TEST_H

#define __FIT_EXAM

#include <exam/suite.h>

class type_traits_test
{
  public:
    // implementation
    int EXAM_DECL(type_traits_internals);
    // [20.4.4.1]
    int EXAM_DECL(type_traits_is_void);
    int EXAM_DECL(type_traits_is_integral);
    int EXAM_DECL(type_traits_is_floating_point);
    int EXAM_DECL(type_traits_is_array);
    int EXAM_DECL(type_traits_is_pointer);
    int EXAM_DECL(type_traits_is_lvalue_reference);
    int EXAM_DECL(type_traits_is_rvalue_reference);
    int EXAM_DECL(type_traits_is_rvalue_reference_neg);
    int EXAM_DECL(type_traits_is_member_object_pointer);
    int EXAM_DECL(type_traits_is_member_function_pointer);
    int EXAM_DECL(type_traits_is_enum);
    int EXAM_DECL(type_traits_is_union);
    int EXAM_DECL(type_traits_is_class);
    int EXAM_DECL(type_traits_is_function);

    // [20.4.4.2]
    int EXAM_DECL(type_traits_is_reference);
    int EXAM_DECL(type_traits_is_arithmetic);
    int EXAM_DECL(type_traits_is_fundamental);
    int EXAM_DECL(type_traits_is_object);
    int EXAM_DECL(type_traits_is_scalar);
    int EXAM_DECL(type_traits_is_compound);
    int EXAM_DECL(type_traits_is_member_pointer);

    // [20.4.4.3]
    int EXAM_DECL(type_traits_is_const);
    int EXAM_DECL(type_traits_is_volatile);
    int EXAM_DECL(type_traits_is_trivial);
    int EXAM_DECL(type_traits_is_standard_layout);
    int EXAM_DECL(type_traits_is_pod);
    int EXAM_DECL(type_traits_is_pod_compiler_supp);
    int EXAM_DECL(type_traits_is_empty);

    int EXAM_DECL(is_constructible);
    int EXAM_DECL(is_assignable);
    int EXAM_DECL(is_destructible);

    int EXAM_DECL(is_trivially_copyable);
    // aux
    // int EXAM_DECL(type_traits_has_x_ctor);

    // int EXAM_DECL(ratio);
};

#endif // __TEST_TYPE_TRAITS_TEST_H
