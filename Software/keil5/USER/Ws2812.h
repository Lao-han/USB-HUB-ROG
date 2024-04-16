#ifndef __WS2812_H
#define __WS2812_H




//-----------------ws2812¶Ë¿Ú¶¨Òå---------------- 

#define ws2812_Crl() GPIO_ResetBits(GPIOB,GPIO_Pin_3)
#define ws2812_Set() GPIO_SetBits(GPIOB,GPIO_Pin_3)

void ws2812_Init(void);
void loop_rainbow(void);

#endif




