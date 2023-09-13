#include <Arduino.h>

// Motors pin A
#define AIN1 21
#define AIN2 22

// Motors pin B 
#define BIN1 21
#define BIN2 22

const int freq = 1000; 

const int channelA1 = 1;
const int channelA2 = 2;
const int channelB1 = 3;
const int channelB2 = 4; 

const int resolution = 8; 

void setup() {

    Serial.begin(9600);

    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT); 

    pinMode(BIN1, OUTPUT); 
    pinMode(BIN2, OUTPUT);

    ledcSetup(channelA1, freq, resolution); 
    ledcSetup(channelA2, freq, resolution); 

    ledcSetup(channelB1, freq, resolution);
    ledcSetup(channelB2, freq, resolution);

    ledcAttachPin(AIN1, channelA1); 
    ledcAttachPin(AIN2, channelA2); 

    ledcAttachPin(BIN1, channelB1); 
    ledcAttachPin(BIN2, channelB2); 

}

void loop() {

    //PWM for the motors A and B 
    digitalWrite(AIN1, LOW); 
    digitalWrite(BIN1, LOW); 

    for(int vel=0; vel< 1000; vel++) {

        ledcWrite(channelA2, vel); 
        ledcWrite(channelB2, vel); 
        Serial.println(vel);
        delay(10);
    }

    delay(500);

    //PWM for the motors A and B 
    digitalWrite(AIN2, LOW); 
    digitalWrite(BIN2, LOW); 

    for(int vel=0; vel< 1000; vel++) {

        ledcWrite(channelA1, vel); 
        ledcWrite(channelB1, vel); 
        Serial.println(vel);
        delay(10);
    }


}