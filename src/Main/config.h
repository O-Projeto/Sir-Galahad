#include <Arduino.h>

// --------------------------- MOTORS 
#define M1_IN1 33
#define M1_IN2 25 
#define M2_IN1 26
#define M2_IN2 27 

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
#define EN_A1 36
#define EN_A2 39
#define EN_B1 34
#define EN_B2 35 

// --------------------------- DEBUG
#define LED_BUILD_IN 2