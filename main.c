#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "SCDOLg6oyOKUMxf2qoNMplQa0fYOc4SB"; //Enter your Blynk application auth token
char ssid[] = ""; //Enter your WIFI name
char pass[] = ""; //Enter your WIFI passowrd

BlynkTimer timer;
int pinValue = 0;

void setup() {
  Serial.begin(9600);
  pinMode(D0, OUTPUT);
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
  pinMode(D6, INPUT);

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, notifiaction);

}
BLYNK_WRITE(V0) {
  pinValue = param.asInt();
}

void notifiaction() {
  bool sensor = digitalRead(D6);
  if (pinValue == 1) {
    Serial.println("System is ON");
    if (sensor == 1) {
      Blynk.notify("WARNING! Please check your security system");
      digitalWrite(D0, HIGH);
      digitalWrite(D1, HIGH);
      digitalWrite(D2, LOW);
    } else if (sensor == 0) {
      digitalWrite(D0, LOW);
      digitalWrite(D1, LOW);
      digitalWrite(D2, HIGH);
    }
  } else if (pinValue == 0) {
    Serial.println("System is OFF");
  }
}

void loop() {
  Blynk.run();
  timer.run();
}
