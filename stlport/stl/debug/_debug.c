/*
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

# ifndef __STLPORT_DEBUG_C
#  define  __STLPORT_DEBUG_C


#if defined ( __STL_DEBUG )

# ifdef __STL_THREADS
#  ifndef __STL_NEED_MUTABLE 
#   define __STL_ACQUIRE_LOCK(_Lock) _Lock._M_acquire_lock();
#   define __STL_RELEASE_LOCK(_Lock) _Lock._M_release_lock();
#  else
#   define __STL_ACQUIRE_LOCK(_Lock) ((_STL_mutex&)_Lock)._M_acquire_lock();
#   define __STL_RELEASE_LOCK(_Lock) ((_STL_mutex&)_Lock)._M_release_lock();
#  endif /* __STL_NEED_MUTABLE */
# else
#  define __STL_ACQUIRE_LOCK(_Lock)
#  define __STL_RELEASE_LOCK(_Lock)
# endif /* __STL_THREADS */

__STL_BEGIN_NAMESPACE

//==========================================================
//  global non-inline functions
//==========================================================

// [ i1, i2)
template <class _Iterator>
inline bool  __STL_CALL
__in_range_aux(const _Iterator& __it, const _Iterator& __first,
               const _Iterator& __last, random_access_iterator_tag) {
    return ( __it >= __first && 
             __it < __last);
}

