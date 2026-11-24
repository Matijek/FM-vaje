#include <Arduino.h>

constexpr int IZHOD_GPIO = 3; // constexpr nastavi vrednost kot konstanto
constexpr int ADC_GPIO = 2;
constexpr unsigned long preklop_ms = 3000;
constexpr float R = 10000.0 ;

unsigned int zadnjiPreklop = 0;
unsigned int zadnjiVzorec = 0;
bool izhodVisok = false;
float avg = 0.0;
int N = 0;

void setup() {
  Serial.begin(115200);
  pinMode(IZHOD_GPIO, OUTPUT);
  digitalWrite(IZHOD_GPIO, LOW);
  analogReadResolution(12);
  analogSetPinAttenuation(ADC_GPIO, ADC_11db);

  zadnjiPreklop = millis();
  zadnjiVzorec = zadnjiPreklop;
}

void loop() {
  const unsigned int zdaj = millis();



  if (zdaj - zadnjiPreklop >= preklop_ms) {
    zadnjiPreklop = zdaj;
    izhodVisok = !izhodVisok;
    digitalWrite(IZHOD_GPIO, izhodVisok ? HIGH : LOW);

    avg = avg/N;
    const float I = avg / R; 

    Serial.print("I (mA) = ");
    Serial.print(I);
    Serial.print(" , ");
    Serial.print("U (M) = ");
    Serial.print(avg);
    Serial.print(" Stevilo meritev je ");
    Serial.print(N);
    Serial.println();

    avg = 0.0;
    N = 0;
  }


  const uint32_t napetost_mV = analogReadMilliVolts(ADC_GPIO);
  avg += napetost_mV;
  N++;



}
