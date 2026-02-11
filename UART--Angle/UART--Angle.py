"""
/************************************************************************************************************
 🔹 MASTER Raspberry Pi Pico: ENVÍO DE ÁNGULO VIA UART AL RP2040-Zero 🔹
  - Envía continuamente un valor de ángulo por UART.
  - Formato enviado: "<angulo>\n" como texto.
  - Uso ideal para pruebas simples de comunicación Pico → Zero.
  - UART0 configurado con TX=GP0 y RX=GP1 (solo TX se usa en esta versión).
  - Baudrate: 115200.
    K. Michalsky – 11.2025
************************************************************************************************************/
"""



from machine import UART, Pin
import utime

# Configuración del LED en GPIO21(Pin16)
led = Pin(16, Pin.OUT)

# UART0 en los pines GP0 (TX) y GP1 (RX)
uart = UART(0, baudrate=115200, tx=Pin(0), rx=Pin(1))

angulo = 123 #valor de prueba

while True:
    mensaje = str(angulo) + "\n"
    uart.write(mensaje)
    print(f"Angulo {angulo}° enviado")
    utime.sleep_ms(500)
    led.value(1)      # LED encendido
    utime.sleep_ms(500)
    led.value(0)      # LED apagado
    utime.sleep_ms(500)
    
    
    

