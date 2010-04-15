// -*- C++ -*- Time-stamp: <09/06/06 00:40:55 ptr>

/*
 * Copyright (c) 2007-2009
 * Petr Ovtchenkov
 *
 * Licensed under the Academic Free License Version 3.0
 *
 */

#include "opts_test.h"

// #include <config/feature.h>

void options_test_suite_init( exam::test_suite& t, opts_test& opts )
{
  exam::test_suite::test_case_type tc[10];

  tc[0] = 
    t.add( &opts_test::flag_option_long, opts, "simple flag(void) option, long" , 
         t.add( &opts_test::flag_option, opts, "simple flag(void) option" ) );

  tc[1] =
    t.add( &opts_test::int_option_long, opts, "option with int parameter, long",
         t.add( &opts_test::int_option, opts, "option with int parameter" ) );

  t.add( &opts_test::add_check_flag, opts, "add_check_flag", tc[0] );
  t.add( &opts_test::add_get_opt, opts, "add_get_opts", tc[1] ); 
  t.add( &opts_test::option_position, opts, "option position", tc[0] );
  t.add( &opts_test::defaults, opts, "defaults", tc[1] );
  t.add( &opts_test::bad_option, opts, "bad option", tc[0] );
  t.add( &opts_test::bad_argument, opts, "bad argument", tc[1] );
  t.add( &opts_test::unexpected_argument, opts, "unexpected_argument", tc[0] );
  t.add( &opts_test::missing_argument, opts, "missing argument", tc[1] );
  
  t.add( &opts_test::user_defined, opts, "user-defined type" );

  tc[2] = t.add( &opts_test::compound, opts, "compound", tc[0] );

  tc[3] = t.add( &opts_test::multiple, opts, "multiple", tc[0] );

  t.add( &opts_test::multiple_compound, opts, "multiple_compound", tc + 2, tc + 4 );

  t.add( &opts_test::args, opts, "args" );

  t.add( &opts_test::stop, opts, "stop", tc, tc + 2 ); 
  
  // check whether autocomplement works
  tc[4] = t.add( &opts_test::autocomplement, opts, "autocomplement", tc[1] ); 
  tc[7] = t.add( &opts_test::autocomplement_failure, opts, "autocomplement_failure", tc[4] );

  t.add( &opts_test::multiple_args, opts, "multiple_args", tc[3] );

  tc[5] = t.add( &opts_test::help, opts, "help", tc, tc + 2 );
  tc[6] = t.add( &opts_test::long_string, opts, "long string" );

  t.add( &opts_test::z_bug_reorder, opts, "autocomplement and precise match, reorder",
    t.add( &opts_test::z_bug, opts, "autocomplement and precise match", tc + 6, tc + 8 ) );

  t.add( &opts_test::named_param, opts, "named parameter", tc[5] );
}
