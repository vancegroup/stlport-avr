/*
 * File to have Microsoft eMbedded Visual C++ 3.0 and .NET working with STLport
 * May 2004
 * Origin : Zdenek Nemec - zero@mapfactor.com
 *          Michael Fink - vividos@users.sourceforge.net
 */

# ifndef _STLP_EVC_H
#  define _STLP_EVC_H

// This flag is being used by STLport to support
// old-fashioned Windows CE SDK (see stl_wince.h)
// do not use with eMebedded Visual C++ 3 or 4!
# ifdef _STLP_WINCE
#  undef _STLP_WINCE
# endif

/* Compiler dependent define. The following defines may be available:
 * _STLP_WCE_EVC3 when compiling under eMbedded Visual C++ 3
 * _STLP_WCE_NET  when compiling under eMbedded Visual C++ .NET
 * _STLP_WCE      always defined when compiling with one of the above
 */
# undef _STLP_WCE_EVC3
# undef _STLP_WCE_NET

# if (_WIN32_WCE > 300)
#  define _STLP_WCE_NET UNDER_CE
# elif (_WIN32_WCE == 300)
#  define _STLP_WCE_EVC3 UNDER_CE
# else
#  error No support for Windows CE below 3.0!
# endif

// This is defined for all platforms using Windows CE
# define _STLP_WCE


// Always threaded in eMbedded Visual C++ 3.0 and .NET
# ifndef _MT
#  define _MT
# endif

/*
 * Workaround Pocket PC 2003 missing RTTI support in OS image:
 * Turn this on if you are targeting Pocket PC 2003 or
 * Windows CE .NET 4.2 image compiled without SYSGEN_RTTI
 * (at this time this bug seems to be in every SDK except
 * version 4.0) you propably want to build your own image
 * with Platform Builder to enable RTTI and exception.
 *
 * This define is off by default since it's recommended
 * to use Microsoft RTTI patch. The patch is available at
 * http://support.microsoft.com/default.aspx?scid=kb;[LN];830482
 *
 * Define this, turn off /GX an /GR compiler options
 * and do not link against Ccrtrtti.lib(rtti patch lib)
 * if you do not want c++ exceptions.
 *
 * Note: This option is always switched on for eMbedded Visual C++ 3!
 */
// # define _STLP_RTTI_BUG

/*
 * Redirect cout, cerr and clog:
 * If defined redirect cout, cerr and clog to
 * files stdout.txt, stderr.txt and stdlog.txt
 */
// # define _STLP_REDIRECT_STDSTREAMS

/*
 * Static class members may generate LNK1179:
 * Wrong COMDAT packing may cause LNK1179 error.
 * For details see http://groups.google.com/groups?th=8a05c82c4ffee280
 * example P78. This define is not used/needed at this moment
 * but may came handy in future...
 */
//# define _STLP_STATIC_MEMBERS_BUG

// Use wide-string interface of windows native functions (CreateFile...).
// Note that this should be defined all the time while under CE.
# if defined(UNICODE)
#  define _STLP_USE_WIDE_INTERFACE
# endif

// Force exception std to std instead of __std_alias.
# if defined (__cplusplus) && ! defined (_STLP_HAS_NO_NAMESPACES)
#  ifdef _STLP_VENDOR_EXCEPT_STD
#   undef _STLP_VENDOR_EXCEPT_STD
#  endif
#   define _STLP_VENDOR_EXCEPT_STD std
# endif

// Ensure _DEBUG is defined.
# if defined(DEBUG) && !defined(_DEBUG)
#  define _DEBUG
# endif

// threads
//# undef _REENTRANT
//#  define _REENTRANT
//# undef _NOTHREADS

// Use old fashioned headers (ctime vs. time.h).
# undef _STLP_NO_NEW_C_HEADERS
# define _STLP_NO_NEW_C_HEADERS

// RTTI Bug support
# if defined(_STLP_RTTI_BUG) || defined(_STLP_WCE_EVC3)
#  define _STLP_NO_EXCEPTION_HEADER
#  define _STLP_NO_EXCEPTIONS
#  undef _STLP_USE_EXCEPTIONS
#  ifdef _STLP_WINCE_USE_OUTPUTDEBUGSTRING
#   define _STLP_WINCE_TRACE(msg)   OutputDebugString(msg)
#  else
#   define _STLP_WINCE_TRACE(msg)   MessageBox(NULL,(msg),NULL,MB_OK)
#  endif
#  ifndef __THROW_BAD_ALLOC
#   define __THROW_BAD_ALLOC { _STLP_WINCE_TRACE(L"out of memory"); ExitThread(1); }
#  endif
# else
#  define _STLP_WINCE_TRACE(msg)   OutputDebugString(msg)
# endif

