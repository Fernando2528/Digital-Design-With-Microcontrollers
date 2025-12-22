

;============================================================
; CÁLCULO DE CHECKSUM RECIBIDO
;============================================================

CALCULAR_CHECKSUM_RX:
    
    CLRF    CHECKSUM_CALCULADO
    CLRF    INDICE_BUFFER
    
CALC_LOOP:
    
    LFSR    0, BUFFER_RX
    MOVF    INDICE_BUFFER,W
    ADDWF   FSR0L,F
    MOVF    INDF0,W
    ADDWF   CHECKSUM_CALCULADO,F
    
    INCF    INDICE_BUFFER,F
    MOVF    INDICE_BUFFER,W
    SUBLW   .16
    BTFSS   STATUS,Z
    GOTO    CALC_LOOP
    
    RETURN

; ------------------------------------------------------------------------------
    
;============================================================
; CALCULAR CHECKSUM RESPUESTA
;============================================================

CALCULAR_CHECKSUM_RESPUESTA:
    
    CLRF    CHECKSUM_CALCULADO
    CLRF    INDICE_BUFFER
    
CALC_RESP_LOOP:
    
    LFSR    0, BUFFER_TX
    MOVF    INDICE_BUFFER,W
    ADDWF   FSR0L,F
    MOVF    INDF0,W
    ADDWF   CHECKSUM_CALCULADO,F
    
    INCF    INDICE_BUFFER,F
    MOVF    INDICE_BUFFER,W
    SUBLW   .20
    BTFSS   STATUS,Z
    GOTO    CALC_RESP_LOOP
    
    RETURN



