#ifdef UNDER_CE

#include "stlport_prefix.h"

#if defined(_STLP_USE_WINCE_CRT_FUNCTIONS)

#include <windows.h>
#include <wchar.h>

//
// Supply a replacement for the mbtowc and wctomb CRT functions that Windows CE does not include
//  (at the moment, these routines simply use the system default code page)
//

int wctomb(char * s, wchar_t wchar)
{
    int retVal = ::WideCharToMultiByte(CP_ACP, 0, &wchar, 1, s, 10, NULL, NULL);
    if (retVal != 0)
        return retVal;
        
    return -1;
}

int mbtowc(wchar_t * pwc, char const * s, size_t n)
{
    if (!s || n == 0)
        return 0;
    
    if (!pwc)
        pwc = (wchar_t *)_alloca( sizeof(wchar_t) );
    
    int mbCharLen = mblen(s, n);
    if (::MultiByteToWideChar(CP_ACP, 0, s, ((mbCharLen > 0) ? mbCharLen : 1), pwc, 1) == 0)
        return -1;
        
    return mbCharLen;
}


int mblen(char const * s, size_t n)
{
    if (n == 0 || !s || s[0] == 0)
        return 0;
        
    if (n == 1 || !IsDBCSLeadByte( s[0] ) || s[1] == 0)
        return 1;
        
    return 2;
}


#endif  // _STLP_USE_WINCE_CRT_FUNCTIONS

#endif  //  UNDER_CE
