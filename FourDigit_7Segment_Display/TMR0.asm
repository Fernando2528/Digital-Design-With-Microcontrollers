#include<P18f4550.inc>
#include"Display_Manager.inc"
#include<TMR0.inc>
    
    global Setup_Timer0_Interrupt
    
    extern Mostrar_Digito    ; Siempre muestra en display el valor
    extern Delay_1s              ; Espera un segundo (puedes usar Delay_1s del otro archivo)
    extern Increment_Clock       ; Suma uno al conteo
    
    
TMR0d  udata

TMR0_ code
 
    ORG     0x0008          ; Vector de interrupción de alta prioridad
    GOTO    Timer0_ISR      ; Salta a la rutina de interrupción
    
Setup_Timer0_Interrupt:
    ; 1) Configurar interrupciones globales
    BANKSEL INTCON
    BSF     INTCON, GIE     ; Habilita interrupciones globales
    BSF     INTCON, TMR0IE  ; Habilita interrupción de Timer0
    BCF     INTCON, TMR0IF  ; Limpia bandera de Timer0
    
    ; 2) Configurar Timer0
    BANKSEL T0CON
    ; T0CON: configuración del Timer0
    ; bit 7 = TMR0ON (1 = Timer0 encendido)
    ; bit 6 = T08BIT (0 = modo 16 bits, 1 = modo 8 bits)
    ; bit 5 = T0CS (0 = clock interno)
    ; bit 4 = T0SE (no importa con clock interno)
    ; bits 2-0 = T0PS (prescaler)
    
    MOVLW   B'10000111'     ; Timer0 ON, 16-bit, clock interno, prescaler 1:256
    MOVWF   T0CON
    
    ; 3) Cargar valor inicial para contar 1000
    ; Cálculo: 65536 - 1000 = 64536 = 0xFC18
    ; Carga Timer0 para 1 segundo
    MOVLW   0xE1           ; parte alta
    MOVWF   TMR0H
    MOVLW   0x6B           ; parte baja
    MOVWF   TMR0L

    
    RETURN
    
    
    
Timer0_ISR:
    
    ; 1) Bajar/limpiar la bandera de Timer0
    BANKSEL INTCON
    BCF     INTCON, TMR0IF
    
    ; 2) Recargar Timer0 para 1 segundo
    MOVLW   0xE1           ; parte alta
    MOVWF   TMR0H
    MOVLW   0x6B           ; parte baja
    MOVWF   TMR0L
    
    ; 3) Llama a la rutina de incremento de reloj
   ; CALL    Increment_Clock
    
    Banksel LATA
    BSF LEDT
    
  
    
    CALL Increment_Clock       ; Suma uno al conteo
    
    
    
    ; 4) Retornar de la interrupción (alta prioridad)
    RETFIE  FAST
    
    
    end 