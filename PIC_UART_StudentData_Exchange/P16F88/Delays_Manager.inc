;===============================================================================
; DELAYS
;===============================================================================

Delay_50ms:
    banksel PORTB
    movlw   .50
    movwf   delay_1
Del_50_L1:
    movlw   .200
    movwf   delay_2
Del_50_L2:
    nop
    nop
    decfsz  delay_2,F
    goto    Del_50_L2
    decfsz  delay_1,F
    goto    Del_50_L1
    return

Delay_500ms:
    call    Delay_50ms
    call    Delay_50ms
    call    Delay_50ms
    call    Delay_50ms
    call    Delay_50ms
    call    Delay_50ms
    call    Delay_50ms
    call    Delay_50ms
    call    Delay_50ms
    call    Delay_50ms
    return

;===============================================================================