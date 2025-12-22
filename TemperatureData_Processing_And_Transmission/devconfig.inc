;#include <p18f4550.inc>

; CONFIG1L
  CONFIG  PLLDIV = 1            ; PLL Prescaler Selection bits
  CONFIG  CPUDIV = OSC1_PLL2    ; System Clock Postscaler Selection bits
  CONFIG  USBDIV = 1            ; USB Clock Selection bit

; CONFIG1H
  CONFIG  FOSC = INTOSCIO_EC    ; Internal oscillator, port function on RA6
  CONFIG  FCMEN = OFF           ; Fail-Safe Clock Monitor disabled
  CONFIG  IESO = OFF            ; Oscillator Switchover mode disabled

; CONFIG2L
  CONFIG  PWRT = ON             ; Power-up Timer enabled
  CONFIG  BOR = ON              ; Brown-out Reset enabled
  CONFIG  BORV = 3              ; Brown-out Reset Voltage (Minimum 2.05V)
  CONFIG  VREGEN = OFF          ; USB voltage regulator disabled

; CONFIG2H
  CONFIG  WDT = OFF             ; WDT disabled
  CONFIG  WDTPS = 32768         ; Watchdog Timer Postscale (1:32768)

; CONFIG3H
  CONFIG  CCP2MX = ON           ; CCP2 input/output multiplexed with RC1
  CONFIG  PBADEN = OFF          ; PORTB<4:0> pins digital (not analog)
  CONFIG  LPT1OSC = OFF         ; Timer1 higher power operation
  CONFIG  MCLRE = ON            ; MCLR pin enabled

; CONFIG4L
  CONFIG  STVREN = ON           ; Stack full/underflow will cause Reset
  CONFIG  LVP = ON              ; Single-Supply ICSP enabled
  CONFIG  ICPRT = OFF           ; ICPORT disabled
  CONFIG  XINST = OFF           ; Legacy mode (no extended instructions)

; CONFIG5L
  CONFIG  CP0 = OFF             ; Block 0 not code-protected
  CONFIG  CP1 = OFF             ; Block 1 not code-protected
  CONFIG  CP2 = OFF             ; Block 2 not code-protected
  CONFIG  CP3 = OFF             ; Block 3 not code-protected

; CONFIG5H
  CONFIG  CPB = OFF             ; Boot block not code-protected
  CONFIG  CPD = OFF             ; Data EEPROM not code-protected

; CONFIG6L
  CONFIG  WRT0 = OFF            ; Block 0 not write-protected
  CONFIG  WRT1 = OFF            ; Block 1 not write-protected
  CONFIG  WRT2 = OFF            ; Block 2 not write-protected
  CONFIG  WRT3 = OFF            ; Block 3 not write-protected

; CONFIG6H
  CONFIG  WRTC = OFF            ; Configuration registers not write-protected
  CONFIG  WRTB = OFF            ; Boot block not write-protected
  CONFIG  WRTD = OFF            ; Data EEPROM not write-protected

; CONFIG7L
  CONFIG  EBTR0 = OFF           ; Block 0 not protected from table reads
  CONFIG  EBTR1 = OFF           ; Block 1 not protected from table reads
  CONFIG  EBTR2 = OFF           ; Block 2 not protected from table reads
  CONFIG  EBTR3 = OFF           ; Block 3 not protected from table reads

; CONFIG7H
  CONFIG  EBTRB = OFF           ; Boot block not protected from table reads


CBLOCK 0x000
    W_TEMP
    STATUS_TEMP 
    BSR_TEMP
    CONTADOR_RETARDO
    TMR0H_AUX
    TMR0L_AUX
ENDC
