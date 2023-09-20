#include "Main/config.h"

#include "Wire.h"
#include "DFRobot_BMP280.h"
#include "DFRobot_BNO055.h"

// object class
typedef DFRobot_BNO055_IIC    BNO; 
typedef DFRobot_BMP280_IIC    BMP;    

// i2c connection
BNO   bno(&Wire, 0x28);    // input TwoWire interface and IIC address
BMP   bmp(&Wire, BMP::eSdoLow);

#define SEA_LEVEL_PRESSURE    1021.0f   // sea level pressure (pressão atmosferica)

// orientation vars 
float linear_acceleration[3];           // [x, y, z]

void BNO_BMP_setup()
{
    pinMode(LED_BUILD_IN, OUTPUT);
    digitalWrite(LED_BUILD_IN, LOW);

    bno.reset();
    bmp.reset();

    while(bno.begin() != BNO::eStatusOK) {
        Serial.println("bno begin faild");
        bno.reset();
    }

    while(bmp.begin()!= BMP::eStatusOK) {
        Serial.println("bmp begin failed");
        bmp.reset();
    }

    Serial.println("bno begin success");
    Serial.println("bmp begin success");

    digitalWrite(LED_BUILD_IN, HIGH);

}

// #define printAxisData(sAxis) \
//   Serial.print(" x: "); \
//   Serial.print(sAxis.x); \
//   Serial.print(" y: "); \
//   Serial.print(sAxis.y); \
//   Serial.print(" z: "); \
//   Serial.println(sAxis.z)

float* BNO_linear_acceleration(){
    BNO::sAxisAnalog_t linear_accel; 

    linear_accel = bno.getAxis(BNO::eAxisLia); 

    linear_acceleration[1] = linear_accel.x; 
    linear_acceleration[2] = linear_accel.y; 
    linear_acceleration[3] = linear_accel.z;

    Serial.print("Linear acceleration:"); 
    Serial.print(linear_accel.x); 
    Serial.print("\t ");
    Serial.print(linear_accel.y); 
    Serial.print("\t ");
    Serial.print(linear_accel.z); 
    Serial.print("\t ");
    
    return linear_acceleration; 
}

// void loop()
// {
//   BNO::sAxisAnalog_t   sAccAnalog, sMagAnalog, sGyrAnalog, sLiaAnalog, sGrvAnalog;
//   BNO::sEulAnalog_t    sEulAnalog;
//   BNO::sQuaAnalog_t    sQuaAnalog;
//   sAccAnalog = bno.getAxis(BNO::eAxisAcc);    // read acceleration
//   sMagAnalog = bno.getAxis(BNO::eAxisMag);    // read geomagnetic
//   sGyrAnalog = bno.getAxis(BNO::eAxisGyr);    // read gyroscope
//   sLiaAnalog = bno.getAxis(BNO::eAxisLia);    // read linear acceleration
//   sGrvAnalog = bno.getAxis(BNO::eAxisGrv);    // read gravity vector
//   sEulAnalog = bno.getEul();                  // read euler angle
//   sQuaAnalog = bno.getQua();                  // read quaternion
//   Serial.println();
//   Serial.println("############################# BNO DATA PRINT BEGIN ######################################");
//   Serial.print("acc analog: (unit mg)       "); printAxisData(sAccAnalog);
//   Serial.print("mag analog: (unit ut)       "); printAxisData(sMagAnalog);
//   Serial.print("gyr analog: (unit dps)      "); printAxisData(sGyrAnalog);
//   Serial.print("lia analog: (unit mg)       "); printAxisData(sLiaAnalog);
//   Serial.print("grv analog: (unit mg)       "); printAxisData(sGrvAnalog);
//   Serial.print("eul analog: (unit degree)   "); Serial.print(" head: "); Serial.print(sEulAnalog.head); Serial.print(" roll: "); Serial.print(sEulAnalog.roll);  Serial.print(" pitch: "); Serial.println(sEulAnalog.pitch);
//   Serial.print("qua analog: (no unit)       "); Serial.print(" w: "); Serial.print(sQuaAnalog.w); printAxisData(sQuaAnalog);
//   Serial.println("############################# BNO DATA PRINT BEGIN ######################################");

//   float   temp = bmp.getTemperature();
//   uint32_t    press = bmp.getPressure();
//   float   alti = bmp.calAltitude(SEA_LEVEL_PRESSURE, press);

//   Serial.println();
//   Serial.println("############################# BMP DATA PRINT BEGIN ######################################");
//   Serial.print("temperature (unit Celsius): "); Serial.println(temp);
//   Serial.print("pressure (unit pa):         "); Serial.println(press);
//   Serial.print("altitude (unit meter):      "); Serial.println(alti);
//   Serial.println("############################# BMP DATA PRINT BEGIN ######################################");

//   delay(500);
// }
