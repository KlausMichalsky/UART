#line 1 "C:\\Users\\Benutzer1\\Documents\\# Github repositories\\UART\\UART--Command\\UART--Command.ino"
// ========================================================================
//               🔸 U A R T  -  C O M M A N D  ( S C A R A )🔸
// ========================================================================
//  Archivo    : UART_Command.ino
//  Autor      : Klaus Michalsky
//  Fecha      : Feb-2026
//
//  DESCRIPCION
//  -----------------------------------------------------------------------
//  - Recibe comandos UART desde un Raspberry Pi Pico.
//  - Comandos esperados: "HOME" → inicia homing, "STATUS" → responde estado.
//  - Envía mensajes de estado: "HOMING_STARTED", "READY".
//  - Comunicación bidireccional usando Serial1 (TX=GPIO0, RX=GPIO1) y Serial USB para debug.
//  - Ideal para pruebas de comunicación UART entre RP2040 y Pico.
/*

//  HARDWARE
//  -----------------------------------------------------------------------
//  MCU     : RP2040-Zero Y Raspberry Pi Pico

 Esquema de conexiones UART y alimentación / Baudrate = 115200:
//  -----------------------------------------------------------------------

 ┌──────────────┐                      ┌──────────────────┐
 │ Raspberry Pi │                      │ RP2040 Zero      │
 │     Pico     │                      │ (Arduino C++)    │
 ├──────────────┤                      ├──────────────────┤
 │ GP0 (TX0) ───────────────▶ GP1 (RX0)│
 │ GP1 (RX0) ◀─────────────── GP0 (TX0)│
 │ GND ─────────────────────── GND      │
 │ VBUS (5V) ───────────────── VBUS (5V)│
 └──────────────┘                      └──────────────────┘

 //  ESTADO
//  -----------------------------------------------------------------------
//  ✅ Funcional
// ========================================================================
*/

#include <Arduino.h>

#line 42 "C:\\Users\\Benutzer1\\Documents\\# Github repositories\\UART\\UART--Command\\UART--Command.ino"
void setup();
#line 53 "C:\\Users\\Benutzer1\\Documents\\# Github repositories\\UART\\UART--Command\\UART--Command.ino"
void loop();
#line 42 "C:\\Users\\Benutzer1\\Documents\\# Github repositories\\UART\\UART--Command\\UART--Command.ino"
void setup()
{
    // USB para debug (opcional)
    Serial.begin(115200);

    // UART hardware en pines 0 y 1
    Serial1.setTX(0);
    Serial1.setRX(1);
    Serial1.begin(115200);
}

void loop()
{
    if (Serial1.available())
    {
        String cmd = Serial1.readStringUntil('\n');
        cmd.trim();

        if (cmd == "HOME")
        {
            Serial1.println("HOMING_STARTED");
        }
        else if (cmd == "STATUS")
        {
            Serial1.println("READY");
        }
    }
}

