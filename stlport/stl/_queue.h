/*
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

/* NOTE: This is an internal header file, included by other STL headers.
 *   You should not attempt to use it directly.
 */

#ifndef __SGI_STL_INTERNAL_QUEUE_H
#define __SGI_STL_INTERNAL_QUEUE_H

#ifndef __SGI_STL_INTERNAL_DEQUE_H
# include <stl/_deque.h>
#endif

#ifndef __SGI_STL_INTERNAL_VECTOR_H
# include <stl/_vector.h>
#endif

#ifndef __SGI_STL_INTERNAL_HEAP_H
# include <stl/_heap.h>
#endif

#ifndef __SGI_STL_INTERNAL_FUNCTIONAL_H
# include <stl/_function.h>
#endif

__STL_BEGIN_NAMESPACE

# if ! defined ( __STL_LIMITED_DEFAULT_TEMPLATES )
template <class _Tp, class _Sequence = STLPORT::deque<_Tp> >
# elif defined ( __STL_MINIMUM_DEFAULT_TEMPLATE_PARAMS )
#  define __STL_QUEUE_ARGS _Tp
template <class _Tp>
# else
template <class _Tp, class _Sequence>
# endif

class queue {
# if defined ( __STL_QUEUE_ARGS )
  typedef deque<_Tp> _Sequence;
# endif
public:
  typedef typename _Sequence::value_type      value_type;
  typedef typename _Sequence::size_type       size_type;
  typedef          _Sequence                  container_type;

  typedef typename _Sequence::reference       reference;
  typedef typename _Sequence::const_reference const_reference;

protected:
  _Sequence c;
public:
  queue() : c() {}
  explicit queue(const _Sequence& __c) : c(__c) {}

  bool empty() const { return c.empty(); }
  size_type size() const { return c.size(); }
  reference front() { return c.front(); }
  const_reference front() const { return c.front(); }
  reference back() { return c.back(); }
  const_reference back() const { return c.back(); }
  void push(const value_type& __x) { c.push_back(__x); }
  void pop() { c.pop_front(); }
  const _Sequence& _Get_c() const { return c; }
};

# ifndef __STL_QUEUE_ARGS
#  define __STL_QUEUE_ARGS _Tp, _Sequence
#  define __STL_QUEUE_HEADER_ARGS class _Tp, class _Sequence
# else
#  define __STL_QUEUE_HEADER_ARGS class _Tp
# endif

template < __STL_QUEUE_HEADER_ARGS >
inline bool __STL_CALL 
operator==(const queue<__STL_QUEUE_ARGS >& __x, const queue<__STL_QUEUE_ARGS >& __y)
{
  return __x._Get_c() == __y._Get_c();
}

template < __STL_QUEUE_HEADER_ARGS >
inline bool __STL_CALL
operator<(const queue<__STL_QUEUE_ARGS >& __x, const queue<__STL_QUEUE_ARGS >& __y)
{
  return __x._Get_c() < __y._Get_c();
}

__STL_RELOPS_OPERATORS( template < __STL_QUEUE_HEADER_ARGS >, queue<__STL_QUEUE_ARGS > )

# if !(defined ( __STL_LIMITED_DEFAULT_TEMPLATES ) || defined ( __STL_TEMPLATE_PARAM_SUBTYPE_BUG ))
template <class _Tp, class _Sequence = vector<_Tp>, 
          class _Compare = less<__STL_HEADER_TYPENAME _Sequence::value_type> >
# elif defined ( __STL_MINIMUM_DEFAULT_TEMPLATE_PARAMS )
template <class _Tp>
# else
template <class _Tp, class _Sequence, class _Compare>
# endif
class  priority_queue {
# ifdef __STL_MINIMUM_DEFAULT_TEMPLATE_PARAMS
  typedef vector<_Tp> _Sequence;
  typedef less< typename vector<_Tp>::value_type> _Compare; 
# endif
public:
  typedef typename _Sequence::value_type      value_type;
  typedef typename _Sequence::size_type       size_type;
  typedef          _Sequence                  container_type;

  typedef typename _Sequence::reference       reference;
  typedef typename _Sequence::const_reference const_reference;
protected:
  _Sequence c;
  _Compare _comp;		//*TY 01/10/1999 - ugrified comp
public:
  priority_queue() : c() {}
  explicit priority_queue(const _Compare& __x) :  c(), _comp(__x) {}		//*TY 01/10/1999 - ugrified comp
  priority_queue(const _Compare& __x, const _Sequence& __s) 
    : c(__s), _comp(__x) 		//*TY 01/10/1999 - ugrified comp
    { make_heap(c.begin(), c.end(), _comp); }		//*TY 01/10/1999 - ugrified comp

#ifdef __STL_MEMBER_TEMPLATES
  template <class _InputIterator>
  priority_queue(_InputIterator __first, _InputIterator __last) 
    : c(__first, __last) { make_heap(c.begin(), c.end(), _comp); }		//*TY 01/10/1999 - ugrified comp

  template <class _InputIterator>
  priority_queue(_InputIterator __first, 
                 _InputIterator __last, const _Compare& __x)
    : c(__first, __last), _comp(__x) 		//*TY 01/10/1999 - ugrified comp
    { make_heap(c.begin(), c.end(), _comp); }		//*TY 01/10/1999 - ugrified comp

  template <class _InputIterator>
  priority_queue(_InputIterator __first, _InputIterator __last,
                 const _Compare& __x, const _Sequence& __s)
  : c(__s), _comp(__x)		//*TY 01/10/1999 - ugrified comp
  { 
    c.insert(c.end(), __first, __last);
    make_heap(c.begin(), c.end(), _comp);		//*TY 01/10/1999 - ugrified comp
  }

#else /* __STL_MEMBER_TEMPLATES */
  priority_queue(const value_type* __first, const value_type* __last) 
    : c(__first, __last) { make_heap(c.begin(), c.end(), _comp); }		//*TY 01/10/1999 - ugrified comp

  priority_queue(const value_type* __first, const value_type* __last, 
                 const _Compare& __x) 
    : c(__first, __last), _comp(__x)		//*TY 01/10/1999 - ugrified comp
    { make_heap(c.begin(), c.end(), _comp); }		//*TY 01/10/1999 - ugrified comp

  priority_queue(const value_type* __first, const value_type* __last, 
                 const _Compare& __x, const _Sequence& __c)
    : c(__c), _comp(__x) 		//*TY 01/10/1999 - ugrified comp
  { 
    c.insert(c.end(), __first, __last);
    make_heap(c.begin(), c.end(), _comp);		//*TY 01/10/1999 - ugrified comp
  }
#endif /* __STL_MEMBER_TEMPLATES */

  bool empty() const { return c.empty(); }
  size_type size() const { return c.size(); }
  const_reference top() const { return c.front(); }
  void push(const value_type& __x) {
    __STL_TRY {
      c.push_back(__x); 
      push_heap(c.begin(), c.end(), _comp);		//*TY 01/10/1999 - ugrified comp
    }
    __STL_UNWIND(c.clear());
  }
  void pop() {
    __STL_TRY {
      pop_heap(c.begin(), c.end(), _comp);		//*TY 01/10/1999 - ugrified comp
      c.pop_back();
    }
    __STL_UNWIND(c.clear());
  }
};

__STL_END_NAMESPACE

#  undef __STL_QUEUE_ARGS
#  undef __STL_QUEUE_HEADER_ARGS

#endif /* __SGI_STL_INTERNAL_QUEUE_H */

// Local Variables:
// mode:C++
// End:
