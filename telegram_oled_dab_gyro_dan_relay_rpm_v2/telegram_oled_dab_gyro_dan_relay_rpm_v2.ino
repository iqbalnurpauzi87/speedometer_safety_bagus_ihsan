#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>   // Universal Telegram Bot Library written by Brian Lough: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
#include <ArduinoJson.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "Wire.h"
#include <MPU6050_light.h>


// Replace with your network credentials
const char* ssid = "qwer";
const char* password = "qwerty12";

// Initialize Telegram BOT
//iqbal
String BOTtoken = "1613209666:AAFT_0VnhMW6pquy4n2RhnVwOySyMNymTq0";   // your Bot Token (Get from Botfather)
String CHAT_ID = "1586166338";

//String BOTtoken = "6288715492:AAHRQbsym6em-_LWRmebCLShLk8VQ6-8Y8M";   // your Bot Token (Get from Botfather)
//String CHAT_ID = "5401629065";


MPU6050 mpu(Wire);

int gyrox,gyroy,gyroz;
unsigned long timer = 0;
int pinkey= 5;
int pinbuzzer = 19; 
int statuskemiringan, sgiro=1; //sgiro=1 gyro aktif

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#ifdef ESP8266
  X509List cert(TELEGRAM_CERTIFICATE_ROOT);
#endif

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// Checks for new messages every 1 second.
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

const int ledPin = 2;
bool ledState = LOW;


char a, c, e, g, i, k;
int b, d, f, h, j, l, x;

// Handle what happens when you receive new messages
void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    // Chat id of the requester
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID){
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }
    
    // Print the received message
    String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;

    if (text == "/start") {
      String welcome = "Welcome, " + from_name + ".\n";
      welcome += "Use the following commands to control your outputs.\n\n";
      welcome += "/led_on to turn GPIO ON \n";
      welcome += "/led_off to turn GPIO OFF \n";
      welcome += "/state to request current GPIO state \n";
      bot.sendMessage(chat_id, welcome, "");
    }

    if (text == "/led_on") {
      bot.sendMessage(chat_id, "LED state set to ON", "");
      ledState = HIGH;
      digitalWrite(ledPin, ledState);
    }
    
    if (text == "/led_off") {
      bot.sendMessage(chat_id, "LED state set to OFF", "");
      ledState = LOW;
      digitalWrite(ledPin, ledState);
    }
    
    if (text == "SOS") {
 String welcome = "SOS is HERE.\n\n";
      welcome += "matikan mesin? \n";
      welcome += "/machin_off \n";
      bot.sendMessage(chat_id, welcome, "");
      sgiro=0;
         }
         
    if (text == "/lokasi") {
 String welcome = "lokasi kendaraan anda di:.\n\n";
      welcome += "https://www.google.com/maps?q=-6.587866,106.785255 \n";
      bot.sendMessage(chat_id, welcome, "");
      sgiro=0;
         }
    if (text == "/machin_off") {
 String welcome = "SOS is HERE.\n\n";
      welcome += "hidupkan mesin? \n";
      welcome += "/machin_on \n";
      bot.sendMessage(chat_id, welcome, "");
         digitalWrite(pinkey, 0);
         sgiro=0;
    }
    if (text == "/machin_on") {
 String welcome = "SOS in HERE.\n\n";
      welcome += "MESIN HIDUP!!.\n\n";
      bot.sendMessage(chat_id, welcome, "");
         
         sgiro=1;
         digitalWrite(pinkey, 1);
    }
    if (text == "/state") {
      if (digitalRead(ledPin)){
        bot.sendMessage(chat_id, "LED is ON", "");
      }
      else{
        bot.sendMessage(chat_id, "LED is OFF", "");
      }
    }
    if (text == "/lokasi" or text == "lokasi") {
      String welcome = "Lokasi kendaraan saat ini.\n\n";
      welcome += "lokasi saat ini :   \n";
      welcome += "https://maps.google.com/?q=";
      welcome += a;
      welcome += b;
      welcome += c;
      welcome += d; 
      
      welcome += ",";
      welcome += f;
      welcome += g;
      welcome += h;
//      
      
      welcome += " \n";
 
 Serial.println("  ");  //
 Serial.println("ini di pnggil lokasi");  //
 Serial.println("  ");  //
 Serial.print(a);  //
  Serial.print(b);    //
  Serial.print(c);    //
  Serial.print(d);  //
  Serial.print(e);  //
  Serial.print(f);    
  Serial.print(g);
  Serial.print(h);    

  
 Serial.println("  ");  //
 Serial.println("di pnggil lokasi selesai");  //
 Serial.println("  ");  //
        bot.sendMessage(chat_id, welcome, "");
     
    }
  }
}

void setup() {
  Serial.begin(115200);
//  Serial2.begin(9600);  //
  Wire.begin();
 pinMode(pinkey, OUTPUT);
 pinMode(pinbuzzer, OUTPUT); 
 digitalWrite(pinkey, 1);
  #ifdef ESP8266
    configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
    client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org
  #endif

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
  
  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  #ifdef ESP32
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  #endif
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  
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
  display.println(F("HAI BAGUS"));
  display.display();
  Serial.println("test oke");

}

void loop() {
//baca_serial();
readsensor();
tampilan();
kontrol();
 delay(200);

  
  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }

 
 
 if(statuskemiringan==1){
  
     String welcome = "BAHAYA, \n";
      welcome += " MOTOR RUBUH NIH KECELAKAAN\n";
      bot.sendMessage(CHAT_ID, welcome, "");
      statuskemiringan=0;     
 }
  
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
  display.setCursor(0,24);             // Start at top-left corner
  display.print(F("RPM : "));        // Start at top-left corner
  display.print(b, DEC);
  display.display();
  Serial.println("display oke");
  Serial.println(b);
}

void kontrol(){
  if(sgiro==1){
    
  if(gyroy>50 or gyroy<-50){
    digitalWrite(pinkey, 0);
    Serial.println("terlalu miring");
    statuskemiringan=1;
  }
  else {
    digitalWrite(pinkey, 1);
    Serial.println("sudah lurus");
  }
  }
}

void baca_serial(){
  Serial.print("baca serial    ");
   while (Serial2.available() > 0) {
    a = Serial2.read();
    b = Serial2.parseInt();
    c = Serial2.read();
    d = Serial2.parseInt();
    e = Serial2.read();
    f = Serial2.parseInt();
    g = Serial2.read();  
    h = Serial2.parseInt();  // disesuaikan dengan panjang data yg dikirim
//    i = Serial2.read();
//    j = Serial2.parseInt();
//    k = Serial2.read();
//    l = Serial2.parseInt();
  if(d==4) d=0;
  Serial.print(a);  //
  Serial.print(b);    //
  Serial.print(c);    //
  Serial.print(d);  //
  Serial.print(e);  //
  Serial.print(f);    
  Serial.print(g);
  Serial.print(h);    
//  Serial.print(i);
//  Serial.print(j);    
//  Serial.print(k);
//  Serial.print(l);
  Serial.print("");
  Serial.println("");
  }
  
  Serial.println("baca serial done");
}

void onboardtele(){
  
}
