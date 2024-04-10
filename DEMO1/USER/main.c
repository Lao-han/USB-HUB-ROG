#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
/************************************************
 ALIENTEK 精英板STM32F103开发板 实验1
 跑马灯实验-HAL库版本
 技术支持：www.openedv.com
 淘宝店铺： http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

/*下面主函数是使用HAL库函数实现控制IO口输出*/
/*
int main(void)
{
    HAL_Init();                    	 	//初始化HAL库    
    Stm32_Clock_Init(RCC_PLL_MUL9);   	//设置时钟,72M
	delay_init(72);               		//初始化延时函数
	LED_Init();							//初始化LED	
	
	while(1)
	{
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET); 	//LED0对应引脚PB5拉低，亮，等同于LED0(0)
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);   	//LED1对应引脚PE5拉高，灭，等同于LED1(1)
        delay_ms(50);											//延时50ms
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET);   	//LED0对应引脚PB5拉高，灭，等同于LED0(1)
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET); 	//LED1对应引脚PE5拉低，亮，等同于LED1(0)
        delay_ms(50);                                      	//延时500ms 
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);   	//LED0对应引脚PB5拉高，灭，等同于LED0(1)
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_RESET); 	//LED1对应引脚PE5拉低，亮，等同于LED1(0)
        delay_ms(50);                                      	//延时500ms
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_SET);   	//LED0对应引脚PB5拉高，灭，等同于LED0(1)
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET); 	//LED1对应引脚PE5拉低，亮，等同于LED1(0)
        delay_ms(50);                                      	//延时500ms
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);   	//LED0对应引脚PB5拉高，灭，等同于LED0(1)
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET); 	//LED1对应引脚PE5拉低，亮，等同于LED1(0)
        delay_ms(50);                                      	//延时500ms 
	}
}
*/
/*下面主函数使用位带操作实现：*/

int main(void)
{ 
    HAL_Init();                    	 	//初始化HAL库    
    Stm32_Clock_Init(RCC_PLL_MUL9);   	//设置时钟,72M
	delay_init(72);               			//初始化延时函数
	LED_Init();							//初始化LED	

	while(1)
	{
		 LED0=0;LED1=0;LED2=0;LED3=0;LED4=0;LED5=0;LED6=0;LED7=0;
//		 delay_ms(500);
//     LED0=0;			     	
//	   LED1=1;				 	
//		 delay_ms(50);
//		 LED0=1;					
//		 LED1=0;					
//		 delay_ms(50);
//		 LED2=0;
//		 LED3=1;
//		 delay_ms(50);
//		 LED2=1;
//		 LED3=0;
//		 delay_ms(50);
		 delay_ms(1);
		 LED0=1;LED1=1;LED2=1;LED3=1;LED4=1;LED5=1;LED6=1;LED7=1;
		 delay_ms(1);
	 }
}
/*
下面主函数使用直接操作结存器方式实现跑马灯
*/

/*int main(void)
{ 
    HAL_Init();                    	 	//初始化HAL库    
    Stm32_Clock_Init(RCC_PLL_MUL9);   	//设置时钟,72M
	delay_init(72);               		//初始化延时函数
	LED_Init();							//初始化LED	

	while(1)
	{
      GPIOB->BSRR=GPIO_PIN_5;     	//LED0亮
	  GPIOE->BSRR=GPIO_PIN_5<<16; 	//LED1灭
	  delay_ms(500);
      GPIOB->BSRR=GPIO_PIN_5<<16; 	//LED0灭
	  GPIOE->BSRR=GPIO_PIN_5;     	//LED1亮
	  delay_ms(500);
	 }
}*/	
