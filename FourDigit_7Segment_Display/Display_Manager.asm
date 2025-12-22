#include<p18f4550.inc>
#include"Display_Manager.inc"
    
    global Increment_Clock
    global Mostrar_Digito
    global Set_Up_clock
    global End_Count
    

Displayd  udata

; Variables de conteo para minutos y segundos
seg_unidades    RES 1    ; 0-9
seg_decenas     RES 1    ; 0-5  
min_unidades    RES 1    ; 0-9
min_decenas     RES 1    ; 0-5
  
Display_ code
 
Set_Up_clock:
    
    CLRF seg_unidades
    CLRF seg_decenas
    CLRF min_unidades
    CLRF    min_decenas
    
    return 
; ==== Actualiza el contador de segundos decimales ====
Increment_Clock:
    INCF seg_unidades, F          ; Incrementa la unidad
    INCF seg_unidades, F          ; Incrementa la unidad
    INCF seg_unidades, F          ; Incrementa la unidad
    INCF seg_unidades, F          ; Incrementa la unidad
    
    MOVF seg_unidades, W
    SUBLW D'40'
    BNZ r
    ;BNZ End_Count
    CLRF seg_unidades             ; Resetea si llega a 10
    
    ; Reset unidades, incrementa decenas
    INCF    seg_decenas, F
    INCF    seg_decenas, F
    INCF    seg_decenas, F
    INCF    seg_decenas, F
    
    
    ; ¿Llegó a 6 decenas? (60 segundos)
    MOVF    seg_decenas, W
    SUBLW   D'24'
    BNZ r
    ;BNZ     End_Count
    
    ; Reset segundos, incrementa minutos
    CLRF    seg_decenas
    
    INCF    min_unidades, F
    INCF    min_unidades, F
    INCF    min_unidades, F
    INCF    min_unidades, F
    
    ; ¿Llegó a 10 minutos?
    MOVF    min_unidades, W
    SUBLW   D'40'
    BNZ r
    ;BNZ     End_Count
    
    ; Reset unidades min, incrementa decenas min
    CLRF    min_unidades
    
    INCF    min_decenas, F
    INCF    min_decenas, F
    INCF    min_decenas, F
    INCF    min_decenas, F
    
    
    ; ¿Llegó a 60 minutos? Reset todo
    MOVF    min_decenas, W
    SUBLW   D'24'
    BNZ r
    ;BNZ     End_Count
    CLRF    min_decenas        ; Reset a 00:00
    
r: return 
    
    
End_Count:
    
    ;Muestra El Primer Digito
    call SOSUD ; Multiplexacion Para La Unidad De Segundos
    call Delay_1ms
    MOVF seg_unidades, W   ; WREG = seg_unidades (0-9)
    call Mostrar_Digito
    
    call Delay_1ms
    call Delay_1ms
    call Delay_1ms
    call Delay_1ms
    
    call Test_1
   
    ;Muestra El Segundo Digito
    call SOSTD ; Multiplexacion Para La Unidad De Segundos
    call Delay_1ms
    MOVF seg_decenas, W   ; WREG = seg_unidades (0-9)
    call Mostrar_Digito
    
    call Delay_1ms
    call Delay_1ms
    call Delay_1ms
    call Delay_1ms
    
    call Test_1
    
    ;prueba 4 ms por digito
    
    ;Muestra El Tercer Digito
    call SOMUD ; Multiplexacion Para La Unidad De Segundos
    call Delay_1ms
    MOVF min_unidades, W   ; WREG = seg_unidades (0-9)
    call Mostrar_Digito
    
    call Delay_1ms
    call Delay_1ms
    call Delay_1ms
    call Delay_1ms
    
    call Test_1
    
    ;Muestra El Cuarto Digito
    call SOMTD ; Multiplexacion Para La Unidad De Segundos
    call Delay_1ms
    MOVF min_decenas, W   ; WREG = seg_unidades (0-9)
    call Mostrar_Digito
    
    
    call Delay_1ms
    call Delay_1ms
    call Delay_1ms
    call Delay_1ms
    
    
    call Test_1
    
    
    RETURN

; ==== Visualiza SOLO el dígito de la unidad ====
Mostrar_Digito:
    ; Corregir instruccion 
    ; Utilizar rlncf y cargar alteracion en el registro w
    
    
    ;MOVF seg_unidades, W   ; WREG = seg_unidades (0-9)
    ADDWF PCL, F           ; Tabla de salto directa
    
    GOTO D0
    GOTO D1
    GOTO D2
    GOTO D3
    GOTO D4
    GOTO D5
    GOTO D6
    GOTO D7
    GOTO D8
    GOTO D9

D0: CALL Digit_0
    
    RETURN
D1: CALL Digit_1
    
    RETURN
D2: CALL Digit_2
    
    RETURN
D3: CALL Digit_3
    
    RETURN
D4: CALL Digit_4
    
    RETURN
D5: CALL Digit_5
    
    RETURN
D6: CALL Digit_6
    
    RETURN
D7: CALL Digit_7
    
    RETURN
D8: CALL Digit_8
    
    RETURN
D9: CALL Digit_9
    
    RETURN
    
    end