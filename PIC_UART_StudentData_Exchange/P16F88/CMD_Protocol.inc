;===============================================================================
; PROCESAMIENTO DE COMANDOS
;===============================================================================

Procesar_Comando:
    call    UART_RX
    banksel PORTB
    movf    uart_dato_rx,W
    movwf   comando
    
    ; Parpadeo LED al recibir comando
    bcf     LED_BOOT
    call    Delay_50ms
    bsf     LED_BOOT
    
    ; Verificar comando W
    movf    comando,W
    sublw   CMD_WRITE
    btfsc   STATUS,Z
    goto    Cmd_Write
    
    ; Verificar comando R
    movf    comando,W
    sublw   CMD_READ
    btfsc   STATUS,Z
    goto    Cmd_Read
    
    return

Cmd_Write:
    ; Enviar string Juan al PIC887
    call    Send_String_Juan
    
    ; Enviar CR+LF
    movlw   0x0D
    call    UART_TX
    movlw   0x0A
    call    UART_TX
    return

Cmd_Read:
    ; Enviar string Juan al PIC887
    call    Send_String_Juan
    
    ; Enviar CR+LF
    movlw   0x0D
    call    UART_TX
    movlw   0x0A
    call    UART_TX
    return