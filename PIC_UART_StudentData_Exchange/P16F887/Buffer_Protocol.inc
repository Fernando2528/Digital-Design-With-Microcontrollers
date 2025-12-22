;===============================================================================
; FUNCIONES DE BUFFER
;===============================================================================

Recibir_Datos:
    banksel PORTD
    clrf    buffer_count
    movlw   buffer_rx
    movwf   FSR                     ; FSR apunta al inicio del buffer
    
    bsf     LED_RX                  ; LED encendido = recibiendo
    
Recibir_Loop:
    ; Timeout simple
    movlw   .50
    movwf   timeout_h
Timeout_Loop:
    call    UART_Available
    banksel PORTD
    xorlw   0x01
    btfsc   STATUS,Z
    goto    Recibir_Byte
    
    call    Delay_1ms
    decfsz  timeout_h,F
    goto    Timeout_Loop
    goto    Recibir_Done

Recibir_Byte:
    call    UART_RX
    banksel PORTD
    
    ; Guardar en buffer
    movf    uart_dato_rx,W
    movwf   INDF
    incf    FSR,F
    incf    buffer_count,F
    
    ; Verificar si es fin de línea
    movf    uart_dato_rx,W
    sublw   0x0A                    ; LF
    btfsc   STATUS,Z
    goto    Recibir_Done
    
    ; Verificar overflow
    movf    buffer_count,W
    sublw   BUFFER_SIZE-1
    btfsc   STATUS,Z
    goto    Recibir_Done
    
    goto    Recibir_Loop

Recibir_Done:
    bcf     LED_RX
    bsf     FLAG_RX_COMPLETE
    return

;--- Analizar qué se recibió ---
Analizar_Buffer:
    ; Por defecto enviar Fernando primero (comando R)
    bsf     FLAG_SEND_FERNANDO
    
    ; Si el buffer tiene pocos bytes, es comando W
    movf    buffer_count,W
    sublw   .5
    btfss   STATUS,C
    return                          ; Es largo = comando R
    
    ; Es corto = comando W (solo eco)
    bcf     FLAG_SEND_FERNANDO
    return

;--- Enviar respuesta completa ---
Enviar_Respuesta:
    banksel PORTD
    
    ; Si es comando R, enviar Fernando primero
    btfsc   FLAG_SEND_FERNANDO
    call    Send_String_Fernando
    
    btfsc   FLAG_SEND_FERNANDO
    goto    Send_CRLF_Mid
    
    goto    Send_Echo

Send_CRLF_Mid:
    movlw   0x0D
    call    UART_TX
    movlw   0x0A
    call    UART_TX

Send_Echo:
    ; Enviar eco del buffer
    movlw   buffer_rx
    movwf   FSR
    clrf    buffer_index

Echo_Loop:
    movf    buffer_index,W
    subwf   buffer_count,W
    btfsc   STATUS,Z
    return
    
    movf    INDF,W
    call    UART_TX
    
    incf    FSR,F
    incf    buffer_index,F
    goto    Echo_Loop