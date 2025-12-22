;#include <p18f25k50.inc>

; reset vector
resetvec EQU 0000h  ;0x0000       .10

 ;high priority interrupt
 
hintvec EQU 0x0008
 
 ;low priority interrupt
 
lointvec EQU 0x0018



