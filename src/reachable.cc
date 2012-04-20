/*
 * Copyright (c) 2011
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

#include <memory>
#include <unordered_map>

_STLP_BEGIN_NAMESPACE

namespace detail {

static unordered_map<void*,unsigned long> _reachable;

void* __undeclare_reachable( void* p ) noexcept
{
  auto i = _reachable.find( p );
  if ( i != _reachable.end() ) {
    if ( --i->second == 0 ) {
      _reachable.erase( i );
    }
    return p;
  }

  return NULL;
}

} // detail

void declare_reachable( void* p )
{
  if ( p != NULL ) {
    ++detail::_reachable[p];
  }
}

void declare_no_pointers( char* /* p */, size_t /* n */ ) noexcept
{
}

void undeclare_no_pointers( char* /* p */, size_t /* n */ ) noexcept
{
}

pointer_safety get_pointer_safety() noexcept
{
  return pointer_safety::relaxed;
}

_STLP_END_NAMESPACE
