#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

float value=0;
float rev=0;
int rpm;
float rps;
int oldtime=0;
int Waktu;

void isr() //interrupt service routine
{
rev++;
}



void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
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
  display.println(F("HAI BAGUS"));
  display.display();
  Serial.println("test oke");

attachInterrupt(0,isr,RISING);  //attaching the interrupt
}

void loop() {
  // put your main code here, to run repeatedly:
delay(1000);
detachInterrupt(0);           //detaches the interrupt
Waktu=millis()-oldtime;        //finds the time 
rpm=(rev/Waktu)*60000;         //calculates rpm
rps=(rev/Waktu)*1000;         //calculates rps
oldtime=millis();             //saves the current time
rev=0;

Serial.print("___TACHOMETER___");
Serial.print(     rpm);
Serial.print(" RPM   ");
Serial.print(     rps);
Serial.print(" RPS");
Serial.println("   ");
attachInterrupt(0,isr,RISING);
delay(1000);
}
