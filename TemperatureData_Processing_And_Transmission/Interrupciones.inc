
    
;============================================================
; RUTINA DE INTERRUPCIÓN UART RX
;============================================================

ALTA_PRIORIDAD:
    
    MOVWF   W_TEMP
    MOVFF   STATUS, STATUS_TEMP
    MOVFF   BSR, BSR_TEMP
    
    BTFSS   PIR1,RCIF
    GOTO    FIN_INT_ALTA
    
    BTFSC   RCSTA,OERR
    CALL    LIMPIAR_OVERRUN
    
    BTFSC   RCSTA,FERR
    GOTO    ERROR_FRAME
    
    MOVF    RCREG,W
    
    BTFSC   FLAG_PAQUETE_COMPLETO,0
    GOTO    FIN_INT_ALTA
    
    MOVF    CONTADOR_RX,W
    SUBLW   .17
    BTFSS   STATUS,C
    GOTO    REINICIAR_RX
    
    LFSR    0, BUFFER_RX
    MOVF    CONTADOR_RX,W
    ADDWF   FSR0L,F
    MOVF    RCREG,W
    MOVWF   INDF0
    
    INCF    CONTADOR_RX,F
    
    MOVF    CONTADOR_RX,W
    SUBLW   .18
    BTFSC   STATUS,Z
    BSF     FLAG_PAQUETE_COMPLETO,0
    
    GOTO    FIN_INT_ALTA

ERROR_FRAME:
    
    MOVF    RCREG,W
    
REINICIAR_RX:
    
    CLRF    CONTADOR_RX
    BCF     FLAG_PAQUETE_COMPLETO,0
    
FIN_INT_ALTA:
    
    MOVFF   BSR_TEMP, BSR
    MOVFF   STATUS_TEMP, STATUS
    MOVF    W_TEMP,W
    RETFIE  FAST

LIMPIAR_OVERRUN:
    
    BCF     RCSTA,CREN
    NOP
    NOP
    BSF     RCSTA,CREN
    RETURN

BAJA_PRIORIDAD:
    
    MOVWF   W_TEMP
    MOVFF   STATUS, STATUS_TEMP
    MOVFF   BSR, BSR_TEMP
    
    MOVFF   BSR_TEMP, BSR
    MOVFF   STATUS_TEMP, STATUS
    MOVF    W_TEMP, W
    RETFIE


