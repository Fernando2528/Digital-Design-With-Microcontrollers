#include<P18F4550.inc>
#include"Pin_Manager.inc"
    
    global Set_Up_Outputs
    
pinmanagerd  udata    
    
    
pinmanagerc  code 
  
Set_Up_Outputs:
    
	; Todas las entradas como digitales (desactiva ADC)
	BANKSEL ADCON1
	MOVLW   0x0F
	MOVWF   ADCON1

	; Asegura latch en 0 antes de poner como salida
	BANKSEL LATD
	CLRF    LATD
	
	Banksel TRISD
    
	BCF     TRISD, 0     ; RD0 como salida
	BCF     TRISD, 1     ; RD1 como salida
	BCF     TRISD, 2     ; RD2 como salida
	BCF     TRISD, 3     ; RD3 como salida
	BCF     TRISD, 4     ; RD4 como salida
	BCF     TRISD, 5     ; RD5 como salida
	BCF     TRISD, 6     ; RD6 como salida
	BCF     TRISD, 7     ; RD7 como salida	
	
	;---------------------------------
	; 1) Configurar PORTA como salida digital para los dígitos
	BANKSEL TRISA
	
	BCF     TRISA, 0     ; RA0 como salida
	BCF     TRISA, 1     ; RA1 como salida
	BCF     TRISA, 2     ; RA2 como salida
	BCF     TRISA, 3     ; RA3 como salida
	BCF     TRISA, 4     ; RA4 como salida
	
	BANKSEL LATA
	CLRF    LATA
	
	
    
    return 
    
    end


