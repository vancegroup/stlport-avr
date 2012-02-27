// -*- C++ -*- Time-stamp: <2012-02-27 21:50:24 ptr>

/*
 * Copyright (c) 2008-2011
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

#include <exam/suite.h>

#include <misc/opts.h>
#include <string>
#include <sstream>

#include "type_traits_test.h"
#include "ratio_test.h"
#include "vector_test.h"
#include "deque_test.h"
#include "list_test.h"
#include "forward_list_test.h"
#include "string_test.h"
#include "cstring_test.h"
#include "map_test.h"
#include "set_operations_test.h"
#include "numerics.h"
#include "stream_test.h"
#include "alg_test.h"
#include "functor_test.h"
#include "sort_test.h"
#include "perm_test.h"
#include "partition_test.h"
#include "iter_test.h"
#include "bind_test.h"
#include "partial_test.h"
#include "heap_test.h"
#include "binary_test.h"
#include "rotate_test.h"
#include "unique_test.h"
#include "ptr2_test.h"
#include "utility_test.h"
#include "rndshf_test.h"
#include "nthelm_test.h"
#include "includes_test.h"
#include "inplace_test.h"
#include "rope_test.h"
#include "unary_test.h"
#include "allocator_test.h"
#include "ptrspec_test.h"
#include "limits_test.h"
#include "mfunptr_test.h"
#include "uninitialized_test.h"
#include "bitset_test.h"
#include "cmath_test.h"
#include "config_test.h"
#include "exception_test.h"
#include "num_put_get_test.h"
#include "codecvt_test.h"
#include "shared_ptr_test.h"
#include "reference_wrapper_test.h"
#include "errno_test.h"
#include "locale_test.h"
#include "chrono_test.h"
#include "null_ptr.h"
#include "thread_test.h"

int main( int argc, const char** argv )
{
  Opts opts;

  opts.description( "test suite for 'sockios' framework" );
  opts.usage( "[options]" );

  opts << option<void>( "print this help message", 'h', "help" )
       << option<void>( "list all test cases", 'l', "list" )
       << option<std::string>( "run tests by number", 'r', "run" )["0"]
       << option<void>( "print status of tests within test suite", 'v', "verbose" )
       << option<void>(  "trace checks", 't', "trace" );

  try {
    opts.parse( argc, argv );
  }
  catch (...) {
    opts.help( std::cerr );
    return 1;
  }

  if ( opts.is_set( 'h' ) ) {
    opts.help( std::cerr );
    return 0;
  }

  exam::test_suite t( "STLport test" );

  type_traits_test ttt;
  exam::test_suite::test_case_type tt_tc[10];

  tt_tc[0] = t.add( &type_traits_test::type_traits_internals, ttt, "traits_internals" );

  t.add( &type_traits_test::type_traits_is_void, ttt, "is_void", tt_tc[0] );
  tt_tc[1] = t.add( &type_traits_test::type_traits_is_integral, ttt, "is_integral", tt_tc[0] );
  tt_tc[2] = t.add( &type_traits_test::type_traits_is_floating_point, ttt, "is_floating_point", tt_tc[0] );
  t.add( &type_traits_test::type_traits_is_array, ttt, "is_array", tt_tc[0] );
  t.add( &type_traits_test::type_traits_is_pointer, ttt, "is_pointer", tt_tc[0] );
  t.add( &type_traits_test::type_traits_is_lvalue_reference, ttt, "is_lvalue_reference",
    t.add( &type_traits_test::type_traits_is_rvalue_reference_neg, ttt, "is_rvalue_reference negative", tt_tc[0] ) );

  tt_tc[5] = t.add( &type_traits_test::type_traits_is_member_object_pointer, ttt, "is_member_object_pointer", tt_tc[0] );
  tt_tc[6] = t.add( &type_traits_test::type_traits_is_member_function_pointer, ttt, "is_member_function_pointer", tt_tc[0] );

  t.add( &type_traits_test::type_traits_is_enum, ttt, "is_enum", tt_tc[0] );
  tt_tc[7] = t.add( &type_traits_test::type_traits_is_function, ttt, "is_function", tt_tc[0] );

  // [20.4.4.2]
  t.add( &type_traits_test::type_traits_is_reference, ttt, "is_reference", tt_tc[0] );
  tt_tc[3] = t.add( &type_traits_test::type_traits_is_arithmetic, ttt, "is_arithmetic", tt_tc + 1, tt_tc + 3 );
  t.add( &type_traits_test::type_traits_is_fundamental, ttt, "is_fundamental", tt_tc[3] );

  t.add( &type_traits_test::type_traits_is_object, ttt, "is_object", tt_tc[0] );
  t.add( &type_traits_test::type_traits_is_scalar, ttt, "is_scalar", tt_tc[0] );
  t.add( &type_traits_test::type_traits_is_compound, ttt, "is_compound", tt_tc[0] );
  tt_tc[8] = t.add( &type_traits_test::type_traits_is_member_pointer, ttt, "is_member_pointer", tt_tc[0] );

  // [20.4.4.3]
  t.add( &type_traits_test::type_traits_is_const, ttt, "is_const", tt_tc[0] );
  t.add( &type_traits_test::type_traits_is_volatile, ttt, "is_volatile", tt_tc[0] );
  t.add( &type_traits_test::type_traits_is_trivial, ttt, "is_trivial", tt_tc[0] );
  t.add( &type_traits_test::type_traits_is_standard_layout, ttt, "is_standard_layout", tt_tc[0] );
  tt_tc[4] = t.add( &type_traits_test::type_traits_is_pod, ttt, "is_pod", tt_tc[0] );
  t.add( &type_traits_test::type_traits_is_pod_compiler_supp, ttt, "is_pod_compiler_supp", tt_tc[4] );
  t.add( &type_traits_test::type_traits_is_empty, ttt, "is_empty", tt_tc[0] );

  t.add( &type_traits_test::type_traits_is_union, ttt, "is_union", tt_tc[0] );
  t.add( &type_traits_test::type_traits_is_union, ttt, "is_class", tt_tc[0] );

  t.add( &type_traits_test::is_constructible, ttt, "is_constructible", tt_tc[0] );

  t.add( &type_traits_test::is_assignable, ttt, "is_assignable", tt_tc[0] );

  t.add( &type_traits_test::is_destructible, ttt, "is_destructible", tt_tc[0] );

  t.add( &type_traits_test::is_trivially_copyable, ttt, "is_trivially_copyable", tt_tc[0] );

  t.add( &type_traits_test::add_reference, ttt, "add reference",
    t.add( &type_traits_test::remove_reference, ttt, "remove_reference", tt_tc[0] ) );

  t.add( &type_traits_test::result_of, ttt, "result_of", tt_tc + 5, tt_tc + 9 );

  null_ptr_test np_tst;

  t.add( &null_ptr_test::convert, np_tst, "null_ptr compare" );

  ratio_test ratio_tst;
  exam::test_suite::test_case_type r_tc[2];

  r_tc[0] = t.add( &ratio_test::ratio, ratio_tst, "ratio", tt_tc[0] );

  chrono_test chrono_tst;

  t.add( &chrono_test::system_clock, chrono_tst, "system clock",
    t.add( &chrono_test::duration_arithmetic, chrono_tst, "duration arithmetic",
      t.add( &chrono_test::duration_ctor, chrono_tst, "duration ctor", r_tc[0] ) ) );

  vector_test vec_test;

  exam::test_suite::test_case_type vec_tc[16];

  t.add( &vector_test::vec_test_1, vec_test, "vec_test_1" );
  t.add( &vector_test::vec_test_2, vec_test, "vec_test_2" );
  t.add( &vector_test::vec_test_3, vec_test, "vec_test_3" );
  t.add( &vector_test::vec_test_4, vec_test, "vec_test_4" );
  t.add( &vector_test::vec_test_5, vec_test, "vec_test_5" );
  t.add( &vector_test::vec_test_6, vec_test, "vec_test_6" );
  t.add( &vector_test::vec_test_7, vec_test, "vec_test_7" );
  t.add( &vector_test::capacity, vec_test, "vector capacity" );
  t.add( &vector_test::at, vec_test, "vector at" );
  t.add( &vector_test::pointer, vec_test, "vector pointer" );
  t.add( &vector_test::auto_ref, vec_test, "vector auto_ref" );
  t.add( &vector_test::allocator_with_state, vec_test, "vector allocator_with_state" );
  vec_tc[12] = t.add( &vector_test::iterators, vec_test, "vector iterators" );
  t.add( &vector_test::optimizations_check, vec_test, "vector optimizations_check" );
  t.add( &vector_test::assign_check, vec_test, "vector assign_check" );
  t.add( &vector_test::ebo, vec_test, "vector ebo" );

  bvector_test bvc_test;

  t.add( &bvector_test::bvec1, bvc_test, "bvec1" );

  deque_test deq_test;

  exam::test_suite::test_case_type deque_test_dep[5];

  t.add( &deque_test::deque1, deq_test, "deque1" );
  t.add( &deque_test::at, deq_test, "deque at" );
  t.add( &deque_test::fill_trivial, deq_test, "deque fill by type with trivial ctor",
    deque_test_dep[0] = t.add( &deque_test::insert, deq_test, "deque insert" ) );
  t.add( &deque_test::fill_non_trivial, deq_test, "deque fill by type with non-trivial ctor", deque_test_dep[0] );
  t.add( &deque_test::erase, deq_test, "deque erase" );
  t.add( &deque_test::auto_ref, deq_test, "deque auto_ref" );
  t.add( &deque_test::allocator_with_state, deq_test, "deque allocator_with_state" );
  t.add( &deque_test::optimizations_check, deq_test, "deque optimizations_check" );
  t.add( &deque_test::init_integral, deq_test, "deque ctor for deque(size,value)" );
  t.add( &deque_test::init_range, deq_test, "deque ctor for deque(from,to)" );

  queue_test que_test;

  t.add( &queue_test::pqueue1, que_test, "queue test 1" );
  t.add( &queue_test::queue1, que_test, "queue test 2" );

  stack_test st_test;

  t.add( &stack_test::stack1, st_test, "stack test 1" );
  t.add( &stack_test::stack2, st_test, "stack test 2" );

  list_test lst_test;

  t.add( &list_test::list1, lst_test, "list1" );
  t.add( &list_test::list2, lst_test, "list2" );
  t.add( &list_test::list3, lst_test, "list3" );
  t.add( &list_test::list4, lst_test, "list4" );
  t.add( &list_test::erase, lst_test, "list erase" );
  t.add( &list_test::resize, lst_test, "list resize" );
  t.add( &list_test::push_back, lst_test, "list push_back" );
  t.add( &list_test::push_front, lst_test, "list push_front" );
  t.add( &list_test::allocator_with_state, lst_test, "list allocator_with_state" );
  t.add( &list_test::swap, lst_test, "list swap" );
  t.add( &list_test::adl, lst_test, "list adl" );
  t.add( &list_test::insert, lst_test, "list insert" );
  // t.add( &list_test::const_list, lst_test, "const_list" );

  forward_list_test slst_test;
  exam::test_suite::test_case_type fwd_l_tc[4];

  t.add( &forward_list_test::forward_list1, slst_test, "forward_list1",
    fwd_l_tc[0] = t.add( &forward_list_test::splice, slst_test, "forward_list splice" ) );
  t.add( &forward_list_test::erase, slst_test, "forward_list erase" );
  t.add( &forward_list_test::insert, slst_test, "forward_list insert" );
  t.add( &forward_list_test::allocator_with_state, slst_test, "forward_list allocator_with_state", fwd_l_tc[0] );
  t.add( &forward_list_test::move, slst_test, "forward_list move", fwd_l_tc[0] );
  t.add( &forward_list_test::assign, slst_test, "forward_list assign" );


  string_test str_test;

  t.add( &string_test::constructor, str_test, "constructor" );
  t.add( &string_test::trivial_char_compare, str_test, "trivial_char_compare" );
  t.add( &string_test::reserve, str_test, "reserve" );
  t.add( &string_test::assign, str_test, "assign" );
  t.add( &string_test::erase, str_test, "erase" );
  t.add( &string_test::data, str_test, "data" );
  t.add( &string_test::c_str, str_test, "c_str" );
  t.add( &string_test::null_char, str_test, "null_char" );
  t.add( &string_test::insert, str_test, "insert" );
  t.add( &string_test::replace, str_test, "replace" );
  t.add( &string_test::resize, str_test, "resize" );
  t.add( &string_test::short_string, str_test, "short_string" );
  t.add( &string_test::find, str_test, "find" );
  t.add( &string_test::bogus_edge_find, str_test, "bogus_edge_find" );
  t.add( &string_test::rfind, str_test, "rfind" );
  t.add( &string_test::find_last_of, str_test, "find_last_of" );
  t.add( &string_test::find_last_not_of, str_test, "find_last_not_of" );
  t.add( &string_test::copy, str_test, "copy" );
  t.add( &string_test::mt, str_test, "mt" );
  t.add( &string_test::short_string_optim_bug, str_test, "short_string_optim_bug" );
  t.add( &string_test::compare, str_test, "compare" );
  t.add( &string_test::template_expression, str_test, "template_expression" );
  t.add( &string_test::te_tmp, str_test, "te_tmp" );
  t.add( &string_test::oper_tmp, str_test, "oper_tmp" );
  t.add( &string_test::template_wexpression, str_test, "template_wexpression" );
  t.add( &string_test::io, str_test, "io" );
  t.add( &string_test::allocator_with_state, str_test, "allocator_with_state" );
  t.add( &string_test::capacity, str_test, "capacity" );
  t.add( &string_test::concat24, str_test, "concat24" );
  t.add( &string_test::assign_from_char, str_test, "string assign from char buf" );

  cstring_test cst_test;

  t.add( &cstring_test::import_checks, cst_test, "import_checks" );

  alg_test algtest;

  t.add( &alg_test::remcopy1, algtest, "algorithm remcopy1" );
  t.add( &alg_test::remcpif1, algtest, "algorithm remcpif1" );
  t.add( &alg_test::remif1, algtest, "algorithm remif1" );
  t.add( &alg_test::remove1, algtest, "algorithm remove1" );
  t.add( &alg_test::repcpif1, algtest, "algorithm repcpif1" );
  t.add( &alg_test::replace0, algtest, "algorithm replace0" );
  t.add( &alg_test::replace1, algtest, "algorithm replace1" );
  t.add( &alg_test::replcpy1, algtest, "algorithm replcpy1" );
  t.add( &alg_test::replif1, algtest, "algorithm replif1" );
  t.add( &alg_test::revcopy1, algtest, "algorithm revcopy1" );
  t.add( &alg_test::reverse1, algtest, "algorithm reverse1" );

  t.add( &alg_test::min_max, algtest, "algorithm min_max" );
  t.add( &alg_test::count_test, algtest, "algorithm count_test" );
  t.add( &alg_test::sort_test, algtest, "algorithm sort_test" );
  t.add( &alg_test::search_n_test, algtest, "algorithm search_n_test" );
  t.add( &alg_test::find_first_of_test, algtest, "algorithm find_first_of_test" );
  t.add( &alg_test::find_first_of_nsc_test, algtest, "algorithm find_first_of_nsc_test" );

  t.add( &alg_test::max1, algtest, "algorithm max1" );
  t.add( &alg_test::max2, algtest, "algorithm max2" );
  t.add( &alg_test::maxelem1, algtest, "algorithm maxelem1" );
  t.add( &alg_test::maxelem2, algtest, "algorithm maxelem2" );

  t.add( &alg_test::min1, algtest, "algorithm min1" );
  t.add( &alg_test::min2, algtest, "algorithm min2" );
  t.add( &alg_test::minelem1, algtest, "algorithm minelem1" );
  t.add( &alg_test::minelem2, algtest, "algorithm minelem2" );

  t.add( &alg_test::lwrbnd1, algtest, "algorithm lwrbnd1" );
  t.add( &alg_test::lwrbnd2, algtest, "algorithm lwrbnd2" );
  t.add( &alg_test::uprbnd1, algtest, "algorithm uprbnd1" );
  t.add( &alg_test::uprbnd2, algtest, "algorithm uprbnd2" );

  t.add( &alg_test::equal_range0, algtest, "algorithm equal_range0" );
  t.add( &alg_test::equal_range1, algtest, "algorithm equal_range1" );
  t.add( &alg_test::equal_range2, algtest, "algorithm equal_range2" );

  t.add( &alg_test::foreach0, algtest, "algorithm foreach0" );
  t.add( &alg_test::foreach1, algtest, "algorithm foreach1" );

  t.add( &alg_test::gener1, algtest, "algorithm gener1" );
  t.add( &alg_test::gener2, algtest, "algorithm gener2" );
  t.add( &alg_test::genern1, algtest, "algorithm genern1" );
  t.add( &alg_test::genern2, algtest, "algorithm genern2" );

  functor_test fntest;

  t.add( &functor_test::equal0, fntest, "functor equal0" );
  t.add( &functor_test::equal1, fntest, "functor equal1" );
  t.add( &functor_test::equal2, fntest, "functor equal2" );
  t.add( &functor_test::equalto, fntest, "functor equalto" );

  t.add( &functor_test::bnegate1, fntest, "functor bnegate1" );
  t.add( &functor_test::bnegate2, fntest, "functor bnegate2" );

  t.add( &functor_test::logicand, fntest, "functor logic and" );
  t.add( &functor_test::logicnot, fntest, "functor logic not" );
  t.add( &functor_test::logicor, fntest, "functor logic or" );

  t.add( &functor_test::lesst, fntest, "functor less" );
  t.add( &functor_test::lesseqt, fntest, "functor less-or-equal" );

  t.add( &functor_test::greatert, fntest, "functor greater" );
  t.add( &functor_test::greatereq, fntest, "functor greater-or-equal" );

  t.add( &functor_test::func1, fntest, "functor func1" );
  t.add( &functor_test::func2, fntest, "functor func2" );
  t.add( &functor_test::func3, fntest, "functor func3" );

  t.add( &functor_test::plus0, fntest, "functor plus0" );
  t.add( &functor_test::minus0, fntest, "functor minus0" );

  iostream_test strm_test;

  t.add( &iostream_test::manipulators, strm_test, "manipulators" );
  t.add( &iostream_test::in_avail, strm_test, "in_avail in std streams" );

  sstream_test sstrm_test;

  t.add( &sstream_test::output, sstrm_test, "sstream output" );
  t.add( &sstream_test::input, sstrm_test, "sstream input" );
  t.add( &sstream_test::input_char, sstrm_test, "sstream input_char" );
  t.add( &sstream_test::io, sstrm_test, "sstream io" );
  t.add( &sstream_test::err, sstrm_test, "sstream err" );
  t.add( &sstream_test::err_long, sstrm_test, "sstream err_long" );
  t.add( &sstream_test::maxint, sstrm_test, "sstream maxint" );
  t.add( &sstream_test::init_in, sstrm_test, "sstream init_in" );
  t.add( &sstream_test::init_out, sstrm_test, "sstream init_out" );
  t.add( &sstream_test::init_in_str, sstrm_test, "sstream str( \"foo\" )" );
  t.add( &sstream_test::buf, sstrm_test, "sstream buf" );
  t.add( &sstream_test::rdbuf, sstrm_test, "sstream rdbuf" );
  t.add( &sstream_test::streambuf_output, sstrm_test, "sstream streambuf_output" );
  t.add( &sstream_test::fail_bit, sstrm_test, "sstream throw ios_base::failure exception for invalid seekg",
    t.add( &sstream_test::seek, sstrm_test, "sstream seek" ) );
  t.add( &sstream_test::seekp, sstrm_test, "sstream seekp" );
  t.add( &sstream_test::seek_gp, sstrm_test, "sstream seek_gp" );
  t.add( &sstream_test::tellp, sstrm_test, "sstream tellp" );
  t.add( &sstream_test::extra0_bug_id_2728232, sstrm_test, "extra 0; bug ID: 2728232" );
  t.add( &sstream_test::negative, sstrm_test, "sstream negative" );

  numerics num_test;

  exam::test_suite::test_case_type num_tc[7];

  t.add( &numerics::accum2, num_test, "accumulate, non-default functor",
    num_tc[0] = t.add( &numerics::accum1, num_test, "accumulate" ) );

  num_tc[1] = vec_tc[12];
  t.add( &numerics::times, num_test, "accumulate, multiplies<int> functor", num_tc, num_tc + 2 );

  num_tc[1] = t.add( &numerics::partsum0, num_test, "partial summ, raw array" );
  num_tc[2] = vec_tc[12];
  num_tc[2] = t.add( &numerics::partsum1, num_test, "partial summ, vector", num_tc + 1, num_tc + 3 );
  num_tc[3] = vec_tc[12];
  t.add( &numerics::partsum2, num_test, "partial summ, multiplies<int> functor", num_tc + 2, num_tc + 4 );

  num_tc[3] = t.add( &numerics::innprod0, num_test, "inner product, raw array" );
  num_tc[4] = vec_tc[12];
  num_tc[4] = t.add( &numerics::innprod1, num_test, "inner product, vector", num_tc + 3, num_tc + 5 );
  num_tc[5] = vec_tc[12];
  t.add( &numerics::innprod2, num_test, "inner product, userdefined functors", num_tc + 4, num_tc + 6 );

  map_test m_test;

  t.add( &map_test::map1, m_test, "map1" );
  t.add( &map_test::mmap1, m_test, "mmap1" );
  t.add( &map_test::mmap2, m_test, "mmap2" );
  t.add( &map_test::iterators, m_test, "map iterators" );
  t.add( &map_test::equal_range, m_test, "map equal_range" );
  t.add( &map_test::allocator_with_state, m_test, "map allocator_with_state" );
  t.add( &map_test::template_methods, m_test, "map template_methods" );

  set_test s_test;

  t.add( &set_test::set1, s_test, "set1" );
  t.add( &set_test::set2, s_test, "set2" );
  t.add( &set_test::erase, s_test, "set erase" );
  t.add( &set_test::insert, s_test, "set insert" );
  t.add( &set_test::find, s_test, "set find" );
  t.add( &set_test::bounds, s_test, "set bounds" );
  t.add( &set_test::specialized_less, s_test, "set specialized_less" );
  t.add( &set_test::implementation_check, s_test, "set implementation_check" );
  t.add( &set_test::allocator_with_state, s_test, "set allocator_with_state" );
  t.add( &set_test::reverse_iterator_test, s_test, "set reverse_iterator_test" );
  t.add( &set_test::template_methods, s_test, "set template_methods" );

  set_union_test su_test;

  t.add( &set_union_test::setunon0, su_test, "setunon0" );
  t.add( &set_union_test::setunon1, su_test, "setunon1" );
  t.add( &set_union_test::setunon2, su_test, "setunon2" );

  set_intersection_test si_test;

  t.add( &set_intersection_test::setintr0, si_test, "setintr0" );
  t.add( &set_intersection_test::setintr1, si_test, "setintr1" );
  t.add( &set_intersection_test::setintr2, si_test, "setintr2" );

  set_difference_test sd_test;

  t.add( &set_difference_test::setdiff0, sd_test, "setdiff0" );
  t.add( &set_difference_test::setdiff1, sd_test, "setdiff1" );
  t.add( &set_difference_test::setdiff2, sd_test, "setdiff2" );
  t.add( &set_difference_test::setsymd0, sd_test, "setsymd0" );
  t.add( &set_difference_test::setsymd1, sd_test, "setsymd1" );
  t.add( &set_difference_test::setsymd2, sd_test, "setsymd2" );

  multiset_test ms_test;

  t.add( &multiset_test::mset1, ms_test, "mset1", fwd_l_tc[0] );
  t.add( &multiset_test::mset3, ms_test, "mset3", fwd_l_tc[0] );
  t.add( &multiset_test::mset5, ms_test, "mset5", fwd_l_tc[0] );

  hash_test h_test;

  t.add( &hash_test::hmap1, h_test, "hmap1", fwd_l_tc[0] );
  t.add( &hash_test::hmmap1, h_test, "hmmap1", fwd_l_tc[0] );
  t.add( &hash_test::hmmap2, h_test, "hmmap2", fwd_l_tc[0] );
  t.add( &hash_test::hmset1, h_test, "hmset1", fwd_l_tc[0] );
  t.add( &hash_test::hmset1, h_test, "hmset1", fwd_l_tc[0] );
  t.add( &hash_test::hset2, h_test, "hset2", fwd_l_tc[0] );
  t.add( &hash_test::insert_erase, h_test, "hash insert_erase", fwd_l_tc[0] );
  t.add( &hash_test::allocator_with_state, h_test, "hash allocator_with_state", fwd_l_tc[0] );
  t.add( &hash_test::remains, h_test, "erase in hash_map", fwd_l_tc[0] );

  unordered_test uo_test;

  t.add( &unordered_test::uset, uo_test, "unordered uset", fwd_l_tc[0] );
  t.add( &unordered_test::umultiset, uo_test, "unordered umultiset", fwd_l_tc[0] );
  t.add( &unordered_test::umap, uo_test, "unordered umap", fwd_l_tc[0] );
  t.add( &unordered_test::umultimap, uo_test, "unordered umultimap", fwd_l_tc[0] );
  t.add( &unordered_test::user_case, uo_test, "unordered user_case", fwd_l_tc[0] );
  t.add( &unordered_test::hash_policy, uo_test, "unordered hash_policy", fwd_l_tc[0] );
  t.add( &unordered_test::buckets, uo_test, "unordered buckets", fwd_l_tc[0] );
  t.add( &unordered_test::equal_range, uo_test, "unordered equal_range", fwd_l_tc[0] );
  t.add( &unordered_test::template_methods, uo_test, "unordered template_methods", fwd_l_tc[0] );
  t.add( &unordered_test::remains, uo_test, "erase in unordered_map" );

  valarray_test val_test;
  t.add( &valarray_test::transcendentals, val_test, "transcendentals" );

  fstream_test fstrm_test;
  exam::test_suite::test_case_type fstream_tc[10];

  fstream_tc[0] = t.add( &fstream_test::err, fstrm_test, "fstream err",
    t.add( &fstream_test::io, fstrm_test, "fstream io",
      t.add( &fstream_test::input_char, fstrm_test, "fstream input_char",
        t.add( &fstream_test::input, fstrm_test, "fstream input",
          t.add( &fstream_test::output, fstrm_test, "fstream output" ) ) ) ) );

  t.add( &fstream_test::tell_binary_wce, fstrm_test, "fstream tellg binary WCE workaround",
    t.add( &fstream_test::tellg, fstrm_test, "fstream tellg", fstream_tc[0] ) );
  t.add( &fstream_test::tellp, fstrm_test, "fstream tellp", fstream_tc[0] );

  t.add( &fstream_test::seek_wide_stream, fstrm_test, "wfstream seek",
    fstream_tc[1] = t.add( &fstream_test::seek_text, fstrm_test, "fstream seek in text",
      t.add( &fstream_test::seek_binary, fstrm_test, "fstream seek in binary", fstream_tc[0] ) ) );
  t.add( &fstream_test::buf, fstrm_test, "fstream buf", fstream_tc[0] );

  t.add( &fstream_test::rdbuf, fstrm_test, "fstream rdbuf",
    t.add( &fstream_test::streambuf_output, fstrm_test, "fstream streambuf_output", fstream_tc[0] ) );
  t.add( &fstream_test::win32_file_format, fstrm_test, "fstream win32_file_format", fstream_tc[0] );
  t.add( &fstream_test::null_stream, fstrm_test, "fstream null_stream", fstream_tc[0] );
  t.add( &fstream_test::null_buf, fstrm_test, "fstream null_buf", fstream_tc[0] );
  t.add( &fstream_test::offset, fstrm_test, "fstream offset", fstream_tc[0] );
  t.add( &fstream_test::big_file, fstrm_test, "fstream big_file", fstream_tc[0] );
  fstream_tc[2] = t.add( &fstream_test::custom_facet, fstrm_test, "fstream custom_facet", fstream_tc[0] );

  t.add( &fstream_test::rewind, fstrm_test, "fstream write after read fail", fstream_tc[1] );
 
  search_test sch_test;
  
  t.add( &search_test::search0, sch_test, "search0" );
  t.add( &search_test::search1, sch_test, "search1" );
  t.add( &search_test::search2, sch_test, "search2" );

  sort_test srt_test;
  
  t.add( &sort_test::sort1, srt_test, "sort1" );
  t.add( &sort_test::sort2, srt_test, "sort2" );
  t.add( &sort_test::sort3, srt_test, "sort3" );
  t.add( &sort_test::sort4, srt_test, "sort4" );
  t.add( &sort_test::stblsrt1, srt_test, "stblsrt1" );
  t.add( &sort_test::stblsrt2, srt_test, "stblsrt2" );
  t.add( &sort_test::bad_predicate_detected, srt_test, "bad_predicate_detected" );

  adj_test a_test;

  t.add( &adj_test::adjfind0, a_test, "adjfind0" );
  t.add( &adj_test::adjfind1, a_test, "adjfind1" );
  t.add( &adj_test::adjfind2, a_test, "adjfind2" );
  t.add( &adj_test::adjdiff0, a_test, "adjdiff0" );
  t.add( &adj_test::adjdiff1, a_test, "adjdiff1" );
  t.add( &adj_test::adjdiff2, a_test, "adjdiff2" );
  
  copy_test cp_test;

  t.add( &copy_test::copy_array, cp_test, "copy_array" );
  t.add( &copy_test::copy_volatile, cp_test, "copy_volatile" );
  t.add( &copy_test::copy_vector, cp_test, "copy_vector" );
  t.add( &copy_test::copy_insert, cp_test, "copy_insert" );
  t.add( &copy_test::copy_back, cp_test, "copy_back" );
  t.add( &copy_test::copy_back_array, cp_test, "copy_back_array" );

  perm_test pm_test;

  t.add( &perm_test::nextprm0, pm_test, "nextprm0" );
  t.add( &perm_test::nextprm1, pm_test, "nextprm1" );
  t.add( &perm_test::nextprm2, pm_test, "nextprm2" );
  t.add( &perm_test::prevprm0, pm_test, "prevprm0" );
  t.add( &perm_test::prevprm1, pm_test, "prevprm1" );
  t.add( &perm_test::prevprm2, pm_test, "prevprm2" );

  find_test fn_test;

  t.add( &find_test::find0, fn_test, "find0" );
  t.add( &find_test::find1, fn_test, "find1" );
  t.add( &find_test::findif0, fn_test, "findif0" );
  t.add( &find_test::findif1, fn_test, "findif1" );
  t.add( &find_test::find_char, fn_test, "find_char" );

  advance_test adv_test;

  t.add( &advance_test::adv, adv_test, "advance test" );

  partition_test prt_test;

  t.add( &partition_test::ptition0, prt_test, "ptition0" );
  t.add( &partition_test::ptition1, prt_test, "ptition1" );
  t.add( &partition_test::stblptn0, prt_test, "stblptn0" );
  t.add( &partition_test::stblptn1, prt_test, "stblptn1" );

  iter_test it_test;

  t.add( &iter_test::iter1, it_test, "iter1" );
  t.add( &iter_test::iter2, it_test, "iter2" );
  t.add( &iter_test::iter3, it_test, "iter3" );
  t.add( &iter_test::iterswp0, it_test, "iterswp0" );
  t.add( &iter_test::iterswp1, it_test, "iterswp1" );
  t.add( &iter_test::iterswp2, it_test, "iterswp2" );
  t.add( &iter_test::iterswp3, it_test, "iterswp3" );

  istream_iterator_test isit_test;

  t.add( &istream_iterator_test::istmit1, isit_test, "istmit1" );
  t.add( &istream_iterator_test::copy_n_test, isit_test, "copy_n_test" );

  ostream_iterator_test osit_test;

  t.add( &ostream_iterator_test::ostmit0, osit_test, "ostmit0" );

  ioiter_test ioit_test;

  t.add( &ioiter_test::ioiterat_test, ioit_test, "ioiterat_test" );
  t.add( &ioiter_test::assign_test, ioit_test, "assign_test" );
  t.add( &ioiter_test::assign2_test, ioit_test, "assign2_test" );

  insert_iter_test ins_test;

  t.add( &insert_iter_test::insert1, ins_test, "insert1" );
  t.add( &insert_iter_test::insert2, ins_test, "insert2" );

  binsert_iter_test bins_test;

  t.add( &binsert_iter_test::binsert1, bins_test, "binsert1" );
  t.add( &binsert_iter_test::binsert2, bins_test, "binsert2" );

  finsert_iter_test fins_test;

  t.add( &finsert_iter_test::finsert1, fins_test, "finsert1" );
  t.add( &finsert_iter_test::finsert2, fins_test, "finsert2" );

  reviter_test rev_test;

  t.add( &reviter_test::reviter1, rev_test, "reviter1" );
  t.add( &reviter_test::reviter2, rev_test, "reviter2" );
  t.add( &reviter_test::revbit1, rev_test, "revbit1" );

  bind_test bn_test;

  t.add( &bind_test::bind1st1, bn_test, "bind1st1" );
  t.add( &bind_test::bind2nd1, bn_test, "bind2nd1" );
  t.add( &bind_test::bind2nd2, bn_test, "bind2nd2" );
  t.add( &bind_test::bind2nd3, bn_test, "bind2nd3" );
  t.add( &bind_test::bind_memfn, bn_test, "bind_memfn" );

  count_test cn_test;

  t.add( &count_test::count0, cn_test, "count0" );
  t.add( &count_test::count1, cn_test, "count1" );
  t.add( &count_test::countif1, cn_test, "countif1" );

  partial_test part_test;

  t.add( &partial_test::parsrt0, part_test, "parsrt0" );
  t.add( &partial_test::parsrt1, part_test, "parsrt1" );
  t.add( &partial_test::parsrt2, part_test, "parsrt2" );
  t.add( &partial_test::parsrtc0, part_test, "parsrtc0" );
  t.add( &partial_test::parsrtc1, part_test, "parsrtc1" );
  t.add( &partial_test::parsrtc2, part_test, "parsrtc2" );
  t.add( &partial_test::bad_predicate_detected, part_test, "bad_predicate_detected partial_test" );

  heap_test hp_test;

  t.add( &heap_test::mkheap1, hp_test, "mkheap1" );
  t.add( &heap_test::mkheap2, hp_test, "mkheap2" );
  t.add( &heap_test::pheap1, hp_test, "pheap1" );
  t.add( &heap_test::pheap2, hp_test, "pheap2" );

  bsearch_test bs_test;

  t.add( &bsearch_test::bsearch1, bs_test, "bsearch1" );
  t.add( &bsearch_test::bsearch2, bs_test, "bsearch2" );

  bcompose_test bcm_test;

  t.add( &bcompose_test::bcompose1, bcm_test, "bcompose1" );
  t.add( &bcompose_test::bcompose2, bcm_test, "bcompose2" );

  rotate_test rt_test;

  t.add( &rotate_test::rotate0, rt_test, "rotate0" );
  t.add( &rotate_test::rotate1, rt_test, "rotate1" );
  t.add( &rotate_test::rotcopy0, rt_test, "rotcopy0" );
  t.add( &rotate_test::rotcopy1, rt_test, "rotcopy1" );

  fill_test fl_test;

  t.add( &fill_test::fill1, fl_test, "fill1" );
  t.add( &fill_test::filln1, fl_test, "filln1" );
  
  unique_test un_test;

  t.add( &unique_test::unique1, un_test, "unique1" );
  t.add( &unique_test::unique2, un_test, "unique2" );
  t.add( &unique_test::uniqcpy1, un_test, "uniqcpy1" );
  t.add( &unique_test::uniqcpy2, un_test, "uniqcpy2" );

  transform_test tr_test;

  t.add( &transform_test::trnsfrm1, tr_test, "trnsfrm1" );
  t.add( &transform_test::trnsfrm2, tr_test, "trnsfrm2" );
  t.add( &transform_test::self_str, tr_test, "self_str" );

  neq_test nq_test;

  t.add( &neq_test::negate0, nq_test, "negate0" );
  t.add( &neq_test::nequal0, nq_test, "nequal0" );

  modulus_test mod_test;

  t.add( &modulus_test::modulus0, mod_test, "modulus0" );

  ptr2_test pt_test;

  t.add( &ptr2_test::ptrbin1, pt_test, "ptrbin1" );
  t.add( &ptr2_test::ptrbin2, pt_test, "ptrbin2" );
  t.add( &ptr2_test::ptrun1, pt_test, "ptrun1" );
  t.add( &ptr2_test::ptrun2, pt_test, "ptrun2" );

  mismatch_test mis_test;

  t.add( &mismatch_test::mismatch0, mis_test, "mismatch0" );
  t.add( &mismatch_test::mismatch1, mis_test, "mismatch1" );
  t.add( &mismatch_test::mismatch2, mis_test, "mismatch2" );

  utility_test pr_test;
  exam::test_suite::test_case_type utility_tc[10];

  t.add( &utility_test::pair0, pr_test, "pair0" );
  t.add( &utility_test::init, pr_test, "init" );
  utility_tc[0] = t.add( &utility_test::move, pr_test, "move<A>",
    t.add( &utility_test::forward, pr_test, "forward<A>" ) );

  rnd_shuffle_test rnd_test;

  t.add( &rnd_shuffle_test::rndshuf0, rnd_test, "rndshuf0" );
  t.add( &rnd_shuffle_test::rndshuf1, rnd_test, "rndshuf1" );

  nth_elem_test nth_test;

  t.add( &nth_elem_test::nthelem0, nth_test, "nthelem0" );
  t.add( &nth_elem_test::nthelem1, nth_test, "nthelem1" );
  t.add( &nth_elem_test::nthelem2, nth_test, "nthelem2" );

  includes_test incl_test;

  t.add( &includes_test::incl0, incl_test, "incl0" );
  t.add( &includes_test::incl1, incl_test, "incl1" );
  t.add( &includes_test::incl2, incl_test, "incl2" );

  inplace_test inp_test;

  t.add( &inplace_test::inplmrg1, inp_test, "inplmrg1" );
  t.add( &inplace_test::inplmrg2, inp_test, "inplmrg2" );

  rope_test rp_test;

  t.add( &rope_test::io, rp_test, "io" );
  t.add( &rope_test::find1, rp_test, "find1" );
  t.add( &rope_test::find2, rp_test, "find2" );
  t.add( &rope_test::construct_from_char, rp_test, "construct_from_char" );
  t.add( &rope_test::bug_report, rp_test, "bug_report" );
  t.add( &rope_test::test_saved_rope_iterators, rp_test, "test_saved_rope_iterators" );

  unary_test uny_test;

  t.add( &unary_test::unegate1, uny_test, "unegate1" );
  t.add( &unary_test::unegate2, uny_test, "unegate2" );
  t.add( &unary_test::unegate3, uny_test, "unegate3" );
  t.add( &unary_test::ucompose1, uny_test, "ucompose1" );
  t.add( &unary_test::ucompose2, uny_test, "ucompose2" );

  swap_test sw_test;

  t.add( &swap_test::swap1, sw_test, "swap1" );
  t.add( &swap_test::swprnge1, sw_test, "swprnge1" );
  t.add( &swap_test::swap_container_non_spec, sw_test, "swap_container_non_spec" );
  t.add( &swap_test::swap_container_spec, sw_test, "swap_container_spec" );

  merge_test mr_test;

  t.add( &merge_test::merge0, mr_test, "merge0" );
  t.add( &merge_test::merge1, mr_test, "merge1" );
  t.add( &merge_test::merge2, mr_test, "merge2" );

  divide_test div_test;
  t.add( &divide_test::div, div_test, "div" );

  lexcmp_test lcm_test;

  t.add( &lexcmp_test::lexcmp1, lcm_test, "lexcmp1" );
  t.add( &lexcmp_test::lexcmp2, lcm_test, "lexcmp2" );

  allocator_test al_test;

  t.add( &allocator_test::zero_allocation, al_test, "zero_allocation" );
  t.add( &allocator_test::bad_alloc_test, al_test, "bad_alloc_test" );
  t.add( &allocator_test::per_thread_alloc, al_test, "per_thread_alloc" );
  t.add( &allocator_test::rebind_alloc, al_test, "rebind alloc" );

  memory_test mem_test;
  t.add( &memory_test::auto_ptr_test, mem_test, "memory_test::auto_ptr_test" );

  rawriter_test rw_test;
  t.add( &rawriter_test::rawiter1, rw_test, "rawiter1" );

  strstream_buffer_test strb_test;
  t.add( &strstream_buffer_test::read_from_buffer, strb_test, "read_from_buffer" );

//file stream_test.cpp with this test wasn't added to Makefile.inc
//  strstream_test strs_test;
//  t.add( &strstream_test::input, strs_test, "strstream_test::input" );

  ptrspec_test pts_test;

  t.add( &ptrspec_test::ptr_specialization_test, pts_test, "ptr_specialization_test" );
  t.add( &ptrspec_test::function_pointer, pts_test, "function_pointer" );

  limits_test lt_test;
  exam::test_suite::test_case_type limits_tc[10];

  limits_tc[0] = t.add( &limits_test::limits, lt_test, "limits_test::limits" );

  t.add( &limits_test::l_float, lt_test, "float limits", limits_tc[0] );
  t.add( &limits_test::l_double, lt_test, "double limits", limits_tc[0] );
  t.add( &limits_test::l_long_double, lt_test, "long double limits", limits_tc[0] );

  t.add( &limits_test::qNaN<float>, lt_test, "numeric_limits<float>::quiet_NaN()" );
  t.add( &limits_test::qNaN<double>, lt_test, "numeric_limits<double>::quiet_NaN()" );
#if !defined ( _STLP_NO_LONG_DOUBLE )
  t.add( &limits_test::qNaN<long double>, lt_test, "numeric_limits<long double>::quiet_NaN()" );
#endif
  t.add( &limits_test::sNaN<float>, lt_test, "numeric_limits<float>::signaling_NaN()" );
  t.add( &limits_test::sNaN<double>, lt_test, "numeric_limits<double>::signaling_NaN()" );
#if !defined ( _STLP_NO_LONG_DOUBLE )
  t.add( &limits_test::sNaN<long double>, lt_test, "numeric_limits<long double>::signaling_NaN()" );
#endif

  mem_fun_ptr_test mf_test;

  t.add( &mem_fun_ptr_test::mem_ptr_fun, mf_test, "mem_ptr_fun" );
  t.add( &mem_fun_ptr_test::find, mf_test, "mem_fun_ptr_test::find" );

  uninitialized_test unin_test;

  t.add( &uninitialized_test::copy_test, unin_test, "copy_test" );
  t.add( &uninitialized_test::fill_test, unin_test, "fill_test" );
  t.add( &uninitialized_test::fill_n_test, unin_test, "fill_n_test" );

  bitset_test bts_test;

  t.add( &bitset_test::bitset1, bts_test, "bitset1" );
  t.add( &bitset_test::iostream, bts_test, "iostream" );

  cmath_test cmt_test;
  t.add( &cmath_test::import_checks, cmt_test, "cmath_test::import_checks" );

  iota_test iot_test;
  t.add( &iota_test::iota1, iot_test, "iota1" );

  config_test conf_test;

  t.add( &config_test::placement_new_bug, conf_test, "placement_new_bug" );
  t.add( &config_test::endianess, conf_test, "endianess" );
  t.add( &config_test::template_function_partial_ordering, conf_test, "template_function_partial_ordering" );
  t.add( &config_test::new_throw_bad_alloc, conf_test, "new_throw_bad_alloc" );

  exception_test exc_test;

  t.add( &exception_test::what, exc_test, "exception_test::what" );
  t.add( &exception_test::unexpected_except, exc_test, "exception_test::unexpected_except" );
  t.add( &exception_test::uncaught_except, exc_test, "exception_test::uncaught_except" );
  t.add( &exception_test::exception_emission, exc_test, "exception_test::exception_emission" );

  errno_test err_test;
  t.add( &errno_test::check, err_test, "errno_test::check" );

  num_put_get_test nmg_test;

  // t.add( &num_put_get_test::scientific_precision, nmg_test, "scientific precision",
  t.add( &num_put_get_test::num_put_float, nmg_test, "num_put_float" ); // );
  t.add( &num_put_get_test::num_put_integer, nmg_test, "num_put_integer" );
  t.add( &num_put_get_test::num_get_float, nmg_test, "num_get_float" );
  t.add( &num_put_get_test::num_get_integer, nmg_test, "num_get_integer" );
  t.add( &num_put_get_test::inhex, nmg_test, "inhex" );
  t.add( &num_put_get_test::pointer, nmg_test, "pointer" );
  t.add( &num_put_get_test::fix_float_long, nmg_test, "fix_float_long" );
  t.add( &num_put_get_test::custom_numpunct, nmg_test, "custom_numpunct" );

  codecvt_test cvt_test;
  exam::test_suite::test_case_type cvt_tc[10];

  t.add( &codecvt_test::variable_encoding, cvt_test, "variable_encoding", fstream_tc[2] );
  t.add( &codecvt_test::in_out_test, cvt_test, "in_out_test" );
  t.add( &codecvt_test::length_test, cvt_test, "length_test" );
  t.add( &codecvt_test::imbue_while_reading, cvt_test, "imbue_while_reading" );

  t.add( &codecvt_test::_936_to_wchar, cvt_test, "convert CP936 to wchar",
    cvt_tc[0] = t.add( &codecvt_test::eol, cvt_test, "convert \\0" ) );

  t.add( &codecvt_test::bad_utf8, cvt_test, "convert bad UTF-8 to wchar",
    cvt_tc[1] = t.add( &codecvt_test::utf8_to_wchar, cvt_test, "convert UTF-8 to wchar", cvt_tc[0] ) );
  t.add( &codecvt_test::partial_conversion, cvt_test, "codecvt partial conversion", cvt_tc[1] );


  memory1_test m1_test;
  t.add( &memory1_test::pointer_traits, m1_test, "pointer_traits" );
  t.add( &memory1_test::align, m1_test, "align" );
  t.add( &memory1_test::uses_allocator, m1_test, "uses_allocator" );

  exam::test_suite::test_case_type shp_tc[10];

  unique_ptr_test unqp_test;
  t.add( &unique_ptr_test::array, unqp_test, "unique_ptr array", 
    shp_tc[2] = t.add( &unique_ptr_test::base, unqp_test, "unique_ptr basic" ) );

  shared_ptr_test shp_test;

  t.add( &shared_ptr_test::deleter, shp_test, "shared_ptr get_deleter",
    t.add( &shared_ptr_test::alias, shp_test, "shared_ptr alias",
      shp_tc[0] = t.add( &shared_ptr_test::shared_ptr_base, shp_test, "shared_ptr basic" ) ) );
  t.add( &shared_ptr_test::convert, shp_test, "shared_ptr convertions", shp_tc[0] );
  t.add( &shared_ptr_test::casts, shp_test, "shared_ptr casts", shp_tc[0] );
  shp_tc[1] = utility_tc[0];
  shp_tc[3] =
    t.add( &shared_ptr_test::allocate, shp_test, "shared_ptr allocate_shared",
      t.add( &shared_ptr_test::make, shp_test, "shared_ptr make_shared",
         t.add( &shared_ptr_test::move, shp_test, "shared_ptr move", shp_tc, shp_tc + 2 ) ) );
  shp_tc[4] = t.add( &shared_ptr_test::assign, shp_test, "shared_ptr assignment", shp_tc[0] );

  t.add( &shared_ptr_test::unique_ptr, shp_test, "shared_ptr from unique_ptr ctor", shp_tc[2] );

  weak_ptr_test wp_test;

  shp_tc[5] = t.add( &weak_ptr_test::base, wp_test, "weak_ptr basic", shp_tc[3] );

  t.add( &shared_ptr_test::shared_from_this, shp_test, "shared_from_this", shp_tc + 4, shp_tc + 6 );

  ref_wrapper_test ref_test;

  t.add( &ref_wrapper_test::ref, ref_test, "ref" );
  t.add( &ref_wrapper_test::cref, ref_test, "cref" );

  locale_test ltest;

  t.add( &locale_test::locale_by_name, ltest, "locale_by_name" );
  t.add( &locale_test::moneypunct_by_name, ltest, "moneypunct_by_name" );
  t.add( &locale_test::time_by_name, ltest, "time_by_name" );
  t.add( &locale_test::numpunct_by_name, ltest, "numpunct_by_name" );
  t.add( &locale_test::ctype_by_name, ltest, "ctype_by_name" );
  t.add( &locale_test::collate_by_name, ltest, "collate_by_name" );
  t.add( &locale_test::messages_by_name, ltest, "messages_by_name" );

  t.add( &locale_test::loc_has_facet, ltest, "loc_has_facet" );
  t.add( &locale_test::hidden, ltest, "locale, aux functions visibility",
    t.add( &locale_test::num_put_get, ltest, "num_put_get" ) );
  t.add( &locale_test::money_put_get, ltest, "money_put_get" );
  t.add( &locale_test::money_put_X_bug, ltest, "money_put_X_bug" );
  t.add( &locale_test::time_put_get, ltest, "time_put_get" );
  t.add( &locale_test::collate_facet, ltest, "collate_facet" );
  t.add( &locale_test::ctype_facet, ltest, "ctype_facet" );
  t.add( &locale_test::locale_init_problem, ltest, "locale_init_problem" );

  t.add( &locale_test::default_locale, ltest, "default_locale" );
  t.add( &locale_test::combine, ltest, "combine" );

  thread_test test_thr;

  t.add( &thread_test::thread_call, test_thr, "thread thread_call" );
  t.add( &thread_test::mutex_rw_test, test_thr, "rw mutex",
    t.add( &thread_test::mutex_test, test_thr, "mutex_test" ) );
  t.add( &thread_test::barrier, test_thr, "barrier" );
  t.add( &thread_test::semaphore, test_thr, "semaphore" );
  t.add( &thread_test::condition_var, test_thr, "condition_variable" );

  if ( opts.is_set( 'l' ) ) {
    t.print_graph( std::cout );
    return 0;
  }

  if ( opts.is_set( 'v' ) ) {
    t.flags( t.flags() | exam::base_logger::verbose );
  }

  if ( opts.is_set( 't' ) ) {
    t.flags( t.flags() | exam::base_logger::trace );
  }

  if ( opts.is_set( 'r' ) ) {
    std::stringstream ss( opts.get<std::string>( 'r' ) );
    int n;
    int res = 0;
    while ( ss >> n ) {
      res |= t.single( n );
    }

    return res;
  }

  return t.girdle();
}
