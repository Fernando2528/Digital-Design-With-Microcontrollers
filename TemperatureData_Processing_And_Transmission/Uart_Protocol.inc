
;============================================================
; PROCESAMIENTO DE PAQUETE RECIBIDO
;============================================================

PROCESAR_PAQUETE_UART:
    
    BCF     INTCON,GIE          ; Deshabilitar interrupciones

    LFSR    0, BUFFER_RX
    MOVLW   .16
    ADDWF   FSR0L,F
    MOVF    INDF0,W
    CALL    HEX_ASCII_A_NIBBLE
    SWAPF   WREG,W
    MOVWF   CHECKSUM_RECIBIDO
    
    INCF    FSR0L,F
    MOVF    INDF0,W
    CALL    HEX_ASCII_A_NIBBLE
    IORWF   CHECKSUM_RECIBIDO,F
    
    CALL    CALCULAR_CHECKSUM_RX
    
    MOVF    CHECKSUM_CALCULADO,W
    SUBWF   CHECKSUM_RECIBIDO,W
    BTFSC   STATUS,Z
    GOTO    CHECKSUM_VALIDO

  
    CALL    LEER_TEMPERATURA
    CALL    ENVIAR_RESPUESTA_ERROR
    BSF     LATD,7          
    GOTO    FIN_PROCESAR_PAQUETE
    
CHECKSUM_VALIDO:
 
    CALL    LEER_TEMPERATURA
    CALL    ENVIAR_RESPUESTA_EXITOSA
    BCF     LATD,7          
    
FIN_PROCESAR_PAQUETE:
    
    CLRF    CONTADOR_RX
    BCF     FLAG_PAQUETE_COMPLETO,0
    
    BSF     INTCON,GIE          ; Rehabilitar interrupciones
    RETURN

; ------------------------------------------------------------------------------
    
;============================================================
; RESPUESTA EXITOSA
;============================================================

ENVIAR_RESPUESTA_EXITOSA:
    
    CLRF    INDICE_BUFFER
    
COPIAR_MENSAJE:
    
    LFSR    0, BUFFER_RX
    LFSR    1, BUFFER_TX
    MOVF    INDICE_BUFFER,W
    ADDWF   FSR0L,F
    ADDWF   FSR1L,F
    MOVF    INDF0,W
    MOVWF   INDF1
    
    INCF    INDICE_BUFFER,F
    MOVF    INDICE_BUFFER,W
    SUBLW   .16
    BTFSS   STATUS,Z
    GOTO    COPIAR_MENSAJE
    
     LFSR    1, BUFFER_TX
    MOVLW   .16
    ADDWF   FSR1L,F
    MOVLW   'k'
    MOVWF   INDF1

    
    CALL    AGREGAR_TEMP_A_RESPUESTA
    
    CALL    CALCULAR_CHECKSUM_RESPUESTA
    
    LFSR    1, BUFFER_TX
    MOVLW   .20
    ADDWF   FSR1L,F
    
    SWAPF   CHECKSUM_CALCULADO,W
    ANDLW   0x0F
    CALL    NIBBLE_A_HEX_ASCII
    MOVWF   INDF1
    INCF    FSR1L,F
    
    MOVF    CHECKSUM_CALCULADO,W
    ANDLW   0x0F
    CALL    NIBBLE_A_HEX_ASCII
    MOVWF   INDF1
    
    CALL    TRANSMITIR_BUFFER_TX
    
    MOVLW   0x0D
    CALL    TX_DATO
    MOVLW   0x0A
    CALL    TX_DATO
    
    RETURN

;============================================================
; RESPUESTA DE ERROR
;============================================================

ENVIAR_RESPUESTA_ERROR:
    
    MOVLW   'E'
    CALL    TX_DATO
    
    MOVF    TEMPERATURA_GRADOS,W
    CALL    CONVERTIR_TEMP_ASCII_TX
    
    MOVLW   0x0D
    CALL    TX_DATO
    MOVLW   0x0A
    CALL    TX_DATO
    
    RETURN

;============================================================
; AGREGAR TEMPERATURA A RESPUESTA
;============================================================

AGREGAR_TEMP_A_RESPUESTA:
    
    MOVF    TEMPERATURA_GRADOS,W
    MOVWF   W_TEMP
    
    CLRF    TEMP_CENTENAS
    CLRF    TEMP_DECENAS
    CLRF    TEMP_UNIDADES
    
LOOP_CENTENAS:
    
    MOVLW   .100
    SUBWF   W_TEMP,W
    BTFSS   STATUS,C
    GOTO    FIN_CENTENAS
    MOVWF   W_TEMP
    INCF    TEMP_CENTENAS,F
    GOTO    LOOP_CENTENAS
    
FIN_CENTENAS:
    
    MOVF    W_TEMP,W
    
LOOP_DECENAS:
    
    MOVLW   .10
    SUBWF   W_TEMP,W
    BTFSS   STATUS,C
    GOTO    FIN_DECENAS
    MOVWF   W_TEMP
    INCF    TEMP_DECENAS,F
    GOTO    LOOP_DECENAS
    
FIN_DECENAS:
    
    MOVF    W_TEMP,W
    MOVWF   TEMP_UNIDADES
    
    LFSR    1, BUFFER_TX
    MOVLW   .17
    ADDWF   FSR1L,F
    
    MOVF    TEMP_CENTENAS,W
    ADDLW   0x30
    MOVWF   INDF1
    INCF    FSR1L,F
    
    MOVF    TEMP_DECENAS,W
    ADDLW   0x30
    MOVWF   INDF1
    INCF    FSR1L,F
    
    MOVF    TEMP_UNIDADES,W
    ADDLW   0x30
    MOVWF   INDF1
    
    RETURN


; -----------------------------------------------------------------------------
    
;============================================================
; TRANSMISIÓN UART
;============================================================

TX_DATO:
    
    BTFSS   PIR1,TXIF
    GOTO    TX_DATO
    MOVWF   TXREG
    RETURN

;============================================================
; MENSAJE DE INICIO
;============================================================    

ENVIAR_MENSAJE_INICIO:
    
    MOVLW   'P'
    CALL    TX_DATO
    MOVLW   'I'
    CALL    TX_DATO
    MOVLW   'C'
    CALL    TX_DATO
    MOVLW   ' '
    CALL    TX_DATO
    MOVLW   'L'
    CALL    TX_DATO
    MOVLW   'I'
    CALL    TX_DATO
    MOVLW   'S'
    CALL    TX_DATO
    MOVLW   'T'
    CALL    TX_DATO
    MOVLW   'O'
    CALL    TX_DATO
    MOVLW   0x0D
    CALL    TX_DATO
    MOVLW   0x0A
    CALL    TX_DATO
    RETURN