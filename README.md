# Digital-Design-With-Microcontrollers.

This repository showcases microcontroller projects developed for the Digital Design with Microcontrollers course, demonstrating core embedded systems concepts using PIC and AVR families. Projects range from basic LED persistence displays and 7-segment interfaces to advanced multi-processor ring networks with UART communication, sensor fusion, data validation, and scalable architectures.

## Repository Structure.

- LED_Persistence_Display: Uses LED visual persistence to create floating numeric displays in air, applicable to light art and motion-based signage .

- FourDigit_7Segment_Display: Assembly-based 4-digit display multiplexing for compact numerical output in clocks and meters .

- TemperatureData_Processing_And_Transmission: PIC18F4550 assembly project for sensor data validation, checksum generation, and packet transmission .

- PIC_UART_StudentData_Exchange: UART communication between PIC16F88/887 for student data block assembly.

- PIC18F4550_UART_Template: Reusable UART configuration template for PIC18F4550 in assembly.

- PIC18F4550_ADC_Pin_Test: XC8-based ADC pin functionality test for analog signal processing.

- PIC_ATMEGA_ADC_PWM_LED_Control: PIC18F4550 + ATmega328P UART-linked ADC-to-PWM LED control with data block exchange.

- BirthdayAlarm_RTC_System: ATmega328P avr-gcc birthday alarm with DS1307 RTC, EEPROM, buzzer melody, and serial menu.

- MultiMCU_SensorRing_Network: 3-MCU ring (ATmega328P/AVR, PIC18F4550/XC8, PIC16F628A/asm) with sensor fusion, RTC, checksums, and ESP32 Bluetooth test mode.

- Scalable_MultiMCU_SensorRing: Extends ring network for external MCU blocks with variable-length data framing.

## Key Technologies.

All projects emphasize low-level programming (assembly, XC8, avr-gcc), UART protocols, ADC/PWM control, RTC integration, and data integrity—building progressively from single-MCU demos to distributed networks suitable for IoT and industrial applications.


## Software Tools Used To Develop This Project.

### MPLABX (V 5.20)
- XC8 (V 2.36)
- AVR (V 5.4.0)
  
### Proteus (V 8.13)
