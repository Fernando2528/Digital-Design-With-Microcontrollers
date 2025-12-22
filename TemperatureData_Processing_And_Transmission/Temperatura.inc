;============================================================
; LEER TEMPERATURA
;============================================================

LEER_TEMPERATURA:
    
    BSF     ADCON0,GO
    
    MOVLW   .255
    MOVWF   TIMEOUT_CONTADOR
    
ESPERAR_ADC:
    
    BTFSS   ADCON0,GO
    GOTO    CONVERSION_OK
    
    DECFSZ  TIMEOUT_CONTADOR,F
    GOTO    ESPERAR_ADC
    
    RETLW   0xFF
    
CONVERSION_OK:
    
    MOVF    ADRESH,W
    MOVWF   ADC_ALTO
    
    MOVF    ADRESL,W
    MOVWF   ADC_BAJO
    
    MOVF    ADC_ALTO,W
    MULLW   .255
    MOVF    PRODH,W
    MOVWF   TEMPERATURA_GRADOS
    
    MOVF    ADC_BAJO,W
    MULLW   .255
    MOVF    PRODH,W
    ADDWF   TEMPERATURA_GRADOS,F
    
    MOVF    TEMPERATURA_GRADOS,W
    MULLW   .128
    MOVF    PRODH,W
    MOVWF   TEMPERATURA_GRADOS
    
    RETLW   0x00


