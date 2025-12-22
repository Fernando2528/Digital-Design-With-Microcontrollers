// PIC18F4550 Configuration Bit Settings
// CONFIG1L
#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1)

// CONFIG1H
#pragma config FOSC = INTOSCIO_EC    // Oscillator Selection bits (Internal oscillator, port function on RA6, EC used by USB (INTIO))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit
#pragma config BOR = ON         // Brown-out Reset Enable bits
#pragma config BORV = 3         // Brown-out Reset Voltage bits
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit
#pragma config MCLRE = ON       // MCLR Pin Enable bit

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit
#pragma config XINST = OFF      // Extended Instruction Set Enable bit
#pragma config DEBUG = OFF      // Background Debug

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit
#pragma config CP1 = OFF        // Code Protection bit
#pragma config CP2 = OFF        // Code Protection bit
#pragma config CP3 = OFF        // Code Protection bit

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit
#pragma config CPD = OFF        // Data EEPROM Code Protection bit

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit
#pragma config WRT1 = OFF       // Write Protection bit
#pragma config WRT2 = OFF       // Write Protection bit
#pragma config WRT3 = OFF       // Write Protection bit

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit
#pragma config WRTB = OFF       // Boot Block Write Protection bit
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit
#pragma config EBTR1 = OFF      // Table Read Protection bit
#pragma config EBTR2 = OFF      // Table Read Protection bit
#pragma config EBTR3 = OFF      // Table Read Protection bit

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit

#include <xc.h>
#define _XTAL_FREQ 8000000      // Definir frecuencia de oscilador a 8MHz

// Función para inicializar el ADC
void ADC_Init(void) {
    // Configurar AN0 como entrada analógica
    TRISAbits.TRISA0 = 1;       // RA0 como entrada
    
    // ADCON1: Configurar voltaje de referencia y pines analógicos
    ADCON1bits.VCFG1 = 0;       // Vref- = VSS (0V)
    ADCON1bits.VCFG0 = 0;       // Vref+ = VDD (5V)
    ADCON1bits.PCFG3 = 1;       // AN0 como analógico
    ADCON1bits.PCFG2 = 1;       // Resto digitales
    ADCON1bits.PCFG1 = 1;
    ADCON1bits.PCFG0 = 0;       // Configuración 1110 = solo AN0 analógico
    
    // ADCON2: Configurar formato de resultado y tiempos
    ADCON2bits.ADFM = 1;        // Resultado justificado a la derecha
    ADCON2bits.ACQT2 = 0;       // Tiempo de adquisición = 2 TAD
    ADCON2bits.ACQT1 = 0;
    ADCON2bits.ACQT0 = 1;
    ADCON2bits.ADCS2 = 0;       // TAD = FOSC/32
    ADCON2bits.ADCS1 = 1;
    ADCON2bits.ADCS0 = 0;
    
    // ADCON0: Seleccionar canal y encender el ADC
    ADCON0bits.CHS3 = 0;        // Seleccionar canal AN0
    ADCON0bits.CHS2 = 0;
    ADCON0bits.CHS1 = 0;
    ADCON0bits.CHS0 = 0;
    ADCON0bits.ADON = 1;        // Encender módulo ADC
    
    __delay_us(20);             // Tiempo de estabilización
}

// Función para leer el ADC
unsigned int ADC_Read(void) {
    __delay_us(20);             // Tiempo de adquisición
    ADCON0bits.GO = 1;          // Iniciar conversión
    while(ADCON0bits.GO);       // Esperar a que termine la conversión
    return ((ADRESH << 8) + ADRESL);  // Retornar resultado de 10 bits
}

// Función para inicializar el UART
void UART_Init(void) {
    // Configurar pines TX y RX
    TRISCbits.TRISC6 = 0;       // RC6/TX como salida
    TRISCbits.TRISC7 = 1;       // RC7/RX como entrada
    
    // Configurar UART a 9600 baudios con FOSC = 8MHz
    TXSTAbits.SYNC = 0;         // Modo asíncrono
    TXSTAbits.BRGH = 0;         // Baja velocidad
    BAUDCONbits.BRG16 = 0;      // Generador de 8 bits
    
    // SPBRG = ((FOSC/64)/BAUD) - 1 = ((8000000/64)/9600) - 1 = 12
    SPBRG = 12;                 // Valor para 9600 baudios
    
    // Habilitar transmisión y recepción
    TXSTAbits.TXEN = 1;         // Habilitar transmisión
    RCSTAbits.SPEN = 1;         // Habilitar puerto serial
    RCSTAbits.CREN = 1;         // Habilitar recepción continua
}

// Función para transmitir un byte por UART
void UART_Write(unsigned char data) {
    while(!TXSTAbits.TRMT);     // Esperar a que el buffer esté vacío
    TXREG = data;               // Enviar dato
}

// Función para transmitir una cadena por UART
void UART_Write_Text(char *text) {
    int i;
    for(i = 0; text[i] != '\0'; i++) {
        UART_Write(text[i]);
    }
}

// Función para convertir número a cadena
void Int_to_String(unsigned int num, char *str) {
    sprintf(str, "%u", num);
}

void main(void) {
    unsigned int adc_value;
    float voltage;
    char buffer[20];
    
    // Configurar oscilador interno a 8MHz
    OSCCONbits.IRCF2 = 1;       // 111 = 8MHz
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 1;
    OSCCONbits.SCS1 = 1;        // Usar oscilador interno
    OSCCONbits.SCS0 = 0;
    
    // Inicializar módulos
    ADC_Init();                 // Inicializar ADC
    UART_Init();                // Inicializar UART
    
    __delay_ms(100);            // Espera inicial
    
    UART_Write_Text("Sistema iniciado\r\n");
    
    while(1) {
        // Leer valor del ADC (0-1023 para 10 bits)
        adc_value = ADC_Read();
        
        // Convertir a voltaje (0-5V)
        voltage = (adc_value * 5.0) / 1023.0;
        
        // Enviar valor digital del ADC
        UART_Write_Text("ADC: ");
        sprintf(buffer, "%u", adc_value);
        UART_Write_Text(buffer);
        
        // Enviar valor de voltaje
        UART_Write_Text(" | Voltaje: ");
        sprintf(buffer, "%.2fV\r\n", voltage);
        UART_Write_Text(buffer);
        
        __delay_ms(500);        // Esperar 500ms entre lecturas
    }
    
    return;
}
