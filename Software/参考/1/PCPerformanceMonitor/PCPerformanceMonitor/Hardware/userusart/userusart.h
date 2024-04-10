#ifndef __USERUSART_H__
#define __USERUSART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define MSG_HEADER_LEN	5					//֡ͷ�ַ�����
#define MSG_HEADER_Quantity	4			//����֡��������
#define HARDWARE_NAME_LEN  64			//Ӳ�������ַ�����
#define CPU_MAX_CORES      64			//CPU������.������

typedef struct{
	uint32_t len;			//���ݸ���
	uint8_t* data;		//����(�����׵�ַ)
}MsgPack_t;					//�������ݵĽṹ��

typedef struct{
	const char* header;							//֡ͷ
	void (*msgHandler)(MsgPack_t*);	//��Ӧ�����ݽ����������������MsgPack_t*
}MsgHeader_t;											//�������ݵĽṹ��

typedef struct{
	uint8_t Year;
	uint8_t Month;
	uint8_t Date;
	uint8_t WeekDay;
	uint8_t Hours;
	uint8_t Minutes;
	uint8_t Seconds;
}Time_t;

typedef struct{
	char name[HARDWARE_NAME_LEN];			//
	uint8_t	coreCounts;
	uint16_t speed;                   // (3)GHz * 100
	uint8_t totalUsage;               // (3)%
	uint8_t coreUsage[CPU_MAX_CORES]; // (3)%
	uint16_t temperture;              // (3)��
}CPUInfo_t;

typedef struct{
	char name[HARDWARE_NAME_LEN];
	uint16_t memTotal;
	uint8_t coreLoad;    	// (3)%
	uint16_t coreSpeed;   // (3)GHz * 100
	uint16_t temperture;  // (3)��
}GPUInfo_t;

typedef struct{
	uint16_t total;       // (6)MB
	uint16_t used;        // (6)MB
}RAMInfo_t;

//typedef struct{
//	uint32_t total;       // (9)MB - R
//	uint16_t used;        // (9)MB - R
//	uint16_t active;      // (6)% * 1000
//}HDDInfo_t;

void UsartDataAnalysis_Task(void);/* �������ݽ��������� */

#ifdef __cplusplus
}
#endif

#endif /* __USERUSART_H__ */

