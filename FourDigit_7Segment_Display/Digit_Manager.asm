#include<P18F4550.inc>
#include"Digit_Manager.inc"
    
    global Test_1
    global Test_0
    
    global Digit_0
    global Digit_1
    global Digit_2
    global Digit_3
    global Digit_4
    global Digit_5
    global Digit_6
    global Digit_7
    global Digit_8
    global Digit_9
    
    global SOSUD
    global SOSTD
    global SOMUD
    global SOMTD
    
    
; En este archivo se alojara la logica que permitira ilustrar los digitos requeridos en el display 
	
Digitd  udata
  
Digit_ code
 
Test_1: ; esta funcion simplemente encendera todos los leds para probar que las conexiones esten bien 
		
	BSF LEDA
	BSF LEDB
	BSF LEDC
	BSF LEDD
	BSF LEDE
	BSF LEDF
	BSF LEDG
	BSF LEDDP
    
	return 
	
Test_0:
    
    BCF LEDA
    BCF LEDB
    BCF LEDC
    
    BCF LEDD
    BCF LEDE
    BCF LEDF
    BCF LEDG
    BCF LEDDP
    
    
    return
	
Digit_0:
    
    BCF LEDA
    BCF LEDB
    BCF LEDC
    BCF LEDD
    BCF LEDE
    BCF LEDF
    
    BSF LEDG
    
    return 
    
Digit_1:
    
    BCF LEDB
    BCF LEDC
    
    BSF LEDA
    BSF LEDD
    BSF LEDE
    BSF LEDF
    
    BSF LEDG
    
    return 
    
Digit_2:
        
    BCF LEDA
    BCF LEDB
    BCF LEDG
    BCF LEDE 
    BCF LEDD
    
    BSF LEDC
    BSF LEDF
    
    return
    
Digit_3:
    
    BCF LEDA
    BCF LEDB
    BCF LEDC
    BCF LEDD
    BCF LEDG
    
    BSF LEDE
    BSF LEDF
    
    return

    
Digit_4:
    
    BCF LEDB
    BCF LEDC
    BCF LEDG
    BCF LEDF
    
    BSF LEDA
    BSF LEDD
    BSF LEDE
    
    return 
    
Digit_5:
    
    BCF LEDA
    BCF LEDF
    BCF LEDG
    BCF LEDC
    BCF LEDD
    
    BSF LEDB
    BSF LEDE
    
    return
    
Digit_6:
    
    BCF LEDF
    BCF LEDG
    BCF LEDC
    BCF LEDD
    BCF LEDE
    
    BSF LEDA
    BSF LEDB
    
    return
    
Digit_7:
    
    BCF LEDA
    BCF LEDB
    BCF LEDC
    BCF LEDG
    
    BSF LEDD
    BSF LEDE
    BSF LEDF
    
    return
    
Digit_8:
    
    BCF LEDA
    BCF LEDB
    BCF LEDC
    BCF LEDD
    
    BCF LEDE
    BCF LEDF
    BCF LEDG
    
    return
    
Digit_9:
  
    BCF LEDA
    BCF LEDB
    BCF LEDC
    BCF LEDF
    BCF LEDG
    
    BSF LEDD
    BSF LEDE
    
    return
    
SOSUD: ; Set On Second Unit Digit
    
    CLRB DIG1
    CLRB DIG2
    CLRB DIG3
    SETB DIG4
    
    return 
    
SOSTD: ; Set On Second Ten Digit
    
    CLRB DIG1
    CLRB DIG2
    SETB DIG3
    CLRB DIG4
    
    
    return
    
SOMUD: ; Set On Minut Unit Digit
    
    CLRB DIG1
    SETB DIG2
    CLRB DIG3
    CLRB DIG4
    
    return 
    
SOMTD: ; Set On Minute Ten Digit
    
    SETB DIG1
    CLRB DIG2
    CLRB DIG3
    CLRB DIG4
    
    return


    end 
    
