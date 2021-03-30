#include <ESP8266WiFi.h>
#include "FirebaseESP8266.h"

int trigPin = 5;
int echoPin = 6;
long duration;
int distance;


double level;
FirebaseData firebaseData;
FirebaseData ledData;


#define FIREBASE_HOST "https://ultrasonicgarbage-7f8f3-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "2qSprNT3gf3ufIHu0r6acqswSO07uAZsK8SoV1Eb"
#define ssid "NABIN"
#define password "12345678"

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  WiFi.disconnect();
  Serial.begin(9600);
  Serial.print("Connecting to Wifi Network");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(5000);

  }
  Serial.println("");
  Serial.println("Successfully connected to WiFi.");
  Serial.println("IP address is : ");
  Serial.println(WiFi.localIP());
  //  server.begin();
  Serial.println("Server started");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

}

void loop() {

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

  delay(8000);
}
