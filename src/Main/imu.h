#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_BMP280.h>
#include <utility/imumaths.h>
#include <SPI.h>
#include "config.h"

 // Possible vector values can be:
 // - VECTOR_ACCELEROMETER - m/s^2
 // - VECTOR_MAGNETOMETER - uT
 // - VECTOR_GYROSCOPE - rad/s
 // - VECTOR_EULER - degrees
 // - VECTOR_LINEARACCEL - m/s^2
 // - VECTOR_GRAVITY - m/s^2

float acceleration[3];
float acceleration_g[3]; 
float orientation[3];
float magnetic[3]; 
float rotation[3];
float quaternion[4];


/* Set the delay between fresh samples */
uint16_t BNO055_SAMPLERATE_DELAY_MS = 100;

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);
Adafruit_BMP280 bmp; // use I2C interface

Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();

void bno_setup() {

    /* Initialise the sensor */
    while (!bno.begin())
    {
        // Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
        // while (1);
    }
    digitalWrite(LED_BUILD_IN, HIGH); 

    uint8_t system, gyro, accel, mag = 0;
    bno.getCalibration(&system, &gyro, &accel, &mag);
    // Serial.println();
    // Serial.print("Calibration: Sys=");
    // Serial.print(system);
    // Serial.print(" Gyro=");
    // Serial.print(gyro);
    // Serial.print(" Accel=");
    // Serial.print(accel);
    // Serial.print(" Mag=");
    // Serial.println(mag);
}

void bmp_setup() {
    /* Initialise the sensor */
    while (!bmp.begin()){
        // Serial.println("Ooops, no BMP280 detected ... Check your wiring or I2C ADDR!");
    } 
    digitalWrite(LED_BUILD_IN, HIGH); 

    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                    Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                    Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                    Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                    Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
    
    bmp_temp->printSensorDetails();
}

// ACCELERATION - m/s^2
float* get_linear_acceleration_with_gravity(){

     /* Get a new sensor event */
    sensors_event_t event;
    bno.getEvent(&event, Adafruit_BNO055::VECTOR_GRAVITY);

    acceleration_g[0] = event.acceleration.x;
    acceleration_g[1] = event.acceleration.y;
    acceleration_g[2] = event.acceleration.z;

    // Serial.print("Aceleração (considerando gravidade): ");
    // Serial.print("x = ");
    // Serial.print(acceleration_g[0]);
    // Serial.print("   |   y = "); 
    // Serial.print(acceleration_g[1]);
    // Serial.print("   |   z = "); 
    // Serial.println(acceleration_g[2]);
  
    return acceleration_g; 
}

// ACCELERATION - m/s^2
float* get_linear_accel_without_gravity(){

     /* Get a new sensor event */
    sensors_event_t event;
    bno.getEvent(&event, Adafruit_BNO055::VECTOR_LINEARACCEL);

    acceleration[0] = event.acceleration.x;
    acceleration[1] = event.acceleration.y;
    acceleration[2] = event.acceleration.z;

    // Serial.print("Aceleração (considerando gravidade): ");
    // Serial.print("x = ");
    // Serial.print(acceleration[0]);
    // Serial.print("   |   y = "); 
    // Serial.print(acceleration[1]);
    // Serial.print("   |   z = "); 
    // Serial.println(acceleration[2]);
  
    return acceleration; 
}

// ORIENTATION - radians
float* get_euler_angles(){

    /* Get a new sensor event */
    sensors_event_t orientationData;
    bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);

    orientation[0] = orientationData.orientation.x * (3.141592 / 180);
    orientation[1] = orientationData.orientation.y * (3.141592 / 180);
    orientation[2] = orientationData.orientation.z * (3.141592 / 180);

    // Serial.print("Ângulos de euler: ");
    // Serial.print("pitch = ");
    // Serial.print(orientation[0]);
    // Serial.print("   |   roll = "); 
    // Serial.print(orientation[1]);
    // Serial.print("   |   yaw = "); 
    // Serial.println(orientation[2]);

    return orientation; 
}

// MAGNETIC FIELD - uT
float* get_magnetic_orientation() {

    /* Get a new sensor event */
    sensors_event_t event;
    bno.getEvent(&event, Adafruit_BNO055::VECTOR_MAGNETOMETER);

    magnetic[0] = event.magnetic.x;
    magnetic[1] = event.magnetic.y;
    magnetic[2] = event.magnetic.z;

    // Serial.print("Orientação campo magnetico: ");
    // Serial.print("x = ");
    // Serial.print(magnetic[0]);
    // Serial.print("   |   y = "); 
    // Serial.print(magnetic[1]);
    // Serial.print("   |   z = "); 
    // Serial.println(magnetic[2]);

    return magnetic; 
}

// GYROSCOPE ROTATION - rad/s  
float* get_angular_vel(){

    /* Get a new sensor event */
    sensors_event_t event;
    bno.getEvent(&event, Adafruit_BNO055::VECTOR_GYROSCOPE);

    rotation[0] = event.gyro.x;
    rotation[1] = event.gyro.y;
    rotation[2] = event.gyro.z;

    // Serial.print("Velocidade angular: ");
    // Serial.print("x = ");
    // Serial.print(rotation[0]);
    // Serial.print("   |   y = "); 
    // Serial.print(rotation[1]);
    // Serial.print("   |   z = "); 
    // Serial.println(rotation[2]);
    
    return rotation; 
}

float* get_quaternion() {
    
    imu::Quaternion quat = bno.getQuat();

    quaternion[0] = quat.x();
    quaternion[1] = quat.y();
    quaternion[2] = quat.z();
    quaternion[3] = quat.w(); 

    // Serial.print("Quaternions: ");
    // Serial.print("x = ");
    // Serial.print(quaternion[0]);
    // Serial.print("   |   y = "); 
    // Serial.print(quaternion[1]);
    // Serial.print("   |   z = "); 
    // Serial.print(quaternion[2]);
    // Serial.print("   |   w = "); 
    // Serial.println(quaternion[3]);

    return quaternion;
}

// Temperature -> °C
float get_temperature() {
    
    sensors_event_t temp_event;
    bmp_temp->getEvent(&temp_event);

    // Serial.print("Temperatura: "); 
    // Serial.println(temp_event.temperature); 
    return temp_event.temperature; 
}

// Pressure -> hPa
float get_pressure() {

    sensors_event_t pressure_event;
    bmp_pressure->getEvent(&pressure_event);

    return pressure_event.pressure; 
}

