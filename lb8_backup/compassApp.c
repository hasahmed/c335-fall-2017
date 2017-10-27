#include <f3d_led.h>
#include <stdio.h>
#include <math.h>
#include "apps.h"
void compassApp(float *accelData, float *magData){
    float compassAngle = getCompassAngle(accelData, magData);
    compassLights(compassAngle);
}
float getCompassAngle(float *accelData, float *magData){
    float compassAngle, Xh, Yh, pitch, roll;
    pitch = (atanf(accelData[0] / sqrt(pow(accelData[1], 2) + pow(accelData[2], 2))));
    roll = (atanf(accelData[1]/sqrt(pow(accelData[0], 2) + pow(accelData[2], 2))));

    Xh = magData[0]*cos(pitch)+magData[2]*sin(pitch);
    Yh = magData[0]*sin(roll)*sin(pitch) + magData[1] * cos(roll) - magData[2] * sin(roll)*cos(pitch);

    //pitch = (atanf(accelData[0] / sqrt(pow(accelData[1], 2) + pow(accelData[2], 2))));
    compassAngle = fabs((atan2(Yh, Xh)) * 180 / M_PI + 180.0f);
    return compassAngle;
}

void compassLights(float dir){
    int led = (int)floor(dir / 45.0f) + 1;
    led = ledNumberConvert(led);
    f3d_led_on(led);
    int i;
    for(i; i < 8; i++){
        if(i != led)
            f3d_led_off(i);
    }
}
