/*
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

/*
 * All the necessary methods used for template expressions with basic_string
 * This file do not have to be macro guarded as it is only used in the _string.h
 * file and it is a part of the basic_string definition.
 */

public:
  template <class _Left, class _Right, class _StorageDir>
  basic_string(__bstr_sum<value_type, traits_type, _Alloc, _Left, _Right, _StorageDir> const& __s) 
    : _String_base<_CharT,_Alloc>(allocator_type(), __s.size()){
    _M_append_sum(__s);
  }

  template <class _Left, class _Right, class _StorageDir>
  basic_string(__bstr_sum<value_type, traits_type, _Alloc, _Left, _Right, _StorageDir> const& __s,
               size_type __pos, size_type __n = npos, 
               const allocator_type& __a = allocator_type())
    : _String_base<_CharT,_Alloc>(__a, (__pos <= __s.size())?((min) (__n, __s.size() - __pos)):0) {
    size_type __size = __s.size();
    if (__pos > __size)
      this->_M_throw_out_of_range();
    else
      _M_append_sum_pos(__s, __pos, (min) (__n, __size - __pos));
  }

  template <class _Left, class _Right, class _StorageDir>
  _Self& operator=(__bstr_sum<value_type, traits_type, _Alloc, _Left, _Right, _StorageDir> const& __s) {
    return _M_assign_sum(__s);
  }

  template <class _Left, class _Right, class _StorageDir>
  _Self& operator+=(__bstr_sum<value_type, traits_type, _Alloc, _Left, _Right, _StorageDir> const& __s) {
    return _M_append_sum(__s);
  }

  template <class _Left, class _Right, class _StorageDir>
  _Self& append(__bstr_sum<value_type, traits_type, _Alloc, _Left, _Right, _StorageDir> const& __s) {
    return _M_append_sum(__s); 
  }

  template <class _Left, class _Right, class _StorageDir>
  _Self& append(__bstr_sum<value_type, traits_type, _Alloc, _Left, _Right, _StorageDir> const& __s,
                size_type __pos, size_type __n) {
   if (__pos > __s.size())
     this->_M_throw_out_of_range();
   return _M_append_sum(__s, __pos, __n);
  }

  template <class _Left, class _Right, class _StorageDir>
  _Self& assign(__bstr_sum<value_type, traits_type, _Alloc, _Left, _Right, _StorageDir> const& __s) {
    return _M_assign_sum(__s); 
  }

  template <class _Left, class _Right, class _StorageDir>
  _Self& assign(__bstr_sum<value_type, traits_type, _Alloc, _Left, _Right, _StorageDir> const& __s, 
                size_type __pos, size_type __n) {
    if (__pos > __s.size())
      this->_M_throw_out_of_range();
    return _M_assign_sum(__s, __pos, __n);
  }

