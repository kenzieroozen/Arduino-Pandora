#include <Servo.h>
#define CommonSenseMetricSystem

Servo microServo;
int sensor = 8;
int metal;

int trigger = 7;
int echo = 6;

int distance() {
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);

  digitalWrite(trigger, HIGH);  
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  long duration = pulseIn(echo, HIGH);
#ifdef CommonSenseMetricSystem
  float distance = duration * 0.034 / 2;
#endif
#ifdef ImperialNonsenseSystem
  float distance = (duration / 2) / 73.914;
#endif

  return distance;
}

void setup() {
  Serial.begin(9600);
  microServo.attach(9);
  microServo.write(45);
  pinMode(sensor, INPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
}

int jarakBenda;
int nomorSampah = 0;
int adaSampah = 0;

void loop() {
  jarakBenda = distance();

  delay(1000);
  metal = digitalRead(sensor);

  if (jarakBenda < 10 && adaSampah == 0) {
    nomorSampah += 1;
    adaSampah = 1;
    Serial.print("Sampah #");
    Serial.print(nomorSampah);
    Serial.print(" terdeteksi. ");
    Serial.print(jarakBenda);
    Serial.println(" cm");
  

    if (metal == 0) {  //deteksi metal
      Serial.println("Metal detected");
      microServo.write(90);

      delay(3000);
      microServo.write(45);
    } else {
      Serial.println("No metal detected");
      microServo.write(0);

      delay(3000);
      microServo.write(45);
    }

    delay(5000);

    adaSampah = 0;
    Serial.println("Success reset");
  }

  delay(2000);
}
