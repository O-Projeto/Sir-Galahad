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

Controller zone_one_controller(0.1,0.015,0.00015); 
Controller zone_two_controller(0.02,0.005,0.0001);
Controller zone_three_controller(0.02, 0.005, 0.0001); 

// gain scheduled
// zone 1 : 80° a 100° 
// zone 2 : 115° a 100°
// zone 3 : 80° a 65°

ESP32Encoder left_encoder; 
ESP32Encoder right_encoder; 

const float STANDARD_SETPOINT = 90.00;
float SETPOINT_theta = 90.00; 
float robot_pitch = 0.0; 
const float angular_robot = 0 ;
float linear_robot = 0 ; 

float left_speed, right_speed ;


float imu_orientation;

void blu_debug_z1();
void blu_debug_z2(); 
void blu_debug_z3(); 


#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() {

  Serial.begin(115200);
  SerialBT.begin("Galahad"); //Bluetooth device name

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

  if(Serial.available()){
    SETPOINT_theta = Serial.parseFloat();
  } else {
    SETPOINT_theta = STANDARD_SETPOINT;
  }
  SerialBT.println("-------------------SETPOINT-------------------------");
  SerialBT.print(SETPOINT_theta);
  SerialBT.println("");

  float* imu_orientation = get_euler_angles(); 
  robot_pitch = imu_orientation[2]; 

  if (robot_pitch > 75 && robot_pitch < 105){

    linear_robot = zone_one_controller.output(SETPOINT_theta,robot_pitch);
    SerialBT.println("-------------------ZONA 1-------------------------");
    blu_debug_z1();
  }

  if (robot_pitch > 105){
    
    linear_robot = zone_two_controller.output(SETPOINT_theta, robot_pitch); 
    SerialBT.println("-------------------ZONA 2-------------------------");
    blu_debug_z2();
  }

  if (robot_pitch < 75){
    
    linear_robot = zone_three_controller.output(SETPOINT_theta, robot_pitch); 
    SerialBT.println("-------------------ZONA 3-------------------------");
    blu_debug_z3(); 
  }

  left_speed = cinematic_left(linear_robot,angular_robot);
  right_speed =  cinematic_right(linear_robot,angular_robot);
  
  motor_left.cmd(left_speed);
  motor_right.cmd(right_speed);

  // Serial.println("");
  // Serial.print("left vel: "); 
  // Serial.print(left_speed);
  // Serial.print(" | right vel: ");
  // Serial.print(right_speed); 
  // Serial.println("");
  // // odom(left_encoder.getCount(), right_encoder.getCount(), imu_orientation[0]);

  // debug();
  // blu_debug();

}

void blu_debug_z2(){

  SerialBT.print(" |SP: ");
  SerialBT.print(zone_two_controller.setpoint_);
  SerialBT.print(" |CV: ");
  SerialBT.print(zone_two_controller.current_value_);

  SerialBT.print(" ||error: ");
  SerialBT.print(zone_two_controller.error);
  SerialBT.print(" |P: ");
  SerialBT.print(zone_two_controller.proportional());
  SerialBT.print(" |I: ");
  SerialBT.print(zone_two_controller.integrative());
  SerialBT.print("|D: ");
  SerialBT.print(zone_two_controller.derivative());

  SerialBT.print(" |OV: ");
  SerialBT.print(zone_two_controller.output_value);
  SerialBT.println("");

}

void blu_debug_z1(){

  SerialBT.print(" |SP: ");
  SerialBT.print(zone_one_controller.setpoint_);
  SerialBT.print(" |CV: ");
  SerialBT.print(zone_one_controller.current_value_);

  SerialBT.print(" ||error: ");
  SerialBT.print(zone_one_controller.error);
  SerialBT.print(" |P: ");
  SerialBT.print(zone_one_controller.proportional());
  SerialBT.print(" |I: ");
  SerialBT.print(zone_one_controller.integrative());
  SerialBT.print("|D: ");
  SerialBT.print(zone_one_controller.derivative());

  SerialBT.print(" |OV: ");
  SerialBT.print(zone_one_controller.output_value);
  SerialBT.println("");

}

void blu_debug_z3(){

  SerialBT.print(" |SP: ");
  SerialBT.print(zone_three_controller.setpoint_);
  SerialBT.print(" |CV: ");
  SerialBT.print(zone_three_controller.current_value_);

  SerialBT.print(" ||error: ");
  SerialBT.print(zone_three_controller.error);
  SerialBT.print(" |P: ");
  SerialBT.print(zone_three_controller.proportional());
  SerialBT.print(" |I: ");
  SerialBT.print(zone_three_controller.integrative());
  SerialBT.print("|D: ");
  SerialBT.print(zone_three_controller.derivative());

  SerialBT.print(" |OV: ");
  SerialBT.print(zone_three_controller.output_value);
  SerialBT.println("");
}