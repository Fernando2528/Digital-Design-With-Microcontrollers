// config_bits.c
// Poner los #pragma config en un .c separado (o al inicio de main.c).

#include <xc.h>

//================ CONFIG BITS =================
#pragma config FOSC = INTOSCIO_EC
#pragma config PWRT = ON
#pragma config BOR  = ON
#pragma config WDT  = OFF
#pragma config MCLRE = ON
#pragma config LVP  = OFF
#pragma config CPD  = OFF
#pragma config CP0  = OFF

