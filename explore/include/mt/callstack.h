// -*- C++ -*- Time-stamp: <09/05/30 02:32:54 ptr>

/*
 * Copyright (c) 2007, 2009
 * Petr Ovtchenkov
 *
 * Licensed under the Academic Free License version 3.0
 *
 */

#ifndef __mt_callstack_h
#define __mt_callstack_h

#include <ostream>
#include <string>

namespace xmt {

void callstack( std::ostream& );
std::string demangle( const char* );

} // namespace xmt

#endif
