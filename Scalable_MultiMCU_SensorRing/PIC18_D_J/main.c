// ============================================================
// PIC18F4550 - NODO (SIMULACIÓN) RX/TX BATCH MINIMO
// RX UART (ISR + ring) -> guarda SOLO 2 tramas k...P
// Cuando hay 2 tramas:
//   1) reenvía esas 2 (FIFO)
//   2) genera su propia trama k...P (MPU6050 + DS1307 + Hash XOR + PoW)
//   3) limpia y vuelve a esperar
//
// DS1307: RB0(RSDA)/RB1(SCL)  (bit-bang)
// MPU6050: RD0(SDA)/RD1(SCL)  (bit-bang)
// BUZZER: RD2 (opcional, aquí no se usa)
// ============================================================

// V1 Version Funcional Sin Modular
//V2 Version Modular 

#include "app_config.h"   // <-- IMPORTANTE: trae __delay_ms/__delay_us

#include "system.h"
#include "uart_rb.h"
#include "node_app.h"

void main(void) {
    SystemInit();
    __delay_ms(300);

    UART_WriteString("\r\n=== PIC18F4550 NODO RX 2x(k...P) + TX own(k...P) ===\r\n");

    NodeApp_Init();

    while(1) {
        NodeApp_Task();
    }
}
