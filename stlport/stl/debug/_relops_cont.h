// Local Variables:
// mode:C++
// End:
// This is an implementation file which
// is intended to be included multiple times with different _STLP_ASSOCIATIVE_CONTAINER
// setting

#ifdef _STLP_EXTRA_OPERATORS_FOR_DEBUG

_STLP_TEMPLATE_HEADER
inline  bool _STLP_CALL
operator==(const _STLP_TEMPLATE_CONTAINER& __x, const _STLP_TEMPLATE_CONTAINER& __y) {
  return (const _STLP_TEMPLATE_CONTAINER_BASE&)__x == (const _STLP_TEMPLATE_CONTAINER_BASE&)__y; 
}

_STLP_TEMPLATE_HEADER
inline  bool _STLP_CALL
operator<(const _STLP_TEMPLATE_CONTAINER& __x, const _STLP_TEMPLATE_CONTAINER& __y) {
  return (const _STLP_TEMPLATE_CONTAINER_BASE&)__x < (const _STLP_TEMPLATE_CONTAINER_BASE&)__y; 
}

_STLP_RELOPS_OPERATORS( _STLP_TEMPLATE_HEADER , _STLP_TEMPLATE_CONTAINER )

#endif /* _STLP_EXTRA_OPERATORS_FOR_DEBUG */

#ifdef _STLP_FUNCTION_TMPL_PARTIAL_ORDER

_STLP_TEMPLATE_HEADER
inline void _STLP_CALL swap(_STLP_TEMPLATE_CONTAINER& __x, _STLP_TEMPLATE_CONTAINER& __y) {
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

#endif /* _STLP_CLASS_PARTIAL_SPECIALIZATION */
