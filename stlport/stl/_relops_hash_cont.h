// This is an implementation file which
// is intended to be included multiple times with different _STLP_ASSOCIATIVE_CONTAINER
// setting

_STLP_TEMPLATE_HEADER
inline bool _STLP_CALL 
operator==(const _STLP_TEMPLATE_CONTAINER& __hm1, const _STLP_TEMPLATE_CONTAINER& __hm2)
{
  return _STLP_TEMPLATE_CONTAINER::_M_equal(__hm1, __hm2);
}

#ifdef _STLP_USE_SEPARATE_RELOPS_NAMESPACE

_STLP_TEMPLATE_HEADER
inline bool _STLP_CALL 
operator!=(const _STLP_TEMPLATE_CONTAINER& __hm1, const _STLP_TEMPLATE_CONTAINER& __hm2) {
  return !(__hm1 == __hm2);
}

#endif /* _STLP_USE_SEPARATE_RELOPS_NAMESPACE */

#ifdef _STLP_FUNCTION_TMPL_PARTIAL_ORDER

_STLP_TEMPLATE_HEADER
inline void _STLP_CALL 
swap(_STLP_TEMPLATE_CONTAINER& __hm1, _STLP_TEMPLATE_CONTAINER& __hm2)
{
  __hm1.swap(__hm2);
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
