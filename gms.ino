#include<ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#define ssid "ranjaniot"
#define key "12345678"


#define FIREBASE_HOST "https://iotgroupproject-92b7e-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "7xfnunEakm8EpFEN9es7te3UjGksWzs8ZAE96b0U"

FirebaseData firebaseData;
FirebaseData ledData;

int trigPin = 13;
int echoPin = 15;
double duration;
double distance;
double level;

void setup() {
  Serial.begin(9600);
  while (!Serial) {

  }
  while (WiFi.status() != WL_CONNECTED) {
    WiFi.disconnect();
    delay(100);
    WiFi.begin(ssid, key);
    delay(10000);
  }
  Serial.print("You're connected to the network");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  //Firebase.reconnectWiFi(true);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {

  delay(1000);

  int r = 0; // retry
  Serial.println("starting connection");

  sensordata();
//  Firebase.setFloat(firebaseData, "/device1/distance", 55);
  delay(3000);
}

void sensordata() {

  //sensorUpdate();
  delay(100);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.0340 / 2;

  Serial.println("Distance");
  Serial.println(distance);

  Firebase.setFloat(firebaseData, "/device1/distance", distance);
  level = ((28 - distance) / 28.0) * 100;

  Serial.println("level");
  Serial.println(level);

  Firebase.setFloat(firebaseData, "/device1/level", level);

  delay(5000);
}
