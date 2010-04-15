// -*- C++ -*- Time-stamp: <09/06/06 00:44:24 ptr>

/*
 * Copyright (c) 2008, 2009
 * Petr Ovtchenkov
 *
 * Copyright (c) 2008, 2009
 * Dmitry Osmakov
 *
 * Licensed under the Academic Free License Version 3.0
 *
 */

#include "opts_test.h"

#include <misc/opts.h>
#include <set>
#include <vector>
#include <list>
#include <iostream>

using namespace std;

int EXAM_IMPL(opts_test::flag_option)
{
  const char* argv[] = { "name", "-h" };
  int argc = sizeof( argv ) / sizeof(argv[0]);

  Opts opts;

  opts << option<void>( "print this help message", 'h', "help" );

  try {
    opts.parse( argc, argv );
  }
  catch ( ... ) {
    EXAM_ERROR("unexpected exception");
  }
  
  EXAM_CHECK( opts.is_set( 'h' ) );

  return EXAM_RESULT;
}

int EXAM_IMPL(opts_test::flag_option_long)
{
  const char* argv[] = { "name", "--help" };
  int argc = sizeof( argv ) / sizeof(argv[0]);

  Opts opts;

  opts << option<void>( "print this help message", 'h', "help" );

  try {
    opts.parse( argc, argv );
  }
  catch ( ... ) {
    EXAM_ERROR("unexpected exception");
  }
  
  EXAM_CHECK( opts.is_set( 'h' ) );

  return EXAM_RESULT;
}


int EXAM_IMPL(opts_test::int_option)
{

  const char* argv[] = { "name", "-p", "80" };
  int argc = sizeof( argv ) / sizeof(argv[0]);

  Opts opts;

  opts << option<int>( "listen tcp port", 'p', "port" )[0];

  try {
    opts.parse( argc, argv );

    EXAM_CHECK( opts.is_set( 'p' ) );
    EXAM_CHECK( opts.get<int>( 'p' ) == 80 );
  }
  catch ( const Opts::unknown_option& e ) {
  }
  catch ( const Opts::arg_typemismatch& e ) {
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(opts_test::int_option_long)
{
  const char* argv[] = { "name", "--port=80" };
  int argc = sizeof( argv ) / sizeof(argv[0]);

  Opts opts;

  opts << option<int>( "listen tcp port", 'p', "port" )[0];

  try {
    opts.parse( argc, argv );

    EXAM_CHECK( opts.is_set( 'p' ) );
    EXAM_CHECK( opts.get<int>( 'p' ) == 80 );
  }
  catch ( const Opts::unknown_option& e ) {
  }
  catch ( const Opts::arg_typemismatch& e ) {
  }
  catch ( const std::invalid_argument& e ) {
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(opts_test::add_check_flag)
{
  const char* argv[] = { "name", "-ht" , "--temp"};
  int argc = sizeof( argv ) / sizeof(argv[0]);

  Opts opts;
  
  int f_token = (opts << option<void>( "", 'f' )).last_token();

  opts << option<void>( "", 't', "tag" );
  
  int foo_token = (opts << option<void>( "", "foo" ) ).last_token();

  opts << option<void>( "temp desc", "temp" );

  int h_token = ( opts << option<void>( "print this help message", 'h', "help" ) ).last_token();

  try {
    opts.parse( argc, argv );

    EXAM_CHECK( opts.is_set( 'h' ) );
  }
  catch ( const Opts::unknown_option& e ) {
  }
  catch ( const Opts::arg_typemismatch& e ) {
  }
  catch ( const std::invalid_argument& e ) {
  }
  catch ( ... ) {
  }

  EXAM_CHECK( !opts.is_set("foo") );
  EXAM_CHECK( !opts.is_set(foo_token) );
  EXAM_CHECK( opts.is_set('h') );
  EXAM_CHECK( opts.is_set(h_token) );
  EXAM_CHECK( opts.is_set("help"));
  EXAM_CHECK( opts.is_set('t'));
  EXAM_CHECK( opts.is_set("temp") );
  EXAM_CHECK( !opts.is_set("unknow option") );
  EXAM_CHECK( !opts.is_set(h_token+1) );

  bool exception_happens = false;
  try {
    opts.get<int>('f');
  }
  catch(const logic_error& e) {
    exception_happens = true;
  }

  EXAM_CHECK( exception_happens );

  exception_happens = false;

  try {
    vector< string > vs;
    opts.getemall( h_token, back_inserter( vs ) );
  }
  catch ( const logic_error& e) {
    exception_happens = true;
  }

  EXAM_CHECK( exception_happens );

  return EXAM_RESULT;
}

int EXAM_IMPL(opts_test::add_get_opt)
{
  const char* argv[] = { "name", "-t" , "20" , "--name=maos" };
  int argc = sizeof( argv ) / sizeof(argv[0]);

  Opts opts;

  int t_token = (opts << option<int>( "", 't' )[10]).last_token();
  int name_token = (opts << option<string>( "", "name" )["soam"]).last_token();
  int port_token = (opts << option<int>( "", 'p', "port" )[80]).last_token();
  int num_token = (opts << option<int>( "number of elements", "num")[100]).last_token();

  try {
    opts.parse( argc, argv );
  }
  catch ( const Opts::unknown_option& e ) {
  }
  catch ( const Opts::arg_typemismatch& e ) {
  }

  EXAM_CHECK( opts.is_set('t') );
  EXAM_CHECK( opts.get_cnt(t_token) == 1 );
  EXAM_CHECK( opts.get<int>('t') == 20);
  EXAM_CHECK( opts.is_set(name_token) );
  EXAM_CHECK( opts.get_cnt("name") == 1 );
  EXAM_CHECK( opts.get<string>(name_token) == "maos");
  EXAM_CHECK( !opts.is_set('p') );

  return EXAM_RESULT;
}

int EXAM_IMPL(opts_test::option_position)
{
  const char* argv[] = { "name" , "--begin", "--f1", "--f2", "--end", "--f1", "--port=10" };
  int argc = sizeof( argv ) / sizeof(argv[0]);

  Opts opts;

  opts << option<int>( "listen tcp port", 'p', "port" )[0];
  opts << option<void>( "", "begin" );
  int f1_token = (opts << option<void>( "", "f1") ).last_token();
  int f2_token = (opts << option<void>( "", "f2") ).last_token();
  int no_such_token = 5000; // I hope no 5000 tests here
  opts << option<void>( "", "end" );

  try {
    opts.parse( argc, argv );
  
    EXAM_CHECK(opts.get_cnt('p') == 1);
    EXAM_CHECK(opts.get_cnt("begin") == 1);
    EXAM_CHECK(opts.get_cnt(f1_token) == 2);
    EXAM_CHECK(opts.get_cnt(f2_token) == 1);
    EXAM_CHECK(opts.get_cnt("end") == 1);
    EXAM_CHECK(opts.get_cnt("unknown") == 0);
    EXAM_CHECK(opts.get_cnt('u') == 0);
    EXAM_CHECK(opts.get_cnt(no_such_token) == 0);

    list<int> p_l( opts.get_cnt('p') );
    vector<int> b_v( opts.get_cnt("begin") );
    vector<int> f1_v( opts.get_cnt(f1_token) );
    vector<int> f2_v( opts.get_cnt(f2_token) );
    vector<int> e_v( opts.get_cnt("end") );
    list<int> u_l( opts.get_cnt("unknown") );

    opts.get_pos( 'p', p_l.begin() );
    opts.get_pos( "begin", b_v.begin() );
    opts.get_pos( "f1", f1_v.begin() );
    opts.get_pos( f2_token, f2_v.begin() );
    opts.get_pos( "end", e_v.begin() );

    try {
      opts.get_pos("unknown",u_l.begin());

      EXAM_ERROR( "Opts::unknown_option exception expected" );
    }
    catch(const Opts::unknown_option& e)
    {
      EXAM_MESSAGE( "Opts::unknown_option exception, as expected" );
    }
    
    EXAM_CHECK( !b_v.empty() && !e_v.empty() && e_v[0] > b_v[0] );
    EXAM_CHECK( f1_v.size() == 2 && f1_v[0] == 2 && f1_v[1] == 5 );
    EXAM_CHECK( !p_l.empty() && *p_l.begin() == 6 );
    EXAM_CHECK( u_l.empty() );
  }
  catch ( const Opts::unknown_option& e ) {
    EXAM_ERROR( "unexpected exception" );
  }
  catch ( const Opts::arg_typemismatch& e ) {
    EXAM_ERROR( "unexpected exception" );
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(opts_test::defaults)
{
  {
    const char* argv[] = { "name" };
    int argc = sizeof( argv ) / sizeof(argv[0]);

    Opts opts;

    opts << option<int>( "listen tcp port", 'p', "port" )[0];

    try {
      opts.parse( argc, argv );

      EXAM_CHECK( !opts.is_set( 'p' ) );
      EXAM_CHECK( opts.get<int>( 'p' ) == 0 );
    }
    catch ( const Opts::unknown_option& e ) {
      EXAM_ERROR( "unexpected exception" );
    }
    catch ( const Opts::arg_typemismatch& e ) {
      EXAM_ERROR( "unexpected exception" );
    }
    catch ( ... ) {
      EXAM_ERROR( "unexpected exception" );
    }
  }

  try {
    const char* argv[] = { "name", "-r", "10" };
    int argc = sizeof( argv ) / sizeof(argv[0]);
 
    Opts opts;

    opts << option<string>( "run tests by number", 'r', "run" )["0"];

    opts.parse( argc, argv );

    EXAM_CHECK( opts.is_set( 'r' ) );
    EXAM_CHECK( opts.get<string>( 'r' ) == "10" );
  }
  catch ( ... ) {
    EXAM_ERROR( "unexpected exception" );
  }

  try {
    const char* argv[] = { "name" };
    int argc = sizeof( argv ) / sizeof(argv[0]);
 
    Opts opts;

    opts << option<string>( "run tests by number", 'r', "run" )["20"];

    opts.parse( argc, argv );

    EXAM_CHECK( opts.is_set( 'r' ) == false ); // not set
    EXAM_CHECK( opts.get<string>( 'r' ) == "20" ); // but has default value
  }
  catch ( ... ) {
    EXAM_ERROR( "unexpected exception" );
  }

  try {
    const char* argv[] = { "name", "-r", "10" };
    int argc = sizeof( argv ) / sizeof(argv[0]);
 
    Opts opts;

    opts << option<string>( "run tests by number", 'r', "run" );

    opts.parse( argc, argv );

    EXAM_CHECK( opts.is_set( 'r' ) );
    EXAM_CHECK( opts.get<string>( 'r' ) == "10" );
  }
  catch ( const Opts::unknown_option& e ) {
    EXAM_ERROR( "unexpected Opts::unknown_option exception" );
  }
  catch ( const Opts::arg_typemismatch& e ) {
    EXAM_ERROR( "unexpected Opts::arg_typemismatch exception" );
  }
  catch( const std::logic_error& e ) {
    EXAM_ERROR( "unexpected std::logic_error exception" );
  }
  catch ( ... ) {
    EXAM_ERROR( "unexpected undefined exception" );
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(opts_test::bad_option)
{
  const char* argv[] = { "name", "-v" };
  int argc = sizeof( argv ) / sizeof(argv[0]);

  Opts opts;

  opts << option<void>( "print this help message", 'h', "help" );

  try {
    opts.parse( argc, argv );

    EXAM_ERROR( "exception expected" );
  }
  catch ( const Opts::unknown_option& e ) {
    EXAM_MESSAGE( "Opts::unknown_option exception, as expected" );
  }
  catch ( const Opts::arg_typemismatch& e ) {
    EXAM_ERROR( "Opts::unknown_option expected" );
  }
  catch ( ... ) {
    EXAM_ERROR( "Opts::unknown_option expected" );
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(opts_test::bad_argument)
{
  const char* argv[] = { "name", "--port=www" };
  int argc = sizeof( argv ) / sizeof(argv[0]);

  Opts opts;

  opts << option<int>( "listen tcp port", 'p', "port" )[10];

  try {
    opts.parse( argc, argv ); // <- exception here

    int t = opts.get<int>('p');

    EXAM_ERROR( "std::invalid_argument exception expected" );
  }
  catch ( const Opts::arg_typemismatch& e ) {
    EXAM_ERROR( "std::invalid_argument exception expected" );
  }
  catch ( const std::invalid_argument& e ) {
    EXAM_MESSAGE( "std::invalid_argument exception, as expected" );
  }
  catch ( ... ) {
    EXAM_ERROR( "std::invalid_argument exception expected" );
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(opts_test::unexpected_argument)
{
  const char* argv[] = { "name", "--help=10" };
  int argc = sizeof( argv ) / sizeof(argv[0]);

  Opts opts;

  opts << option<void>( "", 'h', "help" );

  try {
    opts.parse( argc, argv );

    EXAM_ERROR( "Opts::arg_typemismatch exception expected" );
  }
  catch( const Opts::arg_typemismatch& e ) {
    EXAM_MESSAGE( "Opts::arg_typemismatch exception, as expected" );
  }
  catch ( ... ) {
    EXAM_ERROR( "Opts::arg_typemismatch exception expected" );
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(opts_test::missing_argument)
{
  const char* argv[] = { "name", "-n" };
  int argc = sizeof( argv ) / sizeof(argv[0]);

  Opts opts;

  opts << option<int>( "", 'n', "num" )[10];

  try {
    opts.parse( argc, argv );

    EXAM_ERROR( "Opts::missing_arg exception expected" );
  }
  catch( const Opts::missing_arg& e ) {
    EXAM_MESSAGE( "Opts::missing_arg exception, as expected" );
  }
  catch ( ... ) {
    EXAM_ERROR( "Opts::missing_arg exception expected" );
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(opts_test::multiple)
{
  {
    const char* argv[] = { "name", "-vvv" };
    int argc = sizeof( argv ) / sizeof(argv[0]);

    Opts opts;

    opts << option<void>( "more trace messages", 'v', "verbose" );
    
    try {
      opts.parse( argc, argv );
    }
    catch ( ... ) {
      EXAM_ERROR( "unexpected exception" );
    }
    
    EXAM_CHECK( opts.get_cnt('v') == 3 );
  }

  {
    const char* argv[] = { "name", "-v", "-v", "-v" };
    int argc = sizeof( argv ) / sizeof(argv[0]);

    Opts opts;

    opts << option<void>( "more trace messages", 'v', "verbose" );
    
    try {
      opts.parse( argc, argv );
    }
    catch ( ... ) {
      EXAM_ERROR("unexpected exception");
    }

    EXAM_CHECK( opts.get_cnt('v') == 3 );
  }

  {
    const char* argv[] = { "name", "--verbose", "--verbose", "--verbose" };
    int argc = sizeof( argv ) / sizeof(argv[0]);

    Opts opts;

    opts << option<void>( "more trace messages", 'v', "verbose" );

    try {
      opts.parse( argc, argv );
    }
    catch( ... ) {
      EXAM_ERROR("unexpected exception");
    }

    EXAM_CHECK( opts.get_cnt('v') == 3 );
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(opts_test::compound)
{
  {
    const char* argv[] = { "name", "-abc" };
    int argc = sizeof( argv ) / sizeof(argv[0]);

    Opts opts;

    opts << option<void>( "option a", 'a', "a-option" );
    opts << option<void>( "option b", 'b', "b-option" );
    opts << option<void>( "option c", 'c', "c-option" );

    try {
      opts.parse( argc, argv );
    }
    catch ( ... ) {
      EXAM_ERROR("unexpected exception");
    }

    EXAM_CHECK(opts.is_set('a') && opts.is_set('b') && opts.is_set('c'));
  }


  return EXAM_RESULT;
}

int EXAM_IMPL(opts_test::multiple_compound)
{
  const char* argv[] = { "name", "-xf", "--flag", "-f", "-p=first", "--pa", "second" };
  int argc = sizeof( argv ) / sizeof(argv[0]);

  Opts opts;

  opts << option<void>( "option x", 'x', "x-option" );
  opts << option<void>( "option f", 'f', "flag" );
  
  opts << option<string>( "some path", 'p', "path" )["defaultpath"];
    
  try {
    opts.parse( argc, argv );
  }
  catch ( ... ) {
    EXAM_ERROR("unexpected exception");
  }

  EXAM_CHECK(opts.is_set('x'));
  EXAM_CHECK(opts.is_set("flag"));
  EXAM_CHECK(opts.is_set('p'));
  EXAM_CHECK(opts.get_cnt("flag") == 3 && opts.get_cnt('f') == 3);

  vector<string> vs;

  opts.getemall( "path", back_inserter( vs ) );

  vector<string>::iterator j = vs.begin();
  
  EXAM_CHECK( j != vs.end() );
  EXAM_CHECK( j->empty() );
  ++j;  
  
  EXAM_CHECK( j != vs.end() );
  EXAM_CHECK( *j == "defaultpath" );
  ++j;
  
  EXAM_CHECK( j != vs.end() );
  EXAM_CHECK( *j == "first" );
  ++j;
  EXAM_CHECK( j != vs.end() );
  EXAM_CHECK( *j == "second" );
  ++j;
  EXAM_CHECK( j == vs.end() );

  return EXAM_RESULT;
}

int EXAM_IMPL(opts_test::args)
{
  {
    const char* argv[] = { "name", "-f", "filename.conf", "file1", "file2"  };
    int argc = sizeof( argv ) / sizeof(argv[0]);

    Opts opts;

    opts << option<string>( "configuration file", 'f', "config" )["default.conf"];

    try {
      opts.parse( argc, argv );
    }
    catch ( ... ) {
      EXAM_ERROR("unexpected exception");
    }
    
    EXAM_CHECK( opts.get<string>("config") == "filename.conf" );

    EXAM_CHECK( argc == 3 );
    EXAM_CHECK( argv[0] == "name" );
    EXAM_CHECK( argv[1] == "file1" );
    EXAM_CHECK( argv[2] == "file2" );
  }

  {
    const char* argv[] = { "name", "file1", "file2", "-f", "filename.conf" };
    int argc = sizeof( argv ) / sizeof(argv[0]);

    Opts opts;

    opts << option<string>( "configuration file", 'f', "config" )["default.conf"];

    try {
      opts.parse( argc, argv );
    }
    catch ( ... ) {
      EXAM_ERROR("unexpected exception");
    }
    
    EXAM_CHECK( opts.get<string>('f') == "filename.conf" );

    EXAM_CHECK( argc == 3 );
    EXAM_CHECK( argv[0] == "name" );
    EXAM_CHECK( argv[1] == "file1" );
    EXAM_CHECK( argv[2] == "file2" );
  }

  {
    const char* argv[] = { "name", "file1", "-f", "filename.conf", "file2" };
    int argc = sizeof( argv ) / sizeof(argv[0]);

    Opts opts;

    opts << option<string>( "configuration file", 'f', "config" )["default.conf"];
    
    try {
      opts.parse( argc, argv );
    }
    catch ( ... ) {
      EXAM_ERROR("unexpected exception");
    }
    
    EXAM_CHECK( opts.get<string>('f') == "filename.conf" );

    EXAM_CHECK( argc == 3 );
    EXAM_CHECK( argv[0] == "name" );
    EXAM_CHECK( argv[1] == "file1" );
    EXAM_CHECK( argv[2] == "file2" );
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(opts_test::stop)
{
  {
    const char* argv[] = { "name", "-a", "--", "-f" };
    int argc = sizeof( argv ) / sizeof(argv[0]);

    Opts opts;

    opts << option<void>( "option a", 'a', "a-option" );

    try {
      opts.parse( argc, argv );
    }
    catch ( ... ) {
      EXAM_ERROR("unexpected exception");
    }

    EXAM_CHECK( argc == 2 );
    EXAM_CHECK( argv[1] == "-f" );
  }

  return EXAM_RESULT;
}

struct point
{
  point( int _x = 0, int _y = 0 ) :
      x(_x),
      y(_y)
      { }

    int x;
    int y;
};

istream& operator >>( istream& s, point& p )
{
  s >> p.x >> p.y;

  return s;
}
 
ostream& operator <<( ostream& s, const point& p )
{
  s << p.x << ' ' << p.y;

  return s;
}

int EXAM_IMPL(opts_test::user_defined)
{
  const char* argv[] = { "name", "-s", "1 2" };
  int argc = sizeof( argv ) / sizeof(argv[0]);

  Opts opts;

  opts << option<point>( "start point", 's', "start-point" )[point(1,1)];

  try {
    opts.parse( argc, argv );
  }
  catch ( ... ) {
    EXAM_ERROR("unexpected exception");
  }

  point p = opts.get<point>( 's' );

  EXAM_CHECK( (p.x == 1) && (p.y == 2) );

  return EXAM_RESULT;
}

// check whether autocomplement works
int EXAM_IMPL(opts_test::autocomplement)
{
  const char* argv[] = { "name" , "--num", "4" };
  int argc = sizeof( argv ) / sizeof(argv[0]);

  Opts opts;

  opts << option<int>( "number of processors", 'n', "number_of_processors" )[1];

  try {
    opts.parse( argc, argv );
  }
  catch ( ... ) {
    EXAM_ERROR("unexpected exception");
  }

  EXAM_CHECK( opts.get<int>('n') == 4 );

  return EXAM_RESULT; 
}

int EXAM_IMPL(opts_test::autocomplement_failure)
{
  const char* argv[] = { "name" , "--proc" , "4" };
  int argc = sizeof( argv ) / sizeof(argv[0]);

  Opts opts;

  opts << option<int>( "process number", 'p', "proc_num" )[1];
  opts << option<string>( "process type", 't', "proc_type" )["standard"];

  try {
    opts.parse( argc, argv );

    EXAM_ERROR( "Opts::unknown_option exception expected" );
  }
  catch (const Opts::unknown_option& e) {
    EXAM_MESSAGE( "Opts::unknown_option exception, as expected" );
  }
  catch ( ... ) {
    EXAM_ERROR( "Opts::unknown_option exception expected" );
  }

  return EXAM_RESULT; 
}

int EXAM_IMPL(opts_test::multiple_args)
{
  const char* argv[] = { "name" , "-I", "first", "-I", "second", "-I", "third" };
  int argc = sizeof( argv ) / sizeof(argv[0]);

  Opts opts;

  opts << option<string>( "include paths", 'I', "include" )[ "/usr/include" ];
  
  try {
    opts.parse( argc, argv );
  }
  catch ( ... ) {
    EXAM_ERROR("unexpected exception");
  }

  vector<string> vs;
  
  opts.getemall( 'I', back_inserter(vs) );

  vector<string>::iterator j = vs.begin();
  
  EXAM_CHECK( j != vs.end() );
  EXAM_CHECK( j->empty() );
  ++j;  
  
  
  EXAM_CHECK( j != vs.end() );
  EXAM_CHECK( *j == "/usr/include" );
  ++j;

  EXAM_CHECK( j != vs.end() );
  EXAM_CHECK( *j == "first" );
  ++j;
  
  EXAM_CHECK( j != vs.end() );
  EXAM_CHECK( *j == "second" );
  
  ++j;
  EXAM_CHECK( j != vs.end() );
  EXAM_CHECK( *j == "third" );

  ++j;
  EXAM_CHECK( j == vs.end() );

  return EXAM_RESULT; 
}

int EXAM_IMPL(opts_test::help)
{
  const char* argv[] = { "programname" , "--help" };
  int argc = sizeof( argv ) / sizeof(argv[0]);

  Opts opts;

  opts.description( "test for printing help message" );
  opts.usage( "[options] file-from file-to" );
  opts.author( "B. L. User" );
  opts.copyright( "Copyright (C) Youyoudine, 2008" );

  opts << option<void>( "print this help message", 'h', "help" );
  opts << option<void>( "some program flag", "flag" );
  opts << option<void>( "print version", 'v', "version" );
  opts << option<string>( "include paths", 'I', "include" )["/usr/include"];
  opts << option<int>( "listen to tcp port", 'p', "port" )[80];
  opts << option<string>( "program mode", "mode" )["standard"];
    
  try {
    opts.parse( argc, argv );
  }
  catch ( ... ) {
    EXAM_ERROR("unexpected exception");
  }

  EXAM_CHECK( opts.is_set('h') );
  EXAM_CHECK( opts.get_pname() == "programname" );

  stringstream s;

  opts.help( s );

  const char sample[] =
"\n\
This is programname, test for printing help message\n\
\n\
B. L. User\n\
\n\
Copyright (C) Youyoudine, 2008\n\
\n\
Usage:\n\
\n\
  programname [options] file-from file-to\n\
\n\
Available options:\n\
\n\
  -h, --help\tprint this help message\n\
  --flag\tsome program flag\n\
  -v, --version\tprint version\n\
  -I <string>, --include=<string>\tinclude paths [/usr/include]\n\
  -p <i>, --port=<i>\tlisten to tcp port [80]\n\
  --mode=<string>\tprogram mode [standard]\n\
\n";

  EXAM_CHECK( s.str() == sample );

  return EXAM_RESULT; 
}

int EXAM_IMPL(opts_test::long_string)
{
  {
    const char* argv[] = { "name", "--string", "long string" };
    int argc = sizeof( argv ) / sizeof(argv[0]);
    
    Opts opts;

    opts << option<string>( "some string param", 's', "string" )["default value"];
  
    try {
      opts.parse( argc, argv );
    }
    catch ( ... ) {
      EXAM_ERROR("unexpected exception");
    }

    EXAM_CHECK( opts.get<string>( 's' ) == "long string" );
  }

  {
    const char* argv[] = { "name" };
    int argc = sizeof( argv ) / sizeof(argv[0]);
    
    Opts opts;

    opts << option<string>( "some string param", 's', "string" )["default value"];
  
    try {
      opts.parse( argc, argv );
    }
    catch ( ... ) {
      EXAM_ERROR("unexpected exception");
    }

    EXAM_CHECK( opts.get<string>( 's' ) == "default value" );
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(opts_test::named_param)
{
  const char* argv[] = { "program" };
  int argc = sizeof( argv ) / sizeof(argv[0]);

  Opts opts;

  opts << option<string>( "server name <host>", 's', "server" )
       << option<char*>( "name <name>", 'n', "name" )
       << option<int>( "port <port>", 'p', "port" )[1234];

  opts.parse( argc, argv );

  stringstream s;

  opts.help( s );

  const char sample[] = 
"\n\
This is program\n\
\n\
Usage:\n\
\n\
  program \n\
\n\
Available options:\n\
\n\
  -s <host>, --server=<host>\tserver name <host> []\n\
  -n <name>, --name=<name>\tname <name> []\n\
  -p <port>, --port=<port>\tport <port> [1234]\n\
\n";

   //cerr << s.str();
   //string st = s.str();
   //string::size_type n = mismatch(st.begin(), st.end(), sample ).first - st.begin();
   //cerr << n << endl;

   //cerr << '#' << st.substr( n ) << endl;
  
  EXAM_CHECK( s.str() == sample );

  return EXAM_RESULT;
}

int EXAM_IMPL(opts_test::z_bug)
{
  const char* argv[] = { "name", "--rz=dbmeta-rz.mail.yandex.ru", "--rzc=4392" };
  int argc = sizeof( argv ) / sizeof(argv[0]);

  Opts opts;

  opts << option<string>( "RZ server <host>", "rz" )["localhost"]
       << option<int>( "RZ server control <port>", "rzcontrol" )[4391]
       << option<int>( "RZ server query <port>", "rzquery" )[4390];

  try {
    opts.parse( argc, argv );
  
    EXAM_CHECK( opts.get<string>( "rz" ) == "dbmeta-rz.mail.yandex.ru" );
    // EXAM_CHECK( opts.get<int>( "rzcontrol" ) == 4392 );
  }
  catch( const Opts::arg_typemismatch& e ) {
    EXAM_ERROR( "Opts::arg_typemismatch exception" );
  }
  catch ( const Opts::unknown_option& ) {
    EXAM_ERROR( "Opts::unknown_option exception" );
  }
  catch( const Opts::missing_arg& ) {
    EXAM_ERROR( "Opts::missing_arg exception" );
  }
  catch ( ... ) {
    EXAM_ERROR( "unexpected exception" );
  }

  return EXAM_RESULT;
}

int EXAM_IMPL(opts_test::z_bug_reorder)
{
  const char* argv[] = { "name", "--rzqu=4392", "--rz=dbmeta-rz.mail.yandex.ru" };
  int argc = sizeof( argv ) / sizeof(argv[0]);

  Opts opts;

  opts << option<int>( "RZ server query <port>", "rzquery" )[4390]
       << option<int>( "RZ server control <port>", "rzcontrol" )[4391]
       << option<string>( "RZ server <host>", "rz" )["localhost"];

  try {
    opts.parse( argc, argv );
  
    EXAM_CHECK( opts.get<string>( "rz" ) == "dbmeta-rz.mail.yandex.ru" );
    EXAM_CHECK( opts.get<int>( "rzquery" ) == 4392 );
  }
  catch( const Opts::arg_typemismatch& e ) {
    EXAM_ERROR( "Opts::arg_typemismatch exception" );
  }
  catch ( const Opts::unknown_option& ) {
    EXAM_ERROR( "Opts::unknown_option exception" );
  }
  catch( const Opts::missing_arg& ) {
    EXAM_ERROR( "Opts::missing_arg exception" );
  }
  catch ( ... ) {
    EXAM_ERROR( "unexpected exception" );
  }

  return EXAM_RESULT;
}
