#include <DHT.h>

// ===== CHAN KET NOI =====
int releLight = 8;
int releFan   = 7;
int inputPir  = 2;
int sensorLDR = A0;

#define DHTPIN A1
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// ===== DEM THOI GIAN 3 GIAY =====
unsigned long lastMotionTime = 0;
const unsigned long offDelay = 3000;

void setup() {
  pinMode(releLight, OUTPUT);
  pinMode(releFan, OUTPUT);
  pinMode(inputPir, INPUT);

  digitalWrite(releLight, LOW);
  digitalWrite(releFan, LOW);

  Serial.begin(9600);
  dht.begin();

  Serial.println("UNO started");
}

void loop() {
  int valPir = digitalRead(inputPir);
  int valLDR = analogRead(sensorLDR);

  float temperatureC = dht.readTemperature();
  float humidity     = dht.readHumidity();

  if (isnan(temperatureC) || isnan(humidity)) {
    delay(500);
    return;
  }

  // cap nhat lan cuoi co chuyen dong
  if (valPir == HIGH) {
    lastMotionTime = millis();
  }

  // dieu khien trong 3 giay sau khi thay chuyen dong
  if (millis() - lastMotionTime < offDelay) {
    // den
    if (valLDR < 50) {
      digitalWrite(releLight, HIGH);
    } else {
      digitalWrite(releLight, LOW);
    }

    // quat
    if (temperatureC > 27) {
      digitalWrite(releFan, HIGH);
    } else {
      digitalWrite(releFan, LOW);
    }
  } else {
    digitalWrite(releLight, LOW);
    digitalWrite(releFan, LOW);
  }

  int lightState = digitalRead(releLight);
  int fanState   = digitalRead(releFan);

  // gui qua ESP8266
  Serial.print(temperatureC);
  Serial.print(",");
  Serial.print(humidity);
  Serial.print(",");
  Serial.print(valLDR);
  Serial.print(",");
  Serial.print(valPir);
  Serial.print(",");
  Serial.print(lightState);
  Serial.print(",");
  Serial.println(fanState);

  delay(1000);
}