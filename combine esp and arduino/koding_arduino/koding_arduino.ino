#include "HX711.h"
#define DOUT  3
#define CLK  4
HX711 scale(DOUT, CLK);
float calibration_factor = -1770;
int GRAM;
void setup() {
  Serial.begin(9600);
  scale.set_scale();
  scale.tare();
}

void loop() {
  scale.set_scale(calibration_factor);
  GRAM = scale.get_units()  , 4;
  Serial.print("a");
  Serial.print(GRAM);
  delay(1000);    
}
