// sysver.cpp

/*
OSVERSIONINFO
 The OSVERSIONINFO data structure contains operating system version information.
 The information includes major and minor version numbers, a build number, a
 platform identifier, and descriptive text about the operating system. This
 structure is used with the GetVersionEx function.

 typedef struct _OSVERSIONINFO{
    DWORD dwOSVersionInfoSize;
    DWORD dwMajorVersion;
    DWORD dwMinorVersion;
    DWORD dwBuildNumber;
    DWORD dwPlatformId;
    TCHAR szCSDVersion[ 128 ];
 } OSVERSIONINFO;

Members
dwOSVersionInfoSize
  Specifies the size, in bytes, of this data structure. Set this member to
  sizeof(OSVERSIONINFO) before calling the GetVersionEx function.

dwMajorVersion
 Identifies the major version number of the operating system. For example, for
 Windows NT version 3.51, the major version number is 3; and for Windows NT
 version 4.0, the major version number is 4.

dwMinorVersion
 Identifies the minor version number of the operating system. For example, for
 Windows NT version 3.51, the minor version number is 51; and for Windows NT
 version 4.0, the minor version number is 0.

dwBuildNumber
 Windows NT: Identifies the build number of the operating system.
 Windows 95: Identifies the build number of the operating system in the
 low-order word. The high-order word contains the major and minor version
 numbers.

dwPlatformId
 Identifies the operating system platform. This member can be one of the
 following values:

  Value                       Platform
  VER_PLATFORM_WIN32s         Win32s on Windows 3.1.
  VER_PLATFORM_WIN32_WINDOWS  Win32 on Windows 95 or Windows 98.
                              For Windows 95, dwMinorVersion is zero.
                              For Windows 98, dwMinorVersion is greater than zero.
  VER_PLATFORM_WIN32_NT       Win32 on Windows NT.

szCSDVersion
 Windows NT: Contains a null-terminated string, such as "Service Pack 3",
 that indicates the latest Service Pack installed on the system. If no Service
 Pack has been installed, the string is empty.
 Windows 95: Contains a null-terminated string that provides arbitrary
 additional information about the operating system.

QuickInfo
  Windows NT: Requires version 3.5 or later.
  Windows: Requires Windows 95 or later.
  Windows CE: Requires version 1.0 or later.
  Header: Declared in winbase.h.
  Unicode: Defined as Unicode and ANSI structures.
*/

#include <windows.h>
#include <stdio.h>

void main () {

  unsigned char scKeyValue[128] = {0x0,};
  unsigned char szServicePack[64] = {0x0,};
  long sp6a_flag = 0;
  DWORD dwIndex = 0;
  char scKey[128] = {0x0,};
  DWORD dwKeysize = 128;
  DWORD dwType;
  DWORD dwKeyValueSize = 16;
  static WORD wVer95;
  static WORD wBuild;
  static DWORD dwMajor;
  static DWORD dwMinor;
  static DWORD dwPlatID;
  bool is_empty = true;
  bool is_nt_sp6a = false;

  HKEY hkSubKey;
  OSVERSIONINFO osvi;

  // Initialize the OSVERSIONINFO structure.
  //ZeroMemory( &osvi, sizeof( osvi ) );
  memset( (void*)&osvi, 0, sizeof( osvi ) );
  osvi.dwOSVersionInfoSize = sizeof( osvi );

  int no_error = GetVersionEx( &osvi );

  if( no_error ) {

    wVer95 = HIWORD(osvi.dwBuildNumber);
    wBuild = LOWORD(osvi.dwBuildNumber);
    dwMajor = osvi.dwMajorVersion;
    dwMinor = osvi.dwMinorVersion;
    dwPlatID = osvi.dwPlatformId;

    printf( "Version %d.%d.%d ", dwMajor, dwMinor, wBuild);

    if (RegOpenKey(HKEY_LOCAL_MACHINE,
            "Software\\Microsoft\\Windows NT\\CurrentVersion\\Hotfix\\Q246009",
            &hkSubKey) == ERROR_SUCCESS) {

      if (RegEnumValue( hkSubKey, dwIndex, scKey, &dwKeysize, NULL,
                        &dwType, (unsigned char *)scKeyValue,
                        &dwKeyValueSize) == ERROR_SUCCESS) {

        sp6a_flag = (scKeyValue[3] * 0x1000000) + (scKeyValue[2] * 0x10000) +
                    (scKeyValue[1] * 0x100) + (scKeyValue[0] * 0x1);
      }

      if( dwPlatID == VER_PLATFORM_WIN32_NT &&
          dwMajor == 4 && dwMinor == 0 &&
          wBuild == 1381 && sp6a_flag == 1) {
        is_nt_sp6a = true;
        printf( "%s", "Service Pack 6a" );
      }
      RegCloseKey(hkSubKey);
    }

    if( !is_nt_sp6a ) {
      if( osvi.szCSDVersion[0] != 0 ) {
        if( strlen( osvi.szCSDVersion ) > 0) {
          strncpy(szServicePack, osvi.szCSDVersion, 63);
          for( unsigned int i = 0; i < strlen( szServicePack ); ++i ) {
            if( !isspace( osvi.szCSDVersion[i] ) ) {
              is_empty = false;
            }
            if (!is_empty) {
              printf( " %s", osvi.szCSDVersion);
              break;
            }
          }
        }
      }
    }
  }
}
