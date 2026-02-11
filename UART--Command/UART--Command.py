"""
🔹 MASTER RP2040 PICO: ENVÍO DE COMANDOS UART A ZERO 🔹
  - Solicita al usuario un comando.
  - Envía comando: "^HOME" al Zero vía UART.
  - Espera y muestra mensajes de estado enviados por la Zero: "HOMING_STARTED".
  - Comunicación bidireccional con Zero a través de UART (TX=GPIO0, RX=GPIO1).
  - Permite mandar comandos via serial y sincronización de secuencias.
  K. Michalsky – 11.2025

------------------------------------------------------------
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
"""

from machine import UART, Pin
import time

uart = UART(0, 115200, tx=Pin(0), rx=Pin(1))

command = str(input("Ingrese comando: "))
uart.write(f"{command}\n".encode())

print("Comando enviado al RP2040 Zero!\nEsperando respuesta...\n")

while True:
    if uart.any():
        msg = uart.readline().decode().strip()
        print(msg)
        if msg == "HOMING_STARTED":
            print("Secuencia completada.")
            break
    time.sleep(0.1)