/*
 * eMbedded Visual C++ .NET specific settings
 */
# ifdef _STLP_WCE_NET

// Struct for Windows CE FILE implementation.
// This is ugly and could be danegerous in future Windows CE .NET SDKs.
#  ifndef _FILECE_DEFINED
typedef struct  {
        char *_ptr;
        int   _cnt;
        char *_base;
        int   _flag;

        int   _charbuf;
        int   _bufsiz;
        unsigned    _res1;
        unsigned    _res2;

        unsigned    _res3;
        unsigned    _res4;
        unsigned    _res5;
        void*       _file;

        unsigned    _res6;
        unsigned    _res7;
        unsigned    _res8;
        unsigned    _res9;
} _iobufce;
typedef _iobufce FILECE;
#  define _FILECE_DEFINED
# endif /* _FILECE_DEFINED */

# endif /* _STLP_WCE_NET */


/*
 * eMbedded Visual C++ 3.0 specific settings
 */
#ifdef _STLP_WCE_EVC3

// eMbedded 3 doesn't have mbstate_t and we could define _STLP_NO_MBSTATE_T,
// but the flag isn't fully supported in STLport, and it's easier to use the
// evc4 definition for that type.
typedef int mbstate_t;

// evc3 has no locale and time support
#define _STLP_NO_LOCALE_SUPPORT
#define _STLP_NO_TIME_SUPPORT

// evc3 has new, but no explicit header
#define _STLP_NO_NEW_HEADER
#define _STLP_NO_NEW_NEW_HEADER

// evc3 has no bad_alloc and no typeinfo
# undef _STLP_NO_BAD_ALLOC
# define _STLP_NO_BAD_ALLOC

# undef _STLP_NO_TYPEINFO
# define _STLP_NO_TYPEINFO

// missing things in eMbedded Visual C++ 3.0 headers
# ifndef _SIZE_T_DEFINED
   typedef unsigned int size_t;
#  define _SIZE_T_DEFINED
# endif

# ifndef _WCHAR_T_DEFINED
   typedef unsigned short wchar_t;
#  define _WCHAR_T_DEFINED
# endif

// ptrdiff_t is not defined in evc3 headers
# ifndef _PTRDIFF_T_DEFINED
   typedef int ptrdiff_t;
#  define _PTRDIFF_T_DEFINED
# endif

// clock_t is not defined in evc3 headers
# ifndef _CLOCK_T_DEFINED
   typedef long clock_t;
#  define _CLOCK_T_DEFINED
# endif

// Struct tm is not defined in evc3 headers
# ifndef _TM_DEFINED
struct tm {
   int tm_sec;     /* seconds after the minute - [0,59] */
   int tm_min;     /* minutes after the hour - [0,59] */
   int tm_hour;    /* hours since midnight - [0,23] */
   int tm_mday;    /* day of the month - [1,31] */
   int tm_mon;     /* months since January - [0,11] */
   int tm_year;    /* years since 1900 */
   int tm_wday;    /* days since Sunday - [0,6] */
   int tm_yday;    /* days since January 1 - [0,365] */
   int tm_isdst;   /* daylight savings time flag */
};
# define _TM_DEFINED
# endif

# ifdef __cplusplus
#  ifndef __PLACEMENT_NEW_INLINE
inline void *__cdecl operator new(size_t, void *_P) { return (_P); }
inline void __cdecl operator delete(void *, void *) { return; }
#   define __PLACEMENT_NEW_INLINE
#  endif

# endif /* __cplusplus */

# endif /* _STLP_WCE_EVC3 */


// Minimize windows.h includes
# if !defined(WIN32_LEAN_AND_MEAN)
#  define WIN32_LEAN_AND_MEAN
# endif
# if !defined(VC_EXTRALEAN)
#  define VC_EXTRALEAN
# endif
# if !defined(STRICT)
#  define STRICT
# endif

// Don't let windows.h define its min and max macros.
# if !defined(NOMINMAX)
#  define NOMINMAX
# endif

# ifndef _ABORT_DEFINED
#  define _STLP_ABORT() TerminateProcess(GetCurrentProcess(), 0)
#  define _ABORT_DEFINED
# endif

# ifndef _ASSERT_DEFINED
#  define assert(expr) _STLP_ASSERT(expr)
#  define _ASSERT_DEFINED
# endif

// needed for TerminateProcess and others
# include <windows.h>

#endif /* _STLP_EVC_H */
