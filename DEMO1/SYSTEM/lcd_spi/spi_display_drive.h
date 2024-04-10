
#ifndef __SPI_DISPLAY_DRIVE_H__
#define __SPI_DISPLAY_DRIVE_H__

#ifdef DEBUG
#define END 0xffff
#endif

//�����
//#define ROW  160		    //��ʾ���С�����
//#define COL  128

 //�޸�
#define ROW  128		    //��ʾ���С�����
#define COL  160

//#define TP_TEST		    //���Թ��ܵ�ѡ��ѡ���������壬��Ӧ���Թ��ܿ����� TP_TEST:TP���߲��Թ���
#define READ_REG_H		    //��ID CODE����
//#define SLEEP_TEST	    //���롢�˳�sleep����
//#define DEBUG			    //���Թ��ܣ���Ҫ���Ե�ָ��Ͳ���д�������ڣ�ÿ����ִ��һ��ָ��Ͳ���

//#define EVAL_PIC		    //ʹ��MCUƬ��64k Flash()�ڵ�ͼƬ��160*160�����ʾ����
#define EXTEND_TEST	    //��չ���Թ��ܣ��磬�Ҷȣ�ɫ�ʽ���Ȼ���

//------------------------------------------------------
#define CHAR_FONT_W8_H16	//ѡ����ʾ�ַ������壬CHAR_FONT_W8_H16��8*16��CHAR_FONT_W16_H21��16*21
//#define CHAR_FONT_W16_H21

//#define CONN_USB		    //�ڰ����ȴ�ʱ����USB��������ͨ�š��������Դ�ʵ��USB���Թ��ܣ�	
//#define USE_SD_INIT			//SD����ʼ��
//#define SD_DEMO_PIC			//��ʾSD���ڵ�ͼƬ������������չʾ
//#define AUTO_TEST			//������AUTO-TEST���ȴ�����ʱ���ذ���������ʱһ�κ��Զ�������һ���Ĳ���	
//------------------------------------------------------
//#define DBH  P2				//�ӿڶ��岿��
//#define DBL  P4

//LCM | SPI4W



//sbit	WR0 = P1^7;
//sbit	RD0 = P1^6;

//sbit	CS0 = P1^0;
//sbit	RS  = P3^4;
//sbit	RST = P1^3;
//sbit	SCL = P1^1;
//sbit	SDA = P1^2;



//TP 
//sbit    TP_CS	  = P1^4;
//sbit    TP_PENIRQ = P3^5;
//sbit    TP_DOUT   = P3^3;
//sbit    TP_DIN	  = P3^2;
//sbit    TP_DCLK   = P1^5;
//sbit    TP_BUSY	  = P3^4;

//KEY
//sbit    KEY_STEP  = P3^6;	//���塰��һ��������
//------------------------------------------------------
#ifdef  READ_REG_H	
	#define STRING_FUNCTION
    #define READ_FUNCTION
#endif

#ifdef  DEBUG	
	#define STRING_FUNCTION
#endif

#ifdef  CONN_USB	
	#define STRING_FUNCTION
    #define READ_FUNCTION
#endif
#ifdef  TP_TEST	
	#define DRAW_FUNCTION
	#define STRING_FUNCTION
#endif

#ifdef AUTO_TEST
	#define AUTO_NEXT
#else
	#define MANUA_NEXT
#endif	

//#define STRING_FUNCTION	  //�����ַ����������ʾ�ĺ���
//#define DRAW_FUNCTION		  //����TP���Եĺ���
//#define READ_FUNCTION		  //�����ȡIC�����ĺ���
//------------------------------------------------------
#ifdef  CHAR_FONT_W8_H16	
	#define  FONT_W  8
	#define  FONT_H  16
#endif
#ifdef  CHAR_FONT_W16_H21
	#define  FONT_W  16
	#define  FONT_H  21
#endif
//------------------------------------------------------
#define PIC_WIDTH    160	 //Ԥ����LCD��ʾ��������ͼƬ�Ĵ�С
#define PIC_HEIGHT   160

#if 0
#define RED    0xF800		 //������ɫ���� 
#define GREEN  0x07E0
#define BLUE   0x001F
#define WHITE  0xFFFF
#define BLACK  0x0000
#define GRAY   0xEF5D	     //0x2410
#define GRAY75 0x39E7 
#define GRAY50 0x7BEF	
#define GRAY25 0xADB5
#else

