/*
 * Copyright (c) 1999
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1999 
 * Boris Fomitchev
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

#ifndef FSTREAM_IMPL_H
# define FSTREAM_IMPL_H

#include <stl/_stdio_file.h>

# ifdef __STL_HAS_NO_NAMESPACES
#  define __SGI_BEGIN_NAMESPACE
#  define __SGI_END_NAMESPACE
#  define SGI
# else
#  define __SGI_BEGIN_NAMESPACE namespace SGI {
#  define __SGI_END_NAMESPACE }
# endif

__SGI_BEGIN_NAMESPACE

# ifndef __STL_HAS_NO_NAMESPACES
using __STLPORT_STD::streamoff;
using __STLPORT_STD::ios_base;
using __STLPORT_STD::streamsize;
using __STLPORT_STD::streamoff;
using __STLPORT_STD::char_traits;
# if !(_MSCVER<=1100)
 using __STLPORT_STD::char_traits;
# endif
# ifndef __STL_USE_UNIX_IO
using __STL_VENDOR_CSTD::FILE;
using __STL_VENDOR_CSTD::ftell;
# endif

using __STLPORT_STD::_FILE_fd;
# endif

extern bool __is_regular_file(_STL_fd fd);
extern streamoff __file_size(_STL_fd fd);

__SGI_END_NAMESPACE

#endif /* FSTREAM_IMPL_H */
