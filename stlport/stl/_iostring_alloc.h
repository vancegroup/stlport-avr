/*
 * Copyright (c) 2004
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

 /*
  * This is an internal allocator for the iostream internal strings. Its goals
  * is to improve performance limitating the number of dynamic allocation that
  * could occur when requesting a big float ouput for instance. This allocator
  * is not standard conformant as it has an internal state (the static buffer)
  */

 
# ifndef _STLP_IOSTRING_ALLOC_H
# define _STLP_IOSTRING_ALLOC_H

# ifndef _STLP_INTERNAL_ALLOC_H
#  include <stl/_alloc.h>
# endif /* _STLP_INTERNAL_ALLOC_H */

_STLP_BEGIN_NAMESPACE

template <class _CharT>
class __iostring_allocator : public allocator<_CharT> {

  typedef allocator<_CharT> _Base;
  enum { _BUF_SIZE = 257 };
  _CharT _M_static_buf[_BUF_SIZE];

public:
# if defined (_STLP_MEMBER_TEMPLATE_CLASSES)
  template <class _Tp1> struct rebind {
    typedef allocator<_Tp1> other;
  };
# endif

  _CharT* allocate(size_type __n, const void* __ptr = 0) {
    if (__n > _BUF_SIZE) {
      return _Base::allocate(__n, __ptr);
    }
    return _M_static_buf;
  }
  // __p is permitted to be a null pointer, only if n==0.
  void deallocate(pointer __p, size_type __n) {
    if (__p != _M_static_buf) _Base::deallocate(__p, __n);
  }
};

_STLP_END_NAMESPACE

# endif /* _STLP_IOSTRING_ALLOC_H */
