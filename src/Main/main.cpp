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

motor motor_right(M1_IN1, M1_IN2, CHANNEL_M1_IN1, CHANNEL_M1_IN2); 
motor motor_left(M2_IN1, M2_IN2, CHANNEL_M2_IN1, CHANNEL_M2_IN2);

Controller balancer_controller(3,6,3); 

ESP32Encoder left_encoder; 
ESP32Encoder right_encoder; 

float SETPOINT_theta= -PI/2; 
const float angular_robot = 0 ;
float linear_robot = 0 ; 

float left_speed, right_speed ;


float imu_orientation;

void debug();

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() {

  Serial.begin(9600);
  SerialBT.begin("ESP32test"); //Bluetooth device name

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

  while(Serial.available()==0){

  }

  SETPOINT_theta = Serial.parseFloat  ();

  float* imu_orientation = get_euler_angles(); 

  linear_robot = balancer_controller.output(SETPOINT_theta,imu_orientation[2]);

  left_speed = cinematic_left(linear_robot,angular_robot);
  right_speed =  cinematic_right(linear_robot,angular_robot);
  
  motor_left.cmd(left_speed);
  motor_right.cmd(right_speed);

  Serial.println("");
  Serial.print("left vel: "); 
  Serial.print(left_speed);
  Serial.print(" | right vel: ");
  Serial.print(right_speed); 
  Serial.println("");
  // odom(left_encoder.getCount(), right_encoder.getCount(), imu_orientation[0]);

  debug();
  SerialBT.println(SETPOINT_theta);
}


void debug(){
    Serial.print("Euler:");
    // Serial.print(orientation[0]);
    // Serial.print(", ");
    // Serial.print(orientation[1]);
    // Serial.print(", ");
    Serial.print(orientation[2]);

    balancer_controller.debug();

    Serial.print("|L: ");
    Serial.print(motor_left.PWM);
    Serial.print("_R: ");
    Serial.print(motor_right.PWM);
  
    Serial.println("");




}