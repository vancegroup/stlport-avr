/*
 * Copyright (c) 1999
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1999 
 * Boris Fomitchev
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

# ifndef __STL_NUM_PUT_H
#  define __STL_NUM_PUT_H

#include "stlport_prefix.h"

#include <stl/_num_put.h>
#include <stl/_ostream.h>

__STL_BEGIN_NAMESPACE

// Note that grouping[0] is the number of digits in the *rightmost* group.
// We assume, without checking, that *last is null and that there is enough
// space in the buffer to extend the number past [first, last).
template <class Char>
ptrdiff_t 
__insert_grouping_aux(Char* first, Char* last, const string& grouping,
                      Char separator, Char Plus, Char Minus,
		      int basechars)
{
  typedef string::size_type str_size;

  if (first == last)
    return 0;

  int sign = 0;

  if (*first == Plus || *first == Minus) {
    sign = 1;
    ++first;
  }
 
  first += basechars;
  str_size n = 0;               // Index of the current group.
  Char* cur_group = last;       // Points immediately beyond the rightmost
                                // digit of the current group.
  int groupsize = 0;            // Size of the current group.
  
  while (true) {
    groupsize = n < grouping.size() ? grouping[n] : groupsize;
    ++n;

    if (groupsize <= 0 || groupsize >= cur_group - first)
      break;

    // Insert a separator character just before position cur_group - groupsize
    cur_group -= groupsize;
    ++last;
    copy_backward(cur_group, last, last + 1);
    *cur_group = separator;
  }

  return (last - first) + sign + basechars;
}

__STL_END_NAMESPACE

# endif
