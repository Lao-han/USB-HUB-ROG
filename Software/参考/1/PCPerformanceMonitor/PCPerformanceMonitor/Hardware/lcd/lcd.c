#include "lcd.h"
#include "gpio.h"
#include "tim.h"
#include "spi.h"
#include "lvgl.h"
#include "userflash.h"	

void LCD_Init(void)
{	
	uint32_t Luminance;
	STMFLASH_Read(SetUp_FLASH_Address,&Luminance,1);
	LCD_RES_Clr();	//��λ
	HAL_Delay(50);
	LCD_RES_Set();
	HAL_Delay(50);
	LCD_CS_Clr();
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
	if(Luminance==0xffff)	Luminance=LCD_Luminance;
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_3,Luminance);
  HAL_Delay(50);
	
	//************* Start Initial Sequence **********//
	LCD_WR_REG(0x11); 	//Sleep out 
	HAL_Delay(120);			//Delay 120ms 
	//************* Start Initial Sequence **********// 
	LCD_WR_REG(0x36);
	if(USE_HORIZONTAL==0)			LCD_WR_DATA8(0x00);
	else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC0);
	else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x70);
	else LCD_WR_DATA8(0xA0);

	LCD_WR_REG(0x3A);			
	LCD_WR_DATA8(0x05);

	LCD_WR_REG(0xB2);			
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x0C); 
	LCD_WR_DATA8(0x00); 
	LCD_WR_DATA8(0x33); 
	LCD_WR_DATA8(0x33); 			

	LCD_WR_REG(0xB7);			
	LCD_WR_DATA8(0x35);

	LCD_WR_REG(0xBB);			
	LCD_WR_DATA8(0x32); //Vcom=1.35V
					
	LCD_WR_REG(0xC2);
	LCD_WR_DATA8(0x01);

	LCD_WR_REG(0xC3);			
	LCD_WR_DATA8(0x15); //GVDD=4.8V  ��ɫ���
				
	LCD_WR_REG(0xC4);			
	LCD_WR_DATA8(0x20); //VDV, 0x20:0v

	LCD_WR_REG(0xC6);			
	LCD_WR_DATA8(0x0F); //0x0F:60Hz        	

	LCD_WR_REG(0xD0);			
	LCD_WR_DATA8(0xA4);
	LCD_WR_DATA8(0xA1); 

	LCD_WR_REG(0xE0);
	LCD_WR_DATA8(0xD0);   
	LCD_WR_DATA8(0x08);   
	LCD_WR_DATA8(0x0E);   
	LCD_WR_DATA8(0x09);   
	LCD_WR_DATA8(0x09);   
	LCD_WR_DATA8(0x05);   
	LCD_WR_DATA8(0x31);   
	LCD_WR_DATA8(0x33);   
	LCD_WR_DATA8(0x48);   
	LCD_WR_DATA8(0x17);   
	LCD_WR_DATA8(0x14);   
	LCD_WR_DATA8(0x15);   
	LCD_WR_DATA8(0x31);   
	LCD_WR_DATA8(0x34);   

	LCD_WR_REG(0xE1);     
	LCD_WR_DATA8(0xD0);   
	LCD_WR_DATA8(0x08);   
	LCD_WR_DATA8(0x0E);   
	LCD_WR_DATA8(0x09);   
	LCD_WR_DATA8(0x09);   
	LCD_WR_DATA8(0x15);   
	LCD_WR_DATA8(0x31);   
	LCD_WR_DATA8(0x33);   
	LCD_WR_DATA8(0x48);   
	LCD_WR_DATA8(0x17);   
	LCD_WR_DATA8(0x14);   
	LCD_WR_DATA8(0x15);   
	LCD_WR_DATA8(0x31);   
	LCD_WR_DATA8(0x34);
	LCD_WR_REG(0x21); 

	LCD_WR_REG(0x29);
}

void LCD_Writ_Bus(uint8_t dat) 
{	
//	LCD_CS_Clr();
	HAL_SPI_Transmit(&hspi1,&dat,1,0xff);
//  LCD_CS_Set();	
}

void LCD_WR_DATA8(uint8_t dat)
{
	LCD_Writ_Bus(dat);
}

void LCD_WR_DATA(uint16_t dat)
{
	LCD_Writ_Bus(dat>>8);
	LCD_Writ_Bus(dat);
}

void LCD_WR_REG(uint8_t dat)
{
	LCD_DC_Clr();//д����
	LCD_Writ_Bus(dat);
	LCD_DC_Set();//д����
}

/******************************************************************************
      ����˵����������ʼ�ͽ�����ַ
      ������ݣ�x1,x2 �����е���ʼ�ͽ�����ַ
                y1,y2 �����е���ʼ�ͽ�����ַ
      ����ֵ��  ��
******************************************************************************/
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	if(USE_HORIZONTAL==0)
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//������д
	}
	else if(USE_HORIZONTAL==1)
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1+80);
		LCD_WR_DATA(y2+80);
		LCD_WR_REG(0x2c);//������д
	}
	else if(USE_HORIZONTAL==2)
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//������д
	}
	else
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1+80);
		LCD_WR_DATA(x2+80);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//������д
	}
}

/******************************************************************************
      ����˵������ָ�����������ɫ
      ������ݣ�xsta,ysta   ��ʼ����
                xend,yend   ��ֹ����
								color       Ҫ������ɫ
      ����ֵ��  ��
******************************************************************************/
void LCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color)
{          
	uint16_t i,j; 
	LCD_Address_Set(xsta,ysta,xend-1,yend-1);//������ʾ��Χ
	for(i=ysta;i<yend;i++)
	{													   	 	
		for(j=xsta;j<xend;j++)
		{
			LCD_WR_DATA(color);
		}
	} 					  	    
}

/******************************************************************************
      ����˵������ָ��λ�û���
      ������ݣ�x,y ��������
                color �����ɫ
      ����ֵ��  ��
******************************************************************************/
void LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t color)
{
	LCD_Address_Set(x,y,x,y);//���ù��λ�� 
	LCD_WR_DATA(color);
} 

void LCD_ColorFill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t *color)
{
	uint16_t num;
	num = (xend - xsta + 1) * (yend - ysta + 1);
	LCD_Address_Set(xsta,ysta,xend,yend);//������ʾ��Χ

	hspi1.Instance->CR1 &= ~SPI_CR1_SPE;	//ʧ��SPI
	hspi1.Init.DataSize = SPI_DATASIZE_16BIT;
	HAL_SPI_Init(&hspi1);
	hspi1.Instance->CR1 |= SPI_CR1_SPE;		//ʹ��SPI
	
	while(hspi1.State != HAL_SPI_STATE_READY);
	HAL_SPI_Transmit_DMA(&hspi1,(uint8_t *)color,num);
}


extern lv_disp_drv_t * disp_drv_p;		//��Ļ�����ṹ���ַ����lv_port_disp.c�ж��壬disp_flush()�����б���ֵ

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
  UNUSED(hspi);
	hspi1.Instance->CR1 &= ~SPI_CR1_SPE;	//ʧ��SPI
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	HAL_SPI_Init(&hspi1);
	hspi1.Instance->CR1 |= SPI_CR1_SPE;		//ʹ��SPI
	
	//������õ���,֪ͨ lvgl �����Ѿ� flushing ���������
	lv_disp_flush_ready(disp_drv_p);
}

