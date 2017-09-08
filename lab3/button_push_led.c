#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>     // Pull in include file for the local drivers
#include <f3d_user_btn.h>

// Simple looping delay function
void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

int main(void) {


    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
    GPIO_Init(GPIOE, &GPIO_InitStructure);
  //GPIOE->BSRR = GPIO_Pin_9;

    GPIO_InitTypeDef button; 
    GPIO_StructInit(&button);
    button.GPIO_Pin = GPIO_Pin_0;
    button.GPIO_Mode = GPIO_Mode_IN;
    button.GPIO_PuPd = GPIO_PuPd_NOPULL;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    GPIO_Init(GPIOA, &button);
    

  while(1){
    if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)){
        GPIOE->BSRR = GPIO_Pin_9;
    }
    else{
        GPIOE->BRR = GPIO_Pin_9;
    }
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */
