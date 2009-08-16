#ifndef _STLP_INTERNAL_WINCE_STRING_H
#define _STLP_INTERNAL_WINCE_STRING_H

#if defined(_STLP_USE_WINCE_CRT_FUNCTIONS)

#if defined(__cplusplus)
extern "C" {
#endif

/* Include the string transform function that we are supplying for Windows CE */
_STLP_DECLSPEC char * _STLP_CALL strerror(int errnum);
_STLP_DECLSPEC size_t _STLP_CALL strxfrm(char * strDest, char const * strSource, size_t count);

#if defined(__cplusplus)
}
#endif

#endif  /* _STLP_USE_WINCE_CRT_FUNCTIONS */

#endif  /* _STLP_INTERNAL_WINCE_STRING_H */
