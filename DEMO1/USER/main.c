#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
/************************************************
 ALIENTEK ��Ӣ��STM32F103������ ʵ��1
 �����ʵ��-HAL��汾
 ����֧�֣�www.openedv.com
 �Ա����̣� http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

/*������������ʹ��HAL�⺯��ʵ�ֿ���IO�����*/
/*
int main(void)
{
    HAL_Init();                    	 	//��ʼ��HAL��    
    Stm32_Clock_Init(RCC_PLL_MUL9);   	//����ʱ��,72M
	delay_init(72);               		//��ʼ����ʱ����
	LED_Init();							//��ʼ��LED	
	
	while(1)
	{
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET); 	//LED0��Ӧ����PB5���ͣ�������ͬ��LED0(0)
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);   	//LED1��Ӧ����PE5���ߣ��𣬵�ͬ��LED1(1)
        delay_ms(50);											//��ʱ50ms
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET);   	//LED0��Ӧ����PB5���ߣ��𣬵�ͬ��LED0(1)
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET); 	//LED1��Ӧ����PE5���ͣ�������ͬ��LED1(0)
        delay_ms(50);                                      	//��ʱ500ms 
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);   	//LED0��Ӧ����PB5���ߣ��𣬵�ͬ��LED0(1)
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_RESET); 	//LED1��Ӧ����PE5���ͣ�������ͬ��LED1(0)
        delay_ms(50);                                      	//��ʱ500ms
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_SET);   	//LED0��Ӧ����PB5���ߣ��𣬵�ͬ��LED0(1)
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET); 	//LED1��Ӧ����PE5���ͣ�������ͬ��LED1(0)
        delay_ms(50);                                      	//��ʱ500ms
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);   	//LED0��Ӧ����PB5���ߣ��𣬵�ͬ��LED0(1)
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET); 	//LED1��Ӧ����PE5���ͣ�������ͬ��LED1(0)
        delay_ms(50);                                      	//��ʱ500ms 
	}
}
*/
/*����������ʹ��λ������ʵ�֣�*/

int main(void)
{ 
    HAL_Init();                    	 	//��ʼ��HAL��    
    Stm32_Clock_Init(RCC_PLL_MUL9);   	//����ʱ��,72M
	delay_init(72);               			//��ʼ����ʱ����
	LED_Init();							//��ʼ��LED	

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
����������ʹ��ֱ�Ӳ����������ʽʵ�������
*/

/*int main(void)
{ 
    HAL_Init();                    	 	//��ʼ��HAL��    
    Stm32_Clock_Init(RCC_PLL_MUL9);   	//����ʱ��,72M
	delay_init(72);               		//��ʼ����ʱ����
	LED_Init();							//��ʼ��LED	

	while(1)
	{
      GPIOB->BSRR=GPIO_PIN_5;     	//LED0��
	  GPIOE->BSRR=GPIO_PIN_5<<16; 	//LED1��
	  delay_ms(500);
      GPIOB->BSRR=GPIO_PIN_5<<16; 	//LED0��
	  GPIOE->BSRR=GPIO_PIN_5;     	//LED1��
	  delay_ms(500);
	 }
}*/	
