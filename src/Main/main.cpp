#include "Main/config.h"
#include "Main/motor.h"

motor motor_right(M1_IN1, M1_IN2, CHANNEL_M1_IN1, CHANNEL_M1_IN2); 
motor motor_left(M2_IN1, M2_IN2, CHANNEL_M2_IN1, CHANNEL_M2_IN2);

void setup() {
  // motor_right.setup();
  // motor_left.setup();

  // motor_right.cmd(100);
  // motor_left.cmd(100);
}

void loop() {
  // put your main code here, to run repeatedly:
}
