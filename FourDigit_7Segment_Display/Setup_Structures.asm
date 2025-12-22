#include "Setup_Intermediate_File.inc"
    
setupd_ udata ; posible seccion de Ram
 
    
setup_ code ; seccion que alojara el codigo de la rutina 
 
	setupOSC:
        ; Select Internal Oscillator block as system clock source.
        ; We keep the default frequency (HFINTOSC default ? 16 MHz on this device).
        BANKSEL OSCCON
        BSF     OSCCON, SCS1        ; SCS1:SCS0 = 10 -> System clock = Internal Oscillator Block
        BCF     OSCCON, SCS0

	; If you want to be explicit about 16 MHz, you can set IRCF bits here.
	; Refer to the datasheet/OSCCON for exact IRCF coding on PIC18F25K50.
	; (Not strictly necessary if you are okay with the POR default.)


	; Wait until HFINTOSC is stable (HFIOFS = 1)
	    WAIT_HFINTOSC:
		;BTFSS   OSCCON, HFIOFS
		;GOTO    WAIT_HFINTOSC	

		return
	;*****************************************************************88	
    
    end 



