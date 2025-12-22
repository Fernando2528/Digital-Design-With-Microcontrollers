#include<P18F4550.inc>
#include"Set_Up.inc"
#include "Pin_Manager.inc"
#include "Project_Macros.inc"


    
    ;global setupOSC  
    global Set_Up_General
    
    extern Set_Up_Outputs
    
setupd_  udata 

    
setup_ code 	

 
setupOSC:
	    
    ; IRCF2:IRCF0 = 111 -> 8 MHz
    BSF     OSCCON, IRCF2
    BSF     OSCCON, IRCF1
    BSF     OSCCON, IRCF0

    ; SCS1:SCS0 = 10 -> Selecciona el bloque de oscilador interno como reloj del sistema
    BSF     OSCCON, SCS1
    BCF     OSCCON, SCS0

    
    
WAIT_HFINTOSC:
    
	    BTFSS   OSCCON, IOFS    ; IOFS=1 cuando INTOSC está estable
	    GOTO    WAIT_HFINTOSC

    return
    
setupSW3: ; Unica Entrada Del Circuito Disenado
    
    SETB  TRISB,2         ; RB2 como entrada
    CLRB  INTCON2,RBPU    ; Pull-ups ON en PORTB
    
   ; BSF  WPUB,WPUB2   ;PULL UP RB2 ON (Habilitacion particular de Pull Up RB2) No existe en pics antiguos solo en los nuevos
    
    return
    
Set_Up_PWM:
    
    bcf TRISC, 1      ; RC1 como salida
    bcf TRISC, 2      ; RC2 como salida
    movlw 0x0F
    movwf ADCON1      ; Todos digitales

    movlw 0x0C
    movwf CCP1CON
    movwf CCP2CON

    movlw 0x3F
    movwf PR2

    movlw 0xFF
    movwf CCPR1L
    movwf CCPR2L

    bsf CCP1CON, 5    ; DC1B1 en 1
    bsf CCP1CON, 4    ; DC1B0 en 1
    bsf CCP2CON, 5    ; DC2B1 en 1
    bsf CCP2CON, 4    ; DC2B0 en 1

    movlw 0x07
    movwf T2CON  
    
    return 
	    
Set_Up_General:
    
    call Set_Up_Outputs
    call setupOSC
    call setupSW3
    call Setup_Timer0_Interrupt
    call Set_Up_clock
    call Set_Up_PWM
    
    return
    

	    
    
    end 


