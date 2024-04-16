#include "ws2812.h"
#include "delay.h"
#include "sys.h"
#define NUM_COLORS 7

// �ʺ���ɫ���飬�����졢�ȡ��ơ��̡��ࡢ������������ɫ�� RGB ֵ
uint8_t rainbow_colors[NUM_COLORS][3] = {
    {255, 0, 0},     // ��ɫ
    {255, 127, 0},   // ��ɫ
    {255, 255, 0},   // ��ɫ
    {0, 255, 0},     // ��ɫ
    {0, 255, 255},   // ��ɫ
    {0, 0, 255},     // ��ɫ
    {148, 0, 211}    // ��ɫ
};

void ws2812_IO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��B�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //��ʼ��GPIOA
 	GPIO_SetBits(GPIOB,GPIO_Pin_3);
}

void ws2812_Init(void)
{
	ws2812_IO_Init();//��ʼ��GPIO
	delay_ms(100);
}


uint8_t rgb_data[3] = {0x00,0xFF,0x00};
 
void send_code(uint8_t * sdata)		 //������������
	{   
	uint8_t n = 0;
	uint8_t x = 0,y = 0,z = 0;
	
	for(x = 0;x <3;x++){        //����3�ֽ����ݣ�һ����3�ֽ�����
		n = sdata[x];
		for(y = 0;y < 8;y++){
			z = ((n<<y)&0x80);
			if(z){
				ws2812_Set();         //�ƵĿ��ƽ�λ����Ϊ�����
				delay_ns(7);         
				ws2812_Crl();					//�ƵĿ��ƽ�λ����Ϊ�����
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

// ���亯��
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
        delay_ms(50); // ���������ٶȣ���ʱʱ��Խ�̽����ٶ�Խ��
    }
}
// ѭ�����亯��
void loop_rainbow(void) 
	{
    for (int i = 0; i < NUM_COLORS - 1; i++) {
        uint8_t *start_color = rainbow_colors[i];
        uint8_t *end_color = rainbow_colors[i + 1];
        gradient(start_color, end_color, 100); // ÿ����ɫ���� 100 ��
    }
    // ���һ����ɫ���һ����ɫ����
    uint8_t *start_color = rainbow_colors[NUM_COLORS - 1];
    uint8_t *end_color = rainbow_colors[0];
    gradient(start_color, end_color, 100); // ÿ����ɫ���� 100 ��
}
