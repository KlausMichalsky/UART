
"""
############################################################################################################
 🔹 PING–PONG UART entre Pico/Zero y Arduino 🔹
  - Script MicroPython para Pico/Zero: envía "ping\n" por UART0 (GP0 TX, GP1 RX) y lee respuestas con readline().
  - Comunicación a 115200 baudios, mensajes por línea terminada en '\n'.
  - Función: verificar que Arduino responde con "pong" y mostrar intercambio por consola USB.
  - Recomendaciones: usar masa común entre placas, cruzar TX/RX físicamente, y ajustar tiempos de espera.
  - Compatibilidad: Pico y Zero (usar nombres "Pico" o "Zero" según tu placa).
  K. Michalsky – 11.2025
############################################################################################################
"""


from machine import UART, Pin
import time

# UART0 en los pines GP0 (TX) y GP1 (RX)
uart = UART(0, baudrate=115200, tx=Pin(0), rx=Pin(1))

while True:
    # Enviar ping
    uart.write("ping\n")
    print("Enviado al Arduino: ping")

    # Esperar respuesta
    time.sleep(0.1)
    if uart.any():
        resp = uart.readline()
        if resp:
            print("Recibido del Arduino:", resp.decode().strip())

    time.sleep(1)
