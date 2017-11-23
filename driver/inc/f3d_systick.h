#include <stm32f30x.h>
#define SYSTICK_INT_SEC 100
void f3d_systick_init(void);
void SysTick_Handler(void);
void setTickSpeed(int speed);
