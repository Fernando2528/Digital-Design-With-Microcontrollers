
System_Set_Up:
    
 MOVLW   B'01110000'
    MOVWF   OSCCON
    
    
ESPERAR_OSC:
    
    BTFSS   OSCCON,IOFS
    GOTO    ESPERAR_OSC
    
    MOVLW   0x0E
    MOVWF   ADCON1
    
    CLRF    PORTA
    CLRF    PORTB
    CLRF    PORTC
    CLRF    PORTD
    CLRF    LATA
    CLRF    LATB
    CLRF    LATC
    CLRF    LATD
    
    MOVLW   B'00001001'
    MOVWF   TRISA
    CLRF    TRISB
    CLRF    TRISD
    BCF     TRISC,6
    BSF     TRISC,7
    
    MOVLW   B'00000001'
    MOVWF   ADCON0
    
    MOVLW   B'10101110'
    MOVWF   ADCON2
    
    CLRF    SPBRGH
    MOVLW   .207
    MOVWF   SPBRG
    
    MOVLW   B'00100100'
    MOVWF   TXSTA
    
    MOVLW   B'10010000'
    MOVWF   RCSTA
    
    MOVLW   B'00001000'
    MOVWF   BAUDCON
    
    BCF     PIR1,RCIF
    BCF     PIR1,TXIF
    
    BSF     PIE1,RCIE
    BSF     INTCON,PEIE
    BSF     INTCON,GIE
    
    CLRF    CONTADOR_RX
    BCF     FLAG_PAQUETE_COMPLETO,0
    
    CALL    ENVIAR_MENSAJE_INICIO

    return
