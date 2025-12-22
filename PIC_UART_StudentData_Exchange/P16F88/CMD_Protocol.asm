#include<P16F88.inc>
;#include"CMD_Protocol.inc"
    
    ;GLOBAL Procesar_Comando
    ;GLOBAL Cmd_Write
    ;GLOBAL Cmd_Read
    
    
    ;EXTERN	uart_dato_rx
    ;EXTERN	uart_dato_tx
    ;EXTERN	comando
    ;EXTERN	str_index
    ;EXTERN	char_temp
    ;EXTERN	delay_1
    ;EXTERN	delay_2
    ;EXTERN	flags
    
    
    ;EXTERN  UART_TX
    ;EXTERN  UART_RX
    ;EXTERN  Send_String_Juan
    
    ;EXTERN Delay_50ms
    ;EXTERN Delay_500ms
    
    ;--- Pines ---
    ;#define LED_BOOT    PORTB,0         ; LED indicador
    ;#define FLAG_ACTIVE   flags,0
    
CMDu udata
 
CMDc code 
    

    
    end
