#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// Replace with your network credentials
const char* ssid = "qwer";
const char* password = "qwerty12";
//iqbal
String BOTtoken = "6288715492:AAHRQbsym6em-_LWRmebCLShLk8VQ6-8Y8M";   // your Bot Token (Get from Botfather)
String CHAT_ID = "5401629065";

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int botRequestDelay = 1000;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());
}

void loop() {

 String welcome = "system is Actif \n\n";
      welcome += "Temp             : x *C \n";
      welcome += "Ph                : x \n";
      welcome += "Turbidity       : x NTU\n";
      welcome += "status UV       : x \n";
      welcome += "status pompa : x \n\n";
      welcome += "untuk mengaktifkan pompa, Click -> /pompa_aktif.\n";
      welcome += "untuk mengaktifkan UV, Click -> /UV_aktif.\n\n";
      welcome += "Powered By :ELKA_UNJ 2017 \n";
      bot.sendMessage(CHAT_ID, welcome, "");
  Serial.println("telegram terkikirm");
  delay(50000);
}
