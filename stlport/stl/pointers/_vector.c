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
#ifndef _STLP_SPECIALIZED_VECTOR_C
#define _STLP_SPECIALIZED_VECTOR_C

template <class _Alloc>
void vector<void*, _Alloc>::reserve(size_type __n) {
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

template <class _Alloc>
void vector<void*, _Alloc>::_M_fill_insert(iterator __position, 
                                           size_type __n, void *__x) {
  if (__n != 0) {
    if (size_type(this->_M_end_of_storage._M_data - this->_M_finish) >= __n) {
      const size_type __elems_after = this->_M_finish - __position;
      pointer __old_finish = this->_M_finish;
      if (__elems_after > __n) {
        __copy_trivial(this->_M_finish - __n, this->_M_finish, this->_M_finish);
        this->_M_finish += __n;
        __copy_backward_ptrs(__position, __old_finish - __n, __old_finish, _TrivialAss());
        _STLP_STD::fill(__position, __position + __n, __x);
      }
      else {
        uninitialized_fill_n(this->_M_finish, __n - __elems_after, __x);
        this->_M_finish += __n - __elems_after;
        __copy_trivial(__position, __old_finish, this->_M_finish);
        this->_M_finish += __elems_after;
        _STLP_STD::fill(__position, __old_finish, __x);
      }
    }
    else 
      _M_insert_overflow(__position, __x, __n);
  }
}

template <class _Alloc>
vector<void*,_Alloc>& vector<void*,_Alloc>::operator=(const vector<void*, _Alloc>& __x)
{
  if (&__x != this) {
    const size_type __xlen = __x.size();
    if (__xlen > capacity()) {
      pointer __tmp = _M_allocate_and_copy(__xlen, __CONST_CAST(const_pointer, __x._M_start), 
                                                   __CONST_CAST(const_pointer, __x._M_finish));
      _M_clear();
      this->_M_start = __tmp;
      this->_M_end_of_storage._M_data = this->_M_start + __xlen;
    }
    else if (size() >= __xlen) {
      __copy_trivial(__x._M_start, __x._M_finish, this->_M_start);
    }
    else {
      __copy_trivial(__x._M_start, __x._M_start + size(), this->_M_start);
      __ucopy_trivial(__x._M_start + size(), __x._M_finish, this->_M_finish);
    }
    this->_M_finish = this->_M_start + __xlen;
  }
  return *this;
}

template <class _Alloc>
void vector<void*, _Alloc>::_M_fill_assign(size_t __n, void *__val) {
  if (__n > capacity()) {
    vector<void*, _Alloc> __tmp(__n, __val, get_allocator());
    __tmp.swap(*this);
  }
  else if (__n > size()) {
    fill(begin(), end(), __val);
    this->_M_finish = _STLP_STD::fill_n(this->_M_finish, __n - size(), __val);
  }
  else
    erase(_STLP_STD::fill_n(begin(), __n, __val), end());
}

#endif /*  _STLP_SPECIALIZED_VECTOR_C */

  // Local Variables:
	// mode:C++
	// End:
