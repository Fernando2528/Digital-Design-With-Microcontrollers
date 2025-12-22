
Set_Up_System:
    
    ; Configurar oscilador 4MHz
    banksel OSCCON
    movlw   b'01100000'
    movwf   OSCCON
    
    ; Configurar puertos
    banksel TRISD
    bcf     TRISD,0                 ; RD0 salida (LED)
    
    banksel TRISC
    bsf     TRISC,7                 ; RC7/RX entrada (del PIC88)
    bcf     TRISC,6                 ; RC6/TX salida (al terminal)
    
    banksel PORTD
    clrf    PORTD
    clrf    flags
    
    ; Inicializar UART
    call    UART_Init
    
    ; LED apagado = esperando
    bcf     LED_RX
    
    return


