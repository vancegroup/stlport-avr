// -*- C++ -*- Time-stamp: <08/10/26 20:00:56 ptr>

/*
 * Copyright (c) 2007, 2008
 * Petr Ovtchenkov
 *
 * Licensed under the Academic Free License Version 3.0
 */

#include <exam/logger.h>
#include <iostream>

namespace exam {

using namespace std;
#if 0
using namespace std::tr2;
#endif

int base_logger::flags() const
{
  return _flags;
}

bool base_logger::is_trace() const
{
  return (_flags & trace) != 0;
}

int base_logger::flags( int f )
{
  int tmp = _flags;
  _flags = f;
  if ( (f & silent) != 0 ) {
    _flags &= ~trace_suite;
  }
  return tmp;
}

void trivial_logger::report( const char *file, int line, bool cnd, const char *expr )
{
  if ( (cnd && ((_flags & trace) == 0)) || ((_flags & silent) != 0) ) {
    return;
  }

  if ( s != 0 ) {
    *s << file << ":" << line << ": " << (cnd ? "pass" : "fail" ) << ": " << expr
       << std::endl;
  } else {
    fprintf( f, "%s:%d: %s: %s\n", file, line, (cnd ? "pass" : "fail" ), expr );
  }
}

void trivial_logger::begin_ts()
{
  if ( (_flags & trace_suite) == 0 ) {
    return;
  }

  if ( s != 0 ) {
    *s << "== Begin test suite\n";
  } else {
    fprintf( f, "== Begin test suite\n" );
  }
}

void trivial_logger::end_ts()
{
  if ( (_flags & trace_suite) == 0 ) {
    return;
  }

  if ( *s ) {
    *s << "==  End test suite\n";
  } else {
    fprintf( f, "==  End test suite\n" );
  }
}

void trivial_logger::result( const base_logger::stat& _stat, const string& suite_name )
{
  if ( s != 0 ) {
    *s << "*** " << (_stat.failed != 0 ? "FAIL " : "PASS " ) << suite_name
       << " (+" << _stat.passed
       <<   "-" << _stat.failed
       <<   "~" << _stat.skipped << "/" << _stat.total << ") ***" << endl;
  } else {
    fprintf( f, "*** %s (+%d-%d~%d/%d) ***\n", (_stat.failed != 0 ? "FAIL" : "PASS" ), _stat.passed, _stat.failed, _stat.skipped, _stat.total );
  }
}

void trivial_logger::tc( base_logger::tc_result r, const std::string& name )
{
  if ( ((_flags & silent) != 0) || ((r == pass) && ((_flags & verbose) == 0) )) {
    return;
  }

  static const char *m[] = { "  PASS ", "  FAIL ", "  SKIP ", "  DRY " };
  const char *rs = "";

  switch ( r )
  {
    case pass:
      rs = m[0];
      break;
    case fail:
      rs = m[1];
      break;
    case skip:
      rs = m[2];
      break;
    case dry:
      rs = m[3];
      break;
  }

  if ( s != 0 ) {
    *s << rs << name << endl;
  } else {
    fprintf( f, "%s%s\n", rs, name.c_str() );
  }
}

void trivial_logger::tc( base_logger::tc_result r, const std::string& name, int indent )
{
  if ( ((_flags & silent) != 0) || ((r == pass) && ((_flags & verbose) == 0) )) {
    return;
  }

  if ( s != 0 ) {
    while ( indent-- > 0 ) {
      *s << "  ";
    }
  } else {
    while ( indent-- > 0 ) {
      fprintf( f, "  " );
    }
  }

  tc( r, name );
}

#if 0
void trivial_time_logger::tc_pre()
{
  tst.push_back( get_system_time().nanoseconds_since_epoch() );
}

void trivial_time_logger::tc_post()
{
  tst.back() = get_system_time().nanoseconds_since_epoch() - tst.back();
}

void trivial_time_logger::tc_break()
{
  tst.pop_back();
}

void trivial_time_logger::tc( base_logger::tc_result r, const std::string& name )
{
  if ( r == pass ) {
    // here tst.size() > 0, if test case not throw excepion 
    time_container_t::const_iterator a = tst.begin();
    if ( a != tst.end() ) {
      unsigned n = 1;
      double sum(a->count());
      sum *= 1.0e-9;
      double sum_sq = sum * sum;
      ++a;
      for ( ; a != tst.end(); ++a ) {
        double v(a->count());
        v *= 1.0e-9;
        sum += v;
        sum_sq += v * v;
        // mean = ((n + 1) * mean + static_cast<double>(*a)) / (n + 2);
        ++n;
      }
      sum_sq -= sum * sum / n;
      sum_sq = max( 0.0, sum_sq ); // clear epsilon (round error)
      sum_sq /= n * n; // dispersion
      sum /= n;        // mean
      if ( s != 0 ) {
        *s << "  " << sum << " " << sum_sq << " " << name << endl;
      } else {
        fprintf( f, "  %f %f %s\n", sum, sum_sq, name.c_str() );
      }
    }
  }
  tst.clear();
  trivial_logger::tc( r, name );
}

void trivial_time_logger::tc( base_logger::tc_result r, const std::string& name, int indent )
{
  if ( r == pass ) {
    // here tst.size() > 0, if test case not throw excepion
    time_container_t::const_iterator a = tst.begin();
    if ( a != tst.end() ) {
      unsigned n = 1;
      double sum(a->count());
      sum *= 1.0e-9;
      double sum_sq = sum * sum;
      ++a;
      for ( ; a != tst.end(); ++a ) {
        double v(a->count());
        v *= 1.0e-9;
        sum += v;
        sum_sq += v * v;
        // mean = ((n + 1) * mean + static_cast<double>(*a)) / (n + 2);
        ++n;
      }
      sum_sq -= sum * sum / n;
      sum_sq = max( 0.0, sum_sq ); // clear epsilon (round error)
      sum_sq /= n * n; // dispersion
      sum /= n;        // mean
      if ( s != 0 ) {
        *s << "  " << sum << " " << sum_sq << " " << name << endl;
      } else {
        fprintf( f, "  %f %f %s\n", sum, sum_sq, name.c_str() );
      }
    }
  }
  tst.clear();
  trivial_logger::tc( r, name, indent );
}
#endif

} //namespace exam
