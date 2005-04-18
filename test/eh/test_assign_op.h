/***********************************************************************************
  test_assign_op.h
  
    SUMMARY: Test functor template for assignment operators.

 * Copyright (c) 1997
 * Mark of the Unicorn, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Mark of the Unicorn makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
    
***********************************************************************************/
#ifndef test_assign_op_H_
#define test_assign_op_H_

# include "Prefix.h"
# ifdef EH_NEW_HEADERS
#  include <cassert>
# else
#  include <assert.h>
# endif
#include "nc_alloc.h"

# if defined(_STLP_ASSERTIONS) || defined(_STLP_DEBUG)
#  define _STLP_FILE_UNIQUE_ID TEST_ASSIGN_OP_H
_STLP_INSTRUMENT_FILE();
# endif

template <class T>
struct test_assign_op
{
  test_assign_op( const T& src )
    : source(src)
  {
        gTestController.SetCurrentTestName("assignment operator");
    }
  
  void operator()( T& t ) const
  {
    t = source;
    
    // Prevent simulated failures during verification
    gTestController.CancelFailureCountdown();
    EH_ASSERT( source == t );
  }
private:
  const T& source;
};


# if defined(_STLP_ASSERTIONS) || defined(_STLP_DEBUG)
#  undef _STLP_FILE_UNIQUE_ID
# endif

#endif // test_assign_op_H_
