        .section        ".text",#alloc,#execinstr
        .align 8
        .skip 16

!  int _STLP_atomic_exchange (void *pvalue, int value)
!

        .type   _STLP_atomic_exchange,#function
        .global _STLP_atomic_exchange
        .align  8

_STLP_atomic_exchange:
1:	
	ldx      [%o0], %o2              ! Set the current value
        movx     %o1, %o3                ! Set the new value
        casx     [%o0], %o2, %o3         ! Do the compare and swap
        cmp     %o2, %o3                ! Check whether successful
        bne     0x1b                  ! Retry upon failure
        membar  #LoadLoad | #LoadStore  ! Ensure the cas finishes before
                                        ! returning
        retl                            ! return
        movx     %o2, %o0                                ! Set the new value
        .size   _STLP_atomic_exchange,(.-_STLP_atomic_exchange)

	
! int _STLP_atomic_increment (void *pvalue)

        .type   _STLP_atomic_increment,#function
        .global _STLP_atomic_increment
        .align  8
_STLP_atomic_increment:
        ldx      [%o0], %o2              ! set the current
                add             %o2, 0x1, %o3                   ! Increment and store current
        casx     [%o0], %o2, %o3         ! Do the compare and swap
        cmp     %o3, %o2                ! Check whether successful
                bne     _STLP_atomic_increment                                         ! Retry if we failed.
        membar  #LoadLoad | #LoadStore  ! Ensure the cas finishes before
                                        ! returning
        retl                            ! return
        movx    %o1, %o0                                 ! Set the return value

        .size   _STLP_atomic_increment,(.-_STLP_atomic_increment)

	
!        /* int _STLP_atomic_decrement (void *pvalue) */
        .type   _STLP_atomic_decrement,#function
        .global _STLP_atomic_decrement
        .align  8

_STLP_atomic_decrement:
        ldx      [%o0], %o2              ! set the current
                sub             %o2, 0x1, %o3                   ! decrement and store current
        casx     [%o0], %o2, %o3         ! Do the compare and swap

        cmp     %o3, %o2                ! Check whether successful
        bne     _STLP_atomic_decrement                                         ! Retry if we failed.
        membar  #LoadLoad | #LoadStore  ! Ensure the cas finishes before
                                        ! returning
        retl                            ! return
	nop
        .size   _STLP_atomic_decrement,(.-_STLP_atomic_decrement)

	

