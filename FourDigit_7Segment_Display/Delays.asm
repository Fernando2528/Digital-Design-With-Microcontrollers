#include<p18f4550.inc>
#include "Delays.inc"
    #define FALSE 0
    #define TRUE 1
    
    global Delay_1ms
    global Delay_1s
    global Delay_100ms
    global Delay_10ms
    


#if TRUE

Delays udata ;0x10
d1 res 1
d2 res 1
d3 res 1
    
#ELSE
	cblock
	d1
	d2
	d3
	endc
#ENDIF
	
Delays_ code

Delay_1ms:
	
	
		;1998 cycles
	movlw	0x8F
	movwf	d1
	movlw	0x02
	movwf	d2
	
delay1ms_0:	  
	
	decfsz	d1, f
	bra	$+2*2
	decfsz	d2, f
	bra	delay1ms_0

			;2 cycles
	bra	$+1*2

			;4 cycles (including call)
	return
	

Delay_1s:
    
    	;1999996 cycles
	movlw	0x11
	movwf	d1
	movlw	0x5D
	movwf	d2
	movlw	0x05
	movwf	d3
Delay_0:
	decfsz	d1, f
	bra	$+2*2
	decfsz	d2, f
	bra	$+2*2
	decfsz	d3, f
	bra	Delay_0

			;4 cycles
	goto	$+1*2
	goto	$+1*2
    
    return
    
Delay_100ms:
    	;199998 cycles
	movlw	0x3F
	movwf	d1
	movlw	0x9D
	movwf	d2
	
Delay100ms_0:
    
	decfsz	d1, f
	bra	$+2*2
	decfsz	d2, f
	bra	Delay100ms_0

			;2 cycles
	bra	$+1*2
    return 
    
Delay_10ms:
    	;19998 cycles
	movlw	0x9F
	movwf	d1
	movlw	0x10
	movwf	d2
Delay10ms_0:
	decfsz	d1, f
	bra	$+2*2
	decfsz	d2, f
	bra	Delay10ms_0

			;2 cycles
	bra	$+1*2
    return 
    
    END


