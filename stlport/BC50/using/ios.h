#  ifdef __STL_BROKEN_USING_DIRECTIVE
using namespace __STL_NEW_IO_NAMESPACE;
#  else

using __STL_NEW_IO_NAMESPACE::ios;
using __STL_NEW_IO_NAMESPACE::streamoff;
using __STL_NEW_IO_NAMESPACE::streamsize;

using __STL_NEW_IO_NAMESPACE::ios_base;
using __STL_NEW_IO_NAMESPACE::basic_ios;

// _lib.std.ios.manip_, manipulators:	
using __STL_NEW_IO_NAMESPACE::boolalpha;
using __STL_NEW_IO_NAMESPACE::noboolalpha;
using __STL_NEW_IO_NAMESPACE::showbase;
using __STL_NEW_IO_NAMESPACE::noshowbase;
using __STL_NEW_IO_NAMESPACE::showpoint;
using __STL_NEW_IO_NAMESPACE::noshowpoint;
using __STL_NEW_IO_NAMESPACE::showpos;
using __STL_NEW_IO_NAMESPACE::noshowpos;
using __STL_NEW_IO_NAMESPACE::skipws;
using __STL_NEW_IO_NAMESPACE::noskipws;
using __STL_NEW_IO_NAMESPACE::uppercase;
using __STL_NEW_IO_NAMESPACE::nouppercase;

// _lib.adjustfield.manip_ adjustfield:
using __STL_NEW_IO_NAMESPACE::internal;
using __STL_NEW_IO_NAMESPACE::left;
using __STL_NEW_IO_NAMESPACE::right;

// _lib.basefield.manip_ basefield:
using __STL_NEW_IO_NAMESPACE::dec;
using __STL_NEW_IO_NAMESPACE::hex;
using __STL_NEW_IO_NAMESPACE::oct;

// _lib.floatfield.manip_ floatfield:
using __STL_NEW_IO_NAMESPACE::fixed;
using __STL_NEW_IO_NAMESPACE::scientific;

#  endif  /* __STL_BROKEN_USING_DIRECTIVE */

