#include "ws2812.h"
#include "delay.h"
#include "sys.h"
#define NUM_COLORS 7

// 彩虹颜色数组，包含红、橙、黄、绿、青、蓝、紫七种颜色的 RGB 值
uint8_t rainbow_colors[NUM_COLORS][3] = {
    {255, 0, 0},     // 红色
    {255, 127, 0},   // 橙色
    {255, 255, 0},   // 黄色
    {0, 255, 0},     // 绿色
    {0, 255, 255},   // 青色
    {0, 0, 255},     // 蓝色
    {148, 0, 211}    // 紫色
};

void ws2812_IO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能B端口时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //初始化GPIOA
 	GPIO_SetBits(GPIOB,GPIO_Pin_3);
}

void ws2812_Init(void)
{
	ws2812_IO_Init();//初始化GPIO
	delay_ms(100);
}


uint8_t rgb_data[3] = {0x00,0xFF,0x00};
 
void send_code(uint8_t * sdata)		 //发送亮度数据
	{   
	uint8_t n = 0;
	uint8_t x = 0,y = 0,z = 0;
	
	for(x = 0;x <3;x++){        //发送3字节数据；一个灯3字节数据
		n = sdata[x];
		for(y = 0;y < 8;y++){
			z = ((n<<y)&0x80);
			if(z){
				ws2812_Set();         //灯的控制脚位设置为输出高
				delay_ns(7);         
				ws2812_Crl();					//灯的控制脚位设置为输出低
				delay_ns(1);    
			}else{
				ws2812_Set();
				delay_ns(1);
				ws2812_Crl();
				delay_ns(7);
			}
		}
	}
}

// 渐变函数
void gradient(uint8_t *start_color, uint8_t *end_color, uint16_t steps) 
	{
    float step_r = (end_color[0] - start_color[0]) / steps;
    float step_g = (end_color[1] - start_color[1]) / steps;
    float step_b = (end_color[2] - start_color[2]) / steps;

    uint8_t color[3] = {0};

    for (uint8_t i = 0; i <= steps; i++){
        color[0] = start_color[0] + step_r * i;
        color[1] = start_color[1] + step_g * i;
        color[2] = start_color[2] + step_b * i;

        send_code(color);
        delay_ms(50); // 调整渐变速度，延时时间越短渐变速度越快
    }
}
// 循环渐变函数
void loop_rainbow(void) 
	{
    for (int i = 0; i < NUM_COLORS - 1; i++) {
        uint8_t *start_color = rainbow_colors[i];
        uint8_t *end_color = rainbow_colors[i + 1];
        gradient(start_color, end_color, 100); // 每个颜色渐变 100 步
    }
    // 最后一种颜色与第一种颜色渐变
    uint8_t *start_color = rainbow_colors[NUM_COLORS - 1];
    uint8_t *end_color = rainbow_colors[0];
    gradient(start_color, end_color, 100); // 每个颜色渐变 100 步
}
