#include "RTC.h"
#include "UART.h"
#include "Buzzer.h"
#include "Birthdate.h"
#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL


DateTime current_time;

void System_Init(void) {
    Buzzer_Init();
    DDRD &= ~(1 << PD0);   // RX
    DDRD |=  (1 << PD1);   // TX
}

void Show_Main_Menu(void) {
    UART_Write_String("\r\n=== MENU PRINCIPAL ===\r\n");
    UART_Write_String("  1. Modo Normal (Monitoreo de alarma)\r\n");
    UART_Write_String("  2. Configurar Fecha/Hora Actual\r\n");
    UART_Write_String("  3. Configurar Fecha de Nacimiento\r\n");
    UART_Write_String("  4. Ver Informacion\r\n");
    UART_Write_String("  5. Modo Prueba (Probar melodia)\r\n");
    UART_Write_String("  E. Habilitar/Deshabilitar Alarma\r\n");
    UART_Write_String("  R. Reiniciar Alarma\r\n");
    UART_Write_String("Selecciona una opcion: ");
}

void Config_Current_Time(void) {
    DateTime temp_dt;
    UART_Write_String("\r\n=== CONFIGURAR FECHA/HORA ACTUAL ===\r\n");
    UART_Write_String("Dia (01-31): ");
    temp_dt.date = UART_Read_Number();
    UART_Write_String("Mes (01-12): ");
    temp_dt.month = UART_Read_Number();
    UART_Write_String("Anio (00-99): ");
    temp_dt.year = UART_Read_Number();
    UART_Write_String("Hora (00-23): ");
    temp_dt.hour = UART_Read_Number();
    UART_Write_String("Minuto (00-59): ");
    temp_dt.min = UART_Read_Number();
    UART_Write_String("Segundo (00-59): ");
    temp_dt.sec = UART_Read_Number();
    temp_dt.day = 1; // puedes ajustar el día de semana si lo quieres usar
    RTC_Set_DateTime(&temp_dt);
    UART_Write_String("*** Fecha/hora configurada! ***\r\n");
    Display_DateTime(&temp_dt);
    _delay_ms(2000);
    Show_Main_Menu();
}

void Process_UART_Command(void) {
    static char command_buffer[10];
    static uint8_t buffer_index = 0;
    char c = UART_Read_NoWait();
    if(c == 0) return;
    UART_Write(c);

    if(c == '\r' || c == '\n') {
        UART_Write_String("\r\n");
        if(buffer_index > 0) {
            char cmd = command_buffer[0];
            switch(cmd) {
                case '1': Show_Main_Menu(); break;
                case '2': Config_Current_Time(); break;
                case '3': Birthdate_Config(); Show_Main_Menu(); break;
                case '4': Birthdate_Display_Info(&current_time); Show_Main_Menu(); break;
                case '5':
                    UART_Write_String("Reproduciendo melodia...\r\n");
                    Play_Birthday_Melody();
                    UART_Write_String("Prueba finalizada.\r\n\r\n");
                    Show_Main_Menu(); break;
                case 'E': case 'e':
                    alarm_enabled = !alarm_enabled;
                    Birthdate_Save_To_EEPROM();
                    UART_Write_String(alarm_enabled ? "Alarma HABILITADA\r\n" : "Alarma DESHABILITADA\r\n");
                    Show_Main_Menu(); break;
                case 'R': case 'r':
                    alarm_triggered = 0;
                    Buzzer_Off();
                    UART_Write_String("*** Alarma reiniciada ***\r\n");
                    Show_Main_Menu(); break;
                default:
                    UART_Write_String("Opcion no valida\r\n"); Show_Main_Menu(); break;
            }
            buffer_index = 0;
        }
    } else if(c == 8 || c == 127) {
        if(buffer_index > 0) { buffer_index--; UART_Write_String(" \b"); }
    } else if(buffer_index < 9) {
        command_buffer[buffer_index++] = c;
        command_buffer[buffer_index] = '\0';
    }
}

int main(void) {
    System_Init();
    _delay_ms(500);
    I2C_Init();
    _delay_ms(100);
    UART_Init();
    _delay_ms(200);
    Birthdate_Load_From_EEPROM();
    Show_Main_Menu();

    while(1) {
        RTC_Get_DateTime(&current_time);
        Check_Alarm(&current_time);
        if(UART_Data_Ready()) Process_UART_Command();
        _delay_ms(100);
    }
}
