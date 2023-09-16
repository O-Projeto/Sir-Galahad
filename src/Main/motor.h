#include "Main/config.h"

class motor
{
    private:

    public:
        int IN_A;
        int IN_B;
        int CHANNEL_A;
        int CHANNEL_B;
        int PWM;

        int FREQUENCY_ = FREQUENCY;
        int RESOLUTION_ = RESOLUTION;
        int SATURATION = PWM_SATURATION; 
    
        motor(int inA, int inB, int channelA, int channelB);
        void setup();
        void cmd(int pwm); 
};