#if 0
#define RED    0xF800		 //������ɫ���� 
#define GREEN  0x07E0
#define BLUE   0xFFFF
#define WHITE  0x001F
#define BLACK  0x0000
#define GRAY   0xEF5D	     //0x2410
#define GRAY75 0x39E7 
#define GRAY50 0x7BEF	
#define GRAY25 0xADB5
#endif

#define RED    0xF800		 //������ɫ���� 
#define GREEN  0x07E0
#define BLUE   0xFFFF
#define BLACK  0x0000
#define WHITE  0x0000
#define GRAY   0xEF5D	     //0x2410
#define GRAY75 0x39E7 
#define GRAY50 0x7BEF	
#define GRAY25 0xADB5
	
#endif


#define X_min 0x0043		//TP���Է�Χ��������
#define X_max 0x07AE
#define Y_min 0x00A1



//ģ��spiʹ��
//#define SIMULATIOM_ENABLE_SPI (1)
/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx.h"
#include "string.h"

//#include "../Delay/delay.h"

#define TIME_DELAY	5

//sbit lcd_sclk=P3^2; /*�ӿڶ���:lcd_sclk ���� LCD �� sclk*/
//sbit lcd_sid=P3^1; /*�ӿڶ���:lcd_sid ���� LCD �� sid*/
//sbit lcd_rs=P3^0; /*�ӿڶ���:lcd_rs ���� LCD �� rs*/
//sbit lcd_reset=P1^0; /*�ӿڶ���:lcd_reset ���� LCD �� reset*/
//sbit lcd_cs1=P1^1; /*�ӿڶ���:lcd_cs1 ���� LCD �� cs1*/
//sbit Rom_IN=P1^2; /*�ֿ� IC �ӿڶ���:Rom_IN �����ֿ� IC �� SI*/
//sbit Rom_OUT=P1^3; /*�ֿ� IC �ӿڶ���:Rom_OUT �����ֿ� IC �� SO*/
//sbit Rom_SCK=P1^4; /*�ֿ� IC �ӿڶ���:Rom_SCK �����ֿ� IC �� SCK*/
//sbit Rom_CS=P1^5; /*�ֿ� IC �ӿڶ��� Rom_CS �����ֿ� IC �� CS#*


//#define lcd_cs1(X)  	{if(X){GPIO_SetBits(GPIOD,GPIO_Pin_15);}else{GPIO_ResetBits(GPIOD,GPIO_Pin_15);}}
//#define CS0(X) 		{if(X){do{}while(0);}else{do{}while(0);}}
//#define RS(X)  		{if(X){GPIO_SetBits(GPIOD,GPIO_Pin_15);}else{GPIO_ResetBits(GPIOD,GPIO_Pin_15);}}
//#define	SCL(X)		{if(X){GPIO_SetBits(GPIOC,GPIO_Pin_6);}else{GPIO_ResetBits(GPIOC,GPIO_Pin_6);}}
//#define	SDA(X)		{if(X){GPIO_SetBits(GPIOC,GPIO_Pin_7);}else{GPIO_ResetBits(GPIOC,GPIO_Pin_7);}}
//#define RST_LED(X) 	{if(X){GPIO_SetBits(GPIOD,GPIO_Pin_14);}else{GPIO_ResetBits(GPIOD,GPIO_Pin_14);}}
#define CS0 PBout(5);
#if SIMULATIOM_ENABLE_SPI



//#define	Rom_IN(X)		{if(X){GPIO_SetBits(GPIOB,GPIO_Pin_15);}else{GPIO_ResetBits(GPIOB,GPIO_Pin_15);}}

//#define	Rom_OUT	  		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)

//#define	Rom_SCK(X)		{if(X){GPIO_SetBits(GPIOB,GPIO_Pin_13);}else{GPIO_ResetBits(GPIOB,GPIO_Pin_13);}}

//#define	Rom_CS(X)		{if(X){GPIO_SetBits(GPIOB,GPIO_Pin_12);}else{GPIO_ResetBits(GPIOB,GPIO_Pin_12);}}

#endif



