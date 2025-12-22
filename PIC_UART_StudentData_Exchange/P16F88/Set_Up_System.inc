
    
Set_Up_System:
    
; Configurar oscilador 4MHz
    banksel OSCCON
    movlw   b'01100000'
    movwf   OSCCON
    
    ; Configurar puertos
    banksel TRISB
    bcf     TRISB,0                 ; RB0 salida (LED)
    bsf     TRISB,2                 ; RB2 entrada (RX del terminal)
    bcf     TRISB,5                 ; RB5 salida (TX al PIC887)
    
    banksel PORTB
    clrf    PORTB
    clrf    flags
    
    ; Inicializar UART
    call    UART_Init
    
    ; LED encendido = listo
    bsf     LED_BOOT
    bsf     FLAG_ACTIVE
    
    call    Delay_500ms
    
    return


