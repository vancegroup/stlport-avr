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
# include "stlport_prefix.h"
#include <stdio_streambuf>

#ifdef __STL_UNIX
#include <sys/types.h>
#include <sys/stat.h>
#endif /* __unix */

#include <stl/_fstream.h>
#include "fstream_impl.h"

# if defined (__STL_USE_WIN32_IO)
# if defined (__BORLANDC__)
// #  include <cio.h>
#  include <cfcntl.h>
# else
#  include <io.h>
#  include <fcntl.h>
# endif

#  include <sys/stat.h>
# endif



__SGI_BEGIN_NAMESPACE
//----------------------------------------------------------------------
// Class stdio_streambuf_base

stdio_streambuf_base::stdio_streambuf_base(FILE* file)
  : __STLPORT_STD::basic_streambuf<char, __STLPORT_STD::char_traits<char> >(file, 0),
    _M_file(file)
{}

stdio_streambuf_base::~stdio_streambuf_base()
{
  __STL_VENDOR_CSTD::fflush(_M_file);
}

__STLPORT_STD::streambuf* stdio_streambuf_base::setbuf(char* s, streamsize n)
{
  __STL_VENDOR_CSTD::setvbuf(_M_file, s, (s == 0 && n == 0) ? _IONBF : _IOFBF, n);
  return this;
}

stdio_streambuf_base::pos_type
stdio_streambuf_base::seekoff(off_type off, ios_base::seekdir dir,
                              ios_base::openmode /* mode */)
{
  int whence;
  switch(dir) {
  case ios_base::beg:
    whence = SEEK_SET;
    break;
  case ios_base::cur:
    whence = SEEK_CUR;
    break;
  case ios_base::end:
    whence = SEEK_END;
    break;
  default:
    return pos_type(-1);
  }
      
  if (__STL_VENDOR_CSTD::fseek(_M_file, off, whence) == 0) {
    fpos_t pos;
    __STL_VENDOR_CSTD::fgetpos(_M_file, &pos);
    // added 21 june 00 mdb,rjf,wjs: glibc 2.2 changed fpos_t to be a struct instead
    // of a primitive type
#if (defined(__GLIBC__) && ( (__GLIBC__ > 2) || ( (__GLIBC__ == 2) && (__GLIBC_MINOR__ >= 2) ) ) )
    return pos_type((streamoff)pos.__pos);
#elif defined(__ISCPP__) || defined(__MVS__) || (__OS400__)
     return pos_type(pos.__fpos_elem[ 0 ]);
#else
    return pos_type(pos);
#endif
  }
  else
    return pos_type(-1);
}


stdio_streambuf_base::pos_type
stdio_streambuf_base::seekpos(pos_type pos, ios_base::openmode /* mode */)   // dwa 4/27/00 - suppress unused parameter warning
{

  // added 21 june 00 mdb,rjf,wjs: glibc 2.2 changed fpos_t to be a struct instead
  // of a primitive type
#if (defined(__GLIBC__) && ( (__GLIBC__ > 2) || ( (__GLIBC__ == 2) && (__GLIBC_MINOR__ >= 2) ) ) )
  fpos_t p;
  p.__pos = pos;
  memset( &(p.__state), 0, sizeof(p.__state) );
#elif defined(__MVS__) || (__OS400__)
  fpos_t p;
  p.__fpos_elem[0] = pos;
#else
  fpos_t p(pos);
#endif

  if (__STL_VENDOR_CSTD::fsetpos(_M_file, &p) == 0)
    return pos;
  else
    return pos_type(-1);
}

int stdio_streambuf_base::sync()
{
  return __STL_VENDOR_CSTD::fflush(_M_file) == 0 ? 0 : -1;
}

//----------------------------------------------------------------------
// Class stdio_istreambuf

streamsize stdio_istreambuf::showmanyc()
{
  if (feof(_M_file)) 
    return -1;
  else {
    int fd = _FILE_fd(*_M_file);
# ifdef __STL_USE_WIN32_IO
    // in this case, __file_size works with Win32 fh , not libc one
    streamoff size;
    struct stat buf;
# ifdef __BORLANDC__
    if(fstat(fd, &buf) == 0 && S_ISREG( buf.st_mode ) )
# else
    if(fstat(fd, &buf) == 0 && ( _S_IFREG & buf.st_mode ) )
# endif
      size = ( buf.st_size > 0  ? buf.st_size : 0);
    else
      size = 0;
# else
    streamoff size = SGI::__file_size(fd);
# endif
    // fbp : we can use ftell as this flavour always use stdio.
    long pos = __STL_VENDOR_CSTD::ftell(_M_file);
    return pos >= 0 && size > pos ? size - pos : 0;
  }
}

stdio_istreambuf::int_type stdio_istreambuf::underflow()
{
  int c = getc(_M_file);
  if (c != EOF) {
    __STL_VENDOR_CSTD::ungetc(c, _M_file);
    return c;
  }
  else
    return traits_type::eof();
}

stdio_istreambuf::int_type stdio_istreambuf::uflow()
{
  int c = getc(_M_file);
  return c != EOF ? c : traits_type::eof();
}

stdio_istreambuf::int_type stdio_istreambuf::pbackfail(int_type c)
{
  if (c != traits_type::eof()) {
    int result = __STL_VENDOR_CSTD::ungetc(c, _M_file);
    return result != EOF ? result : traits_type::eof();
  }
  else{
    if (this->eback() < this->gptr()) {
      this->gbump(-1);
      return traits_type::not_eof(c);
    }
    else
      return traits_type::eof();
  }
}

//----------------------------------------------------------------------
// Class stdio_ostreambuf

streamsize stdio_ostreambuf::showmanyc()
{
  return -1;
}

stdio_ostreambuf::int_type stdio_ostreambuf::overflow(int_type c)
{
  // Write the existing buffer, without writing any additional character.
  if (c == traits_type::eof()) {
    // Do we have a buffer to write?
    ptrdiff_t unwritten = this->pptr() - this->pbase();
    if (unwritten != 0) {
      __STL_VENDOR_CSTD::fflush(_M_file);
      // Test if the write succeeded.
      if (this->pptr() - this->pbase() < unwritten)
        return traits_type::not_eof(c);
      else
        return traits_type::eof();
    }

    // We always succeed if we don't have to do anything.
    else
      return traits_type::not_eof(c);
  }

  // Write the character c, and whatever else might be in the buffer.
  else {
    int result = putc(c, _M_file);
    return result != EOF ? result : traits_type::eof();
  }
}

__SGI_END_NAMESPACE

// Local Variables:
// mode:C++
// End:

