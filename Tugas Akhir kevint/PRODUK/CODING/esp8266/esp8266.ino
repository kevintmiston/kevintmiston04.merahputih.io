#include <CTBot.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>


CTBot myBot;
String ssid = "Kedai Kopi MIACATES";
String password = "cintaunyu";
String token = "1211515132:AAHDnIUPJJ-r5UsT2U64WhlR3WhvREZN4TM" ;
const int id = 901543448;

WiFiClientSecure client;
UniversalTelegramBot bot(token, client);

String str;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);

  //kirim pesan
  WifiStatus();
  myBot.wifiConnect(ssid,password);
  myBot.setTelegramToken (token);

  if (myBot.testConnection()) {
  Serial.println("koneksi Bagus");
  } else {
  Serial.println("Koneksi Jelek");
  }
  myBot.sendMessage (id, "NodeMcu ON");
  Serial.println("pesan Terkirim ke Telegram");
  }

void loop() { // run over and over
  if (Serial.available()) {
    str = Serial.readString();
    myBot.sendMessage(id, str);
    //Serial.println(str);
    //Serial.write(Serial.read());
  }
}

void WifiStatus() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
