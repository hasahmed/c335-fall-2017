#ifndef _APPS_H_
#define _APPS_H_
void compassApp(float *accelData, float *magData);
float getCompassAngle(float *accelData, float *magData);
void compassLights(float compassData);

#endif //_APPS_H_
