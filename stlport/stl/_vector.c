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
#ifndef __STL_VECTOR_C
#define __STL_VECTOR_C

# if defined ( __STL_NESTED_TYPE_PARAM_BUG )
#  define __pointer__             _Tp*
#  define __const_pointer__       const _Tp*
#  define __size_type__           size_t
# else
#  define __pointer__         pointer
#  define __const_pointer__   const_pointer
#  define __size_type__       size_type
# endif

#  define __iterator__       __pointer__
#  define __const_iterator__ __const_pointer__  

#  undef  vector
#  define vector __WORKAROUND_DBG_RENAME(vector)

__STL_BEGIN_NAMESPACE

template <class _Tp, class _Alloc>
void 
__vector__<_Tp, _Alloc>::reserve(__size_type__ __n) {
  if (capacity() < __n) {
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
void 
__vector__<_Tp, _Alloc>::_M_fill_insert(
				    __iterator__ __position, 
				    __size_type__ __n, const _Tp& __x) {
  if (__n != 0) {
    if (size_type(this->_M_end_of_storage._M_data - this->_M_finish) >= __n) {
      _Tp __x_copy = __x;
      const size_type __elems_after = this->_M_finish - __position;
      pointer __old_finish = this->_M_finish;
      if (__elems_after > __n) {
        __uninitialized_copy(this->_M_finish - __n, this->_M_finish, this->_M_finish, _IsPODType());
        this->_M_finish += __n;
        __copy_backward_ptrs(__position, __old_finish - __n, __old_finish, _TrivialAss());
        __STLPORT_STD::fill(__position, __position + __n, __x_copy);
      }
      else {
        uninitialized_fill_n(this->_M_finish, __n - __elems_after, __x_copy);
        this->_M_finish += __n - __elems_after;
        __uninitialized_copy(__position, __old_finish, this->_M_finish, _IsPODType());
        this->_M_finish += __elems_after;
        __STLPORT_STD::fill(__position, __old_finish, __x_copy);
      }
    }
    else 
      _M_insert_overflow(__position, __x, _IsPODType(), __n);
  }
}

template <class _Tp, class _Alloc>
__vector__<_Tp,_Alloc>& 
__vector__<_Tp,_Alloc>::operator=(const __vector__<_Tp, _Alloc>& __x)
{
  if (&__x != this) {
    const size_type __xlen = __x.size();
    if (__xlen > capacity()) {
      pointer __tmp = _M_allocate_and_copy(__xlen, (const_pointer)__x._M_start+0, (const_pointer)__x._M_finish+0);
      _M_clear();
      this->_M_start = __tmp;
      this->_M_end_of_storage._M_data = this->_M_start + __xlen;
    }
    else if (size() >= __xlen) {
      pointer __i = __copy_ptrs((const_pointer)__x._M_start+0, (const_pointer)__x._M_finish+0, this->_M_start, _TrivialAss());
      _Destroy(__i, this->_M_finish);
    }
    else {
      __copy_ptrs((const_pointer)__x._M_start, (const_pointer)__x._M_start + size(), this->_M_start, _TrivialAss());
      __uninitialized_copy((const_pointer)__x._M_start + size(), (const_pointer)__x._M_finish+0, this->_M_finish, _IsPODType());
    }
    this->_M_finish = this->_M_start + __xlen;
  }
  return *this;
}

template <class _Tp, class _Alloc>
void __vector__<_Tp, _Alloc>::_M_fill_assign(size_t __n, const _Tp& __val) {
  if (__n > capacity()) {
    __vector__<_Tp, _Alloc> __tmp(__n, __val, get_allocator());
    __tmp.swap(*this);
  }
  else if (__n > size()) {
    fill(begin(), end(), __val);
    this->_M_finish = __STLPORT_STD::uninitialized_fill_n(this->_M_finish, __n - size(), __val);
  }
  else
    erase(__STLPORT_STD::fill_n(begin(), __n, __val), end());
}

__STL_END_NAMESPACE

# undef __pointer__
# undef __const_pointer__
# undef __size_type__
# undef __iterator__
# undef __const_iterator__
# undef vector

#endif /*  __STL_VECTOR_C */

      // Local Variables:
	// mode:C++
	// End:
