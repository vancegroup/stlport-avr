cmake_minimum_required (VERSION 2.6)

PROJECT(stlport)

SET( MAJOR 5)
SET( MINOR 2)
SET( PATCH 2)

SET( SRCS
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/dll_main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/fstream.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/strstream.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/sstream.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/ios.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/stdio_streambuf.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/istream.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/ostream.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/iostream.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/codecvt.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/collate.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/ctype.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/monetary.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/num_get.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/num_put.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/num_get_float.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/num_put_float.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/numpunct.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/time_facets.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/messages.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/locale.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/locale_impl.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/locale_catalog.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/facets_byname.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/complex.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/complex_io.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/complex_trig.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/string.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/bitset.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/allocators.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/thread.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/system_error.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/c_locale.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../../src/cxa.c
)

SET( TEST_SRCS
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/cppunit/test_main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/accum_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/adj_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/advance_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/alg_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/algorithm_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/allocator_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/bcompos_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/bind_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/binsert_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/bitset_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/bitset_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/bnegate_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/boost_check.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/bound_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/bsearch_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/bvector_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/cassert_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/cctype_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/cerrno_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/cfloat_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/ciso646_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/climits_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/clocale_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/cmath_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/cmath_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/codecvt_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/collate_facets_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/complex_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/config_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/copy_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/count_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/csetjmp_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/setjmp_header_test2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/csignal_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/cstdarg_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/cstddef_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/cstdio_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/cstdlib_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/cstring_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/cstring_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/ctime_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/ctype_facets_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/cwchar_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/cwctype_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/deque_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/deque_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/divides_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/equal_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/exception_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/exception_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/epilog_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/fill_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/find_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/finsert_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/foreach_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/fstream_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/fstream_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/func_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/functional_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/generator_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/greater_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/hash_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/heap_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/includes_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/innerprod_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/inplace_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/insert_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/ioiter_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/iomanip_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/ios_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/iosfwd_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/iostream_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/iostream_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/iota_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/istmit_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/istream_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/iter_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/iterator_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/less_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/lexcmp_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/limits_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/limits_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/list_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/list_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/locale_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/locale_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/logic_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/macro_checks.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/map_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/map_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/max_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/memory_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/memory_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/merge_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/messages_facets_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/mfunptr_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/min_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/mismatch_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/modulus_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/money_facets_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/multiset_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/mvctor_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/mvctor_declaration_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/mvctor_traits_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/neq_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/new_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/nthelm_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/num_facets_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/num_put_get_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/numeric_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/ostmit_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/ostream_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/pair_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/partial_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/partition_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/perm_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/plusminus_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/ptr2_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/ptrspec_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/queue_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/queue_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/rawriter_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/reference_wrapper_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/resolve_name.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/reviter_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/rm_cp_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/rndshf_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/rope_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/rotate_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/search_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/set_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/set_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/setdiff_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/setinter_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/setunion_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/shared_ptr_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/slist_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/sort_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/sstream_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/sstream_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/stack_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/stack_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/stdexcept_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/stldbg_include.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/string_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/strstream_buffer_read_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/strstream_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/swap_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/times_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/thread_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/transform_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/type_traits_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/typeinfo_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/unary_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/uninitialized_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/unique_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/unordered_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/utility_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/valarray_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/valarray_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/vector_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/vector_header_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/test_errno.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/time_facets_test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/assert_header_test.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/ctype_header_test.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/c_limits_header_test.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/c_locale_header_test.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/errno_header_test.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/float_header_test.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/iso646_header_test.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/math_header_test.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/setjmp_header_test.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/signal_header_test.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/stdarg_header_test.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/stddef_header_test.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/stdio_header_test.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/stdlib_header_test.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/string_header_test.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/time_header_test.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/wchar_header_test.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../../test/unit/wctype_header_test.c
)

SET( CMAKE_CXX_FLAGS "" )
SET( CMAKE_CXX_FLAGS_RELEASE "" )
SET( CMAKE_CXX_FLAGS_DEBUG "" )
SET( CMAKE_CXX_FLAGS_RELWITHDEBINFO "" )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../../stlport )

add_library(
  stlport SHARED
  ${SRCS}
)

add_library(
  stlport_s STATIC
  ${SRCS}
)

add_executable(
  stl_unit_test
  ${TEST_SRCS}
)

add_dependencies( stl_unit_test stlport )

IF (WIN32)
  SET( SRCS "${SRCS} ${CMAKE_CURRENT_SOURCE_DIR}/../../src/stlport.rc" )
ENDIF (WIN32)

