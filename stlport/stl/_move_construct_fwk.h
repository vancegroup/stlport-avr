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

template <class _Tp>
struct __move_traits
{
  /*
   * implemented tells if a the special move constructor has to be called or the classic
   * copy constructor is just fine. Most of the time the copy constructor is fine only
   * if the following info is true.
   */
  typedef integral_constant<bool,has_trivial_copy_constructor<_Tp>::value && has_trivial_destructor<_Tp>::value> implemented;
  /*
   * complete tells if the move is complete or partial, that is to say, does the source
   * needs to be destroyed once it has been moved.
   */
  typedef typename has_trivial_destructor<_Tp>::type complete;
};

_STLP_MOVE_TO_PRIV_NAMESPACE

/*
 * This struct should never be used if the user has not explicitely stipulated
 * that its class support the full move concept. To check that the return type
 * in such a case will be __invalid_source<_Tp> to generate a compile error
 * revealing the configuration problem.
 */
#if 0
template <class _Tp>
struct _MoveSourceTraits {
  typedef typename __move_traits<_Tp>::implemented _MvImpRet;
#if defined (__BORLANDC__)
  typedef typename __selectT<_MvImpRet,
#else
  enum {_MvImp = __type2bool<_MvImpRet>::_Ret};
  typedef typename __select<_MvImp,
#endif
                            __move_source<_Tp>,
                            _Tp const&>::_Ret _Type;
};

//The helper function
template <class _Tp>
inline _STLP_TYPENAME_ON_RETURN_TYPE _MoveSourceTraits<_Tp>::_Type
_AsMoveSource (_Tp &src) {
  typedef typename _MoveSourceTraits<_Tp>::_Type _SrcType;
  return _SrcType(src);
}
#endif

//Helper structs used for many class.
template <class _Tp>
struct __move_traits_aux {
  typedef typename __move_traits<_Tp>::implemented implemented;
  typedef typename __move_traits<_Tp>::complete complete;
};

template <class _Tp1, class _Tp2>
struct __move_traits_aux2 {
  typedef __move_traits<_Tp1> _MoveTraits1;
  typedef __move_traits<_Tp2> _MoveTraits2;

  typedef typename integral_constant<bool, _MoveTraits1::implemented::value || _MoveTraits2::implemented::value>::type implemented;
  typedef typename integral_constant<bool, _MoveTraits1::complete::value && _MoveTraits2::complete::value>::type complete;
};

_STLP_MOVE_TO_STD_NAMESPACE

_STLP_END_NAMESPACE

#endif /* _STLP_MOVE_CONSTRUCT_FWK_H */

// Local Variables:
// mode:C++
// End:
