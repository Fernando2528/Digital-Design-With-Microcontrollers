; ============================================================
; ARCHIVO: retardos.inc
; Rutinas de retardo para PIC18F4550
; Oscilador: 8 MHz (Tcy = 0.5 µs)
; ============================================================

; ============================================================
; VARIABLES DE RETARDO (definidas en cblock del main)
; CONTADOR_RETARDO
; TMR0H_AUX
; TMR0L_AUX
; ============================================================

; ============================================================
; CONFIGURACIÓN DEL TIMER0
; ============================================================
CONFIG_RETARDO:
    
	MOVLW	B'00000000'		; Timer0 como contador de ciclos
	MOVWF	T0CON			; Configurado como contador de 16 BITS
	CLRF	TMR0L			; Limpia los registros
	CLRF	TMR0H			; asociados al Timer0
	BCF	INTCON,TMR0IF	    ; Limpia la bandera de interrupción del Timer0
	RETURN

; ============================================================
; RETARDO DE SEGURIDAD EN BOTONES (90 ms)
; ============================================================
RET_BOTONES:
    
	CALL	RET_10ms
	CALL	RET_10ms
	CALL	RET_10ms
	CALL	RET_10ms
	CALL	RET_10ms
	CALL	RET_10ms
	CALL	RET_10ms
	CALL	RET_10ms
	CALL	RET_10ms
	RETURN

; ============================================================
; RETARDO DE 1 SEGUNDO
; ============================================================
RET_X1s:
    
	MOVWF	CONTADOR_RETARDO
	BSF	T0CON,T0PS2
	BSF	T0CON,T0PS1
	BSF	T0CON,T0PS0
	MOVLW	0xF4
	MOVWF	TMR0H_AUX
	MOVLW	0x24
	MOVWF	TMR0L_AUX
	GOTO	RETARDOS

; ============================================================
; RETARDO DE 100 ms
; ============================================================
RET_X100ms:
    
	MOVWF	CONTADOR_RETARDO
	BSF	T0CON,T0PS2
	BCF	T0CON,T0PS1
	BCF	T0CON,T0PS0
	MOVLW	0xC3
	MOVWF	TMR0H_AUX
	MOVLW	0x50
	MOVWF	TMR0L_AUX
	GOTO	RETARDOS

; ============================================================
; RETARDO DE 10 ms
; ============================================================
RET_X10ms:
    
	MOVWF	CONTADOR_RETARDO
	BCF	T0CON,T0PS2
	BCF	T0CON,T0PS1
	BSF	T0CON,T0PS0
	MOVLW	0x9C
	MOVWF	TMR0H_AUX
	MOVLW	0x40
	MOVWF	TMR0L_AUX
	GOTO	RETARDOS

; ============================================================
; RETARDO DE X milisegundos
; ============================================================
RET_Xms:
    
	MOVWF	CONTADOR_RETARDO
	BCF	T0CON,T0PS2
	BCF	T0CON,T0PS1
	BSF	T0CON,T0PS0
	MOVLW	0x0F
	MOVWF	TMR0H_AUX
	MOVLW	0xA0
	MOVWF	TMR0L_AUX
	GOTO	RETARDOS

; ============================================================
; RETARDO DE 100 microsegundos
; ============================================================
RET_100us:
    
	MOVWF	CONTADOR_RETARDO
	BCF	T0CON,T0PS2
	BCF	T0CON,T0PS1
	BSF	T0CON,T0PS0
	MOVLW	0x01
	MOVWF	TMR0H_AUX
	MOVLW	0x90
	MOVWF	TMR0L_AUX

; ============================================================
; SUBRUTINA PRINCIPAL DE RETARDO
; ============================================================
RETARDOS:
    
	COMF	TMR0H_AUX,W
	MOVWF	TMR0H
	COMF	TMR0L_AUX,W
	MOVWF	TMR0L
	BSF	T0CON,TMR0ON

CICLO_RETARDO:
    
	BTFSS	INTCON,TMR0IF
	GOTO	CICLO_RETARDO
	BCF	INTCON,TMR0IF
	DECFSZ	CONTADOR_RETARDO
	GOTO	RETARDOS
	RETURN

; ============================================================
; RETARDOS DERIVADOS
; ============================================================
RET_10ms:
    
	MOVLW	.10
	CALL	RET_Xms
	RETURN

RET_5ms:
    
	MOVLW	.5
	CALL	RET_Xms
	RETURN

RET_1ms:
    
	MOVLW	.1
	CALL	RET_Xms
	RETURN

RET_100ms:
    
	MOVLW	.100
	CALL	RET_Xms
	RETURN

RET_500ms:
    
	CALL	RET_100ms
	CALL	RET_100ms
	CALL	RET_100ms
	CALL	RET_100ms
	CALL	RET_10ms
	CALL	RET_10ms
	CALL	RET_10ms
	CALL	RET_10ms
	CALL	RET_10ms
	RETURN

RET_1s:
    
	MOVLW	.1
	CALL	RET_X1s
	RETURN