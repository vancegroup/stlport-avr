// -*- C++ -*- Time-stamp: <09/06/01 01:06:36 ptr>

/*
 * Copyright (c) 2009, 2010
 * Petr Ovtchenkov
 *
 * Licensed under the Academic Free License version 3.0
 *
 */

#include <config/feature.h>

#ifdef __FIT_CPP_DEMANGLE
#  include <exception>
#  include <cxxabi.h>
#endif

#include <mt/callstack.h>

#include <iostream>
#include <cstdlib>

namespace xmt {

using namespace std;

string demangle( const char* symname )
{
#ifdef __FIT_CPP_DEMANGLE
  if ( symname == 0 ) {
    return string();
  }

  // char* buf = static_cast<char *>(malloc( 1024 ));
  int status = 0;
  size_t len = 0;

  char* tmp = abi::__cxa_demangle( symname, 0, 0, &status );
  if ( status == 0 && tmp != 0 ) {
    // cerr << len << endl;
    string nm( tmp );
    free( tmp );
    return nm;
  }
  if ( tmp != 0 ) {
    free( tmp );
  }
#endif

  return string( symname );
}

} // namespace xmt
