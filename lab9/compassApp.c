#include <f3d_led.h>
#include <f3d_lcd_sd.h>
#include <stdio.h>
#include <math.h>
#include "apps.h"



void compassApp_callOnce(){
    LCD_drawCompassApp();

}
void compassApp(float *accelData, float *magData, int appHasChanged){
    if (appHasChanged)
        compassApp_callOnce();
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
void LCD_drawCompassApp(){
    //runningCompassApp = 1;
    f3d_lcd_fillScreen2(BLACK);
    drawString(12, HEIGHT / 2, "SEE LEDs FOR NORTH", RED, BLACK); 
}
int ledNumberConvert(int led){
    led = 9 - led;
    switch(led){
        case 8:
            return 0;
        default: return led;
    }
}
