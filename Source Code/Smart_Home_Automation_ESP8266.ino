#define BLYNK_TEMPLATE_ID "TMPL6ezxza5Qe"
#define BLYNK_TEMPLATE_NAME "Smart Home Automation"
#define BLYNK_AUTH_TOKEN    "cwtJ9tX63Kr3LPyo6YN_BBzDXzcz6ij3"
// set up blynk

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "deer cofee";
char pass[] = "12345678";
// set up wifi

String incomingData = "";


float temperatureC = 0;
float humidity = 0;
int ldrValue = 0;
int pirValue = 0;
int lightState = 0;
int fanState = 0;

// Parse data from arduino
void parseData(String data) {
  int p1 = data.indexOf(',');
  int p2 = data.indexOf(',', p1 + 1);
  int p3 = data.indexOf(',', p2 + 1);
  int p4 = data.indexOf(',', p3 + 1);
  int p5 = data.indexOf(',', p4 + 1);

  if (p1 == -1 || p2 == -1 || p3 == -1 || p4 == -1 || p5 == -1) return;

  temperatureC = data.substring(0, p1).toFloat();
  humidity     = data.substring(p1 + 1, p2).toFloat();
  ldrValue     = data.substring(p2 + 1, p3).toInt();
  pirValue     = data.substring(p3 + 1, p4).toInt();
  lightState   = data.substring(p4 + 1, p5).toInt();
  fanState     = data.substring(p5 + 1).toInt();
}

// send data to blynk
void sendToBlynk() {
  Blynk.virtualWrite(V0, temperatureC);
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V2, ldrValue);
  Blynk.virtualWrite(V3, pirValue);
  Blynk.virtualWrite(V4, lightState);
  Blynk.virtualWrite(V5, fanState);
}

BlynkTimer timer;

void setup() {
  Serial.begin(9600);   // must be the same as arduino

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(1000L, sendToBlynk);

  Serial.println("ESP8266 started");
}

void loop() {
  Blynk.run();
  timer.run();

  while (Serial.available()) {
    char c = Serial.read();

    if (c == '\n') {
      parseData(incomingData);
      incomingData = "";
    } else if (c != '\r') {
      incomingData += c;
    }
  }
}