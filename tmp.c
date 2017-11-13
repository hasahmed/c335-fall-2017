void f3d_timer2_enable(uint32_t samplerate) {
   static TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
   uint32_t period;
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
   TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
   TIM_TimeBaseStructure.TIM_Prescaler = 0x0;       
   TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;    
   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
   period = (SystemCoreClock/(samplerate<<1)) - 1;
   TIM_TimeBaseStructure.TIM_Period = (uint16_t) period;
   TIM_TimeBaseStructure.TIM_Period = period;          
   TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
   TIM_Cmd(TIM2, ENABLE);
}
