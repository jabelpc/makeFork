
#include <Wire.h>

// Variable du gyroscope
int16_t gyroAcX, gyroAcY, gyroAcZ, gyroTmp, gyroGyX, gyroGyY, gyroGyZ;


const int gyroMPU_addr = 0x68;  // I2C address of the MPU-6050


void gyroInit() 
  {
  Wire.begin();
  Wire.beginTransmission(gyroMPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  //Serial.begin(9600);
  }

void gyroData()
{
  Wire.beginTransmission(gyroMPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(gyroMPU_addr, 14, true);  // request a total of 14 registers
                       /*
                       AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
                       AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
                       AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
                       Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
                       */
  gyroGyX = Wire.read() << 8 | Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  gyroGyY = Wire.read() << 8 | Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  gyroGyZ = Wire.read() << 8 | Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
}

void gyroDataPrint ()
{
  Serial.print(" | GyX = "); Serial.print(gyroGyX);
  Serial.print(" | GyY = "); Serial.print(gyroGyY);
  Serial.print(" | GyZ = "); Serial.println(gyroGyZ);
  delay(333);
}


