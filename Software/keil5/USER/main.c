/**************************************************************************************
Ϊ�ҵ�ħ������2023��Ƶġ�USB-HUB-ROG��
STM32C6T6A���ػ�ȡ������Ϣ��ʾ��LCD��
ʵ��USB-HUB3.0 1ת4
���ڻ�ȡ���ݸ�ʽ {(5A XX XX XX XX XX XX A5)  ->  ��ͷ CPUʹ���� CPU�¶� GPUʹ���� GPU�¶� �ڴ�ʹ���� CRC ��β}
LCD��ʾ	 PB8 Reset
	 PB7 SDA
	 PB6 SCL
	 PB5 CS
	 PB4 DC
RGB������ PB3 WS2812B_SDA
����1	 PA11
����2  PA12
By Mr.Han 2024.4.10
*****************************************************************************************/

#include "delay.h"
#include "sys.h"
#include "led.h"
#include "lcd_init.h"
#include "lcd.h"
#include "pic.h"
#include "ws2812.h"
int main(void)
{
	u8 i,j;
	float t=0;
	delay_init();
	ws2812_Init();
	LED_Init();//LED��ʼ��
	LCD_Init();//LCD��ʼ��
	LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
	LED=0;
	while(1)
	{
		LCD_ShowChinese(0,0,"�о�԰����",RED,WHITE,32,0);
		LCD_ShowString(0,40,"LCD_W:",RED,WHITE,16,0);
		LCD_ShowIntNum(48,40,LCD_W,3,RED,WHITE,16);
		LCD_ShowString(80,40,"LCD_H:",RED,WHITE,16,0);
		LCD_ShowIntNum(128,40,LCD_H,3,RED,WHITE,16);
		LCD_ShowString(80,40,"LCD_H:",RED,WHITE,16,0);
		LCD_ShowString(0,70,"Increaseing Nun:",RED,WHITE,16,0);
		LCD_ShowFloatNum1(128,70,t,4,RED,WHITE,16);
		t+=0.11;
		for(j=0;j<3;j++)
		{
			for(i=0;i<6;i++)
			{
				LCD_ShowPicture(40*i,120+j*40,40,40,gImage_1);
			}
		}
		loop_rainbow();
	}
}

