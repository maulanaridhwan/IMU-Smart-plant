# IMU-Smart-plant
// Basic demo for accelerometer readings from Adafruit MPU6050

#include <TimeLib.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#define valve1 2
#define valve2 4

Adafruit_MPU6050 mpu;
int pitch, jam, menit;

void setup(void) {
  setTime(7, 59, 50, 19, 6, 2023);  // Format: setTime(hour, minute, second, day, month, year)

  // Menampilkan waktu awal
  Serial.print("Waktu awal: ");

  Serial.begin(115200);
  pinMode(valve1, OUTPUT);
  pinMode(valve2, OUTPUT);
  while (!Serial)
    delay(10);  // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  Serial.println("");
  delay(100);
}

void loop() {
  jam = hour();
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  pitch = (a.acceleration.y);
  Serial.println(pitch);
  if (jam == 8) {
    if (pitch <= -4) {
      digitalWrite(valve1, HIGH);
      Serial.println("Valve 1 NYALA");

    } else {
      digitalWrite(valve1, LOW);
      digitalWrite(valve2, HIGH);
      Serial.println("Valve 2 NYALA, VALVE 1 MATI");
      delay(5000);
      digitalWrite(valve2, LOW);
      Serial.println("stp ");
      delay(3600000);
    }
  }

  Serial.println("test");
  delay(500);
}
