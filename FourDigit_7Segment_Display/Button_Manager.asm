#include<p18f4550.inc>
#include"Button_Manager.inc"
    
    
    
Buttond  udata
counter1    RES 1    ; Reserva 1 byte para counter1
Nivel_Brillo    RES 1    ; Reserva 1 byte para esta variable
TMP RES 1
  
Button_ code
    
Anti_Bounce:
    
    MOVLW   D'200'       
    MOVWF   counter1
    

Wait_100ms:
    CALL    Delay_1ms
    DECFSZ  counter1, F
    BRA     Wait_100ms
    return 
    
Button_Pressed:
    
    
    call Anti_Bounce
    
    CLRB LEDT ; Apaga led de prueba
    
    INCF    Nivel_Brillo, F 
    INCF    Nivel_Brillo, F 
    INCF    Nivel_Brillo, F 
    INCF    Nivel_Brillo, F 
    
    
    
    MOVLW   D'32'
    CPFSLT  Nivel_Brillo
    CLRF    Nivel_Brillo        ; Si supera 7, vuelve a 0 (100%)
    BRA     Nivel_OK
    
    
     

Nivel_OK:
    
    MOVF    Nivel_Brillo, W
    CALL    Duty_Table          ; Busca duty correspondiente
     
    ; Actualizar CCP1 (PWM2 - RC2)
    MOVWF   CCPR1L              ; Bits 9:2 del duty
    BCF     CCP1CON, 5          ; Limpiar DC1B1
    BCF     CCP1CON, 4          ; Limpiar DC1B0
    
    ; Actualizar CCP2 (PWM1 - RC1)
    MOVWF   CCPR2L              ; Bits 9:2 del duty
    BCF     CCP2CON, 5          ; Limpiar DC2B1
    BCF     CCP2CON, 4          ; Limpiar DC2B0


    RETURN

Duty_Table:
    
    ADDWF   PCL, F
    RETLW   0xFF      ; 100%
    RETLW   0xE0      ; 87%
    RETLW   0xC0      ; 75%
    RETLW   0xA0      ; 62%
    RETLW   0x80      ; 50%
    RETLW   0x60      ; 37%
    RETLW   0x40      ; 25%
    RETLW   0x20    ; 12%
    
    return 
    
    end


