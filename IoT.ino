#define BLYNK_TEMPLATE_ID "TMPL6W5aN_Gko"
#define BLYNK_TEMPLATE_NAME "Smart"
#define BLYNK_AUTH_TOKEN "iBSAmDCc0NyGQFRs86FSnxcsXAIAjGO3"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "FPT Telecom";
char pass[] = "123456789";

#define SOIL_SENSOR_PIN 34
#define RAIN_SENSOR_PIN 35
#define pump 27

int setH = 80;
int soilValue;
int rainValue;

BlynkTimer timer;

BLYNK_WRITE(V2) {
  setH = param.asInt();
  Serial.print("Ngưỡng độ ẩm mới: ");
  Serial.println(setH);
}

void myTimerEvent() {
  Blynk.virtualWrite(V0, soilValue);
  Blynk.virtualWrite(V1, rainValue);
}

void setup() {
  Serial.begin(115200);  // Đổi lại cho đúng
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  pinMode(pump, OUTPUT);
  pinMode(SOIL_SENSOR_PIN, INPUT);
  pinMode(RAIN_SENSOR_PIN, INPUT);
  timer.setInterval(1000L, myTimerEvent);
}

void loop() {
  Blynk.run();
  timer.run();

  soilValue = map(analogRead(SOIL_SENSOR_PIN), 0, 4095, 100, 0);
  rainValue = analogRead(RAIN_SENSOR_PIN);

  Serial.print("Độ ẩm đất: ");
  Serial.print(soilValue);
  Serial.print(" % | Mưa: ");
  Serial.println(rainValue);

  if ((soilValue < setH) && (rainValue > 2000)) {
    digitalWrite(pump, HIGH);
    Serial.println("→ Bơm đang hoạt động");
  } else {
    digitalWrite(pump, LOW);
    Serial.println("→ Bơm đã tắt");
  }

  delay(200);
}
