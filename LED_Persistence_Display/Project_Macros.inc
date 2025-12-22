; #include <p18f25k50.inc>


FALSE  equ 0
  
TRUE  EQU 1
  
;*******************************
;* Macro definitions
;* by Eng. Francisco J. Zamora N. MSc.  fzamora@udistrital.edu.co
;* Version 3, march 05/2018
;*******************************    
; NOTA:  para ver en MPSIM el c digo que se expande en cada macro
; es necesario ver el c digo desensamblado y ver el paso a paso all  tambi n. 
; Para ello con depuraci n Debug corriendo, en mplabx, ir a:
;    Window -> Debugging -> dissasembly	
; el paso a paso del simulador al mostrar  el contenido interno de las macros
; y su ejecuci n instrucci n por instrucci n tal cual son expandidas por el
; ensamblador.
;**********************************	
 
MOVLF	MACRO K,F         ;CARGA LITERAL K EN RAM F
	MOVLW   K
	MOVWF	F
	ENDM
ANDLF	MACRO K,F         ;L and F
	MOVLW   K
	ANDWF	F
	ENDM
IORLF	MACRO K,F         ;L OR F
	MOVLW   K
	IORWF	F
	ENDM   
XORLF	MACRO K,F         ;L XOR F
	MOVLW   K
	XORWF	F
	ENDM	
	
MOVL16F MACRO  HL,H,L	    ;CARGA LITERAL HL DE 16 BITS EN REGISTROS H Y L

 MOVLW    HL>>.8
 MOVWF	  H
 MOVLW    HL&0XFF
 MOVWF	  L
    
    ENDM

DECF16SZ MACRO  H,L   ;ADAPTADO DE:  http://www.microchip.com/forums/m15171.aspx
 ;para PIC18F:
#if 0
 decfsz L, f    ;bra and bz are pic18F instrucions.  On PIC16 require porting!!!
 bra $+8    ;A, to out if no zero ( use goto $+4 on PIC16)
 movf H, f
 bz $+6 ; B, skip the next two instructions (on PIC18F) (use $+3 on PIC16)
 decf H, f
 ;out if no zero  $+12 from A, out of MACRO
 ;out if zero, out of MACRO
#else
;para 16F
 decfsz L, f    ;bra and bz are pic18F instrucions.  On PIC16 require porting!!!
 goto $+5    ;A, to out if no zero ( use goto $+4 on PIC16)
 movf H, f
 btfsc	STATUS,Z
 goto $+3 ; B, skip the next two instructions (on PIC18F) (use $+3 on PIC16)
 decf H, f
 ;out if no zero  $+12 from A, out of MACRO
 ;out if zero, out of MACRO
#endif
	ENDM

;************
BTG_	MACRO	PORT,bitk
		movlw	.1>>bitk
		xorwf	PORT,f
	ENDM


