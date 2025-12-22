;===============================================================================
; DELAYS
;===============================================================================

Delay_1ms:
    banksel PORTD
    movlw   .2
    movwf   delay_1
Del_1ms_L1:
    movlw   .200
    movwf   delay_2
Del_1ms_L2:
    nop
    decfsz  delay_2,F
    goto    Del_1ms_L2
    decfsz  delay_1,F
    goto    Del_1ms_L1
    return

Delay_50ms:
    movlw   .50
    movwf   delay_1
Del_50_Loop:
    call    Delay_1ms
    decfsz  delay_1,F
    goto    Del_50_Loop
    return

Delay_200ms:
    call    Delay_50ms
    call    Delay_50ms
    call    Delay_50ms
    call    Delay_50ms
    return

;===============================================================================


