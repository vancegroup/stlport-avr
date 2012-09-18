#ifdef UNDER_CE

#include "stlport_prefix.h"

#if defined(_STLP_USE_WINCE_CRT_FUNCTIONS)

//
// Supply a replacement for the strerror, strxfrm, and wcsxfrm CRT functions that Windows CE 
//  does not include (at the moment, these routines assume the "C" locale)
//

#include <errno.h>
#include <string.h>
#include <wchar.h>

char * strerror(int errnum)
{
    char * error_message[] = {
        NULL, "EPERM", "ENOENT", "ERSCH", "EINTR", "EIO", "ENXIO", "E2BIG", "ENOEXEC", "EBADF",
        "ECHILD", "EAGAIN", "ENOMEM", "EACCES", "EFAULT", NULL, "EBUSY", "EEXIST", "EXDEV", "ENODEV", 
        "ENOTDIR", "EISDIR", NULL, "ENFILE", "EMFILE", "ENOTTY", NULL, "EFBIG", "ENOSPC", "ESPIPE",
        "EROFS", "EMLINK", "EPIPE", "EDOM", NULL, NULL, "EDEADLK", NULL, "ENAMETOOLONG", "ENOLCK",
        "ENOSYS", "ENOTEMPTY"
        };

    if (errnum >= (sizeof(error_message) / sizeof(char *)))
        return NULL;

    return error_message[errnum];
}

size_t strxfrm(char * strDest, char const * strSource, size_t count)
{
    strncpy(strDest, strSource, count);
    return strlen(strDest);
}

size_t wcsxfrm(wchar_t * strDest, wchar_t const * strSource, size_t count)
{
    wcsncpy(strDest, strSource, count);
    return wcslen(strDest);
}


#endif  // _STLP_USE_WINCE_CRT_FUNCTIONS

#endif  //  UNDER_CE
