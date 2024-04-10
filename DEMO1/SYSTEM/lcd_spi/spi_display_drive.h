
#ifndef __SPI_DISPLAY_DRIVE_H__
#define __SPI_DISPLAY_DRIVE_H__

#ifdef DEBUG
#define END 0xffff
#endif

//例题库
//#define ROW  160		    //显示的行、列数
//#define COL  128

 //修改
#define ROW  128		    //显示的行、列数
#define COL  160

//#define TP_TEST		    //测试功能的选择，选择常量被定义，相应测试功能开启； TP_TEST:TP划线测试功能
#define READ_REG_H		    //读ID CODE功能
//#define SLEEP_TEST	    //进入、退出sleep功能
//#define DEBUG			    //调试功能，把要调试的指令和参数写进数组内，每按键执行一组指令和参数

//#define EVAL_PIC		    //使用MCU片上64k Flash()内的图片，160*160填充显示区域
#define EXTEND_TEST	    //扩展测试功能，如，灰度，色彩渐变等画面

//------------------------------------------------------
#define CHAR_FONT_W8_H16	//选择显示字符的字体，CHAR_FONT_W8_H16：8*16；CHAR_FONT_W16_H21：16*21
//#define CHAR_FONT_W16_H21

//#define CONN_USB		    //在按键等待时连接USB进行数据通信、交换（以此实现USB调试功能）	
//#define USE_SD_INIT			//SD卡初始化
//#define SD_DEMO_PIC			//显示SD卡内的图片以用于评估和展示
//#define AUTO_TEST			//若定义AUTO-TEST，等待按键时不必按按键，延时一段后自动进行下一步的测试	
//------------------------------------------------------
//#define DBH  P2				//接口定义部分
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
//sbit    KEY_STEP  = P3^6;	//定义“下一步”按键
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

//#define STRING_FUNCTION	  //定义字符串处理和显示的函数
//#define DRAW_FUNCTION		  //定义TP测试的函数
//#define READ_FUNCTION		  //定义读取IC操作的函数
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
#define PIC_WIDTH    160	 //预备向LCD显示区域填充的图片的大小
#define PIC_HEIGHT   160

#if 0
#define RED    0xF800		 //定义颜色常量 
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
#define RED    0xF800		 //定义颜色常量 
#define GREEN  0x07E0
#define BLUE   0xFFFF
#define WHITE  0x001F
#define BLACK  0x0000
#define GRAY   0xEF5D	     //0x2410
#define GRAY75 0x39E7 
#define GRAY50 0x7BEF	
#define GRAY25 0xADB5
#endif

#define RED    0xF800		 //定义颜色常量 
#define GREEN  0x07E0
#define BLUE   0xFFFF
#define BLACK  0x0000
#define WHITE  0x0000
#define GRAY   0xEF5D	     //0x2410
#define GRAY75 0x39E7 
#define GRAY50 0x7BEF	
#define GRAY25 0xADB5
	
#endif


#define X_min 0x0043		//TP测试范围常量定义
#define X_max 0x07AE
#define Y_min 0x00A1



//模拟spi使能
//#define SIMULATIOM_ENABLE_SPI (1)
/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx.h"
#include "string.h"

//#include "../Delay/delay.h"

#define TIME_DELAY	5

//sbit lcd_sclk=P3^2; /*接口定义:lcd_sclk 就是 LCD 的 sclk*/
//sbit lcd_sid=P3^1; /*接口定义:lcd_sid 就是 LCD 的 sid*/
//sbit lcd_rs=P3^0; /*接口定义:lcd_rs 就是 LCD 的 rs*/
//sbit lcd_reset=P1^0; /*接口定义:lcd_reset 就是 LCD 的 reset*/
//sbit lcd_cs1=P1^1; /*接口定义:lcd_cs1 就是 LCD 的 cs1*/
//sbit Rom_IN=P1^2; /*字库 IC 接口定义:Rom_IN 就是字库 IC 的 SI*/
//sbit Rom_OUT=P1^3; /*字库 IC 接口定义:Rom_OUT 就是字库 IC 的 SO*/
//sbit Rom_SCK=P1^4; /*字库 IC 接口定义:Rom_SCK 就是字库 IC 的 SCK*/
//sbit Rom_CS=P1^5; /*字库 IC 接口定义 Rom_CS 就是字库 IC 的 CS#*


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


