/*
 *
 * Copyright (c) 2003
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
#ifndef _STLP_LIST_SPECIALIZED_C
#define _STLP_LIST_SPECIALIZED_C

#ifndef _STLP_SPECIALIZED_LIST_H
# include <stl/specialized/_list.h>
#endif


template <class _Alloc>
void list<void*, _Alloc>::resize(size_type __new_size, const_reference __x)
{
  iterator __i = begin();
  size_type __len = 0;
  for ( ; __i != end() && __len < __new_size; ++__i, ++__len);

  if (__len == __new_size)
    erase(__i, end());
  else                          // __i == end()
    insert(end(), __new_size - __len, __x);
}

template <class _Alloc>
list<void*, _Alloc>& list<void*, _Alloc>::operator=(const list<void*, _Alloc>& __x)
{
  if (this != &__x) {
    iterator __first1 = begin();
    iterator __last1 = end();
    const_iterator __first2 = __x.begin();
    const_iterator __last2 = __x.end();
    while (__first1 != __last1 && __first2 != __last2)
      *__first1++ = *__first2++;
    if (__first2 == __last2)
      erase(__first1, __last1);
    else
      insert(__last1, __first2, __last2);
  }
  return *this;
}

template <class _Alloc>
void list<void*, _Alloc>::_M_fill_assign(size_type __n, const_reference __val) {
  iterator __i = begin();
  for ( ; __i != end() && __n > 0; ++__i, --__n)
    *__i = __val;
  if (__n > 0)
    insert(end(), __n, __val);
  else
    erase(__i, end());
}

#endif /*  _STLP_LIST_SPECIALIZED_C */

// Local Variables:
// mode:C++
// End:
