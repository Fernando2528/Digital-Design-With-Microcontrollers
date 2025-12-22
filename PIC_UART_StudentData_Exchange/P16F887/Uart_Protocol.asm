#include<P16F887.inc>
;#include"Uart_Protocol.inc"
    
    ;GLOBAL Tabla_Fernando
    ;GLOBAL UART_Init
    ;GLOBAL UART_TX
    ;GLOBAL UART_RX
    ;GLOBAL UART_Clear_Err
    ;GLOBAL UART_Available
    ;GLOBAL Send_String_Fernando
    
    ;EXTERN uart_dato_rx
    ;EXTERN uart_dato_tx
                
    ;EXTERN buffer_count                ; Contador de bytes recibidos
    ;EXTERN buffer_index                ; Índice para leer buffer
        
    ;EXTERN str_index
    ;EXTERN char_temp    
    
UartPu udata
 
Uartc code
 

    end