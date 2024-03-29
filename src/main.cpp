#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>


//SCL=> D5 , SDA=> D4
#define interrupt_outpt D12
void printGrant(float, float, float);

bool status_ship = false;

Adafruit_MPU6050 mpu;

void setup(void) {
  Serial.begin(115200);
  pinMode(interrupt_outpt, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  while (!Serial)
    delay(10);

  Serial.println("Adafruit MPU6050 test!");

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");
  delay(100);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  float gran_x, gran_y, gran_z;
  gran_x = a.acceleration.x;
  gran_y = a.acceleration.y;
  gran_z = a.acceleration.z;
  
  if(gran_z < -1.00 ){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(10);
    if(!status_ship){
      digitalWrite(interrupt_outpt, HIGH);
      delay(100);
      digitalWrite(interrupt_outpt, LOW);
      status_ship=!status_ship;
    }

  }
  else{
    digitalWrite(LED_BUILTIN, LOW); 
    delay(10); 
    if(status_ship){
      digitalWrite(interrupt_outpt, HIGH);
      delay(100);
      digitalWrite(interrupt_outpt, LOW);
      status_ship=!status_ship;
    }
  }
  printGrant(gran_x, gran_y, gran_z);
  delay(500);
}

void printGrant(float x, float y, float z) {
  Serial.print("Acceleration X: ");
  Serial.print(x);
  Serial.print(", Y: ");
  Serial.print(y);
  Serial.print(", Z: ");
  Serial.print(z);
  Serial.println("");

}