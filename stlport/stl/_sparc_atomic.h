
// Currently, SUN CC requires object file

#if defined (__GNUC__) && defined ( _STLP_NO_SGI_IOSTREAMS ) 

# define _STLP_atomic_exchange _STLP_atomic_global<false>::_STLP_exchange
# define _STLP_atomic_increment _STLP_atomic_global<false>::_STLP_increment
# define _STLP_atomic_decrement _STLP_atomic_global<false>::_STLP_decrement

template <bool __dummy>
struct _STLP_atomic_global {
  static void _STLP_increment(__stl_atomic_t *pvalue);
  static void _STLP_decrement(__stl_atomic_t *pvalue);
  static __stl_atomic_t _STLP_exchange(__stl_atomic_t *pvalue1, __stl_atomic_t value2);
};

#ifdef __GNUC__
# define volatile
#endif

#endif


#if defined (__GNUC__) && (defined (_STLP_NO_SGI_IOSTREAMS) || defined (_STLP_NO_EXTERN_INLINE))

/*
**  int _STLP_atomic_exchange (void *pvalue, int value)
*/

#ifdef _STLP_NO_SGI_IOSTREAMS
template <bool __dummy>
__stl_atomic_t _STLP_atomic_global<__dummy>::_STLP_exchange (__stl_atomic_t *pvalue1, __stl_atomic_t value2)
#else
extern "C"
# ifndef _STLP_NO_EXTERN_INLINE
inline 
# endif
__stl_atomic_t _STLP_atomic_exchange (__stl_atomic_t *pvalue1, __stl_atomic_t value2)
#endif 
{
# ifdef __GNUC__
  register int value1;
  register int tmp;
  asm volatile ("_STLP_atomic_exchange_begin:");
  asm volatile ("        ld      [%1], %0   " : "=r" (value1) : "r" (pvalue1));            // Set the current value
  asm volatile ("        mov     %1, %0  " : "=r" (tmp) : "r" (value2) );                                // Set the new value
  asm volatile ("        cas     [%1], %2, %0     " : "=r" (tmp) : "r" (pvalue1), "r" (value1), "0" (tmp) );     // Do the compare and swap
  asm volatile ("        cmp     %0, %1           " : :  "r" (tmp), "r" (value1) : "icc" );      // Check whether successful
  asm volatile ("        bne             _STLP_atomic_exchange_begin");                // Retry upon failure
  asm volatile ("        membar  #LoadLoad | #LoadStore   "); // Ensure the cas finishes before  
  
  return tmp;
# endif
}

#ifdef _STLP_NO_SGI_IOSTREAMS
template <bool __dummy>
void _STLP_atomic_global<__dummy>::_STLP_increment (__stl_atomic_t *pvalue)
#else
extern "C"
# ifndef _STLP_NO_EXTERN_INLINE
inline 
# endif
void _STLP_atomic_increment (__stl_atomic_t *pvalue)
#endif 
{
# ifdef __GNUC__
  register int value;
  register int value_plus_one;

  asm volatile ("_STLP_atomic_increment_begin:");
  asm volatile ("        ld      [%1], %0   " : "=r" (value) : "r" (pvalue));            // Set the current value
  asm volatile ("        add      %1, 0x1, %0 " : "=r" (value_plus_one) : "r" (value) );  // Increment and store current
  asm volatile ("        cas     [%1], %2, %0    " : "=r" (value_plus_one) : "r" (pvalue), "r" (value), "0" (value_plus_one));      // Do the compare and swap
  asm volatile ("        cmp     %0, %1           " : :  "r" (value), "r" (value_plus_one) : "icc" );      // Check whether successful
  asm volatile ("        bne     _STLP_atomic_increment_begin "); // Retry
  asm volatile ("        membar  #LoadLoad | #LoadStore   "); // Ensure the cas finishes before
# endif
}

#ifdef _STLP_NO_SGI_IOSTREAMS
template <bool __dummy>
void _STLP_atomic_global<__dummy>::_STLP_decrement (__stl_atomic_t *pvalue)
#else
extern "C"
# ifndef _STLP_NO_EXTERN_INLINE
inline 
# endif
void _STLP_atomic_decrement (__stl_atomic_t *pvalue)
#endif 
{
# ifdef __GNUC__
  register int value;
  register int value_minus_one;

  asm volatile ("_STLP_atomic_decrement_begin:");
  asm volatile ("        ld      [%1], %0   " : "=r" (value) : "r" (pvalue));            // Set the current value
  asm volatile ("        sub      %1, 0x1, %0 " : "=r" (value_minus_one) : "r" (value) );  // Decrement and store current
  asm volatile ("        cas     [%1], %2, %0    " : "=r" (value_minus_one)  : "r" (pvalue), "r" (value), "0" (value_minus_one)  );  // Do the compare and swap
  asm volatile ("        cmp     %0, %1           " : :  "r" (value), "r" (value_minus_one) : "icc" );      // Check whether successfu

  asm volatile ("        bne     _STLP_atomic_decrement_begin "); // Retry
  asm volatile ("        membar  #LoadLoad | #LoadStore   "); // Ensure the cas finishes before
# endif
}

#if defined (_STLP_NO_SGI_IOSTREAMS) && defined (__GNUC__)
# undef volatile
#endif

# elif ! defined (_STLP_NO_EXTERN_INLINE) 

extern "C" __stl_atomic_t _STLP_atomic_exchange(__stl_atomic_t * __x, __stl_atomic_t __v);
extern "C" void _STLP_atomic_decrement(__stl_atomic_t* i);
extern "C" void _STLP_atomic_increment(__stl_atomic_t* i);

# endif

