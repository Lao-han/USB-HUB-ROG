#ifndef __USERFLASH_H
#define __USERFLASH_H

#include "main.h"

//FLASH起始地址
#define STM32_FLASH_BASE 		0x08000000 						//STM32 FLASH的起始地址
#define SetUp_FLASH_Address (0x08000000+0x3f800) 	//存储设置的地址0x0803F800
 
uint32_t STMFLASH_ReadWord(uint32_t faddr);		  	//读出字  
void STMFLASH_Write(uint32_t WriteAddr,uint32_t *pBuffer,uint32_t NumToWrite);		//从指定地址开始写入指定长度的数据
void STMFLASH_Read(uint32_t ReadAddr,uint32_t *pBuffer,uint32_t NumToRead);   		//从指定地址开始读出指定长度的数据


#endif





