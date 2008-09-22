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

#ifndef _STLP_MOVE_CONSTRUCT_FWK_H
#define _STLP_MOVE_CONSTRUCT_FWK_H

#ifndef _STLP_TYPE_TRAITS
#  include <type_traits>
#endif

_STLP_BEGIN_NAMESPACE

/*************************************************************
 * Move constructor framework
 *************************************************************/

/*************************************************************
 *Partial move:
 *The source HAS to be a valid instance after the move!
 *************************************************************/
template <class _Tp>
class __move_source
{
  public:
    explicit __move_source( _Tp& _src ) :
        _M_data(_src)
      { }

    _Tp& get() const
      { return _M_data; }
  private:
    _Tp& _M_data;

    //We explicitely forbid assignment to avoid warning:
    typedef __move_source<_Tp> _Self;

    _Self& operator = ( _Self const& );
};

//Class used to signal move constructor support, implementation and type.
_STLP_BEGIN_TR1_NAMESPACE

template <class _Tp>
struct __has_trivial_move :
    public integral_constant<bool, is_trivial<_Tp>::value>
{ };

template <class _Tp>
struct __has_move_constructor :
    public false_type
{ };

_STLP_END_NAMESPACE

_STLP_END_NAMESPACE

#endif /* _STLP_MOVE_CONSTRUCT_FWK_H */

// Local Variables:
// mode:C++
// End:
