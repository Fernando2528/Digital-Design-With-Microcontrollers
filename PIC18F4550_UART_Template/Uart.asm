#include<p18f4550.inc>
#include"Uart.inc"
#include"Project_Macros.inc"
    
    global Set_Up_UART 
    global Uart_Tx
    ;global Uart_Rx
    
    global Send_Mensaje

Uartu udata

Uartc code 
 
Set_Up_UART:
    
    ; Paso 1: Configurar registros de baud rate
    MOVLF spbrgh_, SPBRGH
    MOVLF spbrgl_, SPBRG
    BSF   TXSTA, BRGH          ; High-speed baud rate
    BSF   BAUDCON, BRG16       ; Generador de 16 bits
    
    ; Configurar pines como entrada (requerido por datasheet)
    BSF   TRISC, .6            ; RC6/TX como entrada inicialmente
    BSF   TRISC, .7            ; RC7/RX como entrada
    
    ; Paso 2: Habilitar puerto serial asíncrono
    BCF   TXSTA, SYNC          ; Modo asíncrono
    BSF   RCSTA, SPEN          ; Habilitar puerto serial
    BSF   TXSTA, TXEN          ; Habilitar transmisión (mover aquí)
    
;mensaje  db  "HolaMundoMedTemp27CS", 0   ; El 0 final sirve como delimitador NUL/fin de string
 
mensaje:
    db 'H', 'o', 'l', 'a', 'M', 'u', 'n', 'd', 'o', 'M', 'e', 'd', 'T', 'e', 'm', 'p', '2', '7', 'C', 'S', 0
    
    
    return 
    
Uart_Tx:
    
    ; Asegurar que TX está habilitado
    BSF   TXSTA, TXEN          ; Redundante pero seguro    
    
Uart_Tx_Wait:
    
    BTFSS PIR1, TXIF           ; ¿Buffer vacío?
    GOTO  Uart_Tx_Wait
    
    ; Cargar dato en TXREG
    MOVWF TXREG
    
    return 
    
    
; Test para una cadena con 20 bytes que se muestran de forma consecutiva

    


Send_Mensaje:
    
    ; Asegurar que TX está habilitado (opcional)
    BSF   TXSTA, TXEN
    
    ; Inicializa puntero (usa FSR0)
    LFSR    0, mensaje   ; FSR0 apunta al inicio de la cadena

Send_Mensaje_Loop:
    
    BANKSEL INDF0

    MOVF    INDF0, W     ; Cargar el dato actual apuntado por FSR0
    BZ      Send_Mensaje_Fin   ; Si es cero (fin de cadena) termina
    
    call    Uart_Tx      ; Envía el carácter
    
    INFSNZ  FSR0L, F      ; Incrementa FSR0 (Low byte)
    INCFSZ  FSR0H, F      ; Si hay overflow incrementa High byte
    GOTO    Send_Mensaje_Loop

Send_Mensaje_Fin:
    return
    
    end 

