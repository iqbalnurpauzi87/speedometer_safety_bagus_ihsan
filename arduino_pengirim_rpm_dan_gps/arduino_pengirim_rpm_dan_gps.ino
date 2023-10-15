#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

float value=0;
float rev=0;
int rpm;
float rps;
int oldtime=0;
int Waktu;
float keliling = 2*(22/7)*0.4064;
float kecepatan;

void isr() //interrupt service routine
{
rev++;
}

void setup() {
  mySerial.begin(9600);
  Serial.begin(115200);
  Serial.println("rpm and komnikasi serial on");
  Serial.println(keliling);
  attachInterrupt(0,isr,RISING);  //attaching the interrupt

}

void loop() {
delay(1000);
detachInterrupt(0);           //detaches the interrupt
Waktu=millis()-oldtime;        //finds the time 
rpm=(rev/Waktu)*60000;         //calculates rpm
rps=(rev/Waktu)*1000;         //calculates rps
kecepatan = rpm/(60*keliling);
oldtime=millis();             //saves the current time
rev=0;

Serial.print("___TACHOMETER___");
Serial.print(     rpm);
Serial.print(" RPM   ");
Serial.print(     rps);
Serial.print(" RPS ");
Serial.print(     kecepatan);
Serial.print(" km/h");
Serial.println("   ");
attachInterrupt(0,isr,RISING);
//delay(1000);
  
  mySerial.print("a");
  mySerial.print(250);  //isi rpm
  mySerial.print("c");
  mySerial.print(-6.580779);
  mySerial.print("e");
  mySerial.print(106.840316);
  mySerial.print("g");
  mySerial.print(44);
  mySerial.print("i");
  mySerial.print(55);
  mySerial.print("j");
  mySerial.print(66);
  Serial.println("kirim berhasil");
  delay(1000);    
}
