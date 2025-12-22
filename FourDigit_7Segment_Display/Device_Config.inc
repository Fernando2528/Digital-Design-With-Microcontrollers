;#include <p18f4550.inc> 

; CONFIG1L
    CONFIG  PLLDIV = 1        ; Valor depende del oscilador externo: 1=4MHz, 2=8MHz, 3=12MHz, 5=20MHz (consultar hardware real)
    CONFIG  CPUDIV = OSC1_PLL2 ; Modo de división para el CPU (CPU System Clock Postscaler)
    CONFIG  USBDIV = 2        ; USB clock selection (divide by 2 desde PLL, típicamente necesario para USB)
    
; CONFIG1H
    CONFIG  FOSC = INTOSCIO_EC ; Oscilador interno modo IO (ajusta según el uso real)
    CONFIG  FCMEN = OFF       ; Fail-Safe monitor OFF
    CONFIG  IESO = OFF        ; Oscillator Switchover OFF

; CONFIG2L
    CONFIG  PWRT = OFF        ; Power-up Timer OFF
    CONFIG  BOR = OFF         ; Brown-out Reset OFF
    CONFIG  VREGEN = ON       ; USB voltage regulator ON si usas USB

; CONFIG2H
    CONFIG  WDT = OFF         ; Watchdog Timer OFF
    CONFIG  WDTPS = 32768     ; Postscaler

; CONFIG3H
    CONFIG  CCP2MX = ON   ; CCP2 multiplexado en PORTBE (o PORTC según diseño)
    CONFIG  PBADEN = OFF      ; PORTB como digital al reset
    CONFIG  LPT1OSC = OFF     ; Timer1 osc baja potencia
    CONFIG  MCLRE = ON        ; MCLR habilitado

; CONFIG4L
    CONFIG  STVREN = ON       ; Stack overflow/underflow reset
    CONFIG  LVP = OFF         ; Low-voltage programming OFF
    CONFIG  ICPRT = OFF       ; Puerto programación dedicado OFF
    CONFIG  XINST = OFF       ; Instruction set extendido OFF

; CONFIG5L
    CONFIG  CP0 = OFF
    CONFIG  CP1 = OFF
    CONFIG  CP2 = OFF
    CONFIG  CP3 = OFF

; CONFIG5H
    CONFIG  CPB = OFF
    CONFIG  CPD = OFF

; CONFIG6L
    CONFIG  WRT0 = OFF
    CONFIG  WRT1 = OFF
    CONFIG  WRT2 = OFF
    CONFIG  WRT3 = OFF

; CONFIG6H
    CONFIG  WRTC = OFF
    CONFIG  WRTB = OFF
    CONFIG  WRTD = OFF

; CONFIG7L
    CONFIG  EBTR0 = OFF
    CONFIG  EBTR1 = OFF
    CONFIG  EBTR2 = OFF
    CONFIG  EBTR3 = OFF

; CONFIG7H
    CONFIG  EBTRB = OFF


