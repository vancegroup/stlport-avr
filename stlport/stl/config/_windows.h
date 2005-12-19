#ifndef __stl_config__windows_h
#define __stl_config__windows_h

#if !defined (_STLP_BIG_ENDIAN) && !defined (_STLP_LITTLE_ENDIAN)
#  if defined (_MIPSEB)
#    define _STLP_BIG_ENDIAN 1
#  endif
#  if defined (__i386) || defined (_M_IX86) || defined (_M_ARM) || \
      defined (__amd64__) || defined (_M_AMD64) || defined (__x86_64__) || \
      defined (__alpha__)
#    define _STLP_LITTLE_ENDIAN 1
#  endif
#  if defined (__ia64__)
    /* itanium allows both settings (for instance via gcc -mbig-endian) - hence a seperate check is required */
#    if defined (__BIG_ENDIAN__)
#      define _STLP_BIG_ENDIAN 1
#    else
#      define _STLP_LITTLE_ENDIAN 1
#    endif
#  endif
#endif /* _STLP_BIG_ENDIAN */

#endif /* __stl_config__windows_h */