IF (CMAKE_COMPILER_IS_GNUCXX)

  SET_TARGET_PROPERTIES(stlport PROPERTIES
    COMPILE_FLAGS "-fPIC -fvisibility=hidden -pthread"
    # COMPILE_DEFINITIONS "-D_GNU_SOURCE"
    LINK_FLAGS -nodefaultlibs
    SOVERSION ${MAJOR}.${MINOR}
    VERSION ${MAJOR}.${MINOR}.${PATCH}
  )

  if ( "${LIBRARY_OUTPUT_PATH}" STREQUAL "" )
    SET_TARGET_PROPERTIES(stl_unit_test PROPERTIES
      LINK_FLAGS "-nodefaultlibs -L."
    )
  else()
    SET_TARGET_PROPERTIES(stl_unit_test PROPERTIES
      LINK_FLAGS "-nodefaultlibs -L${LIBRARY_OUTPUT_PATH} -Wl,-rpath=${LIBRARY_OUTPUT_PATH}"
    )
  endif()

  IF ( ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" )
    target_link_libraries( stl_unit_test -lstlport -lgcc_s.10.5 -lc -lm )
  ELSE ( ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" )
    target_link_libraries( stl_unit_test -lstlport -lgcc_s -lpthread -lc -lm -lrt )
  ENDIF ( ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" )

  IF ( ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" )
    SET( CMAKE_CXX_CREATE_SHARED_LIBRARY "${CMAKE_CXX_CREATE_SHARED_LIBRARY} -lgcc_s.10.5 -lc -lm -all_load -lsupc++ -lgcc_eh" )
  ELSE ( ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" )
    SET( CMAKE_CXX_CREATE_SHARED_LIBRARY "${CMAKE_CXX_CREATE_SHARED_LIBRARY} -Wl,--whole-archive -lsupc++ -Wl,--no-whole-archive -lgcc_s -lpthread -lc -lm -lrt" )
  ENDIF ( ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" )

  IF ( "${CMAKE_SYSTEM_NAME}" STREQUAL "Linux" )
    # MESSAGE( STATUS "${CMAKE_SYSTEM_NAME}" )
    # add_definitions( -D_GNU_SOURCE )
    SET_TARGET_PROPERTIES(stlport PROPERTIES
      COMPILE_DEFINITIONS "_GNU_SOURCE"
    )
    # remove_definitions( -Dstlport_EXPORTS )
  ENDIF ( "${CMAKE_SYSTEM_NAME}" STREQUAL "Linux" )

  IF ( "${CMAKE_SYSTEM_NAME}" MATCHES "Darwin" )
    # MESSAGE( STATUS "${CMAKE_SYSTEM_NAME}" )
    # add_definitions( -D_GNU_SOURCE )
    SET_TARGET_PROPERTIES(stlport PROPERTIES
      COMPILE_DEFINITIONS "_REENTRANT"
    )
    SET_TARGET_PROPERTIES(stl_unit_test PROPERTIES
      COMPILE_DEFINITIONS "_REENTRANT"
    )
    # remove_definitions( -Dstlport_EXPORTS )
  ENDIF ( "${CMAKE_SYSTEM_NAME}" MATCHES "Darwin" )

  # MESSAGE( STATUS "${CMAKE_BUILD_TYPE}" )

  #SET( CMAKE_C_FLAGS "-fPIC -fvisibility=hidden"
  #     CACHE STRING "stlport C compiler flags" FORCE )
  SET( CMAKE_C_FLAGS_DEBUG  "-g" )
  SET( CMAKE_C_FLAGS_RELEASE "-O2" )

  #SET( CMAKE_CXX_FLAGS  "-fPIC -fvisibility=hidden"
  #     CACHE STRING "stlport C++ compiler flags" FORCE )
  SET( CMAKE_CXX_FLAGS_DEBUG  "-g" )
  SET( CMAKE_CXX_FLAGS_RELEASE "-O2" )

ENDIF (CMAKE_COMPILER_IS_GNUCXX)

IF (MSVC)
  SET_TARGET_PROPERTIES(stlport PROPERTIES
    COMPILE_FLAGS "/W4 /EHsc /Zi"
    COMPILE_DEFINITIONS "WINVER=0x0501;_STLP_USE_DYNAMIC_LIB"
    LINK_FLAGS "/fixed:no /incremental:no /LTCG /version:${MAJOR}.${MINOR}"
    SOVERSION ${MAJOR}.${MINOR}
  )

  SET_TARGET_PROPERTIES(stl_unit_test PROPERTIES
    COMPILE_FLAGS "/W4 /EHsc /Zi"
    COMPILE_DEFINITIONS WINVER=0x0501
    LINK_FLAGS "/fixed:no /incremental:no /LTCG"
  )

  target_link_libraries( stl_unit_test stlport )

  SET( CMAKE_C_FLAGS_DEBUG  "/MDd /D_DEBUG" )
  SET( CMAKE_C_FLAGS_RELEASE "/DNDEBUG /GL /O2" )

  SET( CMAKE_CXX_FLAGS_DEBUG  "/MDd /D_DEBUG" )
  SET( CMAKE_CXX_FLAGS_RELEASE "/MD /DNDEBUG /GL /O2" )

ENDIF (MSVC)
