#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#define FIREBASE_HOST "alat1-8e1ee-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "C8sM6vvA9FNJ5eibHUCncg75ZcP3C6doJHrb3Edm"
#define WIFI_SSID "vivo 1806"
#define WIFI_PASSWORD "8sampai1"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

//Week Days
String weekDays[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//Month names
String months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

int ngitung;
int led = D2;
int statustelur;
int berat;
char xx;

int ab;
char a;
char c;
void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(25200);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  pinMode(led, OUTPUT);
}

void loop() {
  while (Serial.available() > 0) {
    ab = Serial.parseInt();
    a = Serial.read();
    berat = Serial.parseInt();
    c = Serial.read();
  }
  timeClient.update();

  unsigned long epochTime = timeClient.getEpochTime();
  Serial.print("Epoch Time: ");
  Serial.println(epochTime);

  String formattedTime = timeClient.getFormattedTime();
  Serial.print("Formatted Time: ");
  Serial.println(formattedTime);

  int currentHour = timeClient.getHours();
  Serial.print("Hour: ");
  Serial.println(currentHour);

  int currentMinute = timeClient.getMinutes();
  Serial.print("Minutes: ");
  Serial.println(currentMinute);

  int currentSecond = timeClient.getSeconds();
  Serial.print("Seconds: ");
  Serial.println(currentSecond);

  String weekDay = weekDays[timeClient.getDay()];
  Serial.print("Week Day: ");
  Serial.println(weekDay);

  //Get a time structure
  struct tm *ptm = gmtime ((time_t *)&epochTime);

  int monthDay = ptm->tm_mday;
  Serial.print("Month day: ");
  Serial.println(monthDay);

  int currentMonth = ptm->tm_mon + 1;
  Serial.print("Month: ");
  Serial.println(currentMonth);

  String currentMonthName = months[currentMonth - 1];
  Serial.print("Month name: ");
  Serial.println(currentMonthName);

  int currentYear = ptm->tm_year + 1900;
  Serial.print("Year: ");
  Serial.println(currentYear);

  //Print complete date:
  String currentDate = String(currentYear) + "-" + String(currentMonth) + "-" + String(monthDay);
  Serial.print("Current date: ");
  Serial.println(currentDate);
  Serial.print("BERAT");
  Serial.println(berat);
  Serial.print("st telur");
  Serial.println(Firebase.getInt("A5_status_telur"));

//  berat = 50;
  if (berat >= 40 && berat <= 80  ) {
    statustelur = 1;
    digitalWrite(led, HIGH);
    Firebase.setInt("A5 berat", berat);
      Firebase.setString("A5 berat/Waktu A5", String(currentDate) + "|" + String(formattedTime));
    Firebase.setInt("A5 berat/A5_status_telur", statustelur);
  } else {
    statustelur = 0;
    Serial.println("status : gak ada telur");
    Firebase.setString("A5 berat/Waktu A5", "");
    Firebase.setInt("A5 berat", 0);
    Firebase.setInt("A5 berat/A5_status_telur", statustelur);
    digitalWrite(led, LOW);
  }
  //  if (berat >= 50 && berat <= 80 ) {
  ////    berat = 50;
  //
  //    Firebase.setInt("A8_status_telur", statustelur);
  //  }
  //  if (Firebase.getInt("A8_status_telur") ) {
  //    statustelur = 1;
  //    Serial.println("status : ada telur");
  //    digitalWrite(led, HIGH);
  //  } else {
  //    statustelur = 0;
  //    Serial.println("status : gak ada telur");
  //    digitalWrite(led, LOW);
  //  }
  //  // update value
  //  Firebase.setInt("A8 berat", berat);
  //  Firebase.pushString("A2 berat : ", data);  //coba buat log
  //  Serial.print("pushed: /logs/");
  //  Serial.println(name);
  //  Serial.print("ngitung: ");
  //  Serial.println(ngitung);
  delay(1000);
}
