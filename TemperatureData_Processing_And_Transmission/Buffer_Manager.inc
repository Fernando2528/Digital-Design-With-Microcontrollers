
    
;============================================================
; TRANSMITIR BUFFER RESPUESTA
;============================================================

TRANSMITIR_BUFFER_TX:
    
    CLRF    INDICE_BUFFER
    
TRANS_LOOP:
    
    LFSR    1, BUFFER_TX
    MOVF    INDICE_BUFFER,W
    ADDWF   FSR1L,F
    MOVF    INDF1,W
    CALL    TX_DATO
    
    INCF    INDICE_BUFFER,F
    MOVF    INDICE_BUFFER,W
    SUBLW   .22
    BTFSS   STATUS,Z
    GOTO    TRANS_LOOP
    
    RETURN