//---------------------------------------------------------------------
void WriteComm(unsigned int i);
void WriteData(unsigned int i);
void WriteDispData(unsigned char DataH,unsigned char DataL);
void LCD_Init_st37(void);
void BlockWrite(unsigned int Xstart,unsigned int Xend,unsigned int Ystart,unsigned int Yend);
void DispBand(void);
void DispColor(unsigned int color);
void DispFrame(void);
//void DispPic(unsigned int *picture);
void DispPicFromSD(unsigned char PicNum);

void DispScaleHor1(void);
void DispScaleVer(void);
void DispScaleVer_Red(void);
void DispScaleVer_Green(void);
void DispScaleVer_Blue(void);
void DispScaleVer_Gray(void);
void DispGrayHor16(void);
void DispGrayHor32(void);
void DispScaleHor2(void);
void DispSnow(void);
void DispBlock(void);

void WriteOneDot(unsigned int color);
unsigned char ToOrd(unsigned char ch); 
void  DispOneChar(unsigned char ord,unsigned int Xstart,unsigned int Ystart,unsigned int TextColor,unsigned int BackColor);	 // ord:0~95
void DispStr(unsigned char *str,unsigned int Xstart,unsigned int Ystart,unsigned int TextColor,unsigned int BackColor);
void DispInt(unsigned int i,unsigned int Xstart,unsigned int Ystart,unsigned int TextColor,unsigned int BackColor);

unsigned int ReadData(void);
void DispRegValue(unsigned int RegIndex,unsigned char ParNum);

void Debug(void);

void PutPixel(unsigned int x,unsigned int y,unsigned int color);
void DrawLine(unsigned int Xstart,unsigned int Xend,unsigned int Ystart,unsigned int Yend,unsigned int color);
void DrawGird(unsigned int color);

void Disp_Font_Str(unsigned char *str,unsigned int Xstart,unsigned int Ystart,unsigned int TextColor,unsigned int BackColor);
void Clear_LCD_All(void);

//void getPasswd_Menu(u8 *buf,u16 cnt);
//void getdev_code_Menu(u8 *buf,u16 cnt);
//void SetCode_Menu(u8 *buf,u16 cnt);
//void getcode_Menu(u8 *buf,u16 cnt);


//void show_MainMenu(u8 *buf,u16 cnt);
//void SetSave_Menu(u8 *buf,u16 cnt);
//void SetReset_Menu(u8 *buf,u16 cnt);
//void getSave_Menu(u8 *buf,u16 cnt);
//void getReset_Menu(u8 *buf,u16 cnt);


//void Clock_Menu(u8 *buf,u16 cnt);
//void getClock_Menu(u8 *buf,u16 cnt);
//void SetTime_Menu(u8 * buf, u16 cnt);
//void getTime_Menu(u8 * buf, u16 cnt);

//void SetIP_Menu(u8 * buf, u16 cnt);
//void getIP_Menu(u8 * buf, u16 cnt);
//void SetIP_subnet_Menu(u8 * buf, u16 cnt);
//void getIP_subnet_Menu(u8 * buf, u16 cnt);
//void SetIP_gateway_Menu(u8 * buf, u16 cnt);
//void getIP_gateway_Menu(u8 * buf, u16 cnt);
//void SetIP_dab_ins_Menu(u8 * buf, u16 cnt);
//void getIP_dab_ins_Menu(u8 * buf, u16 cnt);
//void SetIP_dab_ins_port_Menu(u8 * buf, u16 cnt);
//void getIP_dab_ins_port_Menu(u8 * buf, u16 cnt);
//void SetIP_dab_snmp_Menu(u8 * buf, u16 cnt);
//void getIP_dab_snmp_Menu(u8 * buf, u16 cnt);
//void SetIP_dab_snmp_port_Menu(u8 * buf, u16 cnt);
//void getIP_dab_snmp_port_Menu(u8 * buf, u16 cnt);
//void set_emc_level_Menu(u8 * buf, u16 cnt);
//void get_emc_level_Menu(u8 * buf, u16 cnt);

//void set_play_time_mode_Menu(u8 * buf, u16 cnt);
//void get_play_time_mode_Menu(u8 * buf, u16 cnt);

//void Setmiyue_Menu(u8 *buf,u16 cnt);
//void getmiyue_Menu(u8 *buf,u16 cnt);

//void SetDHCP_Menu(u8 *buf,u16 cnt);
//void getDHCP_Menu(u8 *buf,u16 cnt);

//void Show_Menu(u8 flag);
//void DelayMs(u16 ms);

//u8 app_get_region_buf(void);

#endif


