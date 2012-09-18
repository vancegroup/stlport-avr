#ifndef _STLP_INTERNAL_WINCE_TIME_H
#define _STLP_INTERNAL_WINCE_TIME_H

#if defined(_STLP_USE_WINCE_CRT_FUNCTIONS)

#ifdef __cplusplus
extern "C" {
#endif


#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif

#ifndef _TIME_T_DEFINED
typedef long time_t;
#define _TIME_T_DEFINED
#endif

#ifndef _CLOCK_T_DEFINED
typedef long clock_t;
#define _CLOCK_T_DEFINED
#endif

#ifndef _SIZE_T_DEFINED
typedef unsigned int size_t;
#define _SIZE_T_DEFINED
#endif


/* Define NULL pointer value */

#ifndef NULL
#ifdef __cplusplus
#define NULL	0
#else
#define NULL	((void *)0)
#endif
#endif


#ifndef _TM_DEFINED
struct tm 
{
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
};
#define _TM_DEFINED
#endif


#define CLOCKS_PER_SEC	1000


/* Function prototypes */
_STLP_DECLSPEC char * _STLP_CALL asctime(const struct tm *);
_STLP_DECLSPEC char * _STLP_CALL ctime(const time_t *);
_STLP_DECLSPEC clock_t _STLP_CALL clock(void);

_STLP_DECLSPEC struct tm * _STLP_CALL gmtime(const time_t *);
_STLP_DECLSPEC struct tm * _STLP_CALL localtime(const time_t *);
_STLP_DECLSPEC time_t _STLP_CALL mktime(struct tm *);
_STLP_DECLSPEC size_t _STLP_CALL strftime(char *, size_t, const char *, const struct tm *);
_STLP_DECLSPEC char * _STLP_CALL _strdate(char *);
_STLP_DECLSPEC char * _STLP_CALL _strtime(char *);
_STLP_DECLSPEC time_t _STLP_CALL time(time_t *);


#ifndef _SIZE_T_DEFINED
typedef unsigned int size_t;
#define _SIZE_T_DEFINED
#endif

#if	!__STDC__ || defined(_POSIX_)

/* Non-ANSI names for compatibility */
#define CLK_TCK  CLOCKS_PER_SEC

#endif	/* __STDC__ */


#ifdef __cplusplus
}
#endif

#endif  /* _STLP_USE_WINCE_CRT_FUNCTIONS */

#endif /* _STLP_INTERNAL_WINCE_TIME_H */
