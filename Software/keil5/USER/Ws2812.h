#ifndef __WS2812_H
#define __WS2812_H

#include "sys.h"


//-----------------ws2812¶Ë¿Ú¶¨Òå---------------- 

#define ws2812_Crl() GPIO_ResetBits(GPIOB,GPIO_Pin_3)//SCL=SCLK
#define ws2812_Set() GPIO_SetBits(GPIOB,GPIO_Pin_3)


#endif




