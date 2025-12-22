#include "Main_Intermediate_File.inc"
    
;========== vectors def======
Resetv code resetvec ; en la direccion del vector resetvec va la instruccion 
 ; consecutiva
 
    goto    setup_ ; instruccion consecutiva
   
 #if TRUE
 
Hintv   code hintvec
   ; goto highisr
   nop
   
Lintv   code	lointvec
   ;goto lointisr
    nop
 
    #ENDIF
;====================== 
    
main_ code
 
setup_:
    
    call setupOSC
    
    BCF TRISB, 0    ; Led RB0 (TRISB,0)
    BCF TRISB, 1    ; Led RB1 (TRISB,1)
    BCF TRISB, 2    ; Led RB2 (TRISB,2)
    BCF TRISB, 3    ; Led RB3 (TRISB,3)
    BCF TRISB, 4    ; Led RB4 (TRISB,4)
    BCF TRISB, 5    ; Led RB5 (TRISB,5)
    BCF TRISB, 6    ; Led RB6 (TRISB,6)
    BCF TRISB, 7    ; Led RB7 (TRISB,7)
    call Delay
    

    
     
loop:  
    
    call Number0
    
    call Number1
    
    
    
    ; --------------Fin Del Ciclo-----------------------------------------
    
    nop
    goto loop
    
    end



