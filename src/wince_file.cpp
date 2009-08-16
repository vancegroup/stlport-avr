#if _WIN32_WCE >= 0x500

#include "stlport_prefix.h"

#if defined(_STLP_USE_WINCE_CRT_FUNCTIONS)

#include <windows.h>
#include <stdio.h>


//
//  Supply a replacement for the remove and rename CRT functions
//

int remove(const char * filename)
{
    int filename_size = strlen(filename);
    LPWSTR wide_filename = (LPWSTR)_alloca( (filename_size + 1) * sizeof(WCHAR) );
    if(::MultiByteToWideChar(CP_ACP, 0,  filename, filename_size,  wide_filename, filename_size + 1) == 0)
       return true;
    
    return (::DeleteFile(wide_filename) == 0);
}

int rename(const char * oldname, const char * newname)
{
    int oldname_size = strlen(oldname);
    LPWSTR wide_oldname = (LPWSTR)_alloca( (oldname_size + 1) * sizeof(WCHAR) );
    if(::MultiByteToWideChar(CP_ACP, 0,  oldname, oldname_size,  wide_oldname, oldname_size + 1) == 0)
       return true;
    
    int newname_size = strlen(newname);
    LPWSTR wide_newname = (LPWSTR)_alloca( (newname_size + 1) * sizeof(WCHAR) );
    if(::MultiByteToWideChar(CP_ACP, 0,  newname, newname_size,  wide_newname, newname_size + 1) == 0)
       return true;
    
    return (::MoveFile(wide_oldname, wide_newname) == 0);
}


#endif  // _STLP_USE_WINCE_CRT_FUNCTIONS

#endif  //  _WIN32_WCE >= 0x500
