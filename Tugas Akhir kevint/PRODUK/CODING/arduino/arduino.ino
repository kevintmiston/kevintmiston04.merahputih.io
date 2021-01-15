#include <Wire.h>

//sensor gas
#include <MQ2.h>
#define gasPin A0
#define pin8 8  //Notif kipas

//sensor api
const int pin2 = 2;
#define pin9 9
#define pin6 6//Notif buzzer
int bacasensorApi = 0;

#include <SoftwareSerial.h>
SoftwareSerial wifi(A3, A2);//atau pin 16 dan 15

String str;

void setup() {
  //Set serial monitor pada 9600
  Serial.begin(9600);
  wifi.begin(115200);//serial untuk nodeMCU

//gas
  pinMode(pin9, OUTPUT);
  pinMode (pin8, OUTPUT);
  
//PIR  
  pinMode(4, INPUT);
  pinMode(5, OUTPUT);

//api
  pinMode(pin2, INPUT);
  pinMode(pin6, OUTPUT);

}

void loop() {

{
str = "";//reset string

//if(digitalRead(4) == HIGH){
//}
//else { noTone(5);
//}

//pir / gerak
//  if (digitalRead(4) == HIGH) {
//    Serial.println("Motion Detected");
//    digitalWrite(5, HIGH);
//    
//    str = String(str) + String("Terdeteksi Gerakan\n");
//  } else {
//    Serial.println("No Motion");
//    digitalWrite(5, LOW);
//  }

  bacasensorApi = digitalRead(pin2);
  //Serial.println(bacasensorApi);
  if (bacasensorApi == LOW) {
    // turn Buzzer on:
    digitalWrite(pin6, HIGH);
    
    str = String(str) + String("Terdeteksi Kebakaran\n");
    Serial.println(bacasensorApi);
  } else {
    // turn Buzzer off:
    digitalWrite(pin6, LOW);
  }
  
int gasSensor = analogRead(gasPin);
Serial.println(gasSensor);
  if (gasSensor > 550) {
    digitalWrite(pin9, HIGH);
    digitalWrite (pin8, LOW);
    str = String(str) + String("Gas = ") + String(gasSensor) + String(" ppm\n");
    str = String(str) + String("Terdeteksi Kebocoran Gas\n");
    Serial.println(gasSensor);
  } else {
    digitalWrite(pin9, LOW);
    digitalWrite(pin8, HIGH);
  }

    //kirim pesan ke nodeMCU
  wifi.println(str);
  
  delay(1000);}
}
