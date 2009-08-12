# -*- makefile -*- Time-stamp: <08/11/23 22:16:28 ptr>

# this is the version number of needed STLport library for linking
LIBMAJOR = 6
LIBMINOR = 0

PRGNAME = cmp_unit_test
SRC_CC = suite.cc
SRC_CPP = epilog_test.cpp \
        algorithm_header_test.cpp \
	bitset_header_test.cpp \
        boost_check.cpp \
	cassert_header_test.cpp \
	cctype_header_test.cpp \
	cerrno_header_test.cpp \
	cfloat_header_test.cpp \
	ciso646_header_test.cpp \
	climits_header_test.cpp \
	clocale_header_test.cpp \
	cmath_header_test.cpp \
	complex_header_test.cpp \
	csetjmp_header_test.cpp \
	setjmp_header_test2.cpp \
	csignal_header_test.cpp \
	cstdarg_header_test.cpp \
	cstddef_header_test.cpp \
	cstdio_header_test.cpp \
        cstdint_header_test.cpp \
	cstdlib_header_test.cpp \
	cstring_header_test.cpp \
	ctime_header_test.cpp \
	cwchar_header_test.cpp \
	cwctype_header_test.cpp \
	deque_header_test.cpp \
	exception_header_test.cpp \
	fstream_header_test.cpp \
	functional_header_test.cpp \
	iomanip_header_test.cpp \
	ios_header_test.cpp \
	iosfwd_header_test.cpp \
	iostream_header_test.cpp \
	istream_header_test.cpp \
	iterator_header_test.cpp \
	limits_header_test.cpp \
	list_header_test.cpp \
	locale_header_test.cpp \
        macro_checks.cpp \
	map_header_test.cpp \
	memory_header_test.cpp \
	new_header_test.cpp \
	numeric_header_test.cpp \
	ostream_header_test.cpp \
	queue_header_test.cpp \
	set_header_test.cpp \
	sstream_header_test.cpp \
	stack_header_test.cpp \
	stdexcept_header_test.cpp \
        stdint_header_test.cpp \
        stldbg_include.cpp \
        streambuf_header_test.cpp \
        string_header_test.cpp \
	strstream_header_test.cpp \
	typeinfo_header_test.cpp \
	utility_header_test.cpp \
	valarray_header_test.cpp \
	vector_header_test.cpp

SRC_C = assert_header_test.c \
	ctype_header_test.c \
	c_limits_header_test.c \
	c_locale_header_test.c \
	errno_header_test.c \
	float_header_test.c \
	iso646_header_test.c \
	math_header_test.c \
	setjmp_header_test.c \
	signal_header_test.c \
	stdarg_header_test.c \
	stddef_header_test.c \
	stdio_header_test.c \
        stdint_c_header_test.c \
	stdlib_header_test.c \
	string_header_test.c \
	time_header_test.c \
	wchar_header_test.c \
	wctype_header_test.c
