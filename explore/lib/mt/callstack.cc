// -*- C++ -*- Time-stamp: <07/09/21 22:45:51 ptr>

/*
 * Copyright (c) 2007
 * Petr Ovtchenkov
 *
 * Licensed under the Academic Free License version 3.0
 *
 */

/**
 * Derived from:
 * http://www.tlug.org.za/wiki/index.php/Obtaining_a_stack_trace_in_C_upon_SIGSEGV
 *
 * This code is in the public domain.  Use it as you see fit, some credit
 * would be appreciated, but is not a prerequisite for usage.  Feedback
 * on it's use would encourage further development and maintenance.
 *
 * Author:  Jaco Kroon <jaco@kroon.co.za>
 *
 * Copyright (C) 2005 - 2006 Jaco Kroon
 */

#include <config/feature.h>

// #define _GNU_SOURCE
// #include <memory.h>
// #include <stdlib.h>
// #include <stdio.h>

#ifndef __FIT_PRESENT_BFD

#include <mt/callstack.h>

namespace xmt {

using namespace std;

void callstack( std::ostream& s )
{
  s << "Sorry, compiled without BFD\n";
}

} // namespace xmt

#else // __FIT_PRESENT_BFD

#include <bfd.h>
#include <signal.h>
#include <ucontext.h>
#include <dlfcn.h>
#include <execinfo.h>

#ifdef __FIT_CPP_DEMANGLE
#  include <cxxabi.h>
#endif

#if 1
#if defined(REG_RIP)
# define SIGSEGV_STACK_IA64
// # define REGFORMAT "%016lx"
#elif defined(REG_EIP)
# define SIGSEGV_STACK_X86
// # define REGFORMAT "%08x"
#else
# define SIGSEGV_STACK_GENERIC
// # define REGFORMAT "%x"
#endif
#endif

#include <cstring>

#include <mt/callstack.h>
#include <iomanip>
#include <string>
#include <sstream>

