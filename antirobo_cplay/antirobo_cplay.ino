// Anti-burglar alarm based on example tap code by Adafruit
// Modified by Alvaro Figueroa por teaching in Greencore Solutions
// Alarma anti robo basada en ejemplo de código por Adafruit
// Modificada por Alvaro Figueroa para enseñansa en Greencore Solutions
// https://github.com/fede2cr/antirobo_cplay
// https://www.greencore.co.cr

// Luego de prender se espera 5 segundos, y dependiendo del estado
// del switch del Playground, activa la alarma. Si detecta movimiento
// con el acelerómetro, genera una alerta visual y auditiva
#include <Adafruit_CircuitPlayground.h>

// Sensitividad del acelerómetro. ¡Muy sensible!
#define CLICKTHRESHHOLD 40

// Multiplicamos este valor por 10, para el total de tiempo
// a esperar antes de activar la consola
#define WAIT 500

void setup(void) {
  Serial.begin(9600);
  CircuitPlayground.begin();
  // Definimos el rango de sensitividad en unidades de gravedad, 2G
  CircuitPlayground.setAccelRange(LIS3DH_RANGE_2_G);   // 2, 4, 8 or 16 G!
  // Activamos la sensitividad en el acelerómetro
  CircuitPlayground.setAccelTap(1, CLICKTHRESHHOLD);
  // Esperamos antes de activar la alarma. Visualmente indicamos antes de activar
  // activando los neopixel, uno por uno, con color rojo
  for (int i=0; i<10; ++i) {
     CircuitPlayground.strip.setPixelColor(i, 255, 0, 0);
     delay(WAIT);
     CircuitPlayground.strip.show();
  }
  delay(WAIT);
  CircuitPlayground.clearPixels();
}


void loop() {
  uint8_t click = CircuitPlayground.getAccelTap();
  if (click == 0) return;
  if (! (click & 0x30)) return;
  if ((click & 0x10) || (click & 0x20)) {
     Serial.println("Iniciando alerta");
     // Solo se activa si el switch está en +
     while (CircuitPlayground.slideSwitch()) {
  
       for (int i=0; i<10; ++i) {
          CircuitPlayground.strip.setPixelColor(i, 255, 0, 0);
       }
       CircuitPlayground.strip.show();
       delay(500);
       CircuitPlayground.clearPixels();
       delay(500);
       Serial.println("¡Alerta!");
       CircuitPlayground.playTone(2600, 250);  
     }
  }

}
