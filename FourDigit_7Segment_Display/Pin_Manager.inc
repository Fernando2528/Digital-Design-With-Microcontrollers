;#include<P18F4550.inc>

; Pines Para El Control De La Habilitacion Para Los Leds.

#define    LEDA    LATD,0     ; Conexión Terminal A del Display (RD0)
#define    LEDB    LATD,1     ; Conexión Terminal B del Display (RD1)
#define    LEDC    LATD,2     ; Conexión Terminal C del Display (RD2)
#define    LEDD    LATD,3     ; Conexión Terminal D del Display (RD3)
#define    LEDE    LATD,4     ; Conexión Terminal E del Display (RD4)
#define    LEDF    LATD,5     ; Conexión Terminal F del Display (RD5)
#define    LEDG    LATD,6     ; Conexión Terminal G del Display (RD6)
#define    LEDDP   LATD,7     ; Conexión Punto Decimal del Display (RD7)
    
; Pines Para El Control De La Multiplexacion Del Display 

#define  DIG1         LATA,0   ; RA0
#define  DIG2         LATA,1   ; RA1
#define  DIG3         LATA,2   ; RA2
#define  DIG4         LATA,3   ; RA3
    
; Pines Para La Logica Del Boton
    
#define    SW3      PORTB, 2 ; Configuracion Como entrada
#define    SW3T     TRISB, 2 
;#define    SW3A     ANSELB,ANSB2  En pic18f4550 no existen los registros ansel
    
#define LEDT LATA,4 ; Led para pruebas
    
#define PWM2 TRISC, 2        ; RC2 como salida para CCP1
#define PWM1 TRISC, 1        ; RC1 como salida para CCP2 (o usa TRISB, 3 para RB3)