namespace xmt {

using namespace std;

class BFD_Init
{
  public:
    BFD_Init()
      {
        bfd_init();
        bfd_set_default_target( "i686-pc-linux-gnu" );
      }
};

BFD_Init init;

struct params_collect
{
  bfd_boolean found;
  bfd_vma pc;
  asymbol **syms;
  const char *fname;
  const char *funcname;
  unsigned line;
};

void find_address_in_section( bfd *abfd, asection *section, void *data )
{
  bfd_boolean& found = static_cast<params_collect *>(data)->found;

  if ( found ) {
    return;
  }

  if ( (bfd_get_section_flags(abfd, section) & SEC_ALLOC) == 0 ) {
    return;
  }

  bfd_vma vma = bfd_get_section_vma( abfd, section );
  bfd_vma& pc = static_cast<params_collect *>(data)->pc;
  if ( pc < vma ) {
    return;
  }

  bfd_size_type size = bfd_get_section_size( section );
  if ( pc >= vma + size ) {
    return;
  }

  found = bfd_find_nearest_line( abfd, section,
          static_cast<params_collect *>(data)->syms, pc - vma,
          &static_cast<params_collect *>(data)->fname,
          &static_cast<params_collect *>(data)->funcname,
          &static_cast<params_collect *>(data)->line );
}

int extract_info( const char *fname, void *addr, string& file, unsigned& line )
{
  bfd *abfd = bfd_openr( fname, 0 );
  if ( abfd == 0 ) {
    return -1;
  }

  char **matching;
  if ( !bfd_check_format_matches( abfd, bfd_object, &matching ) ) {
    // free (matching);
    return -2;
  }

  // slurp_symtab (abfd);
  asymbol **syms = 0;  // Symbol table

  if ( ( bfd_get_file_flags(abfd) & HAS_SYMS ) != 0 ) {
    long symcount;
    unsigned int size;

    symcount = bfd_read_minisymbols( abfd, 0, (void **)&syms, &size );
    if ( symcount == 0 ) {
      symcount = bfd_read_minisymbols( abfd, 1, (void **)&syms, &size );
    }

    if ( symcount < 0 ) {
      if ( syms != 0 ) {
        free( syms );
      }
      bfd_close( abfd );
      return -3;
    }
  }

  params_collect pars;
  pars.found = 0;
  pars.syms = syms;

  // translate_addresses (abfd, 0);

  // for ( ; ; ) {
  pars.pc = reinterpret_cast<bfd_vma>(addr);
  bfd_map_over_sections( abfd, find_address_in_section, reinterpret_cast<void *>(&pars) );
  if ( pars.found == 0 ) {
    if ( syms != 0 ) {
      free( syms );
    }
    bfd_close( abfd );
    return -4;
  }

  file = pars.fname;
  line = pars.line;
  
  // }
  if ( syms != 0 ) {
    free( syms );
  }

  bfd_close( abfd );

  return 0;
}

void callstack( std::ostream& s )
{
  // s.clear();

#if defined(SIGSEGV_STACK_X86) || defined(SIGSEGV_STACK_IA64)
  ucontext_t ucontext;

  getcontext( &ucontext );

  int f = 0;
  Dl_info dlinfo;
  void **bp = 0;
  void *ip = 0;
#  if defined(SIGSEGV_STACK_IA64)
  ip = (void*)ucontext.uc_mcontext.gregs[REG_RIP];
  bp = (void**)ucontext.uc_mcontext.gregs[REG_RBP];
#  elif defined(SIGSEGV_STACK_X86)
  ip = (void*)ucontext.uc_mcontext.gregs[REG_EIP];
  bp = (void**)ucontext.uc_mcontext.gregs[REG_EBP];
#  endif
  string file;
  unsigned line;

  while ( bp && ip ) {
    if ( !dladdr( ip, &dlinfo ) ) {
      break;
    }

    const char *symname = dlinfo.dli_sname;
#ifdef __FIT_CPP_DEMANGLE
    int status = 0;
    char *tmp = symname == 0 ? 0 : __cxxabiv1::__cxa_demangle( symname, 0, 0, &status );

    if ( status == 0 && tmp != 0 ) {
      symname = tmp;
    }
#endif

    int res;

    // if ( string( "obj/gcc/so_g/mt_ut" ) == dlinfo.dli_fname ) { 
      if ( (res = extract_info( dlinfo.dli_fname, ip, file, line )) != 0 /* false */ ) {
        file = "??";
        line = 0;
        // s << "*** " << res << " " << dlinfo.dli_fname << endl;
      } else {
        // file = "??";
        // line = 0;
      }
    // } else {
    //   file = "??";
    //   line = 0;
    // }

    s << '#' << setw(2) << setiosflags(ios_base::left) << f++ << " " << ip 
      << " in " << (symname == 0 ? "?" : symname )
      << " at " << /* "...\n" */ file << ":" << line << '\n';
      // << "+" << (static_cast<char *>(ip) - static_cast<char *>(dlinfo.dli_saddr))
      // << "> (" << dlinfo.dli_fname << ")\n";
#ifdef __FIT_CPP_DEMANGLE
    if ( tmp ) {
      free(tmp);
    }
#endif

    if ( dlinfo.dli_sname && !strcmp( dlinfo.dli_sname, "main" ) ) {
      break;
    }

    ip = bp[1];
    bp = (void**)bp[0];
  }
#else
  const int btsz = 50;
  void *bt[btsz];

  size_t sz = backtrace( bt, btsz );
  char **line = backtrace_symbols( bt, sz );

  Dl_info dlinfo;
  // string file;
  // unsigned line;

  for ( int i = 0; i < sz; ++i ) {
    stringstream ss( line[i] );
    // s << line[i] << '\n';
    string nm;
    void *addr;
    char c;
    ss >> nm >> c >> hex >> addr;

    if ( !dladdr( addr, &dlinfo ) ) {
      continue;
    }

    const char *symname = dlinfo.dli_sname;
#ifdef __FIT_CPP_DEMANGLE
    int status = 0;
    char *tmp = symname == 0 ? 0 : __cxxabiv1::__cxa_demangle( symname, 0, 0, &status );

    if ( status == 0 && tmp != 0 ) {
      symname = tmp;
    }
#endif

    // int res = extract_info();

    s << '#' << setw(2) << setiosflags(ios_base::left) << i << " " << addr
      << " in " << (symname == 0 ? "..." : symname)
      << " at " << "...\n";
    // s << "== " << nm << " / '" << c << "' " << addr << "\n";
#ifdef __FIT_CPP_DEMANGLE
    if ( tmp ) {
      free(tmp);
    }
#endif
  }

  free( line );
#endif
}

} // namespace xmt

#endif // __FIT_PRESENT_BFD
