// This is an implementation file which
// is intended to be included multiple times with different __STL_ASSOCIATIVE_CONTAINER
// setting

template <class _Key, class _Compare, class _Alloc>
inline bool __STL_CALL operator==(const __STL_SET_FLAVOR<_Key,_Compare,_Alloc>& __x, 
                       const __STL_SET_FLAVOR<_Key,_Compare,_Alloc>& __y) {
  return __x.size() == __y.size() &&
    equal(__x.begin(), __x.end(), __y.begin());
}

template <class _Key, class _Compare, class _Alloc>
inline bool __STL_CALL operator<(const __STL_SET_FLAVOR<_Key,_Compare,_Alloc>& __x, 
                      const __STL_SET_FLAVOR<_Key,_Compare,_Alloc>& __y) {
  return lexicographical_compare(__x.begin(), __x.end(), 
				 __y.begin(), __y.end());
}

#ifdef __STL_USE_SEPARATE_RELOPS_NAMESPACE

template <class _Key, class _Compare, class _Alloc>
inline bool __STL_CALL operator!=(const __STL_SET_FLAVOR<_Key,_Compare,_Alloc>& __x, 
                       const __STL_SET_FLAVOR<_Key,_Compare,_Alloc>& __y) {
  return !(__x == __y);
}

template <class _Key, class _Compare, class _Alloc>
inline bool __STL_CALL operator>(const __STL_SET_FLAVOR<_Key,_Compare,_Alloc>& __x, 
                      const __STL_SET_FLAVOR<_Key,_Compare,_Alloc>& __y) {
  return __y < __x;
}

template <class _Key, class _Compare, class _Alloc>
inline bool __STL_CALL operator<=(const __STL_SET_FLAVOR<_Key,_Compare,_Alloc>& __x, 
                       const __STL_SET_FLAVOR<_Key,_Compare,_Alloc>& __y) {
  return !(__y < __x);
}

template <class _Key, class _Compare, class _Alloc>
inline bool __STL_CALL operator>=(const __STL_SET_FLAVOR<_Key,_Compare,_Alloc>& __x, 
                       const __STL_SET_FLAVOR<_Key,_Compare,_Alloc>& __y) {
  return !(__x < __y);
}
#endif /* __STL_USE_SEPARATE_RELOPS_NAMESPACE */

#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER

template <class _Key, class _Compare, class _Alloc>
inline void __STL_CALL swap(__STL_SET_FLAVOR<_Key,_Compare,_Alloc>& __x, 
                 __STL_SET_FLAVOR<_Key,_Compare,_Alloc>& __y) {
  __x.swap(__y);
}

#endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */
