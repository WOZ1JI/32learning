#ifndef __LED_H
#define __LED_H

void LED_Init(void);
void LED1_on(void);
void LED1_off(void);
void LED2_on(void);
void LED2_off(void);
void LED1_turn(void);  //读取端口输出，并取反
void LED2_turn(void);

#endif       //防止头文件重复包含的代码
