
; V0_Version en la que sirve todo pero no el contador y falta la impletacion de pwm

; V0.1 En esta version del circuito funciona el primer digito del contador 

; V0.2 En esta version el contador funciona y los pwms estan declarados e inicializados (Falta logica de variacion de brillo)

; V1 Version a priori funcional es posible que haya que ajustar el contador que se encarga de los niveles de briilo en 
; Button.asm
    
; V1.1 Busca solucionar los problemas de conmutacion exesivamente rapida
    
; V1.2 Se mejoro considerablemente el tema de la comutacion 
    
;V 1.3 Se modificara el hardware de la simulacion para mejorar la fiabilidad del codigo
    
; V1.4 En esta version todo es funcional y esta comprobado mediante simulacion, sin embargo, aun se podria mejorar
; el antirrebote incorporando los conceptos vistos en clase y lo mismo en cuanto a la tabla de direcciones.
    
#include<P18F4550.inc>
#include"Main_Public_File.inc"

Resetv code resetvec
 
    goto    Initialice_Circuit
    
Lointvec code lointvec 
 
    ;goto TMR0

maind  udata
  
main_ code
    
Initialice_Circuit:
	
	call Set_Up_General
	goto loop
	
	
loop: 
    
    BANKSEL PORTB
    BTFSS   PORTB,2          ; ¿RB2=1? (No presionado) ? Salta el apagado
    CALL    Button_Pressed   ; Si RB2=0 (presionado), apaga LEDA     
   
    Call End_Count
    
    goto loop
    
    

    end