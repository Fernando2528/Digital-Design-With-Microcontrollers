
    
;============================================================
; CONVERSIÓN HEX ASCII A NIBBLE (CORREGIDA)
;============================================================

HEX_ASCII_A_NIBBLE:
    
    MOVWF   W_TEMP
    
    ADDLW   -'0'
    MOVWF   TEMP_RESULTADO
    
    ADDLW   -.10
    BTFSS   STATUS,C
    GOTO    ES_DIGITO_VALIDO
    
    MOVF    W_TEMP,W
    ADDLW   -'A'
    MOVWF   TEMP_RESULTADO
    
    ADDLW   -.6
    BTFSS   STATUS,C
    GOTO    ES_LETRA_MAYUSCULA
    
    MOVF    W_TEMP,W
    ADDLW   -'a'
    MOVWF   TEMP_RESULTADO
    
    ADDLW   -.6
    BTFSS   STATUS,C
    GOTO    ES_LETRA_MINUSCULA
    
    RETLW   0x00
    
ES_DIGITO_VALIDO:
    
    MOVF    TEMP_RESULTADO,W
    RETURN
    
ES_LETRA_MAYUSCULA:
    
    MOVF    TEMP_RESULTADO,W
    ADDLW   .10
    RETURN
    
ES_LETRA_MINUSCULA:
    
    MOVF    TEMP_RESULTADO,W
    ADDLW   .10
    RETURN
    
    
; ------------------------------------------------------------------------------
    
;============================================================
; CONVERTIR TEMPERATURA A ASCII Y TRANSMITIR
;============================================================

CONVERTIR_TEMP_ASCII_TX:
    
    MOVWF   W_TEMP
    
    CLRF    TEMP_CENTENAS
    CLRF    TEMP_DECENAS
    CLRF    TEMP_UNIDADES
    
LOOP_CENT_TX:
    
    MOVLW   .100
    SUBWF   W_TEMP,W
    BTFSS   STATUS,C
    GOTO    FIN_CENT_TX
    MOVWF   W_TEMP
    INCF    TEMP_CENTENAS,F
    GOTO    LOOP_CENT_TX
    
FIN_CENT_TX:
    
    MOVF    W_TEMP,W
    
LOOP_DEC_TX:
    
    MOVLW   .10
    SUBWF   W_TEMP,W
    BTFSS   STATUS,C
    GOTO    FIN_DEC_TX
    MOVWF   W_TEMP
    INCF    TEMP_DECENAS,F
    GOTO    LOOP_DEC_TX
    
FIN_DEC_TX:
    
    MOVF    W_TEMP,W
    MOVWF   TEMP_UNIDADES
    
    MOVF    TEMP_CENTENAS,W
    ADDLW   0x30
    CALL    TX_DATO
    
    MOVF    TEMP_DECENAS,W
    ADDLW   0x30
    CALL    TX_DATO
    
    MOVF    TEMP_UNIDADES,W
    ADDLW   0x30
    CALL    TX_DATO
    
    RETURN

;============================================================
; CONVERTIR NIBBLE A HEX ASCII
;============================================================

NIBBLE_A_HEX_ASCII:
    
    SUBLW   .9
    BTFSS   STATUS,C
    GOTO    ES_LETRA
    
    SUBLW   .9
    ADDLW   0x30
    RETURN
    
ES_LETRA:
    
    SUBLW   .9
    ADDLW   0x37
    RETURN



