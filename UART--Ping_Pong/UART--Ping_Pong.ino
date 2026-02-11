/************************************************************************************************************
 🔹 PING–PONG UART entre Arduino y Pico/Zero 🔹
  - Comunicación UART bidireccional: Arduino escucha en Serial1 (pines 0/1) y responde "pong".
  - El Pico/Zero envía "ping\n" por UART0 (GP0 TX, GP1 RX) y espera la respuesta "pong".
  - Velocidad: 115200 baudios (configurable en ambos lados).
  - Formato de mensajes: líneas terminadas en '\n' (se usan readStringUntil('\n') / readline()).
  - Uso típico: pruebas de enlace serie, depuración de cableado TX/RX y verificación de niveles lógicos.
  - Recomendaciones: confirmar conexión TX→RX cruzada y masa común; ajustar delays si se pierden mensajes.
  K. Michalsky – 11.2025
************************************************************************************************************/

void setup()
{
  Serial.begin(115200);
  Serial1.setTX(0);
  Serial1.setRX(1);
  Serial1.begin(115200);
}
void loop()
{
  if (Serial1.available())
  {
    String s = Serial1.readStringUntil('\n');
    Serial1.println("pong");
    Serial.println("Recibido del Pico: " + s);
  }
}
