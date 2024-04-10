#include "userusart.h"
#include "usart.h"
#include "tim.h"
#include "userflash.h"	
#include "lvgl.h"

static uint8_t uartMsgBuffer[BUFFER_SIZE];
MsgPack_t uartMessagePark = {.len = 0,.data = uartMsgBuffer,};

Time_t NowTime;
CPUInfo_t monCpuInfo;
GPUInfo_t monGpuInfo;
RAMInfo_t monRamInfo;
//HDDInfo_t monHddInfo;

uint8_t InfoFlag=0;

static void ParseUartDataPack(void);
static void TimeAndDateSetHandler(MsgPack_t* pack);
static void MonitorInitInfoHandler(MsgPack_t* pack);
static void MonitorInfoHandler(MsgPack_t* pack);
static void SetLuminanceHandler(MsgPack_t* pack);
static int ParseInt(uint8_t** hData, uint16_t len);
	
static const MsgHeader_t msgHeaders[MSG_HEADER_Quantity] = {
		{.header = "WTIME", .msgHandler = TimeAndDateSetHandler}, 	// ����ʱ��
		{.header = "WINIT", .msgHandler = MonitorInitInfoHandler}, 	// �����ʼ������
		{.header = "WINFO", .msgHandler = MonitorInfoHandler}, 			// ��������
		{.header = "WSTBG", .msgHandler = SetLuminanceHandler}, 		// ��������
};

extern TaskHandle_t UsartDataAnalysis_Handle;	/* �������ݽ��������� */
extern TaskHandle_t UIInterface_Handle;				/* ���������� */

extern lv_obj_t * CPUName_Lable;
extern lv_obj_t * GPUName_Lable;

void UsartDataAnalysis_Task(void)	/* �������ݽ��������� */
{
	__HAL_UART_CLEAR_IDLEFLAG(&huart1);
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
	HAL_UART_Receive_DMA(&huart1,rx_buffer,BUFFER_SIZE);
	while(1)
	{
		ulTaskNotifyTake(pdTRUE,portMAX_DELAY);			
//		HAL_UART_Transmit(&huart1,rx_buffer,rx_len,0xffff);
//		printf("\r\n");
		memcpy(uartMessagePark.data,rx_buffer,rx_len);
		uartMessagePark.len = rx_len;
		ParseUartDataPack();		
		rx_len = 0;//�������
		memset(rx_buffer,0,rx_len);
		HAL_UART_Receive_DMA(&huart1,rx_buffer,BUFFER_SIZE);//���´�DMA����
		if(InfoFlag==1)
		{
			InfoFlag=0;
			xTaskNotifyGive(UIInterface_Handle);
		}
//		vTaskDelay(10);
	}
}

static void ParseUartDataPack(void)
{
	uint16_t i;
	if(uartMessagePark.len==0)return;
	for(i = 0; i < MSG_HEADER_Quantity; i++)
	{
		char* pChar = (char*)(uartMessagePark.data);
		const char* pHeader = msgHeaders[i].header;
		int c = 0;
		for(c = 0; c < MSG_HEADER_LEN; c++)
		{
			if((*pChar++) != (*pHeader++))
			{
				break;
			}
		}
		if(c == MSG_HEADER_LEN)
		{
			msgHeaders[i].msgHandler(&uartMessagePark);
			break;
		}
	}
}

static void TimeAndDateSetHandler(MsgPack_t* pack)
{
	uint8_t* pData = pack->data + MSG_HEADER_LEN;
	NowTime.Year		=ParseInt(&pData,2);
	NowTime.Month		=ParseInt(&pData,2);
	NowTime.Date		=ParseInt(&pData,2);
	NowTime.WeekDay	=ParseInt(&pData,1);
	NowTime.Hours		=ParseInt(&pData,2);
	NowTime.Minutes	=ParseInt(&pData,2);
	NowTime.Seconds	=ParseInt(&pData,2);
	
//	printf("------------DATE------------\r\n");
//	printf("20%d��%d��%d������%d , %d:%d:%d\r\n"	,NowTime.Year,NowTime.Month,NowTime.Date,NowTime.WeekDay
//																								,NowTime.Hours,NowTime.Minutes,NowTime.Seconds);
}

