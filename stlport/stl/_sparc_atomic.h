
// Currently, SUN CC requires object file

#if defined (__GNUC__)

/*
**  int _STLP_atomic_exchange (__stl_atomic_t *pvalue, __stl_atomic_t value)
*/
 
# ifdef __WORD64
#  define _STLP_atomic_exchange(__pvalue1, __value2) \
 ({ register __stl_atomic_t *_L_pvalue1 = __pvalue1, _L_value1 =0, _L_value2 =  __value2 ; \
   asm volatile ("0:; ldx [%2], %0 ; casx [%2], %0, %1 ; cmp  %0, %1 ; \
                bne 0b ;  membar  #LoadLoad | #LoadStore " : \
                "=r" (_L_value1), "=r" (_L_value2) : \
                "r" (_L_pvalue1), \
		"r" (_L_pvalue1), "0" (_L_value1),  "1" (_L_value2): \
		"icc", "xcc" ); \
   _L_value1; \
 }

#  define _STLP_atomic_increment(__pvalue) \
 ({ register __stl_atomic_t *_L_pvalue = __pvalue, _L_value, _L_value_plus_one; \
   asm volatile ("0:; ldx [%2], %0 ; addx %0, 0x1, %1 ;  casx [%2], %0, %1 ; cmp  %0, %1 ; \
                bne 0b ;  membar  #LoadLoad | #LoadStore " : \
                "=r" (_L_value), "=r" (_L_value_plus_one) : \
                "r" (_L_pvalue), \
		"r" (_L_pvalue), "0" (_L_value),  "1" (_L_value_plus_one): \
		"icc", "xcc" ); \
   _L_value; \
 })

#  define _STLP_atomic_decrement(__pvalue) \
 { register __stl_atomic_t *_L_pvalue = __pvalue, _L_value, _L_value_plus_one ; \
   asm volatile ("0:; ldx [%2], %0 ; subx %0, 0x1, %1 ;  casx [%2], %0, %1 ; cmp  %0, %1 ; \
                bne 0b ;  membar  #LoadLoad | #LoadStore " : \
                "=r" (_L_value), "=r" (_L_value_plus_one) : \
                "r" (_L_pvalue), \
		"r" (_L_pvalue), "0" (_L_value),  "1" (_L_value_plus_one): \
		"icc", "xcc" );
 }


# else 
#  define _STLP_atomic_exchange(__pvalue1, __value2) \
 ({ register __stl_atomic_t *_L_pvalue1 = __pvalue1, _L_value1 =0, _L_value2 =  __value2 ; \
   asm volatile ("0:; ld [%2], %0 ; swap [%2], %1 ; cmp  %0, %1 ; \
                bne 0b ;  stbar " : \
                "=r" (_L_value1), "=r" (_L_value2) : \
                "r" (_L_pvalue1), \
		"r" (_L_pvalue1), "0" (_L_value1),  "1" (_L_value2): \
		"icc" ); \
   _L_value1; \
 })

#  define _STLP_atomic_increment(__pvalue) \
 { register __stl_atomic_t *_L_pvalue = __pvalue, _L_value, _L_value_plus_one ; \
   asm volatile ("0:; ld [%2], %0 ; add %0, 0x1, %1 ;  swap [%2], %1 ; cmp  %0, %1 ; \
                bne 0b ;  stbar " : \
                "=r" (_L_value), "=r" (_L_value_plus_one) : \
                "r" (_L_pvalue), \
		"r" (_L_pvalue), "0" (_L_value),  "1" (_L_value_plus_one): \
		"icc" ); \
 }

#  define _STLP_atomic_decrement(__pvalue) \
 { register __stl_atomic_t *_L_pvalue = __pvalue, _L_value, _L_value_plus_one ; \
   asm volatile ("0:; ld [%2], %0 ; sub %0, 0x1, %1 ;  swap [%2], %1 ; cmp  %0, %1 ; \
                bne 0b ;  stbar " : \
                "=r" (_L_value), "=r" (_L_value_plus_one) : \
                "r" (_L_pvalue), \
		"r" (_L_pvalue), "0" (_L_value),  "1" (_L_value_plus_one): \
		"icc" ); \
 }
# endif

# elif ! defined (_STLP_NO_EXTERN_INLINE) 

extern "C" __stl_atomic_t _STLP_atomic_exchange(__stl_atomic_t * __x, __stl_atomic_t __v);
extern "C" void _STLP_atomic_decrement(__stl_atomic_t* i);
extern "C" void _STLP_atomic_increment(__stl_atomic_t* i);

#  define _STLP_ATOMIC_INCREMENT(__x)           _STLP_atomic_increment((__stl_atomic_t*)__x)
#  define _STLP_ATOMIC_DECREMENT(__x)           _STLP_atomic_decrement((__stl_atomic_t*)__x)
#  define _STLP_ATOMIC_EXCHANGE(__x, __y)       _STLP_atomic_exchange((__stl_atomic_t*)__x, (__stl_atomic_t)__y)

# endif

