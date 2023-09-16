#include "Main/config.h"

void setup() {

    pinMode(M1_IN1, OUTPUT);
    pinMode(M1_IN2, OUTPUT); 

    pinMode(M2_IN1, OUTPUT); 
    pinMode(M2_IN2, OUTPUT);

    ledcSetup(CHANNEL_M1_IN1, FREQUENCY, RESOLUTION); 
    ledcSetup(CHANNEL_M1_IN2, FREQUENCY, RESOLUTION); 

    ledcSetup(CHANNEL_M2_IN1, FREQUENCY, RESOLUTION);
    ledcSetup(CHANNEL_M2_IN2, FREQUENCY, RESOLUTION);

    ledcAttachPin(M1_IN1, CHANNEL_M1_IN1); 
    ledcAttachPin(M1_IN2, CHANNEL_M1_IN2); 

    ledcAttachPin(M2_IN1, CHANNEL_M2_IN1); 
    ledcAttachPin(M1_IN2, CHANNEL_M2_IN2); 

}

void loop() {

    //PWM for the motors A and B 
    digitalWrite(M1_IN1, LOW); 
    digitalWrite(M1_IN2, LOW); 

    for(int vel=0; vel< 1000; vel++) {

        ledcWrite(CHANNEL_M1_IN1, vel); 
        ledcWrite(CHANNEL_M1_IN2, vel); 
        Serial.println(vel);
        delay(10);
    }

    delay(500);

    //PWM for the motors A and B 
    digitalWrite(M2_IN1, LOW); 
    digitalWrite(M2_IN2, LOW); 

    for(int vel=0; vel< 1000; vel++) {

        ledcWrite(CHANNEL_M2_IN1, vel); 
        ledcWrite(CHANNEL_M2_IN2, vel); 
        Serial.println(vel);
        delay(10);
    }


}