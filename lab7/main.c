/* main.c ---
 *
 * Filename: main.c
 * Description:
 * Hasan Y Ahmed, Kyle
 * Created: 10/16/17
/* Code: */


#include <stm32f30x.h> // Pull in include files for F30x standard drivers
#include <f3d_uart.h>
#include <f3d_user_btn.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_rtc.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <f3d_gyro.h>
#include <f3d_led.h>
#include <stm32f30x_dma.h>
#include <stm32f30x_dac.h>

#include <math.h>
#include <stdio.h>

#define TIMER 20000
#define CHARSTEP 6 //the amount of space to put between characters
#define HEIGHT ST7735_height
#define WIDTH ST7735_width

#define SQUARESIZE  10 //the size of the "bubble"
#define SQUARE_START_X  WIDTH/2 - (SQUARESIZE / 2)
#define SQUARE_START_Y  HEIGHT/2 - (SQUARESIZE / 2)


int runningCompassApp;


void drawString(int startx, int y, const char *str, uint16_t charColor, uint16_t charBGColor){
    int i = 0;
    while(str[i] != '\0'){
        f3d_lcd_drawChar(startx + (i * CHARSTEP), y, str[i], charColor, charBGColor);
        i++;
    }
}

int ledNumberConvert(int led){
    led = 9 - led;
    switch(led){
        case 8:
            return 0;
        default: return led;
    }
}


/*
 * starting led - current rotation w/ logic for wrapping around
 */

void LCD_drawCompassApp(){
    runningCompassApp = 1;
    f3d_lcd_fillScreen2(BLACK);
    drawString(12, HEIGHT / 2, "SEE LEDs FOR NORTH", RED, BLACK); 

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

void LCD_drawTiltAppScreen() {
    runningCompassApp = 0;
    f3d_lcd_fillScreen2(BLACK);
    //drawString(12, HEIGHT / 2, "This The Tilt App", RED, BLACK); 
}

void appSwitch(){
    if (runningCompassApp){
        LCD_drawTiltAppScreen();
    } else {
        LCD_drawCompassApp();

    }

}




void drawMiddleSquare() {
    //draw middle square
    int i, j;
    for(i = 0; i < SQUARESIZE; i++){ //horizontal
        for(j = 0; j < SQUARESIZE; j++){ //vertical
            if ((j == 0 || j == SQUARESIZE -1) || (i == 0 || i == SQUARESIZE -1))
                f3d_lcd_drawPixel(SQUARE_START_X + i, SQUARE_START_Y + j, WHITE);
        }
    }
}


void drawBubble(int x, int y, int* dirtyArea){
    int bubbleOffset = -2;
    int bubbleSize = SQUARESIZE + bubbleOffset;
    int i, j;
    int drawX = ((SQUARE_START_X) + bubbleOffset) + (int)y;
    int drawY = ((SQUARE_START_Y) + bubbleOffset) + (int)x;
    for(i = 0; i < bubbleSize; i++) { //horizontal
        for(j = 0; j < bubbleSize; j++) { //vertical
            f3d_lcd_drawPixel(drawX + i, drawY + j, WHITE);
        }
    }
    dirtyArea[0] = drawX;
    dirtyArea[1] = drawY;
}

void cleanDirtyArea(int dirtyX, int dirtyY){
    int bubbleOffset = -2;
    int bubbleSize = SQUARESIZE + bubbleOffset;
    int i, j;
    for(i = 0; i < bubbleSize; i++) { //horizontal
        for(j = 0; j < bubbleSize; j++) { //vertical
            f3d_lcd_drawPixel(dirtyX + i, dirtyY + j, BLACK);
        }
    }

}

int main(void) {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    // Set up your inits before you go ahead
    f3d_uart_init();
    delay(10);
    f3d_gyro_init();
    delay(10);
    f3d_led_init();
    delay(10);
    f3d_user_btn_init();
    delay(10);
    f3d_lcd_init();
    delay(10);
    f3d_i2c1_init();
    delay(10);
    f3d_accel_init();
    delay(10);
    f3d_mag_init();
    delay(10);


    float mag[3];
    float accel[3];
    int dirtyArea[] = {0, 0};

    float x, y, z;
    float compassAngle, Xh, Yh, pitch, roll;


    LCD_drawCompassApp();
    runningCompassApp = 1;
    int i = 0;
    while(1){
        f3d_mag_read(mag);
        f3d_accel_read(accel);



        pitch = (atanf(accel[0] / sqrt(pow(accel[1], 2) + pow(accel[2], 2))));
        roll = (atanf(accel[1]/sqrt(pow(accel[0], 2) + pow(accel[2], 2))));

        Xh = mag[0]*cos(pitch)+mag[2]*sin(pitch);
        Yh = mag[0]*sin(roll)*sin(pitch) + mag[1] * cos(roll) - mag[2] * sin(roll)*cos(pitch);

        //pitch = (atanf(accel[0] / sqrt(pow(accel[1], 2) + pow(accel[2], 2))));
        compassAngle = fabs((atan2(Yh, Xh)) * 180 / 3.1415926535 + 180.0f);

        x = accel[0] * 180;
        y = accel[1] * 180;
        printf("Y:%f\n", y);

        if (runningCompassApp){
            compassLights(compassAngle);
        }
        else { //Level App
            f3d_led_all_off();
            cleanDirtyArea(dirtyArea[0], dirtyArea[1]);
            drawMiddleSquare();
            drawBubble(x, y, dirtyArea);
        }

        if (user_btn_read()){
            appSwitch();
        }
    }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
    printf("There has been an error, Use GDB to find the source");
    /* Infinite loop */
    /* Use GDB to find out why we're here */
    while (1);
}
#endif

/* main.c ends here */

//z = accel[2] * 180;
//x = (mag[0] * cos(pitch)) + (mag[2] * sin(pitch));
//y = (mag[0] * sin(roll) * sin(pitch)) + (mag[1] * cos(roll)) - (mag[2] * sin(roll) * cos(pitch)); 
//x = (x * 180) / M_PI;
//y = (y * 180) / M_PI;
//x = Xh;
//y = Yh;
