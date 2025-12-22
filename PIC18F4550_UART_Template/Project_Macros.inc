;#include<P18F4550.inc>
	
FALSE  equ 0
  
TRUE  EQU 1
  
MOVLF	MACRO K,F         ;CARGA LITERAL K EN RAM F
	MOVLW   K
	MOVWF	F
	ENDM
	
OVLF	MACRO K,F         ;CARGA LITERAL K EN RAM F
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
		
GIntENABLE  MACRO
	BANKSEL INTCON
	BSF	INTCON,GIE
	ENDM
	
GIntDISABLE  MACRO
	BANKSEL INTCON
	BCF	INTCON,GIE    
	ENDM
	
SETB  macro    reg, bit
	BANKSEL reg
	bsf     reg,bit
	endm
CLRB  macro    reg,bit
        banksel reg
	bcf	reg,bit
	endm
	
BTGB macro reg, bit
    BTG reg, bit 
    endm
    
MOVLFSHL macro k, REG, pos ; Desplaza a la izquierda 
    movlw (k << pos) 
    banksel REG
    iorwf  REG, f 

    endm
    



