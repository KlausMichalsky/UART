#include <Arduino.h>
#line 1 "C:\\Users\\Benutzer1\\Documents\\# Github repositories\\UART\\UART--Blink_Nano\\UART--Blink_Nano.ino"
/************************************************************************************************************
 🔹 SLAVE ARDUINO NANO: CONTROL DE LED VIA UART DESDE PICO 🔹
  - Recibe comandos UART desde un Raspberry Pi Pico.
  - Comando esperado: "BLINK:<tiempo_ms>"
  - Parpadea el LED 3 veces con el retardo indicado.
  - Envia: "LED ON", "LED OFF" y "DONE"
  - UART hardware del Nano (D0 RX, D1 TX)
  K. Michalsky – 11.2025
*************************************************************************************************************/

#define LED_PIN 2

#line 13 "C:\\Users\\Benutzer1\\Documents\\# Github repositories\\UART\\UART--Blink_Nano\\UART--Blink_Nano.ino"
void setup();
#line 25 "C:\\Users\\Benutzer1\\Documents\\# Github repositories\\UART\\UART--Blink_Nano\\UART--Blink_Nano.ino"
void loop();
#line 13 "C:\\Users\\Benutzer1\\Documents\\# Github repositories\\UART\\UART--Blink_Nano\\UART--Blink_Nano.ino"
void setup()
{
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    // UART hardware del Nano
    Serial.begin(115200);

    // Mensaje opcional al Pico
    Serial.println("READY");
}

void loop()
{
    if (Serial.available())
    {
        String msg = Serial.readStringUntil('\n');
        msg.trim();

        if (msg.startsWith("BLINK:"))
        {
            int delayTime = msg.substring(6).toInt();

            for (int i = 0; i < 3; i++)
            {
                digitalWrite(LED_PIN, HIGH);
                Serial.println("LED ON");
                delay(delayTime);

                digitalWrite(LED_PIN, LOW);
                Serial.println("LED OFF");
                delay(delayTime);
            }

            Serial.println("DONE");
        }
    }
}

