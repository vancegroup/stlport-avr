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

#ifndef _STLP_TYPE_MANIPS_H
# include <stl/type_manips.h>
#endif

_STLP_BEGIN_NAMESPACE

/*************************************************************
 * Move construct feature
 *************************************************************/

/*************************************************************
 *Partial move:
 *The source HAS to be destroyable after the move!
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

//Class used to signal partial move support.
template <class _Tp>
struct __partial_move_traits {
#if defined(_STLP_USE_PARTIAL_SPEC_WORKAROUND) && !defined(_STLP_CLASS_PARTIAL_SPECIALIZATION)
  typedef typename _IsStlportClass<_Tp>::_Ret supported;
#else
  //By default not supported:
  typedef __false_type supported;
#endif /* _STLP_USE_PARTIAL_SPEC_WORKAROUND */
};

template <class _Tp>
struct _PartialMoveSourceTraits {
  typedef typename __partial_move_traits<_Tp>::supported _PartialMvSupRet;
  enum {_PartialMvSup = __type2bool<_PartialMvSupRet>::_Ret};
  typedef typename __select<_PartialMvSup,
                            __partial_move_source<_Tp>,
                            _Tp const&>::_Ret _Type;
};

template <class _Tp>
inline _STLP_TYPENAME_ON_RETURN_TYPE _PartialMoveSourceTraits<_Tp>::_Type
_AsPartialMoveSource (_Tp &src) {
  typedef typename _PartialMoveSourceTraits<_Tp>::_Type _SrcType;
  return _SrcType(src);
};

/*************************************************************
 *Full move:
 *The source do not required to be destroyable after the move!
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

//Class used to signal full move support.
template <class _Tp>
struct __full_move_traits {
  //By default not supported
  typedef __false_type supported;
};

template <class _Tp>
struct _FullMoveSourceTraits {
	typedef typename __full_move_traits<_Tp>::supported _FullMvSupRet;
  enum {_FullMvSup = __type2bool<_FullMvSupRet>::_Ret};
  typedef typename __select<_FullMvSup,
                            __full_move_source<_Tp>,
                            _Tp const&>::_Ret _Type;
};

/*
template <class _Tp>
inline  _STLP_TYPENAME_ON_RETURN_TYPE _FullMoveSourceTraits<_Tp>::_Type
_ForceFullMoveSource(_Tp &src) {
	typedef typename _FullMoveSourceTraits<_Tp>::_Type _MvSrcType;
	return _MvSrcType(src);
}
*/

//To implement a full move constructor, the aggregated datas has also to handle the
//full move constructor as no destruction will occur, this can be done with the 
//following method.
template <class _Tp>
inline  __full_move_source<_Tp>
_ForceFullMoveSource(_Tp &src) {
	return __full_move_source<_Tp>(src);
}

template <class _Tp>
struct _MoveConstructSupported {
	typedef typename __partial_move_traits<_Tp>::supported _PartialSup;
	typedef typename __full_move_traits<_Tp>::supported _FullSup;

	typedef typename _Lor2<_PartialSup, _FullSup>::_Ret _Ret;
	static _Ret _Answer() {return _Ret();}
};

template<class _Tp>
_MoveConstructSupported<_Tp> _IsMoveConstructSupported (_Tp const* pt)
{return _MoveConstructSupported<_Tp>();}

template <class _Tp>
struct _MoveSourceTraits {
  typedef typename _PartialMoveSourceTraits<_Tp>::_Type _PartialSrcType;
	typedef typename __full_move_traits<_Tp>::supported _FullMvSupRet;
  enum {_FullMvSup = __type2bool<_FullMvSupRet>::_Ret};
  typedef typename __select<_FullMvSup,
                            __full_move_source<_Tp>,
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
