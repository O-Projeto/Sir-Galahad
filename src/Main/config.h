#include <Arduino.h>

// --------------------------- MOTORS 
#define M1_IN1 25
#define M1_IN2 33 
#define M2_IN1 27
#define M2_IN2 26

// --------------------------- PWM
#define CHANNEL_M1_IN1 1
#define CHANNEL_M1_IN2 2
#define CHANNEL_M2_IN1 3
#define CHANNEL_M2_IN2 4

#define FREQUENCY 1000
#define RESOLUTION 10

// --------------------------- SATURANTION
#define PWM_SATURATION 800

// --------------------------- ENCODERS 
#define EN_A1 39
#define EN_A2 36
#define EN_B1 34
#define EN_B2 35 

#define PRP 240

// --------------------------- DEBUG
#define LED_BUILD_IN 2

// --------------------------- ODOMETRY
#define L  0.145 
#define R 0.0325

#define MAX_SPEED 10.00
#define MIN_SPEED 0

#define MAX_PWM 1023.00