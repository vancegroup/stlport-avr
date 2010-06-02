// -*- C++ -*- Time-stamp: <10/06/02 15:17:35 ptr>

/*
 * Copyright (c) 2007-2009
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
 */

#ifndef __suite_h
#define __suite_h

#include <iostream>
#include <sstream>
#include <map>
#include <stack>
#include <string>
#include <exception>
#include <stdexcept>
#include <list>
#include <vector>
#include <algorithm>

#if 0
#include <mt/mutex>
#endif
#include <exam/logger.h>
#include <exam/defs.h>

namespace exam {

class test_suite;

namespace detail {

struct call_impl
{
    virtual ~call_impl()
      { }
    // virtual int invoke() = 0;
    virtual int invoke( test_suite *, int = 0 ) = 0;
};

template <typename F>
class call_impl_t :
        public call_impl
{
  public:
    explicit call_impl_t( F f ) :
        _f( f )
      { }

    // virtual int invoke()
    //  { return _f(); }

    virtual int invoke( test_suite *s, int count = 0 )
      { return _f( s, count ); }


  private:
    F _f;
};

class dummy
{
  public:
    // virtual int f()
    //   { return 0; }

    virtual int f( test_suite *, int count = 0 )
      { return count; }

    virtual ~dummy()
      { }
};

template <class TC>
class method_invoker
{
  public:
    // typedef int (TC::*mf_type_a)();
    typedef int (TC::*mf_type)( test_suite *, int );

    explicit method_invoker( TC& instance, mf_type f ) :
        _inst(instance),
        _func(f)
      { }

    method_invoker( const method_invoker<TC>& m ) :
        _inst( m._inst ),
        _func( m._func )
      { }

    // int operator()()
    //   { return (_inst.*_func)(); }

    int operator()( test_suite *ts, int count = 0 )
      { return (_inst.*_func)( ts, count ); }

  private:
    method_invoker& operator =( const method_invoker<TC>& )
      { return *this; }

    TC& _inst;
    mf_type _func;
};

class call
{
  public:
    call()
      { }

    template <class F>
    call( F f )
      { new (&_buf[0]) call_impl_t<F>(f); }

    // int operator()()
    //   { return reinterpret_cast<call_impl *>(&_buf[0])->invoke(); }

    int operator()( test_suite *ts, int count = 0 )
      { return reinterpret_cast<call_impl *>(&_buf[0])->invoke( ts, count ); }

  private:
    // call_impl *_f;
    char _buf[((sizeof(call_impl_t<method_invoker<dummy> >)+64) / 64) << 6];
};


class test_case
{
  public:
    test_case( const call& f ) :
        _tc( f )
      { }

    // int operator ()()
    //   { return _tc(); }

    int operator ()( test_suite *ts, int count = 0 )
      { return _tc( ts, count ); }

  private:
    call _tc;
};

inline test_case *make_test_case( const call& f )
{
  return new test_case( f );
}

template <class TC>
inline test_case *make_test_case( int (TC::*f)( test_suite *, int ), TC& instance )
{
  return new test_case( method_invoker<TC>(instance, f) );
}

} // namespace detail

class init_exception :
  public std::exception
{
};

class skip_exception :
  public std::exception
{
};

class test_suite
{
  private:
    typedef unsigned vertex_t;

  public:
    typedef int (*func_type)( test_suite *, int );
    typedef vertex_t test_case_type;

    test_suite( const std::string& name, unsigned n = 1 );
    test_suite( const char *name, unsigned n = 1 );
    ~test_suite();

    test_case_type add( func_type, const std::string& name );
    test_case_type add( func_type, const std::string& name, test_case_type );

    template <class InputIter>
    test_case_type add( func_type, const std::string& name, InputIter, InputIter );

    template <class TC>
    test_case_type add( int (TC::*)( test_suite *, int ), TC&, const std::string& name );

    template <class TC>
    test_case_type add( int (TC::*)( test_suite *, int ), TC&, const std::string& name, test_case_type );

    template <class TC, class InputIter>
    test_case_type add( int (TC::*)( test_suite *, int ), TC&, const std::string& name, InputIter, InputIter );

    int girdle( test_case_type start );
    int girdle()
      { return girdle( 0 ); }
    int single( test_case_type one );
    int run( test_suite *, int count = 0 );

    int dry_girdle( test_case_type start );
    int dry_girdle()
      { return dry_girdle( 0 ); }
    int dry_run( test_suite *, int count = 0 );

    int flags();
    int flags( int );
    bool is_trace();
    void report( const char*, bool, const char* );
    static void report_async( const char*, bool, const char* );
    base_logger *set_global_logger( base_logger * );
    base_logger *set_logger( base_logger * );

    test_case_type test_by_name( const std::string& );
    void print_graph( std::ostream& );

  private:
    enum {
      pass = 0,
      fail = 1,
      skip = 2
    };

    base_logger *local_logger;
#if 0
    std::tr2::mutex _lock_ll;
#endif

    struct test_case_collect
    {
        detail::test_case *tc;
        int state;
        std::string name;
    };

    typedef std::pair<vertex_t,vertex_t> edge_t;
    typedef std::pair<vertex_t,unsigned> weight_t;
    typedef std::map<vertex_t,test_case_collect> test_case_map_type;
    vertex_t _count;
    std::list<edge_t> _edges;
    std::vector<weight_t> _vertices;
    int _last_state;
    test_case_map_type _test;
    base_logger::stat _stat;
    std::string _suite_name;
    unsigned _iterations;

    void run_test_case( vertex_t v, unsigned n = 1 );
    void dry_run_test_case( vertex_t v, unsigned n, int indent );
    static bool vertices_compare( weight_t, weight_t );

    static int _root_func( test_suite *, int = 0 );

    static base_logger *logger;
#if 0
    static std::tr2::mutex _lock_gl;
#endif

    static std::stack<test_suite *> _stack;
#if 0
    static std::tr2::mutex _lock_stack;
#endif
};

template <class TC>
test_suite::test_case_type test_suite::add( int (TC::*f)( test_suite *, int ), TC& instance, const std::string& name )
{
  vertex_t v = ++_count;
  _edges.push_back( std::make_pair( 0, v ) );
  _vertices.push_back( std::make_pair( v, 1 ) );
  _test[v].tc = detail::make_test_case( f, instance );
  _test[v].state = 0;
  _test[v].name = name;
  // ++_stat.total;

  return v;
}

template <class InputIter>
test_suite::test_case_type test_suite::add( test_suite::func_type f, const std::string& name, InputIter first, InputIter last )
{
  vertex_t v = ++_count;
  unsigned weight = 1;
  while ( first != last ) {
    if ( *first >= _count ) {
      throw std::logic_error( "bad test dependency" );
    }
    weight += _vertices[*first].second;
    _edges.push_back( std::make_pair( *first++, v ) );
  }
  _vertices.push_back( std::make_pair( v, weight ) );
  _test[v].tc = detail::make_test_case( detail::call( f ) );
  _test[v].state = 0;
  _test[v].name = name;
  // ++_stat.total;

  return v;
}

template <class TC>
test_suite::test_case_type test_suite::add( int (TC::*f)( test_suite *, int ), TC& instance, const std::string& name, test_suite::test_case_type depends )
{
  vertex_t v = ++_count;
  if ( depends >= _count ) {
    throw std::logic_error( "bad test dependency" );
  }
  _edges.push_back( std::make_pair( depends, v ) );
  _vertices.push_back( std::make_pair( v, _vertices[depends].second + 1 ) );
  _test[v].tc = detail::make_test_case( f, instance );
  _test[v].state = 0;
  _test[v].name = name;
  // ++_stat.total;

  return v;
}

template <class TC, class InputIter>
test_suite::test_case_type test_suite::add( int (TC::*f)( test_suite *, int ), TC& instance, const std::string& name, InputIter first, InputIter last )
{
  vertex_t v = ++_count;
  unsigned weight = 1;
  while ( first != last ) {
    if ( *first >= _count ) {
      throw std::logic_error( "bad test dependency" );
    }
    weight += _vertices[*first].second;
    _edges.push_back( std::make_pair( *first++, v ) );
  }
  _vertices.push_back( std::make_pair( v, weight ) );
  _test[v].tc = detail::make_test_case( f, instance );
  _test[v].state = 0;
  _test[v].name = name;
  // ++_stat.total;

  return v;
}

typedef test_suite::test_case_type test_case_type;

} // namespace exam

#ifdef __FIT_EXAM
#  define EXAM_IMPL(F) F( exam::test_suite *__exam_ts, int __exam_counter )
#  define EXAM_DECL(F) F( exam::test_suite *, int = 0 )
#  define EXAM_RESULT __exam_counter
#  define EXAM_CHECK(C) if ( !(C) ) { __exam_ts->report( HERE, false, #C );  __exam_counter |= 1; } else __exam_ts->report( HERE, true, #C )
#  define EXAM_CHECK_ASYNC(C) if ( !(C) ) { exam::test_suite::report_async( HERE, false, #C ); } else exam::test_suite::report_async( HERE, true, #C )
#  define EXAM_CHECK_ASYNC_F(C,V) if ( !(C) ) { exam::test_suite::report_async( HERE, false, #C ); V |= 1; } else exam::test_suite::report_async( HERE, true, #C )
#  define EXAM_MESSAGE(M) __exam_ts->report( HERE, true, M )
#  define EXAM_MESSAGE_ASYNC(M) exam::test_suite::report_async( HERE, true, M )
#  define EXAM_REQUIRE(C) if ( !(C) ) { __exam_ts->report( HERE, false, #C );  return 1; } else __exam_ts->report( HERE, true, #C )
#  define EXAM_FAIL(M) __exam_ts->report( HERE, false, M ); return 1
#  define EXAM_ERROR(M) __exam_ts->report( HERE, false, M ); __exam_counter |= 1
#  define EXAM_ERROR_ASYNC(M) exam::test_suite::report_async( HERE, false, M )
#  define EXAM_ERROR_ASYNC_F(M,V) exam::test_suite::report_async( HERE, false, M ); V |= 1
#else
#  define EXAM_IMPL(F) F( exam::test_suite *, int )
#  define EXAM_DECL(F) F( exam::test_suite *, int = 0 )
#  define EXAM_RESULT 0
#  define EXAM_CHECK(C) (C)
#  define EXAM_CHECK_ASYNC(C) (C)
#  define EXAM_CHECK_ASYNC_F(C,V) (C)
#  define EXAM_MESSAGE(M)
#  define EXAM_MESSAGE_ASYNC(M)
#  define EXAM_REQUIRE(C) (C)
#  define EXAM_FAIL(M)
#  define EXAM_ERROR(M)
#  define EXAM_ERROR_ASYNC(M)
#  define EXAM_ERROR_ASYNC_F(M,V)
#endif


#endif // __suite_h

