/*
**  int _STLP_atomic_exchange (void *pvalue, int value)
*/
	asm("        .type   _STLP_atomic_exchange,#function ");
	asm("        .global _STLP_atomic_exchange ");
	asm("        .align  8 ");
	asm("_STLP_atomic_exchange: ");
	asm("        ld      [%o0], %o2   ");            // Set the current value
	asm("                mov     %o1, %o3  ");                                // Set the new value
	asm("        cas     [%o0], %o2, %o3     ");     // Do the compare and swap
	asm("        cmp     %o2, %o3           ");      // Check whether successful
	asm("                bne             _STLP_atomic_exchange   ");                // Retry upon failure
	asm("        membar  #LoadLoad | #LoadStore   "); // Ensure the cas finishes before
	asm("        retl                         ");    // return
	asm("                mov     %o3, %o0     ");                            // Set the new value
	asm("        .size   _STLP_atomic_exchange,(.-_STLP_atomic_exchange)
	asm("                                      ");

/* int _STLP_atomic_increment (void *pvalue) */
	asm("        .type   _STLP_atomic_increment,#function  ");
	asm("        .global _STLP_atomic_increment ");
	asm("        .align  8 ");
	asm("_STLP_atomic_increment: ");
	asm("        ld      [%o0], %o2   ");            // set the current
	asm("                add          ");    %o2, 0x1, %o3                   // Increment and store current
	asm("        cas     [%o0], %o2, %o3    ");      // Do the compare and swap
	asm("        cmp     %o3, %o2            ");     // Check whether successful
	asm("                bne     _STLP_atomic_increment "); Retry
	asm("        membar  #LoadLoad | #LoadStore   "); // Ensure the cas finishes before
	asm("                                     ");    // returning
	asm("        retl                          ");   // return
	asm("                mov    %o1, %o0           ");                       // Set the return value
	asm("        .size   _STLP_atomic_increment,(.-_STLP_atomic_increment)  ");

/* int _STLP_atomic_decrement (void *pvalue) */
	asm("        .type   _STLP_atomic_decrement,#function  ");
	asm("        .global _STLP_atomic_decrement  ");
	asm("        .align  8  ");
	asm("_STLP_atomic_decrement:  ");
	asm("        ld      [%o0], %o2      ");         // set the current
	asm("                sub             %o2, 0x1, %o3    ");                // decrement and store current
	asm("        cas     [%o0], %o2, %o3     ");     // Do the compare and swap
	asm("        cmp     %o3, %o2       ");          // Check whether successful
	asm("                bne     _STLP_atomic_decrement   ");                                        // Retry if we failed.
	asm("        membar  #LoadLoad | #LoadStore   "); // Ensure the cas finishes before
	asm("                                      ");   // returning
	asm("        retl                           ");  // return
	asm("        mov    %o1, %o0                 ");                 // Set the return value
	asm("                                       ");  // returning
	asm("        retl                            "); // return
	asm("        mov    %o1, %o0                  ");                // Set the return value
	asm("        .size   _STLP_atomic_decrement,(.-_STLP_atomic_decrement) ");
