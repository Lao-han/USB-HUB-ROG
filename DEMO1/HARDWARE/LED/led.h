#ifndef _LED_H
#define _LED_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F103������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2017/5/25
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

#define LED0 PAout(0)   	//LED0
#define LED1 PAout(1)   	//LED1
#define LED2 PAout(2)   	//LED2
#define LED3 PAout(3)   	//LED3
#define LED4 PAout(4)   	//LED4
#define LED5 PAout(5)   	//LED5
#define LED6 PAout(6)   	//LED6
#define LED7 PAout(7)   	//LED7

void LED_Init(void);
#endif
