#include <Arduino.h>
#line 1 "C:\\Users\\Benutzer1\\Documents\\# Github repositories\\UART\\UART--Blink\\UART--Blink.ino"
/************************************************************************************************************
 🔹 SLAVE RP2040-Zero: CONTROL DE LED VIA UART DESDE PICO 🔹
  - Recibe comandos UART desde un Raspberry Pi Pico.
  - Comando esperado: "bLINK:<tiempo_ms>" → parpadea el LED 3 veces con retardo indicado.
  - Envía mensajes de estado de Led: "LED ON", "LED OFF" y "DONE".
  - Comunicación bidireccional usando Serial1 (TX=GPIO0, RX=GPIO1) y Serial USB para debug.
  - Ideal para pruebas de comunicación UART entre RP2040.
  K. Michalsky – 11.2025
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

 LED externo:
   Ánodo (+)  → GPIO8
   Cátodo (–) → GND

------------------------------------------------------------
 Configuración de pines usada:
   UART TX = GPIO0
   UART RX = GPIO1
   LED     = GPIO8
   Baudrate = 115200
------------------------------------------------------------
*************************************************************************************************************/

#define LED_PIN 2

#line 40 "C:\\Users\\Benutzer1\\Documents\\# Github repositories\\UART\\UART--Blink\\UART--Blink.ino"
void setup();
#line 60 "C:\\Users\\Benutzer1\\Documents\\# Github repositories\\UART\\UART--Blink\\UART--Blink.ino"
void loop();
#line 40 "C:\\Users\\Benutzer1\\Documents\\# Github repositories\\UART\\UART--Blink\\UART--Blink.ino"
void setup()
{
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  // Debug por USB (monitor del PC)
  Serial.begin(115200); // Monitor serie USB a 115200bps
  // Serial puede usarse para imprimir mensajes para depuración:
  // Serial.println("Iniciando...");

  // Mapeo del UART hardware que usaremos para comunicar con el Pico.
  // Forzamos Serial1 a usar GPIO0 como TX y GPIO1 como RX,
  // que corresponden a los pines físicos donde hemos conectado los cables.
  Serial1.setTX(0); // asigna TX de Serial1 a GPIO0
  Serial1.setRX(1); // asigna RX de Serial1 a GPIO1

  // Inicializamos el UART para la comunicación entre placas
  Serial1.begin(115200);    // UART en GPIO0/GPIO1 a 115200 bps
  Serial1.println("READY"); // opcional: decirle al Pico que estamos listos
}

void loop()
{
  if (Serial1.available())
  {
    // Aquí el Zero lee todos los caracteres recibidos hasta encontrar un salto de línea \n.
    // El resultado (todo el texto antes del salto) se guarda en la variable msg. msg = "BLINK:500"
    // msg.trim() Elimina espacios o saltos de línea sobrantes al inicio o al final del texto.
    // Así, si por error llega " BLINK:500 " → se limpia a "BLINK:500".
    String msg = Serial1.readStringUntil('\n');
    msg.trim();
    Serial.print("Comando recibido: ");
    Serial.println(msg);

    if (msg.startsWith("BLINK:"))
    {
      // Toma lo que viene después de “BLINK:” (desde el carácter 6 en adelante) y lo convierte a número entero.
      int delayTime = msg.substring(6).toInt(); //

      for (int i = 0; i < 3; i++)
      {
        digitalWrite(LED_PIN, HIGH);
        Serial1.println("LED ON");
        Serial.println("LED ON");
        delay(delayTime);

        digitalWrite(LED_PIN, LOW);
        Serial1.println("LED OFF");
        Serial.println("LED OFF");
        delay(delayTime);
      }

      Serial1.println("DONE");
      Serial.println("DONE");
    }
  }
}

