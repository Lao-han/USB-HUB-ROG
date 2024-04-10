#include "userflash.h"	

//读取指定地址的字(32位数据) 
//faddr:读地址 
//返回值:对应数据.
uint32_t STMFLASH_ReadWord(uint32_t faddr)
{
	return *(__IO uint32_t *)faddr;
}

/**
 * @brief		识别FLASH地址所在BANK(该芯片有两个BANK)
 * @param   Addr	FLASH地址
 * @return  uint32_t	FLASH地址所属BANK区
 */
static uint32_t Get_FLASH_Bank(uint32_t Addr)
{
	uint32_t bank = 0;
	if(Addr < (FLASH_BASE + FLASH_BANK_SIZE))
	{
		bank = FLASH_BANK_1;
	}
	#if defined (STM32L471xx) || defined (STM32L475xx) || defined (STM32L476xx) || defined (STM32L485xx) || defined (STM32L486xx) || \
			defined (STM32L496xx) || defined (STM32L4A6xx) || defined (STM32L4P5xx) || defined (STM32L4Q5xx) || defined (STM32L4R5xx) || \
			defined (STM32L4R7xx) || defined (STM32L4R9xx) || defined (STM32L4S5xx) || defined (STM32L4S7xx) || defined (STM32L4S9xx)
	else
	{
		bank = FLASH_BANK_2;
	}
	#endif
	return bank;
}

//从指定地址开始写入指定长度的数据
//WriteAddr:起始地址(此地址必须为4的倍数!!)
//pBuffer:数据指针
//NumToWrite:字(32位)数(就是要写入的32位数据的个数.) 
void STMFLASH_Write(uint32_t WriteAddr,uint32_t *pBuffer,uint32_t NumToWrite)	
{ 
	uint32_t PageError=0,FlashPage,FlashNbPages,i;
	uint64_t WriteData;
	FLASH_EraseInitTypeDef FlashSet;
	HAL_StatusTypeDef status;

	if(WriteAddr<STM32_FLASH_BASE)	return;
	if(pBuffer==NULL)	return;
	if(NumToWrite==0)	return;
	
	FlashPage=(WriteAddr-STM32_FLASH_BASE)/2048;	//一页2KB,2048 Byte
	FlashNbPages=NumToWrite/512+1;								//一页2KB,512  Word
	
	FlashSet.TypeErase = FLASH_TYPEERASE_PAGES;
	FlashSet.Banks = Get_FLASH_Bank(WriteAddr);
	FlashSet.Page = FlashPage;
	FlashSet.NbPages = FlashNbPages;
	
	//擦除Flash操作
	HAL_FLASH_Unlock();
	status = HAL_FLASHEx_Erase(&FlashSet, &PageError);
	HAL_FLASH_Lock();
	if(status!=HAL_OK)
	{
//		printf("erase fail, PageError = %d\r\n", PageError);
	}
	
	//写入Flash操作
	
	HAL_FLASH_Unlock();
	for (i =0;i<(NumToWrite+1)/2; i++)
	{
		//一个字是32位，一次写入两个字，64位，8个字节
		if((NumToWrite%2==1)&&(i==NumToWrite/2))
		{
			WriteData=( 0xffffffff00000000 ) | (pBuffer[2*i]);
		}
		else
		{
			WriteData=( ( (uint64_t)pBuffer[2*i+1] )<<32 ) | (pBuffer[2*i]);
		}
		status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,WriteAddr+i*8,WriteData);
		if(status != HAL_OK)
		{
//			printf("write fail\r\n");
			break;
		}
	}
	HAL_FLASH_Lock();

	
} 

//从指定地址开始读出指定长度的数据
//ReadAddr:起始地址
//pBuffer:数据指针
//NumToRead:字(32位)数
void STMFLASH_Read(uint32_t ReadAddr,uint32_t *pBuffer,uint32_t NumToRead)   	
{
	uint32_t i;
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=STMFLASH_ReadWord(ReadAddr);//读取4个字节.
		ReadAddr+=4;//偏移4个字节.	
	}
}





