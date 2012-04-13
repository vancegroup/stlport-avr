/*
 *
 * Copyright (c) 2012
 * Petr Ovtchenkov
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

#include "stlport_prefix.h"

#include <new>
#include <stdlib.h>

_STLP_BEGIN_NAMESPACE

#if !defined(_STLP_WCE_EVC3)
#  if defined(_STLP_NO_BAD_ALLOC) || defined(_STLP_OPERATORS_NEW_DELETE)
const nothrow_t nothrow = {};
#  endif
#endif

_STLP_END_NAMESPACE

#ifdef _STLP_OPERATORS_NEW_DELETE
// static _STLP_STD::new_handler _newhandler = 0;

// see libsupc++.a
extern _STLP_STD::new_handler __new_handler;
static _STLP_STD::new_handler& _newhandler = __new_handler;

_STLP_BEGIN_NAMESPACE

// __attribute__ ((__visibility__("default")))
new_handler get_new_handler() noexcept
{ return __sync_fetch_and_add( &_newhandler, (new_handler)0 ); }

new_handler set_new_handler( new_handler new_p ) noexcept
{ return __sync_lock_test_and_set( &_newhandler, new_p ); }

_STLP_END_NAMESPACE

 __attribute__ ((weak,visibility("default")))
void* operator new(_STLP_STD::size_t size)
{
  void* p;
  _STLP_STD::new_handler h;

  while ( (p = malloc(size)) == 0 ) {
    h = _STLP_STD::get_new_handler();
    if ( h != 0 ) {
      h();
    } else {
      throw _STLP_STD::bad_alloc();
    }
  }
  return p;
}

__attribute__ ((weak,visibility("default")))
void* operator new(_STLP_STD::size_t size, const _STLP_STD::nothrow_t&) noexcept
{
  try {
    /* This nothrow version of operator new returns a pointer obtained
       as if acquired from the (possibly replaced) ordinary version.
       This requirement is binding on a replacement version of this function.
     */
    return ::operator new( size );
  }
  catch ( const _STLP_STD::bad_alloc& ) {
    return 0;
  }
}

__attribute__ ((weak,visibility("default")))
void operator delete(void* ptr) noexcept
{
  // if ( ptr ) {
  ::free( ptr ); // check for 0 is in the 'free'
  // }
}

__attribute__ ((weak,visibility("default")))
void operator delete(void* ptr, const _STLP_STD::nothrow_t&) noexcept
{ ::operator delete( ptr ); }

__attribute__ ((weak,visibility("default")))
void* operator new[](_STLP_STD::size_t size)
{
  return ::operator new( size );
}

__attribute__ ((weak,visibility("default")))
void* operator new[](_STLP_STD::size_t size, const _STLP_STD::nothrow_t&) noexcept
{
   try {
    /* This nothrow version of operator new returns a pointer obtained
       as if acquired from the (possibly replaced) ordinary version.
       This requirement is binding on a replacement version of this function.
     */
    return ::operator new[]( size );
  }
  catch ( const _STLP_STD::bad_alloc& ) {
    return 0;
  } 
}

__attribute__ ((weak,visibility("default")))
void operator delete[](void* ptr) noexcept
{ ::operator delete( ptr ); }

__attribute__ ((weak,visibility("default")))
void operator delete[](void* ptr, const _STLP_STD::nothrow_t&) noexcept
{ ::operator delete[]( ptr ); }

#endif // _STLP_OPERATORS_NEW_DELETE
