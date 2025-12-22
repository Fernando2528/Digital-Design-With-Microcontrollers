;===============================================================================
; FUNCIONES UART
;===============================================================================

UART_Init:
    banksel TXSTA
    movlw   b'00100100'             ; BRGH=1, TXEN=1
    movwf   TXSTA
    movlw   SPBRG_VAL
    movwf   SPBRG
    
    banksel RCSTA
    movlw   b'10010000'             ; SPEN=1, CREN=1
    movwf   RCSTA
    
    banksel PIR1
    bcf     PIR1,RCIF
    return

UART_TX:
    movwf   uart_dato_tx
    banksel TXSTA
UART_TX_Wait:
    btfss   TXSTA,TRMT
    goto    UART_TX_Wait
    
    banksel TXREG
    movf    uart_dato_tx,W
    movwf   TXREG
    return

UART_RX:
    banksel PIR1
UART_RX_Wait:
    btfss   PIR1,RCIF
    goto    UART_RX_Wait
    
    banksel RCSTA
    btfsc   RCSTA,OERR
    call    UART_Clear_Err
    
    banksel RCREG
    movf    RCREG,W
    banksel PORTB
    movwf   uart_dato_rx
    return

UART_Clear_Err:
    banksel RCSTA
    bcf     RCSTA,CREN
    bsf     RCSTA,CREN
    return

;--- Enviar string Juan David ---
Send_String_Juan:
    clrf    str_index
SSJ_Loop:
    movf    str_index,W
    call    Tabla_Juan
    movwf   char_temp
    
    movf    char_temp,F
    btfsc   STATUS,Z
    return
    
    movf    char_temp,W
    call    UART_TX
    
    incf    str_index,F
    goto    SSJ_Loop