template <class _Iterator1, class _Iterator>
# if defined (__STL_MSVC) && (__STL_MSVC >= 1100)
inline bool __STL_CALL  __in_range_aux(_Iterator1 __it, const _Iterator& __first,
# else
inline bool __STL_CALL  __in_range_aux(const _Iterator1& __it, const _Iterator& __first,
# endif
                                       const _Iterator& __last, forward_iterator_tag) {
    _Iterator1 __i(__first);
    for (;  __i != __last && __i != __it; ++__i);
    return (__i!=__last);
}

# if defined (__STL_NONTEMPL_BASE_MATCH_BUG) /* OBSOLETE by inheritance */
template <class _Iterator1, class _Iterator>
inline bool  __STL_CALL
__in_range_aux(const _Iterator1& __it, const _Iterator& __first,
               const _Iterator& __last, bidirectional_iterator_tag) {
    _Iterator1 __i(__first);
    for (;  __i != __last && __i != __it; ++__i);
    return (__i !=__last);
}
# endif

template <class _Iterator>
bool __STL_CALL  __check_range(const _Iterator& __first, const _Iterator& __last) {
    __STL_VERBOSE_RETURN(__valid_range(__first,__last), _StlMsg_INVALID_RANGE )
    return true;
}

template <class _Iterator>
bool __STL_CALL  __check_range(const _Iterator& __it, 
                               const _Iterator& __start, const _Iterator& __finish) {
    __STL_VERBOSE_RETURN(__in_range(__it,__start, __finish), 
                         _StlMsg_NOT_IN_RANGE_1)
    return true;
}

template <class _Iterator>
bool __STL_CALL  __check_range(const _Iterator& __first, const _Iterator& __last, 
                               const _Iterator& __start, const _Iterator& __finish) {
    __STL_VERBOSE_RETURN(__in_range(__first, __last, __start, __finish), 
                         _StlMsg_NOT_IN_RANGE_2)
    return true;
}

//===============================================================

template <class _Iterator>
void  __STL_CALL __invalidate_range(const __owned_list* __base, 
                                    const _Iterator& __first,
                                    const _Iterator& __last)
{
    typedef _Iterator* _Safe_iterator_ptr;
    typedef __owned_link _L_type;
    __STL_ACQUIRE_LOCK(__base->_M_lock)
    _L_type* __pos;
    _L_type* __prev;

    for (__prev = (_L_type*)&__base->_M_node, __pos= (_L_type*)__prev->_M_next; 
         __pos!=0;) {	    
        if ((!(&__first == (_Iterator*)__pos || &__last == (_Iterator*)__pos))
            &&  __in_range_aux(
			       *(_Iterator*)__pos,
			       __first,
			       __last,
			       __ITERATOR_CATEGORY(__first, _Iterator))) {
	  __pos->_M_owner = 0;
	  __pos = (_L_type*) (__prev->_M_next = __pos->_M_next);
	}
	else {
	  __prev = __pos;
	  __pos=(_L_type*)__pos->_M_next;
	}
    }
    __STL_RELEASE_LOCK(__base->_M_lock)    
}

template <class _Iterator>
void  __STL_CALL __invalidate_iterator(const __owned_list* __base, 
                                       const _Iterator& __it)
{
    typedef __owned_link   _L_type;
    _L_type*  __position, *__prev;
    __STL_ACQUIRE_LOCK(__base->_M_lock)
    for (__prev = (_L_type*)&__base->_M_node, __position = (_L_type*)__prev->_M_next; 
         __position!= 0;) {
      // this requires safe iterators to be derived from __owned_link
       if ((__position != (_L_type*)&__it) && *((_Iterator*)__position)==__it) {
	    __position->_M_owner = 0;
	    __position = (_L_type*) (__prev->_M_next = __position->_M_next);
        }
       else {
	 __prev = __position;
	 __position=(_L_type*)__position->_M_next;
       }
    }
    __STL_RELEASE_LOCK(__base->_M_lock)
}

__STL_END_NAMESPACE

# endif /* __STL_DEBUG */

# if defined (__STL_EXPOSE_GLOBALS_IMPLEMENTATION)

// dwa 12/26/99 -- for abort
#  if defined (__STL_USE_NEW_C_HEADERS)
#   include <cstdlib>
#  else
#   include <stdlib.h>
#  endif

# if defined (__STL_WIN32)
#  include <stl/_threads.h>
# endif

//==========================================================
// .c section
//  owned_list non-inline methods and global functions 
//==========================================================

#if defined ( __STL_ASSERTIONS )

__STL_BEGIN_NAMESPACE

# ifndef __STL_STRING_LITERAL
# define __STL_STRING_LITERAL(__x) __x
# endif

# ifdef __STL_WINCE
#  define __STL_PERCENT_S "%hs" 
# else
#  define __STL_PERCENT_S "%s" 
# endif

# define __STL_MESSAGE_TABLE_BODY = { \
__STL_STRING_LITERAL("\n" __STL_PERCENT_S "(%d): STL error: %s\n"), \
__STL_STRING_LITERAL(__STL_PERCENT_S "(%d): STL assertion failure : " __STL_PERCENT_S "\n" __STL_ASSERT_MSG_TRAILER), \
__STL_STRING_LITERAL("\n" __STL_PERCENT_S "(%d): STL error : " __STL_PERCENT_S "\n" __STL_PERCENT_S "(%d): STL assertion failure:     " __STL_PERCENT_S " \n" __STL_ASSERT_MSG_TRAILER), \
__STL_STRING_LITERAL("Invalid argument to operation (see operation documentation)"),                  \
__STL_STRING_LITERAL("Taking an iterator out of destroyed (or otherwise corrupted) container"),       \
__STL_STRING_LITERAL("Trying to extract an object out from empty container"),\
__STL_STRING_LITERAL("Past-the-end iterator could not be erased"),  \
__STL_STRING_LITERAL("Index out of bounds"),  \
__STL_STRING_LITERAL("Container doesn't own the iterator"),  \
__STL_STRING_LITERAL("Uninitialized or invalidated (by mutating operation) iterator used"),  \
__STL_STRING_LITERAL("Uninitialized or invalidated (by mutating operation) lefthand iterator in expression"),  \
__STL_STRING_LITERAL("Uninitialized or invalidated (by mutating operation) righthand iterator in expression"),  \
__STL_STRING_LITERAL("Iterators used in expression are from different owners"),  \
__STL_STRING_LITERAL("Iterator could not be dereferenced (past-the-end ?)"),  \
__STL_STRING_LITERAL("Range [first,last) is invalid"),  \
__STL_STRING_LITERAL("Iterator is not in range [first,last)"),  \
__STL_STRING_LITERAL("Range [first,last) is not in range [start,finish)"),  \
__STL_STRING_LITERAL("The advance would produce invalid iterator"),  \
__STL_STRING_LITERAL("Iterator is singular (advanced beyond the bounds ?)"),  \
__STL_STRING_LITERAL("Memory block deallocated twice"),  \
__STL_STRING_LITERAL("Deallocating a block that was never allocated"),  \
__STL_STRING_LITERAL("Deallocating a memory block allocated for another type"),  \
__STL_STRING_LITERAL("Size of block passed to deallocate() doesn't match block size"),  \
__STL_STRING_LITERAL("Pointer underrun - safety margin at front of memory block overwritten"),  \
__STL_STRING_LITERAL("Pointer overrrun - safety margin at back of memory block overwritten"),   \
__STL_STRING_LITERAL("Unknown problem") \
  }

# if ( __STL_STATIC_TEMPLATE_DATA > 0 )
template <class _Dummy>
const char* __stl_debug_engine<_Dummy>::_Message_table[_StlMsg_MAX]  __STL_MESSAGE_TABLE_BODY;

