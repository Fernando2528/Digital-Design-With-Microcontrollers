#define F_CPU 16000000UL
#include <avr/eeprom.h>
#include <stdio.h>
#include "Birthdate.h"
#include "UART.h"
#include "Buzzer.h"

#define EEPROM_BIRTH_DAY    0x00
#define EEPROM_BIRTH_MONTH  0x01
#define EEPROM_BIRTH_YEAR   0x02
#define EEPROM_BIRTH_HOUR   0x03
#define EEPROM_BIRTH_MIN    0x04
#define EEPROM_ALARM_ENABLE 0x05

BirthDate birth_date;
uint8_t alarm_enabled = 1;
uint8_t alarm_triggered = 0;
static char uart_buffer[80];

void Birthdate_Save_To_EEPROM(void) {
    eeprom_write_byte((uint8_t*)EEPROM_BIRTH_DAY,   birth_date.day);
    eeprom_write_byte((uint8_t*)EEPROM_BIRTH_MONTH, birth_date.month);
    eeprom_write_byte((uint8_t*)EEPROM_BIRTH_YEAR,  birth_date.year);
    eeprom_write_byte((uint8_t*)EEPROM_BIRTH_HOUR,  birth_date.hour);
    eeprom_write_byte((uint8_t*)EEPROM_BIRTH_MIN,   birth_date.min);
    eeprom_write_byte((uint8_t*)EEPROM_ALARM_ENABLE, alarm_enabled);
}
void Birthdate_Load_From_EEPROM(void) {
    birth_date.day   = eeprom_read_byte((uint8_t*)EEPROM_BIRTH_DAY);
    birth_date.month = eeprom_read_byte((uint8_t*)EEPROM_BIRTH_MONTH);
    birth_date.year  = eeprom_read_byte((uint8_t*)EEPROM_BIRTH_YEAR);
    birth_date.hour  = eeprom_read_byte((uint8_t*)EEPROM_BIRTH_HOUR);
    birth_date.min   = eeprom_read_byte((uint8_t*)EEPROM_BIRTH_MIN);
    alarm_enabled    = eeprom_read_byte((uint8_t*)EEPROM_ALARM_ENABLE);
    if(birth_date.day == 0xFF || birth_date.day == 0 || birth_date.day>31) {
        birth_date.day = 27; birth_date.month = 11; birth_date.year = 5;
        birth_date.hour = 0; birth_date.min = 0; alarm_enabled = 1;
        Birthdate_Save_To_EEPROM();
    }
}
void Birthdate_Config(void) {
    UART_Write_String("\r\n=== CONFIGURAR FECHA DE NACIMIENTO ===\r\n");
    UART_Write_String("Dia de nacimiento (01-31): ");
    birth_date.day   = UART_Read_Number();
    UART_Write_String("Mes de nacimiento (01-12): ");
    birth_date.month = UART_Read_Number();
    UART_Write_String("Anio de nacimiento (00-99): ");
    birth_date.year  = UART_Read_Number();
    UART_Write_String("Hora de nacimiento (00-23): ");
    birth_date.hour  = UART_Read_Number();
    UART_Write_String("Minuto de nacimiento (00-59): ");
    birth_date.min   = UART_Read_Number();
    Birthdate_Save_To_EEPROM();

    UART_Write_String("\r\n*** Fecha de nacimiento guardada! ***\r\n");
    sprintf(uart_buffer, "Nacimiento: %02d/%02d/20%02d %02d:%02d\r\n\r\n",
            birth_date.day, birth_date.month, birth_date.year,
            birth_date.hour, birth_date.min);
    UART_Write_String(uart_buffer);
}
void Birthdate_Display_Info(const DateTime *current) {
    uint8_t age = Calculate_Age();
    UART_Write_String("\r\n=== INFORMACION ALMACENADA ===\r\n\r\n");
    UART_Write_String("Fecha/Hora Actual:\r\n");
    Display_DateTime(current);
    sprintf(uart_buffer, "\r\nFecha de Nacimiento: %02d/%02d/20%02d %02d:%02d\r\n",
        birth_date.day, birth_date.month, birth_date.year, birth_date.hour, birth_date.min);
    UART_Write_String(uart_buffer);
    sprintf(uart_buffer, "Edad Actual: %d anos\r\n", age);
    UART_Write_String(uart_buffer);
    sprintf(uart_buffer, "Proximo Cumpleanos: %02d/%02d/20%02d %02d:%02d\r\n",
        birth_date.day, birth_date.month, current->year, birth_date.hour, birth_date.min);
    UART_Write_String(uart_buffer);
    UART_Write_String("\r\nEstado de Alarma: ");
    UART_Write_String(alarm_enabled ? "HABILITADA\r\n" : "DESHABILITADA\r\n");
    if(alarm_triggered) UART_Write_String("Alarma ya sono hoy!\r\n");
    UART_Write_String("\r\n");
}
uint8_t Calculate_Age(void) {
    extern DateTime current_time;
    uint8_t age = current_time.year - birth_date.year;
    if(current_time.month < birth_date.month ||
       (current_time.month == birth_date.month && current_time.date < birth_date.day))
        age--;
    return age;
}
void Check_Alarm(const DateTime *current) {
    if(!alarm_enabled || alarm_triggered) return;
    if(current->date == birth_date.day && current->month == birth_date.month) {
        alarm_triggered = 1;
        uint8_t age = Calculate_Age();
        UART_Write_String("\r\n*** FELIZ CUMPLEAÑOS ***\r\n");
        sprintf(uart_buffer, "¡Cumples %d años!\r\n", age);
        UART_Write_String(uart_buffer);
        Play_Birthday_Melody();
        UART_Write_String("Melodia finalizada.\r\nUsa 'R' para reiniciar alarma.\r\n\r\n");
    }
}
