// This is an implementation file which
// is intended to be included multiple times with different _STLP_ASSOCIATIVE_CONTAINER
// setting

#ifndef _STLP_EQUAL_OPERATOR_SPECIALIZED
_STLP_TEMPLATE_HEADER
inline bool  _STLP_CALL operator==(const _STLP_TEMPLATE_CONTAINER& __x, 
                                   const _STLP_TEMPLATE_CONTAINER& __y) {
  return __x.size() == __y.size() &&
    equal(__x.begin(), __x.end(), __y.begin());
}
#endif /* _STLP_EQUAL_OPERATOR_SPECIALIZED */

_STLP_TEMPLATE_HEADER
inline bool  _STLP_CALL operator<(const _STLP_TEMPLATE_CONTAINER& __x, 
                                  const _STLP_TEMPLATE_CONTAINER& __y) {
  return lexicographical_compare(__x.begin(), __x.end(), 
				 __y.begin(), __y.end());
}

_STLP_RELOPS_OPERATORS( _STLP_TEMPLATE_HEADER , _STLP_TEMPLATE_CONTAINER )
    
#ifdef _STLP_FUNCTION_TMPL_PARTIAL_ORDER
_STLP_TEMPLATE_HEADER
inline void  _STLP_CALL swap(_STLP_TEMPLATE_CONTAINER& __x, 
                             _STLP_TEMPLATE_CONTAINER& __y) {
  __x.swap(__y);
}
#endif /* _STLP_FUNCTION_TMPL_PARTIAL_ORDER */

#ifdef _STLP_CLASS_PARTIAL_SPECIALIZATION
_STLP_TEMPLATE_HEADER
struct __partial_move_traits<_STLP_TEMPLATE_CONTAINER > {
  typedef __true_type supported;
};

_STLP_TEMPLATE_HEADER
struct __action_on_move<_STLP_TEMPLATE_CONTAINER > {
  typedef __true_type swap;
};

/*
_STLP_TEMPLATE_HEADER
struct __full_move_traits<_STLP_TEMPLATE_CONTAINER > {
  typedef __true_type supported;
};
*/
#endif /* _STLP_CLASS_PARTIAL_SPECIALIZATION */
