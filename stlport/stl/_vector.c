/*
 *
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1997
 * Moscow Center for SPARC Technology
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
#ifndef _STLP_VECTOR_C
#define _STLP_VECTOR_C

# if !defined (_STLP_INTERNAL_VECTOR_H)
#  include <stl/_vector.h>
# endif

#ifdef _STLP_DEBUG
#  undef  vector
#  define vector __WORKAROUND_DBG_RENAME(vector)
#endif

#include <stl/_range_errors.h>

_STLP_BEGIN_NAMESPACE

template <class _Tp, class _Alloc> 
void _Vector_base<_Tp,_Alloc>::_M_throw_length_error() const {
    __stl_throw_length_error("vector");
}

template <class _Tp, class _Alloc> 
void _Vector_base<_Tp, _Alloc>::_M_throw_out_of_range() const {
    __stl_throw_out_of_range("vector");
}

template <class _Tp, class _Alloc>
void _VECTOR_IMPL<_Tp, _Alloc>::reserve(size_type __n) {
  if (capacity() < __n) {
    if (max_size() < __n) {
      this->_M_throw_length_error();
    }

    const size_type __old_size = size();
    pointer __tmp;
    if (this->_M_start) {
      __tmp = _M_allocate_and_copy(__n, this->_M_start, this->_M_finish);
      _M_clear();
    } else {
      __tmp = this->_M_end_of_storage.allocate(__n);
    }
    _M_set(__tmp, __tmp + __old_size, __tmp + __n);
  }
}

template <class _Tp, class _Alloc>
void _VECTOR_IMPL<_Tp, _Alloc>::_M_insert_overflow(pointer __position, const _Tp& __x, const __false_type& /*IsPOD*/,
                                                   size_type __fill_len, bool __atend ) {
  const size_type __old_size = size();
  const size_type __len = __old_size + (max)(__old_size, __fill_len);

  pointer __new_start = this->_M_end_of_storage.allocate(__len);
  pointer __new_finish = __new_start;
  _STLP_TRY {
    __new_finish = __uninitialized_move(this->_M_start, __position, __new_start, __false_type());
    // handle insertion
    if (__fill_len == 1) {
      _Copy_Construct(__new_finish, __x);
      ++__new_finish;
    } else
      __new_finish = __uninitialized_fill_n(__new_finish, __fill_len, __x, __false_type());
    if (!__atend)
      __new_finish = __uninitialized_move(__position, this->_M_finish, __new_finish, __false_type()); // copy remainder
  }
  _STLP_UNWIND((_STLP_STD::_Destroy_Range(__new_start,__new_finish),
               this->_M_end_of_storage.deallocate(__new_start,__len)))

  _STLP_STD::_Destroy_Mvd_Sources(this->_M_start, this->_M_finish);
  this->_M_end_of_storage.deallocate(this->_M_start, this->_M_end_of_storage._M_data - this->_M_start);
  _M_set(__new_start, __new_finish, __new_start + __len);
}

template <class _Tp, class _Alloc>
void _VECTOR_IMPL<_Tp, _Alloc>::_M_insert_overflow(pointer __position, const _Tp& __x, const __true_type& /*IsPOD*/,
                                                   size_type __fill_len, bool __atend ) {
  const size_type __old_size = size();
  const size_type __len = __old_size + (max)(__old_size, __fill_len);

  pointer __new_start = this->_M_end_of_storage.allocate(__len);
  pointer __new_finish = (pointer)__copy_trivial(this->_M_start, __position, __new_start);
  // handle insertion
  __new_finish = fill_n(__new_finish, __fill_len, __x);
  if (!__atend)
    __new_finish = (pointer)__copy_trivial(__position, this->_M_finish, __new_finish); // copy remainder
  _M_clear();
  _M_set(__new_start, __new_finish, __new_start + __len);
}

template <class _Tp, class _Alloc>
void _VECTOR_IMPL<_Tp, _Alloc>::_M_fill_insert(iterator __position,
                                               size_type __n, const _Tp& __x) {
  if (__n != 0) {
    if (size_type(this->_M_end_of_storage._M_data - this->_M_finish) >= __n) {
      _Tp __x_copy = __x;
      const size_type __elems_after = this->_M_finish - __position;
      pointer __old_finish = this->_M_finish;
      if (__elems_after > __n) {
        __uninitialized_move(this->_M_finish - __n, this->_M_finish, this->_M_finish, _IsPODType());
        this->_M_finish += __n;
        __copy_backward_ptrs(__position, __old_finish - __n, __old_finish, _TrivialAss());
        _STLP_STD::fill(__position, __position + __n, __x_copy);
      } else {
        uninitialized_fill_n(this->_M_finish, __n - __elems_after, __x_copy);
        this->_M_finish += __n - __elems_after;
        __uninitialized_move(__position, __old_finish, this->_M_finish, _IsPODType());
        this->_M_finish += __elems_after;
        _STLP_STD::fill(__position, __old_finish, __x_copy);
      }
    } else 
      _M_insert_overflow(__position, __x, _IsPODType(), __n);
  }
}

template <class _Tp, class _Alloc>
_VECTOR_IMPL<_Tp,_Alloc>& _VECTOR_IMPL<_Tp,_Alloc>::operator=(const _VECTOR_IMPL<_Tp, _Alloc>& __x) {
  if (&__x != this) {
    const size_type __xlen = __x.size();
    if (__xlen > capacity()) {
      pointer __tmp = _M_allocate_and_copy(__xlen, __CONST_CAST(const_pointer, __x._M_start)+0, __CONST_CAST(const_pointer, __x._M_finish)+0);
      _M_clear();
      this->_M_start = __tmp;
      this->_M_end_of_storage._M_data = this->_M_start + __xlen;
    } else if (size() >= __xlen) {
      pointer __i = __copy_ptrs(__CONST_CAST(const_pointer, __x._M_start)+0, __CONST_CAST(const_pointer, __x._M_finish)+0, this->_M_start, _TrivialAss());
      _STLP_STD::_Destroy_Range(__i, this->_M_finish);
    } else {
      __copy_ptrs(__CONST_CAST(const_pointer, __x._M_start), __CONST_CAST(const_pointer, __x._M_start) + size(), this->_M_start, _TrivialAss());
      __uninitialized_copy(__CONST_CAST(const_pointer, __x._M_start) + size(), __CONST_CAST(const_pointer, __x._M_finish)+0, this->_M_finish, _IsPODType());
    }
    this->_M_finish = this->_M_start + __xlen;
  }
  return *this;
}

template <class _Tp, class _Alloc>
void _VECTOR_IMPL<_Tp, _Alloc>::_M_fill_assign(size_t __n, const _Tp& __val) {
  if (__n > capacity()) {
    _VECTOR_IMPL<_Tp, _Alloc> __tmp(__n, __val, get_allocator());
    __tmp.swap(*this);
  } else if (__n > size()) {
    fill(begin(), end(), __val);
    this->_M_finish = _STLP_STD::uninitialized_fill_n(this->_M_finish, __n - size(), __val);
  } else
    erase(_STLP_STD::fill_n(begin(), __n, __val), end());
}

template <class _Tp, class _Alloc>
typename _VECTOR_IMPL<_Tp, _Alloc>::iterator _VECTOR_IMPL<_Tp, _Alloc>::insert(iterator __position, const _Tp& __x) {
  size_type __n = __position - begin();
  if (this->_M_finish != this->_M_end_of_storage._M_data) {
    if (__position == end()) {
      _Copy_Construct(this->_M_finish, __x);
      ++this->_M_finish;
    } else {
      _Copy_Construct(this->_M_finish, *(this->_M_finish - 1));
      ++this->_M_finish;
      _Tp __x_copy = __x;
      __copy_backward_ptrs(__position, this->_M_finish - 2, this->_M_finish - 1, _TrivialAss());
      *__position = __x_copy;
    }
  } else
    _M_insert_overflow(__position, __x, _IsPODType(), 1UL);
  return begin() + __n;
}

_STLP_END_NAMESPACE

#ifdef _STLP_DEBUG
# undef vector
#endif

#endif /*  _STLP_VECTOR_C */

// Local Variables:
// mode:C++
// End:
