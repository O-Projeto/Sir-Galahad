#include "motor.h"

//! considera que IN1 e positivo

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

void motor::cmd(int pwm)
{
    PWM = pwm; 


    // --------------------------- saturation
    if (PWM >= SATURATION){
        PWM = SATURATION;
    }

    if (PWM <= -SATURATION){
        PWM = -SATURATION;
    }


    // --------------------------- cmd_vel
    if (PWM > 0){
        ledcWrite(CHANNEL_A, PWM);
        digitalWrite(IN_B, LOW); 
    }

    if (PWM < 0){
        ledcWrite(CHANNEL_B, abs(PWM));
        digitalWrite(IN_A, LOW);
    }

    if (PWM == 0){
        digitalWrite(IN_A, LOW);
        digitalWrite(IN_B, LOW);
    }
}