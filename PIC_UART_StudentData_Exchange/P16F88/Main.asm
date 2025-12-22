; V0 Version dividida como en clase 
; V1 Version Dividida Funcional En Simulacion
    
;===============================================================================
; PIC16F88 - TRANSMISOR PRINCIPAL
;===============================================================================
; Recibe comandos W/R del terminal y envía su string al PIC16F887
; Configuración: 4MHz interno, 9600bps
;===============================================================================

    LIST P=16F88
    #include <p16f88.inc>

#include"Device_Manager.inc"

;===============================================================================
; CONSTANTES
;===============================================================================
SPBRG_VAL       EQU     .25         ; 9600 bps @ 4MHz
CMD_WRITE       EQU     'W'
CMD_READ        EQU     'R'

;--- Pines ---
#define LED_BOOT    PORTB,0         ; LED indicador

;===============================================================================
; VARIABLES RAM
;===============================================================================
    CBLOCK  0x20
        uart_dato_rx
        uart_dato_tx
        comando
        str_index
        char_temp
        delay_1
        delay_2
        flags
    ENDC

#define FLAG_ACTIVE   flags,0

;===============================================================================
; VECTORES
;===============================================================================
    ORG     0x0000
    goto    Inicio
    
    ORG     0x0004
    retfie

;===============================================================================
; TABLA DE STRING - Juan David
;===============================================================================
    ORG     0x0010

Tabla_Juan:
    addwf   PCL,F
    retlw   'J'
    retlw   'u'
    retlw   'a'
    retlw   'n'
    retlw   ' '
    retlw   'D'
    retlw   'a'
    retlw   'v'
    retlw   'i'
    retlw   'd'
    retlw   ' '
    retlw   'A'
    retlw   'r'
    retlw   'i'
    retlw   'a'
    retlw   's'
    retlw   ' '
    retlw   'M'
    retlw   'e'
    retlw   'l'
    retlw   'o'
    retlw   ' '
    retlw   '2'
    retlw   '0'
    retlw   '2'
    retlw   '3'
    retlw   '1'
    retlw   '0'
    retlw   '0'
    retlw   '5'
    retlw   '0'
    retlw   '3'
    retlw   '3'
    retlw   0x00

;===============================================================================
; PROGRAMA PRINCIPAL
;===============================================================================
    ORG     0x0100

Inicio:
    
    call Set_Up_System
    
    

;--- Loop principal ---
Loop_Main:
    
    banksel PORTB
    btfss   FLAG_ACTIVE
    goto    Loop_Main
    
    ; Verificar comando del terminal
    banksel PIR1
    btfss   PIR1,RCIF
    goto    Loop_Main
    
    ; Procesar comando
    call    Procesar_Comando
    
    goto    Loop_Main

#include"Uart_Protocol.inc"
#include"CMD_Protocol.inc"
#include"Delays_Manager.inc"
#include"Set_Up_System.inc"

    END