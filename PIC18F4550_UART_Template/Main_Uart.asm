
;V0 Funciona el ejemplo visto en clase 
    
#include"Main_Uart.inc"
    
Resetv code 0x000
    goto Set_Up
    
inthigh code 0x008
    ;goto highISR
    
intlow code 0x018
    ;goto lowISR
    
Mainu udata 
 
mensaje  res 21          ; Reserva 21 bytes en RAM
 
Mainc code 
 
Set_Up:
    
    ; Inicializa RAM con "HolaMundoMedTemp27CS"
    MOVLW 'H'     ; Direccion base de mensaje
    MOVWF mensaje
    MOVLW 'o'
    MOVWF mensaje+1
    MOVLW 'l'
    MOVWF mensaje+2
    ; ... repetir hasta llenar los 20 bytes
    MOVLW 0
    MOVWF mensaje+20     ; NUL de terminación
    ; Luego sigues con el resto del Setup
    
    call setupOSC
    call Set_Up_UART
    
loop:
    
    ; Cargar 'h' en W y transmitir
    ;MOVLW 'h'              ; Cargar el carácter 'h' en W
    ;call Uart_Tx           ; Llamar función de transmisión
    
    ;nop
    
    
    call Send_Mensaje     ; Envía todo el mensaje
    ;call Delay_Short      ; Opcional, espera un poco para no saturar
    
    nop 
    
    goto loop
    
    sleep                   ; Esta línea nunca se ejecutará

 end 