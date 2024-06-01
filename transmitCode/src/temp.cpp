/**
 * TCA9548 I2CScanner.ino -- I2C bus scanner for Arduino
 *
 * Based on https://playground.arduino.cc/Main/I2cScanner/
 *
 */
#include <Arduino.h>
#include "Wire.h"
#include <MPU6050.h>

MPU6050 mpu;
#define statusLed 5
#define TCAADDR 0x70
#define MPU 6

unsigned long timer = 0;
float timeStep = 0.01;



//you need to select the multiplexer channel every time you use something


void tcaselect(uint8_t i);
void readMPU();
void flashLed(int status);

void setup()
{
    pinMode(statusLed, OUTPUT);
    while (!Serial);
    delay(1000);

    Wire.begin();
    
    Serial.begin(115200);
    tcaselect(MPU);
    while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
    mpu.calibrateGyro();

  // Set threshold sensivty. Default 3.
  // If you don't want use threshold, comment this line or set 0.
  mpu.setThreshold(3);
  flashLed(1);
    
}

void loop() 
{
  
  readMPU();
  delay((timeStep*1000) - (millis() - timer));
  
  
}

void flashLed(int status) {
  digitalWrite(statusLed, status);
}

void tcaselect(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}

void readMPU() {
  float PITCH = 0;
float ROLL = 0;
float YAW = 0;
  tcaselect(MPU);
  timer = millis();
  // Read normalized values 
  Vector normAccel = mpu.readNormalizeAccel();
  Vector norm = mpu.readNormalizeGyro();

  // Calculate Pitch & Roll
  int absPitch = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis*normAccel.YAxis + normAccel.ZAxis*normAccel.ZAxis))*180.0)/M_PI;
  int absRoll = (atan2(normAccel.YAxis, normAccel.ZAxis)*180.0)/M_PI;
  //temp
  float temp = mpu.readTemperature();
  // Calculate Gyro
  PITCH = PITCH + norm.YAxis * timeStep;
  ROLL = ROLL + norm.XAxis * timeStep;
  YAW = YAW + norm.ZAxis * timeStep;



  // Output
  Serial.print(" Temp = ");
  Serial.print(temp);
  Serial.print(" Pitch = ");
  Serial.print(absPitch);
  Serial.print(" Roll = ");
  Serial.print(absRoll);
  Serial.print(" Pitch = ");
  Serial.print(PITCH);
  Serial.print(" Roll = ");
  Serial.print(ROLL);  
  Serial.print(" Yaw = ");
  Serial.println(YAW);
}