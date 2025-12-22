#include<p18f4550.inc>
#include"System_Set_Up.inc"
    
    global setupOSC
    
Sysu udata
 
Sysc code 
 
setupOSC:
	  
    banksel OSCCON 
    ; IRCF2:IRCF0 = 111 -> 8 MHz
    BSF     OSCCON, IRCF2
    BSF     OSCCON, IRCF1
    BSF     OSCCON, IRCF0

    ; SCS1:SCS0 = 10 -> Selecciona el bloque de oscilador interno como reloj del sistema
    BSF     OSCCON, SCS1
    BCF     OSCCON, SCS0

    
    
WAIT_HFINTOSC:
    
	    ;BTFSS   OSCCON, IOFS    ; IOFS=1 cuando INTOSC está estable
	    ;GOTO    WAIT_HFINTOSC

    return
    
 
 end 