static void MonitorInitInfoHandler(MsgPack_t* pack)
{
	uint8_t* pData = pack->data + MSG_HEADER_LEN;
	memcpy(monCpuInfo.name, pData, HARDWARE_NAME_LEN);
	pData += HARDWARE_NAME_LEN;
	monCpuInfo.coreCounts = ParseInt(&pData, 3);
	memcpy(monGpuInfo.name, pData, HARDWARE_NAME_LEN);
	pData += HARDWARE_NAME_LEN;
	monGpuInfo.memTotal = ParseInt(&pData, 6);
	
	lv_label_set_text(CPUName_Lable,monCpuInfo.name);
	lv_label_set_text(GPUName_Lable,monGpuInfo.name);
	
//	printf("------------CPU------------\r\n");
//	printf("%s\r\n",monCpuInfo.name);
//	printf("������:%d\r\n",monCpuInfo.coreCounts);
//	printf("------------GPU------------\r\n");
//	printf("%s\r\n",monGpuInfo.name);
//	printf("�Դ��С:%.0fGB\r\n",((float)(monGpuInfo.memTotal))/1024);
}

static void MonitorInfoHandler(MsgPack_t* pack)
{
	uint8_t* pData = pack->data + MSG_HEADER_LEN;
	// CPU
	monCpuInfo.speed = ParseInt(&pData, 3);
	monCpuInfo.totalUsage = ParseInt(&pData, 3);
	for(int i = 0; i < monCpuInfo.coreCounts; i++)
	{
		monCpuInfo.coreUsage[i] = ParseInt(&pData, 3);
	}
	monCpuInfo.temperture = ParseInt(&pData, 3);

	// �ڴ�
	monRamInfo.total = ParseInt(&pData, 6);
	monRamInfo.used  = ParseInt(&pData, 6);

	// Ӳ�̻ʱ��
	pData+=6;
//	monHddInfo.active = ParseInt(&pData, 6);

	// GPU��Ϣ
	monGpuInfo.coreLoad    = ParseInt(&pData, 3);
	monGpuInfo.coreSpeed   = ParseInt(&pData, 4);
	pData+=9;
	monGpuInfo.temperture  = ParseInt(&pData, 3);

	InfoFlag=1;
	
//	printf("------------CPU------------\r\n");
//	printf("Ƶ��:%.2fGHz\r\n",((float)(monCpuInfo.speed))/100);
//	printf("��ʹ����:%d%%\r\n",monCpuInfo.totalUsage);
//	printf("Core1ʹ����:%d%%\r\n",monCpuInfo.coreUsage[1]);
//	printf("Core2ʹ����:%d%%\r\n",monCpuInfo.coreUsage[2]);
//	printf("Core3ʹ����:%d%%\r\n",monCpuInfo.coreUsage[3]);
//	printf("Core4ʹ����:%d%%\r\n",monCpuInfo.coreUsage[4]);
//	printf("�¶�:%d��\r\n",monCpuInfo.temperture);
//	
//	printf("------------GPU------------\r\n");
//	printf("ʹ����:%d%%\r\n",monGpuInfo.coreLoad);
//	printf("����Ƶ��:%.3fGHz\r\n",((float)(monGpuInfo.coreSpeed))/1000);
//	printf("�¶�:%d��\r\n",monGpuInfo.temperture);
//	
//	printf("------------RAM------------\r\n");
//	printf("RAM�ܴ�С:%.0fGB\r\n",((float)(monRamInfo.total))/1024);
//	printf("RAM��ʹ��:%dMB\r\n",monRamInfo.used);
//	printf("RAMʹ����:%d%%\r\n",monRamInfo.used*100/monRamInfo.total);
}

static void SetLuminanceHandler(MsgPack_t* pack)
{
	uint32_t Luminance;
	uint8_t* pData = pack->data + MSG_HEADER_LEN;
	Luminance=ParseInt(&pData,3);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_3,Luminance);
	STMFLASH_Write(SetUp_FLASH_Address,&Luminance,1);
}

static int ParseInt(uint8_t** hData, uint16_t len)
{
	uint8_t buf[16] = {0};
	uint8_t* pData = *hData;
	for(int i = 0; i < len; i++)
	{
		buf[i] = *pData++;
	}
	*hData += len;
	return atoi((const char*)buf);
}


