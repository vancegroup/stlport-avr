/*
 * Copyright (c) 2012
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

#include "stlport_prefix.h"

#include <string>
#include <memory>

_STLP_BEGIN_NAMESPACE

static const string bad_weak_ptr_str( "bad_weak_ptr" );

bad_weak_ptr::bad_weak_ptr() : /* noexcept */
      __Named_exception( bad_weak_ptr_str )
{ }

_STLP_END_NAMESPACE
