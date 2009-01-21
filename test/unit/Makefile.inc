# -*- makefile -*- Time-stamp: <08/12/12 22:30:34 ptr>

# this is the version number of needed STLport library for linking
LIBMAJOR = 6
LIBMINOR = 0

PRGNAME = stl_unit_test
SRC_CC = suite.cc \
         numerics.cc
SRC_CPP = adj_test.cpp \
	alg_test.cpp \
	allocator_test.cpp \
	bcompos_test.cpp \
	bind_test.cpp \
	binsert_test.cpp \
	bitset_test.cpp \
	bsearch_test.cpp \
	bvector_test.cpp \
	cmath_test.cpp \
	codecvt_test.cpp \
	collate_facets_test.cpp \
	config_test.cpp \
	copy_test.cpp \
	count_test.cpp \
	cstring_test.cpp \
	ctype_facets_test.cpp \
	deque_test.cpp \
	divides_test.cpp \
	exception_test.cpp \
	fill_test.cpp \
	find_test.cpp \
	finsert_test.cpp \
	fstream_test.cpp \
        functor_test.cpp \
	hash_test.cpp \
	heap_test.cpp \
	includes_test.cpp \
	inplace_test.cpp \
	insert_test.cpp \
	ioiter_test.cpp \
	stream_test.cpp \
	iota_test.cpp \
	istmit_test.cpp \
	iter_test.cpp \
	lexcmp_test.cpp \
	limits_test.cpp \
	list_test.cpp \
	locale_test.cpp \
	map_test.cpp \
	memory_test.cpp \
	merge_test.cpp \
	messages_facets_test.cpp \
	mfunptr_test.cpp \
	mismatch_test.cpp \
	modulus_test.cpp \
	money_facets_test.cpp \
	multiset_test.cpp \
	neq_test.cpp \
	nthelm_test.cpp \
	num_facets_test.cpp \
	num_put_get_test.cpp \
	ostmit_test.cpp \
	pair_test.cpp \
	partial_test.cpp \
	partition_test.cpp \
	perm_test.cpp \
	ptr2_test.cpp \
	ptrspec_test.cpp \
	rawriter_test.cpp \
	reference_wrapper_test.cpp \
	resolve_name.cpp \
	reviter_test.cpp \
	rndshf_test.cpp \
	rope_test.cpp \
	rotate_test.cpp \
	search_test.cpp \
	set_test.cpp \
	setdiff_test.cpp \
	setinter_test.cpp \
	setunion_test.cpp \
	shared_ptr_test.cpp \
	slist_test.cpp \
	sort_test.cpp \
	string_test.cpp \
	strstream_buffer_read_test.cpp \
	swap_test.cpp \
	transform_test.cpp \
	unary_test.cpp \
	uninitialized_test.cpp \
	unique_test.cpp \
	unordered_test.cpp \
	valarray_test.cpp \
	vector_test.cpp \
	test_errno.cpp \
	time_facets_test.cpp
