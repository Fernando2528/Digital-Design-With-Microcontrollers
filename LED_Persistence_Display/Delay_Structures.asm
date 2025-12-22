#include "Delay_Intermediate_File.inc"
    
#define FALSE 0
#define TRUE 1
    
; Delay = 0.002 seconds
; Clock frequency = 16 MHz

; Actual delay = 0.002 seconds = 8000 cycles
; Error = 0 %
    
#if FALSE ; if = 0

Delays udata ; se define una porcion de la memoria ram de nombre delay
d1 res 1 ; reserva un byte
d2 res 1 ; reserva un byte
d3 res 1 ; reserva un byte
    
#ELSE 
	cblock
	d1
	d2
	d3
	endc
#ENDIF
	
Delays_ code ; 

Delay:
		;399999 cycles
	movlw	0x36
	movwf	d1
	movlw	0xE0
	movwf	d2
	movlw	0x01
	movwf	d3
Delay_0:
	decfsz	d1, f
	bra	$+2*2
	decfsz	d2, f
	bra	$+2*2
	decfsz	d3, f
	bra	Delay_0

			;1 cycle
	nop
	return

    end 



