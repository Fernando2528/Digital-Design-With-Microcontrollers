;V0 Version Separada Segun Lo Visto En Clase
;V1 Version Separada Funcional
    
    
;===============================================================================
; PIC16F887 - RECEPTOR CON ECO
;===============================================================================
; Recibe datos del PIC16F88, agrega su string y envía todo al terminal
; Configuración: 4MHz interno, 9600bps
;===============================================================================

    LIST P=16F887
    #include <p16f887.inc>


;===============================================================================
; CONSTANTES
;===============================================================================
SPBRG_VAL       EQU     .25         ; 9600 bps @ 4MHz
BUFFER_SIZE     EQU     .80         ; Tamaño buffer recepción

;--- Pines ---
#define LED_RX      PORTD,0         ; LED indicador recepción

;===============================================================================
; VARIABLES RAM
;===============================================================================
    CBLOCK  0x20
        uart_dato_rx
        uart_dato_tx
        
        buffer_rx:BUFFER_SIZE       ; Buffer para datos recibidos
        buffer_count                ; Contador de bytes recibidos
        buffer_index                ; Índice para leer buffer
        
        str_index
        char_temp
        delay_1
        delay_2
        flags
        timeout_h
        timeout_l
    ENDC

#define FLAG_RX_COMPLETE    flags,0
#define FLAG_SEND_FERNANDO  flags,1

;===============================================================================
; VECTORES
;===============================================================================
    ORG     0x0000
    goto    Inicio
    
    ORG     0x0004
    retfie

;===============================================================================
; TABLA DE STRING - Fernando
;===============================================================================
    ORG     0x0010

Tabla_Fernando:
    addwf   PCL,F
    retlw   'F'
    retlw   'e'
    retlw   'r'
    retlw   'n'
    retlw   'a'
    retlw   'n'
    retlw   'd'
    retlw   'o'
    retlw   ' '
    retlw   'A'
    retlw   'n'
    retlw   'd'
    retlw   'r'
    retlw   'e'
    retlw   's'
    retlw   ' '
    retlw   'R'
    retlw   'o'
    retlw   'j'
    retlw   'a'
    retlw   's'
    retlw   ' '
    retlw   'F'
    retlw   'e'
    retlw   'r'
    retlw   'n'
    retlw   'a'
    retlw   'n'
    retlw   'd'
    retlw   'e'
    retlw   'z'
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
    retlw   '1'
    retlw   '8'
    retlw   0x00

;===============================================================================
; PROGRAMA PRINCIPAL
;===============================================================================
    ORG     0x0100

Inicio:
    call Set_Up_System

;--- Loop principal ---
Loop_Main:
    banksel PORTD
    clrf    buffer_count
    bcf     FLAG_RX_COMPLETE
    bcf     FLAG_SEND_FERNANDO
    
    ; Esperar recepción del PIC88
    call    Recibir_Datos
    
    ; Verificar si hay datos
    banksel PORTD
    movf    buffer_count,F
    btfsc   STATUS,Z
    goto    Loop_Main
    
    ; Determinar qué enviar según el contenido
    call    Analizar_Buffer
    
    ; Enviar respuesta al terminal
    call    Enviar_Respuesta
    
    ; Delay entre comandos
    call    Delay_200ms
    
    goto    Loop_Main

#include"Uart_Protocol.inc"
#include"Buffer_Protocol.inc"
#include"Delays_Manager.inc"
#include"System_Set_Up.inc"
#include"Device_Manager.inc"


    END