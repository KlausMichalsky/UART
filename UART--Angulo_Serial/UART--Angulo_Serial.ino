/************************************************************************************************************
 🔹 SLAVE RP2040-Zero: RECEPCIÓN DE ÁNGULO VIA UART DESDE PICO 🔹
  - Recibe por UART un ángulo enviado desde el Pico.
  - Lee datos como texto hasta encontrar '\n'.
  - Muestra el ángulo recibido en el Serial USB para debug.
  - UART1 configurado con TX=GPIO0 y RX=GPIO1.
  - Envia “pong” como respuesta básica para pruebas.
  - Baudrate: 115200.
    K. Michalsky – 11.2025
************************************************************************************************************/

void setup() {
{
  Serial.begin(115200);
  Serial1.setTX(0);
  Serial1.setRX(1);
  Serial1.begin(115200);
}

void loop() {
  if (Serial1.available()) {
    String angulo = Serial1.readStringUntil('\n');  // lee hasta salto de línea
    Serial.print("Angulo recibido: ");
    Serial.println(angulo);
  }
}