private:
  value_type* _M_append_fast(__char_wrapper<value_type> __c, value_type *__buf) {
     _STLP_STD::_Copy_Construct(__buf, __c.getValue());
     return __buf + 1;
  }
  value_type* _M_append_fast(__cstr_wrapper<value_type> const& __s, value_type *__buf) {
    return uninitialized_copy(__s.c_str(), __s.c_str() + __s.size(), __buf);
  }
  value_type* _M_append_fast(__bstr_wrapper<value_type, traits_type, _Alloc> __s, value_type *__buf) {
    return _M_append_fast(__s.b_str(), __buf);
  }
  value_type* _M_append_fast(_Self const& __s, value_type *__buf) {
    return uninitialized_copy(__s.begin(), __s.begin() + __s.size(), __buf);
  }
  value_type* _M_append_fast(__sum_storage_elem<value_type, traits_type, _Alloc> const& __s, value_type *__buf) {
    return __buf;
  }
  template <class _Left, class _Right, class _StorageDir>
  value_type* _M_append_fast(__bstr_sum<value_type, traits_type, _Alloc, _Left, _Right, _StorageDir> const& __s, value_type *__buf) {
    return _M_append_fast(__s.getRhs(), _M_append_fast(__s.getLhs(), __buf));
  }


  value_type* _M_append_fast_pos(__char_wrapper<value_type> __c, value_type *__buf, size_type /*__pos*/, size_type /*__n*/) {
     _STLP_STD::_Copy_Construct(__buf, __c.getValue());
     return __buf + 1;
  }
  value_type* _M_append_fast_pos(__cstr_wrapper<value_type> const& __s, value_type *__buf, 
                             size_type __pos, size_type __n) {
    return uninitialized_copy(__s.c_str() + __pos, __s.c_str() + (min)(__pos + __n, __s.size()), __buf);
  }
  value_type* _M_append_fast_pos(__bstr_wrapper<value_type, traits_type, _Alloc> __s, value_type *__buf, 
                             size_type __pos, size_type __n) {
    return _M_append_fast_pos(__s.b_str(), __buf, __pos, __n);
  }
  value_type* _M_append_fast_pos(_Self const& __s, value_type *__buf, 
                             size_type __pos, size_type __n) {
    return uninitialized_copy(__s.begin() + __pos, __s.begin() + (min)(__pos + __n, __s.size()), __buf);
  }
  value_type* _M_append_fast_pos(__sum_storage_elem<value_type, traits_type, _Alloc> const& __s, value_type *__buf, 
                             size_type __pos, size_type __n) {
    return __buf;
  }

  template <class _Left, class _Right, class _StorageDir>
  value_type* _M_append_fast_pos(__bstr_sum<value_type, traits_type, _Alloc, _Left, _Right, _StorageDir> const& __s, value_type *__buf,
                                 size_type __pos, size_type __n) {
    if (__n == 0) {
      return __buf;
    }
    if (__pos < __s.getLhs().size()) {
      if (__n < (__s.getLhs().size() - __pos)) {
        return _M_append_fast_pos(__s.getLhs(), __buf, __pos, __n);
      } else {
        return _M_append_fast_pos(__s.getRhs(), _M_append_fast_pos(__s.getLhs(), __buf, __pos, __n),
                              0, __n - (__s.getLhs().size() - __pos));
      }
    } else {
      return _M_append_fast_pos(__s.getRhs(), __buf, __pos - __s.getLhs().size(), __n);
    }
  }

  template <class _Left, class _Right, class _StorageDir>
  _Self& _M_assign_overflow (size_type __new_size, __bstr_sum<value_type, traits_type, _Alloc, _Left, _Right, _StorageDir> const& __s) {
#ifdef _STLP_USE_SHORT_STRING_OPTIM
    if (__new_size < _DEFAULT_SIZE + 1)
      __new_size = _DEFAULT_SIZE + 1;
#endif /* _STLP_USE_SHORT_STRING_OPTIM */
    pointer __new_start = this->_M_end_of_storage.allocate(__new_size);
    pointer __new_finish = __new_start;
    _STLP_TRY {
      __new_finish = _M_append_fast(__s, __new_start);
      _M_construct_null(__new_finish);
    }
    _STLP_UNWIND((_STLP_STD::_Destroy_Range(__new_start,__new_finish),
                  this->_M_end_of_storage.deallocate(__new_start,__new_size)))
    this->_M_destroy_range();
    this->_M_deallocate_block();
    this->_M_reset(__new_start, __new_finish, __new_start + __new_size);
    return *this;
  }

  template <class _Left, class _Right, class _StorageDir>
  _Self& _M_assign_overflow_pos (size_type __new_size, __bstr_sum<value_type, traits_type, _Alloc, _Left, _Right, _StorageDir> const& __s,
                                 size_type __pos, size_type __n) {
#ifdef _STLP_USE_SHORT_STRING_OPTIM
    if (__new_size < _DEFAULT_SIZE + 1)
      __new_size = _DEFAULT_SIZE + 1;
#endif /* _STLP_USE_SHORT_STRING_OPTIM */
    pointer __new_start = this->_M_end_of_storage.allocate(__new_size);
    pointer __new_finish = __new_start;
    _STLP_TRY {
      __new_finish = _M_append_fast_pos(__s, __new_start, __pos, __n);
      _M_construct_null(__new_finish);
    }
    _STLP_UNWIND((_STLP_STD::_Destroy_Range(__new_start,__new_finish),
                  this->_M_end_of_storage.deallocate(__new_start,__new_size)))
    this->_M_destroy_range();
    this->_M_deallocate_block();
    this->_M_reset(__new_start, __new_finish, __new_start + __new_size);
    return *this;
  }

  template <class _Left, class _Right, class _StorageDir>
  _Self& _M_assign_sum (__bstr_sum<value_type, traits_type, _Alloc, _Left, _Right, _StorageDir> const& __s) {
    //TODO: We systematically use a new allocation to avoid the self referencing trouble, try to avoid it.
    size_type __len = size();
    const size_type __s_size = __s.size();
    if (__s_size > max_size() || __len > (max_size() - __s_size))
      this->_M_throw_length_error();
    if (__s_size > __len) {
      __len = __len + (max)(__len, __s_size) + 1;
    }
    return _M_assign_overflow(__len, __s);
  }

  template <class _Left, class _Right, class _StorageDir>
  _Self& _M_assign_sum_pos (__bstr_sum<value_type, traits_type, _Alloc, _Left, _Right, _StorageDir> const& __s,
                            size_type __pos, size_type __n = npos) {
    //TODO: We systematically use a new allocation to avoid the self referencing trouble, try to avoid it.
    size_type __len = size();
    const size_type __s_size = (min) (__s.size() - __pos, __n);
    if (__s_size > max_size() || __len > (max_size() - __s_size))
      this->_M_throw_length_error();
    if (__s_size > capacity()) {
      __len = __len + (max)(__len, __s_size) + 1;
    }
    return _M_assign_overflow_pos(__len, __s, __pos, __n);
  }

  template <class _Left, class _Right, class _StorageDir>
  _Self& _M_append_sum (__bstr_sum<value_type, traits_type, _Alloc, _Left, _Right, _StorageDir> const& __s) {
    //TODO: We systematically use a new allocation to avoid the self referencing trouble, try to avoid it.
    const size_type __old_size = size();
    size_type __s_size = __s.size();
    if (__s_size > max_size() || __old_size > (max_size() - __s_size))
      this->_M_throw_length_error();
    size_type __len = capacity();
    if (__old_size + __s_size > __len)
      __len = __old_size + (max)(__old_size, __s_size) + 1;
    return _M_assign_overflow(__len, __s);
  }

  template <class _Left, class _Right, class _StorageDir>
  _Self& _M_append_sum_pos (__bstr_sum<value_type, traits_type, _Alloc, _Left, _Right, _StorageDir> const& __s, 
                            size_type __pos, size_type __n = npos) {
    //TODO: We systematically use a new allocation to avoid the self referencing trouble, try to avoid it.
    const size_type __old_size = size();
    size_type __s_size = (min)(__s.size() - __pos, __n);
    if (__s_size > max_size() || __old_size > (max_size() - __s_size))
      this->_M_throw_length_error();
    size_type __len = capacity();
    if (__old_size + __s_size > __len)
      __len = __old_size + (max)(__old_size, __s_size) + 1;
    return _M_assign_overflow_pos(__len, __s, __pos, __n);
  }
