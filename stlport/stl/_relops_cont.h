// This is an implementation file which
// is intended to be included multiple times with different __STL_ASSOCIATIVE_CONTAINER
// setting

__STL_TEMPLATE_HEADER
inline bool  __STL_CALL operator==(const __STL_TEMPLATE_CONTAINER& __x, 
                                   const __STL_TEMPLATE_CONTAINER& __y) {
  return __x.size() == __y.size() &&
    equal(__x.begin(), __x.end(), __y.begin());
}

__STL_TEMPLATE_HEADER
inline bool  __STL_CALL operator<(const __STL_TEMPLATE_CONTAINER& __x, 
                                  const __STL_TEMPLATE_CONTAINER& __y) {
  return lexicographical_compare(__x.begin(), __x.end(), 
				 __y.begin(), __y.end());
}

__STL_RELOPS_OPERATORS( __STL_TEMPLATE_HEADER , __STL_TEMPLATE_CONTAINER )
    
#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER
__STL_TEMPLATE_HEADER
inline void  __STL_CALL swap(__STL_TEMPLATE_CONTAINER& __x, 
                             __STL_TEMPLATE_CONTAINER& __y) {
  __x.swap(__y);
}
#endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */
