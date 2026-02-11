"""
========================================================================
              🔸 U A R T  -  C O M M A N D  ( S C A R A )🔸 
========================================================================
  Archivo    : UART_Command.py
  Autor      : Klaus Michalsky
  Fecha      : Feb-2026

  DESCRIPCION
-----------------------------------------------------------------------
  - Recibe comandos UART desde un Raspberry Pi Pico.
  - Comandos esperados: "HOME" → inicia homing, "STATUS" → responde estado.
  - Envía mensajes de estado: "HOMING_STARTED", "READY".
  - Comunicación bidireccional usando Serial1 (TX=GPIO0, RX=GPIO1) y Serial USB para debug.
  - Ideal para pruebas de comunicación UART entre RP2040 y Pico.


  HARDWARE
-----------------------------------------------------------------------
  MCU     : RP2040-Zero Y Raspberry Pi Pico

 Esquema de conexiones UART y alimentación / Baudrate = 115200:
-----------------------------------------------------------------------

 ┌──────────────┐                      ┌──────────────────┐
 │ Raspberry Pi │                      │ RP2040 Zero      │
 │     Pico     │                      │ (Arduino C++)    │
 ├──────────────┤                      ├──────────────────┤
 │ GP0 (TX0) ───────────────▶ GP1 (RX0)│
 │ GP1 (RX0) ◀─────────────── GP0 (TX0)│
 │ GND ─────────────────────── GND      │
 │ VBUS (5V) ───────────────── VBUS (5V)│
 └──────────────┘                      └──────────────────┘

  ESTADO
-----------------------------------------------------------------------
  ✅ Funcional
========================================================================
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
