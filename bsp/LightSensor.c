#include "stm32f10x.h"                  // Device header

void LightSensor_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure); //默认低电平，上电就响  ← 推挽+ODR=0，配置成输出后，把0输出
	
	GPIO_SetBits(GPIOB,GPIO_Pin_13);  //置1，上电不点亮
}

uint8_t LightSensor_Get()
{
	return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);
}
