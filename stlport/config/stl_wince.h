/*
 * File to have Windows CE Toolkit for VC++ 5.0 working with STLport
 * 09 - 03 - 1999
 * Origin : Giuseppe Govi - g.govi@iol.it
 */

#ifndef _STLP_WINCE_H
#define _STLP_WINCE_H

// this flag is being used by STLport
#   define _STLP_WINCE

// tell other parts no iostreams are desired
#   define _STLP_NO_IOSTREAMS 1

// tell other parts no threads are there
#   define _STLP_NO_THREADS 1

// not all new-style headers are available...
# define _STLP_HAS_NO_NEW_C_HEADERS

#     undef _STLP_HAS_NO_EXCEPTIONS
#     define _STLP_HAS_NO_EXCEPTIONS
#     undef _STLP_NO_EXCEPTION_HEADER
#     define _STLP_NO_EXCEPTION_HEADER

// we have to use malloc instead of new
# undef  _STLP_USE_NEWALLOC
# define _STLP_USE_MALLOC

//# ifdef _STLP_MSVC
//#     pragma warning (disable: 4786)
//# endif

#ifdef _STLP_WINCE_USE_OUTPUTDEBUGSTRING
#define _STLP_WINCE_TRACE(msg)   OutputDebugString(msg)
#else
#define _STLP_WINCE_TRACE(msg)   MessageBox(NULL,(msg),NULL,MB_OK)
#endif

#ifndef __THROW_BAD_ALLOC
#define __THROW_BAD_ALLOC _STLP_WINCE_TRACE(L"out of memory"); ExitThread(1)
#endif

#ifndef _SIZE_T_DEFINED
typedef unsigned int size_t;
#define _SIZE_T_DEFINED
#endif

#ifndef __PLACEMENT_NEW_INLINE
inline void *__cdecl operator new(size_t, void *_P) { return (_P); }
#define __PLACEMENT_NEW_INLINE
#endif

#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif

//ptrdiff_t is not defined in Windows CE SDK
#ifndef _PTRDIFF_T_DEFINED
typedef int ptrdiff_t;
#define _PTRDIFF_T_DEFINED
#endif

#ifndef _ABORT_DEFINED
# define _STLP_ABORT() TerminateProcess(GetCurrentProcess(), 0)
# define _ABORT_DEFINED
#endif


#ifndef _ASSERT_DEFINED
# define assert(expr) _STLP_ASSERT(expr)
# define _ASSERT_DEFINED
#endif

// they say it's needed 
# include <windows.h>

#endif /* _STLP_WCE_H */


