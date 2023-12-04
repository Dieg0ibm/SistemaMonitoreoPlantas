#define BLYNK_TEMPLATE_ID "TMPL2PgItMGTl"
#define BLYNK_TEMPLATE_NAME "Planta"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial
#define APP_DEBUG

#include "BlynkSimpleEsp32.h"
#include "DHT.h"

#define RELAY_PIN_3 5
#define RELAY_PIN_1 17
#define dhin 14
#define dhtt DHT11

char auth[] = "KxNz77K0nPaG1f3R7_ZLxcgnFX7w31pZ";
char ssid[] = "Nombre de la Señal";
char pass[] = "Contraseña de la señal";

int _moisture, sensor_analog;
const int sensor_pin = A0;

DHT dht(dhin, dhtt);

void setup()
{
  Serial.begin(115200);
  delay(100);
  pinMode(RELAY_PIN_1, OUTPUT);
  pinMode(RELAY_PIN_3, OUTPUT);
  digitalWrite(RELAY_PIN_1, LOW);
  digitalWrite(RELAY_PIN_3, LOW);
  dht.begin();
  Blynk.begin(auth, ssid, pass);
}


void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  sensor_analog = analogRead(sensor_pin);
  _moisture = ( 100 - ( (sensor_analog / 4095.00) * 100 ) );
  digitalWrite(RELAY_PIN_3, HIGH);
  if (isnan(h) || isnan(t) ) {
    Serial.println(F("Failed to read from DHT sensor!"));
    digitalWrite(RELAY_PIN_3, LOW);
    return;
  }
  if (_moisture <= 30 && t < 27) {
    Blynk.virtualWrite(V3, _moisture);
    digitalWrite(RELAY_PIN_1, HIGH);
    delay(4000);
    digitalWrite(RELAY_PIN_1, LOW);
  }

  Blynk.virtualWrite(V3, _moisture);
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
  Blynk.run();
}
