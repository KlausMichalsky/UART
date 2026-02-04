#line 1 "C:\\Users\\Benutzer1\\Documents\\# Github repositories\\UART\\UART--Blink\\_manual_.md"
# Mini-Manual: Comunicación Master-Slave entre RP2040 Pico y Zero para Control de LED

## Descripción general
Este proyecto permite controlar un **LED en la RP2040 Zero** mediante **comandos enviados desde un Raspberry Pi Pico** usando UART.  
El sistema está dividido en **Master (Pico)** y **Slave (Zero)**:

- **Master (Pico)**: envía comandos de parpadeo con tiempo configurable y muestra los mensajes de estado de la Zero.
- **Slave (Zero)**: recibe comandos, ejecuta la acción en el LED, y responde con mensajes de estado.

## Pines y conexiones

| Función           | Pico   | Zero   |
|------------------|--------|--------|
| UART TX           | GPIO0  | GPIO1  |
| UART RX           | GPIO1  | GPIO0  |
| LED               | —      | 8      |

⚠️ Conectar TX del Pico al RX del Zero y viceversa. GND común entre placas.

## Librerías usadas
- Zero: solo funciones estándar de Arduino (`Serial` y `Serial1`).  
- Pico: MicroPython estándar (`machine.UART`, `time`, `Pin`).

## Comandos
- Formato: `BLINK:<tiempo_ms>`  
  - `<tiempo_ms>`: duración de encendido y apagado en milisegundos.  
  - Ejemplo: `BLINK:500` → LED parpadea 3 veces con 500 ms ON/OFF.

## Flujo de ejecución

### Master (Pico)
1. Pide al usuario el valor de delay en ms.
2. Envía comando `BLINK:<ms>` al Zero por UART.
3. Escucha mensajes del Zero hasta recibir `"DONE"`.
4. Imprime todos los mensajes recibidos en la consola.

### Slave (Zero)
1. Inicializa UART en GPIO0/GPIO1 y LED en pin 8.
2. Espera comandos desde Pico.
3. Si recibe `"BLINK:<ms>"`, parpadea el LED 3 veces.
4. Envía mensajes de estado: `"LED ON"`, `"LED OFF"` y `"DONE"`.

## Notas adicionales
- `msg.trim()` en Zero asegura que no haya espacios o saltos de línea al inicio o final.
- Comunicación bidireccional: mensajes de estado permiten al master confirmar la ejecución.
- Se puede extender el master para enviar secuencias más complejas o múltiples LEDs.
- Ideal para probar comunicación UART entre RP2040 y otros microcontroladores.

## Estructura recomendada del proyecto

