# define _STLP_NO_EXTERN_INLINE

# include <stl/_sparc_atomic.h>

# ifdef __GNUC__
#  define _STLP_ASM_VOLATILE asm volatile
# else
#  define _STLP_ASM_VOLATILE asm
# endif

/*
**  int _STLP_atomic_exchange (void *pvalue, int value)
*/
extern "C"
__stl_atomic_t _STLP_atomic_exchange (__stl_atomic_t *pvalue, __stl_atomic_t value)
{
  _STLP_ASM_VOLATILE  ("        ld      [%o0], %o2   ");            // Set the current value
  _STLP_ASM_VOLATILE  ("        mov     %o1, %o3  ");                                // Set the new value
  _STLP_ASM_VOLATILE  ("        cas     [%o0], %o2, %o3     ");     // Do the compare and swap
  _STLP_ASM_VOLATILE  ("        cmp     %o2, %o3           ");      // Check whether successful
  _STLP_ASM_VOLATILE  ("        bne             _STLP_atomic_exchange   ");                // Retry upon failure
  _STLP_ASM_VOLATILE  ("        membar  #LoadLoad | #LoadStore   "); // Ensure the cas finishes before
  _STLP_ASM_VOLATILE  ("        retl                         ");    // return
  _STLP_ASM_VOLATILE  ("        mov     %o3, %o0     ");           // Set the new value
# ifndef __GNUC__
  return (__stl_atomic_t)(long)pvalue;
# endif
}

extern "C"
void _STLP_atomic_increment (__stl_atomic_t *pvalue)
{
  _STLP_ASM_VOLATILE  ("        ld      [%o0], %o2   ");            // set the current
  _STLP_ASM_VOLATILE  ("        add      %o2, 0x1, %o3 ");            // Increment and store current
  _STLP_ASM_VOLATILE  ("        cas     [%o0], %o2, %o3    ");      // Do the compare and swap
  _STLP_ASM_VOLATILE  ("        cmp     %o3, %o2            ");     // Check whether successful
  _STLP_ASM_VOLATILE  ("        bne     _STLP_atomic_increment "); // Retry
  _STLP_ASM_VOLATILE  ("        membar  #LoadLoad | #LoadStore   "); // Ensure the cas finishes before
  _STLP_ASM_VOLATILE  ("                                     ");    // returning
  _STLP_ASM_VOLATILE  ("        retl                          ");   // return
  _STLP_ASM_VOLATILE  ("        mov    %o1, %o0  ");                       // Set the return value, unused
}

extern "C"
void 
_STLP_atomic_decrement (__stl_atomic_t *pvalue)
{
  _STLP_ASM_VOLATILE  ("        ld      [%o0], %o2      ");          // set the current
  _STLP_ASM_VOLATILE  ("        sub             %o2, 0x1, %o3    "); // decrement and store current
  _STLP_ASM_VOLATILE  ("        cas     [%o0], %o2, %o3     ");      // Do the compare and swap
  _STLP_ASM_VOLATILE  ("        cmp     %o3, %o2       ");           // Check whether successful
  _STLP_ASM_VOLATILE  ("        bne     _STLP_atomic_decrement   ");                                        // Retry if we failed.
  _STLP_ASM_VOLATILE  ("        membar  #LoadLoad | #LoadStore   "); // Ensure the cas finishes before
  _STLP_ASM_VOLATILE  ("        retl                           ");   // return
  _STLP_ASM_VOLATILE  ("        mov    %o1, %o0                 ");  // Set the return value, unused
}

// # endif /* __GNUC__ */
