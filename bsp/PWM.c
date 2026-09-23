#include "stm32f10x.h"                  // Device header


void PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  //TIM2在APB1中
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;     
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;        //使用通道3
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure); 
	
	TIM_InternalClockConfig(TIM2);   

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;    //分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;       //ARR        
	TIM_TimeBaseInitStructure.TIM_Prescaler = 36 - 1; //更改频率到20k,听不到电机蜂鸣,更改PSC不影响占空比
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;  
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure); 
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit( &TIM_OCInitStructure );   //将结构体所有成员配置完整or给结构体赋初始值
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;          //CCR        
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);   //PA2口对应OC3
	
	TIM_Cmd(TIM2, ENABLE);
}

void PWM_SetCompare3(uint16_t Compare)    
{
	TIM_SetCompare3(TIM2, Compare);
}


