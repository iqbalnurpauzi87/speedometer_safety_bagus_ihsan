 
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 10, TXPin = 11;
static const uint32_t GPSBaud = 9600;

char a, c, e, g, i, k;
int b, d, f, h, j, l, x;
// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

int serialtopc = 0;   //pilih 1 untuk ke pc, dan 0 untuk ke esp32

void setup(){
  ss.begin(GPSBaud);
  if(serialtopc == 1){
  Serial.begin(115200);
    Serial.print("mulai system gps");
  }
  else Serial.begin(9600);
}

void loop(){
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      float Latitude,Longitude;

      if(serialtopc == 1){   //pilih 1 untuk ke pc, dan 0 untuk ke esp32

      Serial.print("Latitude= "); 
      Serial.print(gps.location.lat(), 6);
//      Serial.print(Latitude);
      Serial.print(" Longitude= "); 
      Serial.println(gps.location.lng(), 6);
//      Serial.println(Longitude);
      }
      else {
//========= untuk dikirim ke esp32 ==============
      Serial.print("");   //Latitude
      Serial.print(gps.location.lat(), 6);
      Serial.print("b"); //Longitude
      Serial.print(gps.location.lng(), 6);




Serial.print("-6.580735b106.840332");
// Serial.print("a");  //rpm
//  Serial.print(6);    //status alat
//  Serial.print(".");    //lat
//  Serial.print(580735);  //latitude
//  Serial.print("b");  //lon
//  Serial.print(106);    //lontitude
//  Serial.print(".");
//  Serial.print(840332);    //statustombol
//  Serial.print(i);
//  Serial.print(j);    //statuspsu
//  Serial.print(k);
//  Serial.print(l);    //statuspsu
//  Serial.print("");
//  Serial.print("");

//  Serial.print("a");
//  Serial.print(11);
//  Serial.print("c");
//  Serial.print(22);
//  Serial.print("e");
//  Serial.print(33);
//  Serial.print("g");
//  Serial.print(44);
//  Serial.print("i");
//  Serial.print(55);
//  Serial.print("j");
//  Serial.print(66);
  
//  Serial.println("done");
      }
    delay(20000);
      
    }
  }
}
