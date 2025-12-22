; V0 Version Funcional En Simulacion
; V1 Version Separada

    
;============================================================
; PIC18F4550 - SISTEMA UART RECEPTOR CON ARDUINO
; Solo responde cuando recibe paquetes del Arduino
;============================================================

#include "p18f4550.inc"
#include"Device_Manager.inc"
    
;============================================================
; RESERVA DE MEMORIA
;============================================================

    CBLOCK 0x000
    W_TEMP
    STATUS_TEMP
    BSR_TEMP
    
    ADC_ALTO
    ADC_BAJO
    TEMPERATURA_GRADOS
    TIMEOUT_CONTADOR
    
    BUFFER_RX:18
    CONTADOR_RX
    FLAG_PAQUETE_COMPLETO
    CHECKSUM_RECIBIDO
    CHECKSUM_CALCULADO
    
    BUFFER_TX:23
    INDICE_BUFFER
    TEMP_CENTENAS
    TEMP_DECENAS
    TEMP_UNIDADES
    TEMP_RESULTADO
    ENDC

;============================================================
; VECTORES DE INTERRUPCIÓN
;============================================================

    ORG 0x000
    GOTO INICIO

    ORG 0x008
    GOTO ALTA_PRIORIDAD

    ORG 0x0018
    GOTO BAJA_PRIORIDAD



;============================================================
; PROGRAMA PRINCIPAL
;============================================================

    ORG 0x0100

    #include"Interrupciones.inc"
    #include"System_Set_Up.inc"
    
INICIO:
    
   call System_Set_Up

;============================================================
; LOOP PRINCIPAL
;============================================================

PRINCIPAL:
    
    BTFSC   FLAG_PAQUETE_COMPLETO,0
    CALL    PROCESAR_PAQUETE_UART
    
    GOTO    PRINCIPAL
    
#include"Temperatura.inc"
#include"Uart_Protocol.inc"
#include"Checksum_Validator.inc"
#include"Conversion_Manager.inc"
#include"Buffer_Manager.inc"


    END