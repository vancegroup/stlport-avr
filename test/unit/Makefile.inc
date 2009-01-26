# -*- makefile -*- Time-stamp: <09/01/26 23:28:10 ptr>

# this is the version number of needed STLport library for linking
LIBMAJOR = 6
LIBMINOR = 0

PRGNAME = stl_unit_test
SRC_CC = suite.cc \
         numerics.cc
SRC_CPP = alg_test.cpp \
	allocator_test.cpp \
	binary_test.cpp \
	bind_test.cpp \
	bitset_test.cpp \
	cmath_test.cpp \
	codecvt_test.cpp \
	collate_facets_test.cpp \
	config_test.cpp \
	cstring_test.cpp \
	ctype_facets_test.cpp \
	deque_test.cpp \
        errno_test.cpp \
	exception_test.cpp \
	fstream_test.cpp \
        functor_test.cpp \
	hash_test.cpp \
	heap_test.cpp \
	includes_test.cpp \
	inplace_test.cpp \
	insert_test.cpp \
	ioiter_test.cpp \
	stream_test.cpp \
	istmit_test.cpp \
	iter_test.cpp \
	limits_test.cpp \
	list_test.cpp \
	locale_test.cpp \
	map_test.cpp \
	messages_facets_test.cpp \
	mfunptr_test.cpp \
	money_facets_test.cpp \
	multiset_test.cpp \
	nthelm_test.cpp \
	num_facets_test.cpp \
	num_put_get_test.cpp \
	ostmit_test.cpp \
	utility_test.cpp \
	partial_test.cpp \
	partition_test.cpp \
	perm_test.cpp \
	ptr2_test.cpp \
	ptrspec_test.cpp \
	reference_wrapper_test.cpp \
	resolve_name.cpp \
	reviter_test.cpp \
	rndshf_test.cpp \
	rope_test.cpp \
	rotate_test.cpp \
	set_test.cpp \
	setdiff_test.cpp \
	setinter_test.cpp \
	setunion_test.cpp \
	shared_ptr_test.cpp \
	slist_test.cpp \
	sort_test.cpp \
	string_test.cpp \
	unary_test.cpp \
	uninitialized_test.cpp \
	unique_test.cpp \
	unordered_test.cpp \
	valarray_test.cpp \
	vector_test.cpp \
	time_facets_test.cpp
