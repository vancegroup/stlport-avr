#define _STLP_PLATFORM "Cygwin"

#define _STLP_UNIX

/* Glibc is the platform API */
#if !defined (_STLP_USE_GLIBC)
#  define _STLP_USE_GLIBC
#endif

#ifndef _STLP_USE_STDIO_IO
#  define _STLP_USE_UNIX_IO
#endif

#define _STLP_LDOUBLE_96
