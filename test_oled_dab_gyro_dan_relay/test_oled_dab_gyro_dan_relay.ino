
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "Wire.h"
#include <MPU6050_light.h>

MPU6050 mpu(Wire);

int gyrox,gyroy,gyroz;
unsigned long timer = 0;
int pinkey= 5;
int pinbuzzer = 19; 

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
 Wire.begin();
 pinMode(pinkey, OUTPUT);
 pinMode(pinbuzzer, OUTPUT);
 
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
//  mpu.calcOffsets(true,true); // HANYA DIGUNAKAN SAAT KALIBRASI AJA GUYS!!
  Serial.println("Done!\n");
  
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  Serial.println("1");

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();

  
  display.clearDisplay();

  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(5,5);             // Start at top-left corner
  display.println(F("Ready"));
  display.display();
  Serial.println("");

 }

void loop() {
readsensor();
tampilan();
kontrol();
 delay(200);
}

void readsensor(){
 mpu.update();
  if(millis() - timer > 1000){ // print data every second
    Serial.print(F("TEMPERATURE: "));Serial.println(mpu.getTemp());
    Serial.print(F("ACCELERO  X: "));Serial.print(mpu.getAccX());
    Serial.print("\tY: ");Serial.print(mpu.getAccY());
    Serial.print("\tZ: ");Serial.println(mpu.getAccZ());
  
    Serial.print(F("GYRO      X: "));Serial.print(mpu.getGyroX());
    Serial.print("\tY: ");Serial.print(mpu.getGyroY());
    Serial.print("\tZ: ");Serial.println(mpu.getGyroZ());
  
    Serial.print(F("ACC ANGLE X: "));Serial.print(mpu.getAccAngleX());
    Serial.print("\tY: ");Serial.println(mpu.getAccAngleY());
    
    Serial.print(F("ANGLE     X: "));Serial.print(mpu.getAngleX());
    Serial.print("\tY: ");Serial.print(mpu.getAngleY());
    Serial.print("\tZ: ");Serial.println(mpu.getAngleZ());
    Serial.println(F("=====================================================\n"));
    timer = millis();
  }
gyrox = mpu.getAccAngleX();
gyroy = mpu.getAccAngleY();
gyroz = mpu.getAccZ();
}

void tampilan(){
    display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.print(F("X : "));         // Start at top-left corner
  display.print(gyrox, DEC);
  display.setCursor(0,8);             // Start at top-left corner
  display.print(F("Y : "));        // Start at top-left corner
  display.print(gyroy, DEC);
  display.setCursor(0,16);             // Start at top-left corner
  display.print(F("Z : "));        // Start at top-left corner
  display.print(gyroz, DEC);
  display.display();
  Serial.println("test oke");
}

void kontrol(){
  if(gyroy>50 or gyroy<-50){
    digitalWrite(pinkey, HIGH);
    Serial.println("terlalu miring");
  }
  else {
    digitalWrite(pinkey, LOW);
    Serial.println("sudah lurus");
  }
}
