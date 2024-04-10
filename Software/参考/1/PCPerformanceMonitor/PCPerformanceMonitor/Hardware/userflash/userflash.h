#ifndef __USERFLASH_H
#define __USERFLASH_H

#include "main.h"

//FLASH��ʼ��ַ
#define STM32_FLASH_BASE 		0x08000000 						//STM32 FLASH����ʼ��ַ
#define SetUp_FLASH_Address (0x08000000+0x3f800) 	//�洢���õĵ�ַ0x0803F800
 
uint32_t STMFLASH_ReadWord(uint32_t faddr);		  	//������  
void STMFLASH_Write(uint32_t WriteAddr,uint32_t *pBuffer,uint32_t NumToWrite);		//��ָ����ַ��ʼд��ָ�����ȵ�����
void STMFLASH_Read(uint32_t ReadAddr,uint32_t *pBuffer,uint32_t NumToRead);   		//��ָ����ַ��ʼ����ָ�����ȵ�����


#endif





