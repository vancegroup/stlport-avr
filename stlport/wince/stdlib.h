#ifndef _STLP_INTERNAL_WINCE_STDLIB_H
#define _STLP_INTERNAL_WINCE_STDLIB_H

#if defined(_STLP_USE_WINCE_CRT_FUNCTIONS)

#if defined(__cplusplus)
extern "C" {
#endif

/* Multi-byte definitions that we are adding for Windows CE */
_STLP_DECLSPEC int _STLP_CALL wctomb(char * mbchar, wchar_t wchar);
_STLP_DECLSPEC int _STLP_CALL mbtowc(wchar_t * wchar, char const * mbchar, size_t count);
_STLP_DECLSPEC int _STLP_CALL mblen(char const * mbstr, size_t count);

/* Environment definitions that we are adding for Windows CE */
_STLP_DECLSPEC extern char * environ[];
_STLP_DECLSPEC char * _STLP_CALL getenv(char const * name);

#if defined(__cplusplus)
}
#endif

#endif  /* _STLP_USE_WINCE_CRT_FUNCTIONS */

#endif  /* _STLP_INTERNAL_WINCE_STDLIB_H */
