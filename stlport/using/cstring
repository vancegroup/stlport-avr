using __STL_VENDOR_CSTD::size_t;

#  ifndef __STL_NO_CSTD_FUNCTION_IMPORTS
#   if defined(__MSL__) && __MC68K__ && !_No_BlockMove && __dest_os == __mac_os
#    undef memcpy
#    undef memmove
inline void* memcpy(void* dst, const void* src, size_t len)
{
	return __STL_VENDOR_CSTD::__memcpy(dst, src, len);
}
inline void* memmove(void* dst, const void* src, size_t len)
{
	return __STL_VENDOR_CSTD::__memmove(dst, src, len);
}
#   else

 using __STL_VENDOR_CSTD::memmove;
 using __STL_VENDOR_CSTD::memcpy;

#   endif

# if ! defined (__BORLANDC__)
using __STL_VENDOR_CSTD::memchr;
using __STL_VENDOR_CSTD::strchr;
using __STL_VENDOR_CSTD::strpbrk;
using __STL_VENDOR_CSTD::strrchr;
using __STL_VENDOR_CSTD::strstr;
# endif

using __STL_VENDOR_CSTD::memcmp;
using __STL_VENDOR_CSTD::memset;

using __STL_VENDOR_CSTD::strcat;

# if !defined (strcmp)
using __STL_VENDOR_CSTD::strcmp;
# endif

using __STL_VENDOR_CSTD::strcoll;
# if !defined (strcpy)
using __STL_VENDOR_CSTD::strcpy;
# endif
using __STL_VENDOR_CSTD::strcspn;
using __STL_VENDOR_CSTD::strerror;
using __STL_VENDOR_CSTD::strlen;
using __STL_VENDOR_CSTD::strncat;
using __STL_VENDOR_CSTD::strncmp;

using __STL_VENDOR_CSTD::strncpy;
using __STL_VENDOR_CSTD::strspn;

using __STL_VENDOR_CSTD::strtok;
using __STL_VENDOR_CSTD::strxfrm;
#  endif /* __STL_NO_CSTD_FUNCTION_IMPORTS */