# else
__DECLARE_INSTANCE(const char*, __stl_debug_engine<bool>::_Message_table[_StlMsg_MAX],
		   __STL_MESSAGE_TABLE_BODY);

# endif

# undef __STL_STRING_LITERAL
# undef __STL_PERCENT_S
__STL_END_NAMESPACE

// abort()
#    include <cstdlib>

#  if !defined( __STL_DEBUG_MESSAGE )

#    include <cstdarg>
#    include <cstdio>

__STL_BEGIN_NAMESPACE

template <class _Dummy>
void __STL_CALL  
__stl_debug_engine<_Dummy>::_Message(const char * __format_str, ...)
{
	STLPORT_CSTD::va_list __args;
	va_start( __args, __format_str );

# if defined (__STL_WINCE)
	TCHAR __buffer[512];
	int _convert = strlen(__format_str) + 1;
	LPWSTR _lpw = (LPWSTR)alloca(_convert*sizeof(wchar_t));
	_lpw[0] = '\0';
	MultiByteToWideChar(GetACP(), 0, __format_str, -1, _lpw, _convert);
	wvsprintf(__buffer, _lpw, __args);
	//	wvsprintf(__buffer, __format_str, __args);
	__STL_WINCE_TRACE(__buffer);
# elif defined (__STL_WIN32) && ( defined(__STL_MSVC) || defined (__ICL) || defined (__BORLANDC__))
    char __buffer [4096];
    vsnprintf(__buffer, sizeof(__buffer) / sizeof(char),
               __format_str, __args);
    OutputDebugStringA(__buffer);
# else
    STLPORT_CSTD::vfprintf(stderr, __format_str, __args);
# endif /* WINCE */

# ifdef __STL_DEBUG_MESSAGE_POST
	__STL_DEBUG_MESSAGE_POST
# endif

    va_end(__args);

}

__STL_END_NAMESPACE

#  endif /* __STL_DEBUG_MESSAGE */


__STL_BEGIN_NAMESPACE


template <class _Dummy>
void __STL_CALL  
__stl_debug_engine<_Dummy>::_IndexedError(int __error_ind, const char* __f, int __l)
{
  __stl_debug_message(_Message_table[_StlFormat_ERROR_RETURN], 
		      __f, __l, _Message_table[__error_ind]);
}

template <class _Dummy>
void __STL_CALL  
__stl_debug_engine<_Dummy>::_VerboseAssert(const char* __expr, int __error_ind, const char* __f, int __l)
{
  __stl_debug_message(_Message_table[_StlFormat_VERBOSE_ASSERTION_FAILURE],
		      __f, __l, _Message_table[__error_ind], __f, __l, __expr);
  __stl_debug_terminate();
}

template <class _Dummy>
void __STL_CALL 
__stl_debug_engine<_Dummy>::_Assert(const char* __expr, const char* __f, int __l)
{
  __stl_debug_message(_Message_table[_StlFormat_ASSERTION_FAILURE],__f, __l, __expr);
  __stl_debug_terminate();
}

// if exceptions are present, sends unique exception
// if not, calls abort() to terminate
template <class _Dummy>
void __STL_CALL 
__stl_debug_engine<_Dummy>::_Terminate()
{
# ifdef __STL_USE_NAMESPACES
  using namespace __STLPORT_STD;
# endif
# if defined (__STL_USE_EXCEPTIONS) && ! defined (__STL_NO_DEBUG_EXCEPTIONS)
  throw __stl_debug_exception();
# elif defined (__STL_WINCE)
  TerminateProcess(GetCurrentProcess(), 0);
# else
  abort();
# endif
}

__STL_END_NAMESPACE

# endif /* __STL_ASSERTIONS */

#ifdef __STL_DEBUG

__STL_BEGIN_NAMESPACE

//==========================================================
//  owned_list non-inline methods 
//==========================================================

template <class _Dummy>
void  __STL_CALL
__stl_debug_engine<_Dummy>::_Invalidate_all(__owned_list* __l) {
  // crucial
  if (__l->_M_node._M_owner) {
    for (__owned_link*  __position = (__owned_link*)__l->_M_node._M_next; 
	 __position != 0; __position= (__owned_link*)__position->_M_next) {
      __STL_ASSERT(__position->_Owner()== __l)
      __position->_M_owner=0;
    }
    __l->_M_node._M_next =0;
  }
}

template <class _Dummy>
void  __STL_CALL
__stl_debug_engine<_Dummy>::_Verify(const __owned_list* __l) {
  if (__l) {
    __STL_ASSERT(__l->_M_node._Owner() != 0)
    for (__owned_link* __position = (__owned_link*)__l->_M_node._M_next; 
         __position != 0; __position= (__owned_link*)__position->_M_next) {
      __STL_ASSERT(__position->_Owner()== __l)
    }
  }
}

template <class _Dummy>
void __STL_CALL  
__stl_debug_engine<_Dummy>::_Swap_owners(__owned_list& __x, __owned_list& __y, bool __swap_roots) {
  __x._Invalidate_all();
  __y._Invalidate_all();
  if (__swap_roots) {
    __owned_list* __tmp = __x._M_node._M_owner;
    __x._M_node._M_owner=__y._M_node._M_owner;
    __y._M_node._M_owner=__tmp;
  }
}

template <class _Dummy>
void __STL_CALL 
__stl_debug_engine<_Dummy>::_M_detach(__owned_list* __l, __owned_link* __c_node) {
  if (__l  != 0) {

    __STL_VERBOSE_ASSERT(__l->_Owner()!=0, _StlMsg_INVALID_CONTAINER)

    __STL_ACQUIRE_LOCK(__l->_M_lock)

    __owned_link* __prev, *__next;
   
    for (__prev = &__l->_M_node; (__next = __prev->_M_next) != __c_node; 
	 __prev = __next) {
 	 	__STL_ASSERT(__next && __next->_Owner() == __l)
    }
      
    __prev->_M_next = __c_node->_M_next;
    __c_node->_M_owner=0;

    __STL_RELEASE_LOCK(__l->_M_lock)
  }
}

template <class _Dummy>
void __STL_CALL 
__stl_debug_engine<_Dummy>::_M_attach(__owned_list* __l, __owned_link* __c_node) {
  if (__l ==0) {
    (__c_node)->_M_owner = 0;    
  } else {
    __STL_VERBOSE_ASSERT(__l->_Owner()!=0, _StlMsg_INVALID_CONTAINER)
    __STL_ACQUIRE_LOCK(__l->_M_lock)
    __c_node->_M_owner = __l;
    __c_node->_M_next = __l->_M_node._M_next;
    __l->_M_node._M_next = __c_node;
    __STL_RELEASE_LOCK(__l->_M_lock)
  }
}


template <class _Dummy>
void* __STL_CALL
__stl_debug_engine<_Dummy>::_Get_container_ptr(const __owned_link* __l) {
  const __owned_list* __owner    = __l->_Owner();
  __STL_VERBOSE_RETURN_0(__owner != 0, _StlMsg_INVALID_ITERATOR)
  void* __ret = (void*)__owner->_Owner();
  __STL_VERBOSE_RETURN_0(__ret !=0, _StlMsg_INVALID_CONTAINER)
  return __ret;
}

template <class _Dummy>
bool __STL_CALL
__stl_debug_engine<_Dummy>::_Check_same_owner( const __owned_link& __i1, 
                                               const __owned_link& __i2)
{
  __STL_VERBOSE_RETURN(__i1._Valid(), _StlMsg_INVALID_LEFTHAND_ITERATOR)
  __STL_VERBOSE_RETURN(__i2._Valid(), _StlMsg_INVALID_RIGHTHAND_ITERATOR)
  __STL_VERBOSE_RETURN((__i1._Owner()==__i2._Owner()), _StlMsg_DIFFERENT_OWNERS)
  return true;
}

template <class _Dummy>
bool  __STL_CALL
__stl_debug_engine<_Dummy>::_Check_same_owner_or_null( const __owned_link& __i1, 
							    const __owned_link& __i2)
{
  __STL_VERBOSE_RETURN(__i1._Owner()==__i2._Owner(), _StlMsg_DIFFERENT_OWNERS)
  return true;
}

template <class _Dummy>
bool __STL_CALL
__stl_debug_engine<_Dummy>::_Check_if_owner( const __owned_list * __l, const __owned_link& __it)
{
  const __owned_list* __owner_ptr = __it._Owner();
  __STL_VERBOSE_RETURN(__owner_ptr!=0, _StlMsg_INVALID_ITERATOR)
  __STL_VERBOSE_RETURN(__l==__owner_ptr, _StlMsg_NOT_OWNER)
  return true;
}


__STL_END_NAMESPACE

#endif /* __STL_DEBUG */

#endif /* if defined (EXPOSE_GLOBALS_IMPLEMENTATION) */

#endif /* header guard */

// Local Variables:
// mode:C++
// End:

