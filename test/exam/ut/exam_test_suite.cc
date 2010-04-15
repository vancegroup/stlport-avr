// -*- C++ -*- Time-stamp: <07/09/04 11:11:41 ptr>

/*
 * Copyright (c) 2007
 * Petr Ovtchenkov
 *
 * Licensed under the Academic Free License Version 3.0
 */

#include "exam_test_suite.h"
#include <iostream>

#include "dummy_test.cc"

int EXAM_IMPL(exam_basic_test::function_good)
{
  buff.str( "" );
  buff.clear();

  exam::test_suite t( "exam self test, good function" );
  t.set_logger( &logger );

  test_x tx;
  t.add( func_good, "function" );
  t.add( &test_x::f_good, tx, "member function" );

  t.girdle();

  EXAM_REQUIRE( buff.str() == r0 );

  // std::cerr << "%%%\n";
  // std::cerr << buff.str() << std::endl;
  // std::cerr << "%%%\n";

  return EXAM_RESULT;
}

int EXAM_IMPL(exam_basic_test::function)
{
  buff.str( "" );
  buff.clear();

  exam::test_suite t( "exam self test, fail function" );
  t.set_logger( &logger );

  test_x tx;
  t.add( func, "function" );
  t.add( &test_x::f, tx, "member function" );

  t.girdle();

  // std::cerr << "%%%\n";
  // std::cerr << buff.str() << std::endl;
  // std::cerr << "%%%\n";
  // std::cerr << "^^^\n";
  // std::cerr << r1 << std::endl;
  // std::cerr << "^^^\n";

  EXAM_REQUIRE( buff.str() == r1 );

  return EXAM_RESULT;
}

int EXAM_IMPL(exam_basic_test::dep)
{
   buff.str( "" );
   buff.clear();

   exam::test_suite t( "exam self test, fail function" );
   t.set_logger( &logger );

   test_x tx;
   t.add( func_good, "function good", // "child"
   t.add( &test_x::f_good, tx, "member function good" ) ); // "parent"
   t.add( func, "function fail", // <- skiped, because depends upon failed (next line)
   t.add( &test_x::f, tx, "member function fail" ) ); // <- fail

   t.girdle();

   EXAM_REQUIRE( buff.str() == r2 );

   // std::cerr << "%%%\n";
   // std::cerr << buff.str() << std::endl;
   // std::cerr << "%%%\n";

   return EXAM_RESULT;
}

int EXAM_IMPL(exam_basic_test::trace)
{
  buff.str( "" );
  buff.clear();

  exam::test_suite t( "exam self test, fail function" );
  t.set_logger( &logger );

  logger.flags( exam::base_logger::trace_suite );

  test_x tx;
  t.add( func_good, "function good", // "child"
  t.add( &test_x::f_good, tx, "member function good" ) ); // "parent"
  t.add( func, "function fail", // <- skiped, because depends upon failed (next line)
  t.add( &test_x::f, tx, "member function fail" ) ); // <- fail

  t.girdle();

  EXAM_REQUIRE( buff.str() == r3 );

  buff.str( "" );
  buff.clear();

  logger.flags( exam::base_logger::silent );

  t.girdle();

  EXAM_REQUIRE( buff.str() == r4 );

  buff.str( "" );
  buff.clear();

  logger.flags( exam::base_logger::trace );

  t.girdle();

  EXAM_REQUIRE( buff.str() == r5 );

  buff.str( "" );
  buff.clear();

  logger.flags( exam::base_logger::verbose );

  t.girdle();

  logger.flags( 0 );

  EXAM_REQUIRE( buff.str() == r6 );

  // std::cerr << "%%%\n";
  // std::cerr << buff.str() << std::endl;
  // std::cerr << "%%%\n";

  return EXAM_RESULT;
}

int EXAM_IMPL(exam_basic_test::dep_test_suite)
{
  buff.str( "" );
  buff.clear();

  exam::test_suite t0( "exam self test, test suite master" );
  t0.set_logger( &logger );

  test_x tx0;
  t0.add( func_good, "function" );
  t0.add( &test_x::f_good, tx0, "member function" );

  exam::test_suite t1( "exam self test, test suite slave" );
  t1.set_logger( &logger );

  test_x tx1;
  t1.add( func_good, "function good", // "child"
  t1.add( &test_x::f_good, tx1, "member function good" ) ); // "parent"
  t1.add( func, "function fail", // <- skiped, because depends upon failed (next line)
  t1.add( &test_x::f, tx1, "member function fail" ) ); // <- fail

  exam::test_suite t( "exam self test, test suites dependency" );
  t.set_logger( &logger );

  t.add( &exam::test_suite::run, t1, "slave test suite",
  t.add( &exam::test_suite::run, t0, "master test suite" ) );

  t.girdle();

  EXAM_REQUIRE( buff.str() == r7 );

  // std::cerr << "%%%\n";
  // std::cerr << buff.str() << std::endl;
  // std::cerr << "%%%\n";

  return EXAM_RESULT;
}

int EXAM_IMPL(exam_basic_test::multiple_dep)
{
  buff.str( "" );
  buff.clear();
  
  exam::test_suite t( "exam self test, fail function" );
  t.set_logger( &logger );

  test_x tx;

  exam::test_suite::test_case_type tc[2];

  tc[0] = t.add( &test_x::f_good, tx, "member function good" );
  tc[1] = t.add( func_good, "function good" );

  t.add( func, "function fail", tc, tc + 2 );
  t.add( &test_x::f, tx, "member function fail", tc, tc + 2 );
  t.add( func_good2, "function 2 good", tc, tc + 2 );

  t.girdle();

  EXAM_REQUIRE( buff.str() == r8 );

  // std::cerr << "%%%\n";
  // std::cerr << buff.str() << std::endl;
  // std::cerr << "%%%\n";

  return EXAM_RESULT;
}

int EXAM_IMPL(exam_basic_test::multiple_dep_complex)
{
  buff.str( "" );
  buff.clear();
  
  exam::test_suite t( "exam self test, fail function" );
  t.set_logger( &logger );

  test_x tx;

  exam::test_suite::test_case_type tc[2];
  exam::test_suite::test_case_type tcx[2];

  tc[0] = t.add( &test_x::f_good, tx, "member function good" );
  tc[1] = t.add( func_good, "function good" );

  tcx[0] = t.add( func, "function fail", tc, tc + 2 );
  t.add( &test_x::f, tx, "member function fail", tc, tc + 2 );
  tcx[1] = t.add( func_good2, "function 2 good", tc, tc + 2 );
  t.add( func_good3, "function 3 good", tcx, tcx + 2 ); //  <-- problem

  // logger.flags( exam::base_logger::verbose );
  t.girdle();
  // logger.flags( 0 );

  EXAM_REQUIRE( buff.str() == r9 );

  // std::cerr << "%%%\n";
  // std::cerr << buff.str() << std::endl;
  // std::cerr << "%%%\n";

  return EXAM_RESULT;
}

int EXAM_IMPL(exam_basic_test::perf)
{
#if 1
  throw exam::skip_exception();
#else
  buff.str( "" );
  buff.clear();
  
  exam::test_suite t( "exam self test, time profile", 20 );
  t.set_logger( &tlogger );

  t.add( loop, "timer" );

  t.girdle();

  double mean = -1.0;
  double disp = -1.0;
  std::string nm;

  buff >> mean >> disp; // >> nm;

  EXAM_CHECK( mean >= 0.0 );
  EXAM_CHECK( disp >= 0.0 );

  std::getline( buff, nm );

  EXAM_CHECK( nm == " timer" );

  std::getline( buff, nm );

  EXAM_CHECK( nm == "*** PASS exam self test, time profile (+1-0~0/1) ***" );
  
  // std::cerr << buff.str() << std::endl; 
#endif

  return EXAM_RESULT;
}

int EXAM_IMPL(exam_basic_test::dry)
{
  buff.str( "" );
  buff.clear();

  exam::test_suite t( "exam self test, fail function" );
  t.set_logger( &logger );

  test_x tx;

  exam::test_suite::test_case_type tc[2];
  exam::test_suite::test_case_type tcx[2];

  tc[0] = t.add( &test_x::f_good, tx, "member function good" );
  tc[1] = t.add( func_good, "function good" );

  tcx[0] = t.add( func, "function fail", tc, tc + 2 );
  t.add( &test_x::f, tx, "member function fail", tc, tc + 2 );
  tcx[1] = t.add( func_good2, "function 2 good", tc, tc + 2 );
  t.add( func_good3, "function 3 good", tcx, tcx + 2 ); //  <-- problem
  t.add( &test_x::f_good, tx, "member function good 2" );

  logger.flags( exam::base_logger::verbose );
  t.dry_girdle();
  logger.flags( 0 );

  //  std::cerr << "%%%\n";
  //  std::cerr << buff.str();
  //  std::cerr << "%%%\n";
  //  std::cerr << r10 << std::endl;
  //  std::cerr << "%%%\n";
  //  int j = 0;
  //  while ( (j < buff.str().length()) && (buff.str().at(j) == r10[j]) ) {
  //    ++j;
  //  }
  //  std::cerr << buff.str().substr(j) << "; " << j << " " << int(buff.str().at(j)) << " " << int(r10[j]) << std::endl;

  EXAM_REQUIRE( buff.str() == r10 );

  return EXAM_RESULT;
}

int EXAM_IMPL(exam_basic_test::single)
{
  buff.str( "" );
  buff.clear();

  exam::test_suite t( "exam self test, fail function" );
  t.set_logger( &logger );

  test_x tx;

  exam::test_suite::test_case_type tc[2];
  exam::test_suite::test_case_type tcx[2];

  tc[0] = t.add( &test_x::f_good, tx, "member function good" );
  tc[1] = t.add( func_good, "function good" );

  tcx[0] = t.add( func, "function fail", tc, tc + 2 );
  t.add( &test_x::f, tx, "member function fail", tc, tc + 2 );
  tcx[1] = t.add( func_good2, "function 2 good", tc, tc + 2 );
  t.add( func_good3, "function 3 good", tcx, tcx + 2 ); //  <-- problem
  t.add( &test_x::f_good, tx, "member function good 2" );

  logger.flags( exam::base_logger::verbose );
  t.single( t.test_by_name( "function 3 good" ) );
  logger.flags( 0 );

  EXAM_REQUIRE( buff.str() == r11 );

  return EXAM_RESULT;
}

const std::string exam_basic_test::r0 = "\
*** PASS exam self test, good function (+2-0~0/2) ***\n";

const std::string exam_basic_test::r1 = "\
dummy_test.cc:14: fail: false\n\
  FAIL function\n\
dummy_test.cc:25: fail: false\n\
  FAIL member function\n\
*** FAIL exam self test, fail function (+0-2~0/2) ***\n";

const std::string exam_basic_test::r2 = "\
dummy_test.cc:25: fail: false\n\
  FAIL member function fail\n\
  SKIP function fail\n\
*** FAIL exam self test, fail function (+2-1~1/4) ***\n";

const std::string exam_basic_test::r3 = "\
== Begin test suite\n\
dummy_test.cc:25: fail: false\n\
  FAIL member function fail\n\
  SKIP function fail\n\
==  End test suite\n\
*** FAIL exam self test, fail function (+2-1~1/4) ***\n";

const std::string exam_basic_test::r4 = "\
*** FAIL exam self test, fail function (+2-1~1/4) ***\n";

const std::string exam_basic_test::r5 = "\
dummy_test.cc:33: pass: true\n\
dummy_test.cc:34: pass: true\n\
dummy_test.cc:25: fail: false\n\
dummy_test.cc:26: pass: true\n\
  FAIL member function fail\n\
dummy_test.cc:42: pass: true\n\
  SKIP function fail\n\
*** FAIL exam self test, fail function (+2-1~1/4) ***\n";

const std::string exam_basic_test::r6 = "\
  PASS member function good\n\
dummy_test.cc:25: fail: false\n\
  FAIL member function fail\n\
  PASS function good\n\
  SKIP function fail\n\
*** FAIL exam self test, fail function (+2-1~1/4) ***\n";

const std::string exam_basic_test::r7 = "\
*** PASS exam self test, test suite master (+2-0~0/2) ***\n\
dummy_test.cc:25: fail: false\n\
  FAIL member function fail\n\
  SKIP function fail\n\
*** FAIL exam self test, test suite slave (+2-1~1/4) ***\n\
  FAIL slave test suite\n\
*** FAIL exam self test, test suites dependency (+1-1~0/2) ***\n";

const std::string exam_basic_test::r8 = "\
dummy_test.cc:14: fail: false\n\
  FAIL function fail\n\
dummy_test.cc:25: fail: false\n\
  FAIL member function fail\n\
*** FAIL exam self test, fail function (+3-2~0/5) ***\n";

const std::string exam_basic_test::r9 = "\
dummy_test.cc:14: fail: false\n\
  FAIL function fail\n\
dummy_test.cc:25: fail: false\n\
  FAIL member function fail\n\
  SKIP function 3 good\n\
*** FAIL exam self test, fail function (+3-2~1/6) ***\n";

const std::string exam_basic_test::r10 = "\
  DRY \n\
    DRY member function good\n\
    DRY function good\n\
    DRY member function good 2\n\
        DRY function fail\n\
        DRY member function fail\n\
        DRY function 2 good\n\
                DRY function 3 good\n\
*** PASS exam self test, fail function (+0-0~8/8) ***\n";

const std::string exam_basic_test::r11 = "\
  PASS function 3 good\n\
*** PASS exam self test, fail function (+1-0~0/1) ***\n";

int EXAM_IMPL(exam_self_test)
{
  exam::test_suite t( "exam self test" );
  exam_basic_test exam_basic;

  exam::test_suite::test_case_type d0 = t.add( &exam_basic_test::function_good, exam_basic, "call test, good calls" );
  t.add( &exam_basic_test::function, exam_basic, "call test, fail calls", d0 );
  exam::test_suite::test_case_type d = t.add( &exam_basic_test::dep, exam_basic, "call test, tests dependency", d0 );
  t.add( &exam_basic_test::trace, exam_basic, "trace flags test", d );
  t.add( &exam_basic_test::dep_test_suite, exam_basic, "test suites grouping", d );
  exam::test_suite::test_case_type d2 = t.add( &exam_basic_test::multiple_dep, exam_basic, "multiple dependencies", d );
  t.add( &exam_basic_test::multiple_dep_complex, exam_basic, "complex multiple dependencies", d2 );

  t.add( &exam_basic_test::perf, exam_basic, "performance timer test", d0 );
  t.add( &exam_basic_test::dry, exam_basic, "complex multiple dependencies, dry run", d2 );
  t.add( &exam_basic_test::single, exam_basic, "complex multiple dependencies, single test", d2 );

  return t.girdle();
}
