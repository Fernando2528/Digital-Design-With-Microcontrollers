#include<P16F887.inc>
;#include"Buffer_Protocol.inc"
    
    ;GLOBAL Recibir_Datos
    ;GLOBAL Recibir_Byte
    ;GLOBAL Recibir_Done
    ;GLOBAL Analizar_Buffer
    ;GLOBAL Enviar_Respuesta
    ;GLOBAL Send_CRLF_Mid
    
    ;EXTERN Delay_1ms
    
    ;EXTERN UART_TX
    ;EXTERN UART_RX
    
    ;EXTERN UART_Available
    ;EXTERN Send_String_Fernando
    
    ;EXTERN uart_dato_rx
    ;EXTERN uart_dato_tx
                
    ;EXTERN buffer_count                ; Contador de bytes recibidos
    ;EXTERN buffer_index                ; Índice para leer buffer
        
    ;EXTERN str_index
    ;EXTERN char_temp
    ;EXTERN delay_1
    ;EXTERN delay_2
    ;EXTERN flags
    ;EXTERN timeout_h
    ;EXTERN timeout_l
	
    
    
    
    
Bufferu udata

;buffer_rx   RES BUFFER_SIZE    ; Buffer de recepción
 
Bufferc code 
 

    end


