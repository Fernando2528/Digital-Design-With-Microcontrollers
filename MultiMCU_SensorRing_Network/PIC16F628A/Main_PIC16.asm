; ================================================================
; Test PIC16F18875 - Encender todos los pines de PORTA y PORTB
; Ensamblador: MPASM (mpasmx)
; ================================================================

        LIST    P=16F18875
        INCLUDE <P16F18875.INC>

; ------------------------------------------------
; BITS DE CONFIGURACIÓN
; ------------------------------------------------
; IMPORTANTE:
; 1) Comenta o borra TODAS las __CONFIG que tengas antes.
; 2) En MPLAB X:
;       Window -> PIC Memory Views -> Configuration Bits
;    - Selecciona el dispositivo PIC16F18875
;    - Elige el oscilador, WDT, LVP, etc.
;    - Pulsa "Generate Source Code to Output"
;    - Copia SOLO las lineas __CONFIG que salen ahí
; 3) Pégalas aquí, en lugar de este bloque de comentarios.
;
;   EJEMPLO (NO copiar tal cual, usa las que genere MPLAB):
;   __CONFIG _CONFIG1, 0x3FFF
;   __CONFIG _CONFIG2, 0x3FFF
;   __CONFIG _CONFIG3, 0x3FFF
;   __CONFIG _CONFIG4, 0x3FFF
;   __CONFIG _CONFIG5, 0x3FFF
;
; Así evitas los errores 107, 108 y el símbolo desconocido.
; ------------------------------------------------

; ================================================================
; VECTORES
; ================================================================

        ORG     0x0000
        GOTO    INIT

        ORG     0x0004          ; Vector de interrupción (no usado)
        RETFIE

; ================================================================
; PROGRAMA PRINCIPAL
; ================================================================

INIT
    ; ---- Deshabilitar funciones analógicas ----
    BANKSEL ANSELA
    CLRF    ANSELA          ; PORTA digital
    BANKSEL ANSELB
    CLRF    ANSELB          ; PORTB digital
    ; Si quieres usar más puertos, descomenta:
    ;BANKSEL ANSELC
    ;CLRF    ANSELC
    ;BANKSEL ANSELD
    ;CLRF    ANSELD
    ;BANKSEL ANSELE
    ;CLRF    ANSELE

    ; ---- Configurar pines como salida ----
    BANKSEL TRISA
    CLRF    TRISA           ; Todos los pines de PORTA como salida
    BANKSEL TRISB
    CLRF    TRISB           ; Todos los pines de PORTB como salida
    ; Para más puertos:
    ;BANKSEL TRISC
    ;CLRF    TRISC
    ;BANKSEL TRISD
    ;CLRF    TRISD
    ;BANKSEL TRISE
    ;CLRF    TRISE

    ; ---- Encender todos los bits de los puertos ----
    BANKSEL PORTA
    MOVLW   0xFF
    MOVWF   PORTA

    BANKSEL PORTB
    MOVLW   0xFF
    MOVWF   PORTB

    ; Si usas más puertos:
    ;BANKSEL PORTC
    ;MOVLW   0xFF
    ;MOVWF   PORTC
    ;BANKSEL PORTD
    ;MOVLW   0xFF
    ;MOVWF   PORTD
    ;BANKSEL PORTE
    ;MOVLW   0xFF
    ;MOVWF   PORTE

; Bucle infinito
MAIN_LOOP
    GOTO    MAIN_LOOP

        END
