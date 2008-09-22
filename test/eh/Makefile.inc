# -*- makefile -*- Time-stamp: <05/03/29 23:39:01 ptr>

# this is the version number of needed STLport library for linking
LIBMAJOR = 5
LIBMINOR = 2

PRGNAME = eh_test
SRC_CPP = TestClass.cpp \
          main.cpp \
          nc_alloc.cpp \
          random_number.cpp \
          test_algo.cpp \
          test_algobase.cpp \
          test_list.cpp \
          test_slist.cpp \
          test_bit_vector.cpp \
          test_vector.cpp \
          test_deque.cpp \
          test_set.cpp \
          test_map.cpp \
          test_hash_map.cpp \
          test_hash_set.cpp \
          test_rope.cpp \
          test_string.cpp \
          test_bitset.cpp \
          test_valarray.cpp

