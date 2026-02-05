/************************************************************************************************************
 🔹 SLAVE RP2040-Zero: CONTROL DE ROBOT VIA UART DESDE PICO 🔹
  - Recibe comandos UART desde un Raspberry Pi Pico.
  - Comandos esperados: "HOME" → inicia homing, "STATUS" → responde estado.
  - Envía mensajes de estado: "HOMING_STARTED", "READY".
  - Comunicación bidireccional usando Serial1 (TX=GPIO0, RX=GPIO1) y Serial USB para debug.
  - Ideal para pruebas de comunicación UART entre RP2040 y Pico.
  K. Michalsky – 05.02.2026
*************************************************************************************************************/

/************************************************************************************************************

 Esquema de conexiones UART y alimentación:

 ┌──────────────┐                      ┌──────────────────┐
 │ Raspberry Pi │                      │ RP2040 Zero      │
 │     Pico     │                      │ (Arduino C++)    │
 ├──────────────┤                      ├──────────────────┤
 │ GP0 (TX0) ───────────────▶ GP1 (RX0)│
 │ GP1 (RX0) ◀─────────────── GP0 (TX0)│
 │ GND ─────────────────────── GND      │
 │ VBUS (5V) ───────────────── VBUS (5V)│
 └──────────────┘                      └──────────────────┘

------------------------------------------------------------
 Configuración de pines usada:
   UART TX = GPIO0
   UART RX = GPIO1
   Baudrate = 115200
------------------------------------------------------------
*************************************************************************************************************/

#include <Arduino.h>

// DEFINICIÓN DE LA UART DE COMUNICACIÓN
// =======================================================================
#if defined(ARDUINO_ARCH_RP2040)
#define CMD_SERIAL Serial1
#else
#define CMD_SERIAL Serial
#endif

// CONFIGURACIÓN DE DEPURACIÓN UART
// =======================================================================
#define DEBUG_UART 1 // cambiar a 0 cuando el codigo esta listo

// PROTOTIPOS
// =======================================================================
void UART_Init();
bool commandAvailable();
String receiveCommand();
void processCommand(const String &cmd);

void setup()
{
    UART_Init();

#if DEBUG_UART
    Serial.println("Sistema listo -> Ingresar comando...");
#endif
}

void loop()
{
    if (commandAvailable())
    {
        String cmd = receiveCommand();
        processCommand(cmd);
    }
}

// INICIALIZACIÓN DE COMUNICACIÓN UART
// =======================================================================
void UART_Init()
{
#if DEBUG_UART
    Serial.begin(115200);
    unsigned long start = millis();
    while (!Serial && millis() - start < 1000)
    {
        // espera segura
    }
    Serial.println("Debug UART lista!");
#endif

#if defined(ARDUINO_ARCH_RP2040)
    CMD_SERIAL.setTX(0);
    CMD_SERIAL.setRX(1);
#endif

    CMD_SERIAL.begin(115200);
}

// COMPROBACIÓN DE COMANDOS DISPONIBLES
// =======================================================================
bool commandAvailable()
{
    return CMD_SERIAL.available() > 0;
}

// LEER COMANDOS
// =======================================================================
String receiveCommand()
{
    String cmd = CMD_SERIAL.readStringUntil('\n');
    cmd.trim();
    return cmd;
}

// PROCESAMIENTO DE COMANDOS
// =======================================================================
void processCommand(const String &cmd)
{
    if (cmd == "HOME")
    {
        CMD_SERIAL.println("HOMING_STARTED");
        // arrancar homing acá
    }
    else if (cmd == "STATUS")
    {
        CMD_SERIAL.println("READY");
    }
}
