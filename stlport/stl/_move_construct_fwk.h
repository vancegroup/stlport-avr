/*
 *
 * Copyright (c) 2003
 * François Dumont
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

#ifndef _STLP_TYPE_TRAITS_H
# include <stl/type_traits.h>
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
class __partial_move_source {
  _Tp &_data;
public:
  explicit __partial_move_source (_Tp &_src) : _data(_src)
  {};

  _Tp& get() const
  {return _data;}
};

//Class used to signal partial move constructor implementation.
template <class _Tp>
struct __partial_move_traits {
#if defined(_STLP_USE_PARTIAL_SPEC_WORKAROUND) && !defined(_STLP_CLASS_PARTIAL_SPECIALIZATION)
  typedef typename _IsStlportClass<_Tp>::_Ret implemented;
#else
  //By default not implemented:
  typedef __false_type implemented;
#endif /* _STLP_USE_PARTIAL_SPEC_WORKAROUND */
};

template <class _Tp>
struct _PartialMoveSourceTraits {
  typedef typename __partial_move_traits<_Tp>::implemented _PartialMvImplRet;
  enum {_PartialMvImpl = __type2bool<_PartialMvImplRet>::_Ret};
  typedef typename __select<_PartialMvImpl,
                            __partial_move_source<_Tp>,
                            _Tp const&>::_Ret _Type;
};

//The helper function
template <class _Tp>
inline _STLP_TYPENAME_ON_RETURN_TYPE _PartialMoveSourceTraits<_Tp>::_Type
_AsPartialMoveSource (_Tp &src) {
  typedef typename _PartialMoveSourceTraits<_Tp>::_Type _SrcType;
  return _SrcType(src);
};

/*************************************************************
 *Full move:
 *The source do not required to be destroyable after the move
 * but it HAS to release all the managed ressources as the
 * destructor won't be called.
 *************************************************************/
template <class _Tp>
class __full_move_source {
  _Tp &_data;
public:
  explicit __full_move_source (_Tp &_src) : _data(_src)
  {};

  _Tp& get() const
  {return _data;}
};

/*
 * A little class to report trouble in terms of compile error:
 * If the compiler complains that you lack a construstor from a
 * __invalid_source<_Tp> type it means that the move constructor
 * framework for _Tp is misconfigured.
 */
template <class _Tp>
class __invalid_source {
public:
  explicit __invalid_source (_Tp &_src) {};
};

/*
 *Class used to signal full move support.
 * supported means that the object is conform to the full move concept
 * implemented means that a special full_move constructor has been implemented
 *             for this purpose.
 */
template <class _Tp>
struct __full_move_traits {
  /*
   * By default POD types do support it without implementing it.
   */
  typedef typename __type_traits<_Tp>::is_POD_type supported;
  typedef __false_type implemented;
};

/*
 * This struct should never be used if the user has not explicitely stipulated
 * that its class support the full move concept. To check that the return type
 * in such a case will be __invalid_source<_Tp> to generate a compile error
 * revealing the configuration problem.
 */
template <class _Tp>
struct _FullMoveSourceTraits {
  typedef typename __full_move_traits<_Tp>::implemented _FullMvImpRet;
  enum {_FullMvImp = __type2bool<_FullMvImpRet>::_Ret};
  typedef typename __select<_FullMvImp,
                            __full_move_source<_Tp>,
                            _Tp const&>::_Ret _AuxType;
  typedef typename __full_move_traits<_Tp>::supported _FullMvSupRet;
  enum {_FullMvSup = __type2bool<_FullMvSupRet>::_Ret};
  typedef typename __select<_FullMvSup,
                            _AuxType,
                            __invalid_source<_Tp> >::_Ret _Type;
};

//The helper function
template <class _Tp>
inline _STLP_TYPENAME_ON_RETURN_TYPE _FullMoveSourceTraits<_Tp>::_Type
_AsFullMoveSource (_Tp &src) {
  typedef typename _FullMoveSourceTraits<_Tp>::_Type _SrcType;
  return _SrcType(src);
};

template <class _Tp>
struct _MoveConstructImplemented {
  typedef typename __partial_move_traits<_Tp>::implemented _PartialImpl;
  typedef typename __full_move_traits<_Tp>::implemented _FullImpl;

  typedef typename _Lor2<_PartialImpl, _FullImpl>::_Ret _Ret;
  static _Ret _Answer() {return _Ret();}
};

template<class _Tp>
_MoveConstructImplemented<_Tp> _IsMoveConstructImplemented (_Tp const* pt)
{return _MoveConstructImplemented<_Tp>();}

template <class _Tp>
struct _MoveSourceTraits {
  typedef typename _PartialMoveSourceTraits<_Tp>::_Type _PartialSrcType;
  typedef typename _FullMoveSourceTraits<_Tp>::_Type _FullSrcType;
  typedef typename __full_move_traits<_Tp>::supported _FullMvSupRet;
  enum {_FullMvSup = __type2bool<_FullMvSupRet>::_Ret};
  //The full move is prefered to the partial:
  typedef typename __select<_FullMvSup,
                            _FullSrcType,
                            _PartialSrcType>::_Ret _Type;
};

template <class _Tp>
inline _STLP_TYPENAME_ON_RETURN_TYPE _MoveSourceTraits<_Tp>::_Type 
_AsMoveSource(_Tp &src) {
  typedef typename _MoveSourceTraits<_Tp>::_Type _MvSrcType;
  return _MvSrcType(src);
}

_STLP_END_NAMESPACE

#endif /* _STLP_MOVE_CONSTRUCT_FWK_H */
