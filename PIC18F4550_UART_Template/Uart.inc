;#include<p18f4550.inc>


#define baudrate .9600
    
#define  spbrghl .207 
#define spbrgh_ spbrghl>>8
#define spbrgl_  spbrghl & 0xFF
    
;#define spbrghl 0x1A0
;#define spbrgh_ spbrghl >> 8
;#define spbrgl_ spbrghl & 0xFF