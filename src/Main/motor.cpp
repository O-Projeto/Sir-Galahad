#include "motor.h"

//! considera que IN1 é positivo

motor::motor(int inA, int inB, int channelA, int channelB)
{
    IN_A = inA;
    IN_B = inB; 

    CHANNEL_A = channelA; 
    CHANNEL_B = channelB; 

}

void motor::setup()
{
    pinMode(IN_A, OUTPUT);
    pinMode(IN_B, OUTPUT); 

    ledcSetup(CHANNEL_A, FREQUENCY_, RESOLUTION_); 
    ledcSetup(CHANNEL_B, FREQUENCY_, RESOLUTION_); 

    ledcAttachPin(IN_A, CHANNEL_A);
    ledcAttachPin(IN_B, CHANNEL_B);
}

void motor::cmd(float speed)
{
    if (speed > MAX_SPEED){
        speed = MAX_SPEED; 
    }

    if (speed < -10.00){
        Serial.print("menor que vel min");
        speed = -MAX_SPEED;
    }

    PWM = speed*(MAX_PWM/MAX_SPEED); 
    // Serial.println(map(speed, MIN_SPEED, MAX_SPEED, MIN_PWM, MAX_PWM));

    // if (abs(PWM) < 400 && PWM > 0) {
    //     PWM = 400; 
    // }

    // if (abs(PWM) < 400 && PWM < 0) {
    //     PWM = -400; 
    // }

    int PWM_ = round(PWM); 

    // Serial.print("-->  PWM É "); 
    // Serial.println(PWM_); 

    // --------------------------- cmd_vel
    if (PWM > 0){
        ledcWrite(CHANNEL_A, PWM_);
        digitalWrite(IN_B, LOW); 
    }

    if (PWM < 0){
        ledcWrite(CHANNEL_B, abs(PWM_));
        digitalWrite(IN_A, LOW);
    }

    if (PWM == 0){
        digitalWrite(IN_A, LOW);
        digitalWrite(IN_B, LOW);
    }
}