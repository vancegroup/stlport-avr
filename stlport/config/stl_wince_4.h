/*
 * File to have Windows CE .NET (eMebedded Visual C++ 4) working with STLport
 * May 2004
 * Origin : Zdenek Nemec - zero@mapfactor.com
 */

# ifndef _STLP_WINCE_4_H
#   define _STLP_WINCE_4_H

// This flag is being used by STLport to support 
// old-fashioned Windows CE SDK (see stl_wince.h)
// do not use with eMebedded Visual C++ 4!
# ifdef _STLP_WINCE
#   undef _STLP_WINCE
# endif

// New STLport Windows CE .NET define.
# undef _STLP_WCE_NET
# define _STLP_WCE_NET UNDER_CE

// Always threaded in Windows CE .NET.
# ifndef _MT                            
#   define _MT
# endif

/*
 * Workaround Pocket PC 2003 missing RTTI support in OS image:
 * Turn this on if you are targeting Pocket PC 2003 or 
 * Windows CE .NET 4.2 image compiled whitout SYSGEN_RTTI 
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
#   define _STLP_USE_WIDE_INTERFACE 
# endif

// Force exception std to std instead of __std_alias.
# if defined (__cplusplus) && ! defined (_STLP_HAS_NO_NAMESPACES)
#   ifdef _STLP_VENDOR_EXCEPT_STD
#     undef _STLP_VENDOR_EXCEPT_STD
#   endif
#   define _STLP_VENDOR_EXCEPT_STD std
# endif

// Ensure _DEBUG is defined.
# if defined(DEBUG) && !defined(_DEBUG)
#   define _DEBUG
# endif

// Use old fashioned headers (ctime vs. time.h).
# undef _STLP_NO_NEW_C_HEADERS
# define _STLP_NO_NEW_C_HEADERS

// RTTI Bug support
# ifdef _STLP_RTTI_BUG
#   define _STLP_NO_EXCEPTION_HEADER
#   define _STLP_NO_EXCEPTIONS
#   undef _STLP_USE_EXCEPTIONS
#   ifdef _STLP_WINCE_USE_OUTPUTDEBUGSTRING
#       define _STLP_WINCE_TRACE(msg)   OutputDebugString(msg)
#   else
#       define _STLP_WINCE_TRACE(msg)   MessageBox(NULL,(msg),NULL,MB_OK)
#   endif
#   ifndef __THROW_BAD_ALLOC
#       define __THROW_BAD_ALLOC { _STLP_WINCE_TRACE(L"out of memory"); ExitThread(1); }
#   endif
# else
#   define _STLP_WINCE_TRACE(msg)   OutputDebugString(msg)
# endif

// Struct for Windows CE FILE implementation.
// This is ugly and could be danegerous in future Windows CE .NET SDKs.
# ifndef _FILECE_DEFINED
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
# define _FILECE_DEFINED
# endif

// Don't let windows.h define its min and max macros.
# if !defined(NOMINMAX)
#   define NOMINMAX
# endif

# ifndef _ABORT_DEFINED
#   define _STLP_ABORT() TerminateProcess(GetCurrentProcess(), 0)
#   define _ABORT_DEFINED
# endif

# ifndef _ASSERT_DEFINED
#   define assert(expr) _STLP_ASSERT(expr)
#   define _ASSERT_DEFINED
# endif

// They say it's needed.
# include <windows.h>

# endif /* _STLP_WINCE_4_H */
