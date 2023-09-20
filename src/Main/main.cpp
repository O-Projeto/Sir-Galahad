// pin config 
#include "Main/config.h"

// auxiliary functions
#include "Main/motor.h"
#include "Main/controller.h"
#include "Main/encoder.h"
#include "Main/imu.h"

motor motor_right(M1_IN1, M1_IN2, CHANNEL_M1_IN1, CHANNEL_M1_IN2); 
motor motor_left(M2_IN1, M2_IN2, CHANNEL_M2_IN1, CHANNEL_M2_IN2);

Controller left_controller(1,0,0); 
Controller right_controller(1,0,0); 

Encoder encoders(EN_A1, EN_A2, EN_B1, EN_B2); 

float linear_accel[3]; 

void setup() {

  Serial.begin(115200);

  motor_right.setup();
  motor_left.setup();

  motor_right.cmd(500);
  motor_left.cmd(500);
}

void loop() {

  float* linear_accel = BNO_linear_acceleration();

}
