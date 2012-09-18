#ifdef UNDER_CE

#include "stlport_prefix.h"

#if defined(_STLP_USE_WINCE_CRT_FUNCTIONS)

#include <windows.h>


//
//  Supply a replacement for the time CRT function that Windows CE declares but never defines
//

#include <time.h>

static void ConvertFileTimeToUnixTime(const FILETIME & fileTime, time_t & unixTime)
{
    // Subtract off the diffence from 1 Jan 1601 to 1 Jan 1970
    unsigned long long newTime = ((unsigned long long)fileTime.dwHighDateTime << 32) | (fileTime.dwLowDateTime);
    newTime -= 116444736000000000;

    // Convert from 100 nanoseconds to seconds
    unixTime = time_t(newTime / 10000000);
}


static void ConvertUnixTimeToFileTime(time_t unixTime,  FILETIME & fileTime)
{
    // Convert from seconds to 100 nanoseconds
    unsigned long long newTime = (unsigned long long)unixTime * (unsigned long long)10000000;

    // Add in the diffence from 1 Jan 1601 to 1 Jan 1970
    newTime += 116444736000000000;

    fileTime.dwLowDateTime = (newTime & 0xFFFFFFFF);
    fileTime.dwHighDateTime = ((newTime >> 32) & 0xFFFFFFFF);
}

const int first_yday_of_month[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

static void ConvertSystemTimeToTM(const SYSTEMTIME & sysTime, struct tm & gtime )
{
    gtime.tm_sec = sysTime.wSecond;
    gtime.tm_min = sysTime.wMinute;
    gtime.tm_hour = sysTime.wHour;
    gtime.tm_mday = sysTime.wDay;
    gtime.tm_mon = (sysTime.wMonth - 1);
    gtime.tm_year = (sysTime.wYear - 1900);
    gtime.tm_wday = sysTime.wDayOfWeek;
    gtime.tm_isdst = 0;

    gtime.tm_yday = first_yday_of_month[ gtime.tm_mon ] + (gtime.tm_mday - 1);

    // If it is a leap year and we are after February, add one day
    if (gtime.tm_mon > 1 && (((sysTime.wYear % 400) == 0) || (((sysTime.wYear % 4) == 0) && ((sysTime.wYear % 100) != 0))))
        ++gtime.tm_yday;
}



time_t time(time_t * timer)
{
    SYSTEMTIME sysTime;
    GetSystemTime( &sysTime );

    FILETIME fileTime;
    SystemTimeToFileTime( &sysTime, &fileTime );

    time_t unixTime;
    ConvertFileTimeToUnixTime( fileTime, unixTime );

    if (timer)
        *timer = unixTime;

    return unixTime;
}


//
//  Supply a replacement for the clock CRT function that Windows CE declares but never defines
//

clock_t clock()
{
    unsigned int ticks = GetTickCount();
    return (ticks * CLOCKS_PER_SEC / 1000);
}


//
//  Supply replacements for the gmtime and localtime CRT functions that Windows CE declares but never defines
//

static DWORD g_TimeHolderTLSIndex = 0xFFFFFFFF;

static struct tm * GetTimeHolder()
{
    if (g_TimeHolderTLSIndex == 0xFFFFFFFF)
    {
        DWORD newIndex = TlsAlloc();
        if (InterlockedCompareExchangePointer((PVOID*)&g_TimeHolderTLSIndex, (PVOID)newIndex, (PVOID)0xFFFFFFFF) != (PVOID)0xFFFFFFFF)
            TlsFree( newIndex );
    }

    struct tm * pTimeHolder = (struct tm *)TlsGetValue( g_TimeHolderTLSIndex );
    if (!pTimeHolder)
    {
        pTimeHolder = (struct tm *)LocalAlloc(0, sizeof(struct tm));
        TlsSetValue( g_TimeHolderTLSIndex, (PVOID)pTimeHolder );
    }

    return pTimeHolder;
}


struct tm * gmtime(const time_t * timer)
{
    if (!timer || *timer < 0)
        return NULL;

    struct tm * pTimeHolder = GetTimeHolder();
    if (!pTimeHolder)
        return NULL;

    FILETIME fileTime;
    ConvertUnixTimeToFileTime( *timer,  fileTime );

    SYSTEMTIME sysTime;
    FileTimeToSystemTime( &fileTime, &sysTime );

    ConvertSystemTimeToTM( sysTime, *pTimeHolder );
    return pTimeHolder;
}

struct tm * localtime(const time_t * timer)
{
    if (!timer || *timer < 0)
        return NULL;

    struct tm * pTimeHolder = GetTimeHolder();
    if (!pTimeHolder)
        return NULL;

    FILETIME fileTime;
    ConvertUnixTimeToFileTime( *timer,  fileTime );

    FILETIME localFileTime;
    FileTimeToLocalFileTime( &fileTime, &localFileTime );

    SYSTEMTIME sysTime;
    FileTimeToSystemTime( &localFileTime, &sysTime );

    ConvertSystemTimeToTM( sysTime, *pTimeHolder );
    return pTimeHolder;
}


#endif  // _STLP_USE_WINCE_CRT_FUNCTIONS

#endif  //  UNDER_CE
