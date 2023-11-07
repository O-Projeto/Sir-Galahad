// pin config 
#include "Main/config.h"

// auxiliary functions
#include "Main/motor.h"
#include "Main/controller.h"
#include "Main/odom.h"
#include "Main/imu.h"
#include "Main/kinematics.h"

// auxiliary libraries 
#include <ESP32Encoder.h>



// #include "Main/imu.h"

motor motor_right(M1_IN1, M1_IN2, CHANNEL_M1_IN1, CHANNEL_M1_IN2); 
motor motor_left(M2_IN1, M2_IN2, CHANNEL_M2_IN1, CHANNEL_M2_IN2);

Controller balancer_controller(0.7,0.001,0.008); 

ESP32Encoder left_encoder; 
ESP32Encoder right_encoder; 

float SETPOINT_theta= -PI/2; 
const float angular_robot = 0 ;
float linear_robot = 0 ; 

float left_speed, right_speed ;
String message = String(7);

float imu_orientation;

// void debug();

void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(115200);

  // encoder setup
  ESP32Encoder::useInternalWeakPullResistors=UP; 
  left_encoder.attachHalfQuad(EN_A1, EN_A2);
  right_encoder.attachHalfQuad(EN_B1, EN_B2); 

  motor_right.setup();
  motor_left.setup();

  bno_setup(); 
  //bmp_setup(); 

}

void loop() {
  while(Serial.available()) {
    message = Serial.readString();
    for (int i = 0; i < message.length(); i++) {
      Serial.write(message[i]);
    }
    if (message == "Forward") {
      SETPOINT_theta = -1.48353;
      digitalWrite(2,HIGH);
    } else {
      SETPOINT_theta= -PI/2;
    }
  }

  float* imu_orientation = get_euler_angles(); 

  linear_robot = balancer_controller.output(SETPOINT_theta,imu_orientation[2]);

  left_speed = cinematic_left(linear_robot,angular_robot);
  right_speed =  cinematic_right(linear_robot,angular_robot);
  
  motor_left.cmd(left_speed);
  motor_right.cmd(right_speed);

  // Serial.println(linear_robot);
  // Serial.println(left_speed); 
  // odom(left_encoder.getCount(), right_encoder.getCount(), imu_orientation[0]);

  // debug();
}


void debug(){
    // Serial.print("Euler:");
    // Serial.print(orientation[0]);
    // Serial.print(", ");
    // Serial.print(orientation[1]);
    // Serial.print(", ");
    // Serial.print(orientation[2]);

    balancer_controller.debug();

    // Serial.print("|L: ");
    // Serial.print(motor_left.PWM);
    // Serial.print("_R: ");
    // Serial.print(motor_right.PWM);
  
    // Serial.println("");




}