#include "lvglapp.h"
#include "lvgl.h"
#include "tim.h"
#include "userusart.h"

static void UI_Init(void);

extern TaskHandle_t UIInterface_Handle;	/* 界面任务句柄 */
extern TaskHandle_t LVGL_TASK_Handle;

extern Time_t NowTime;				//年月日星期时分秒
extern CPUInfo_t monCpuInfo;	//CPU型号、核心数、频率、总使用率、单核使用率*核心数、温度
extern GPUInfo_t monGpuInfo;	//GPU型号、显存大小、使用率、核心频率、温度
extern RAMInfo_t monRamInfo;	//运行内存总大小、已使用大小

static lv_obj_t * scr;

lv_obj_t * CPUName_Lable;
static lv_obj_t * CPUFre_Gauge;
static lv_obj_t * CPUFre_Lable;
static lv_obj_t * CPUUse_Chart;
static lv_chart_series_t * CPUUse_Series;
static lv_obj_t * CPUUse_Lable;
static lv_obj_t * CPUTemp_bar;
static lv_obj_t * CPUTemp_Lable;

lv_obj_t * GPUName_Lable;
static lv_obj_t * GPUFre_Gauge;
static lv_obj_t * GPUFre_Lable;
static lv_obj_t * GPUUse_Chart;
static lv_chart_series_t * GPUUse_Series;
static lv_obj_t * GPUUse_Lable;
static lv_obj_t * GPUTemp_bar;
static lv_obj_t * GPUTemp_Lable;

static lv_obj_t * RAMUse_bar;
static lv_obj_t * RAMUse_Lable;
static lv_style_t RAMUse_BarIndic_style;

static lv_style_t BackGround_style;
static lv_style_t Lable_style;
static lv_style_t CPUTempLable_style;
static lv_style_t GPUTempLable_style;
static lv_style_t Dashboard_style;
static lv_style_t Chart_style;
static lv_style_t BarBg_style;
static lv_style_t CPUBarIndic_style;
static lv_style_t GPUBarIndic_style;

lv_color_t CPUFre_Gauge_Colors[1];
const lv_coord_t series1_y[10] = {0,0,0,0,0,0,0,0,0,0};

static void UI_Init(void)
{
	scr = lv_scr_act();//获取当前活跃的屏幕对象
	
	lv_style_copy(&BackGround_style,&lv_style_plain_color);
	BackGround_style.body.main_color = LV_COLOR_BLACK;
	BackGround_style.body.grad_color = LV_COLOR_BLACK;
	lv_obj_set_style(scr,&BackGround_style);
	
	CPUName_Lable = lv_label_create(scr,NULL);//创建标签
	lv_label_set_long_mode(CPUName_Lable,LV_LABEL_LONG_SROLL);	//设置左右滚动模式
	lv_obj_set_width(CPUName_Lable,240);//设置宽度,一定得放在lv_label_set_long_mode的后面,否则不起作用的
	lv_label_set_align(CPUName_Lable,LV_LABEL_ALIGN_CENTER);//文本居中对齐
	lv_obj_align(CPUName_Lable,NULL,LV_ALIGN_IN_TOP_MID,0,2);
	lv_label_set_anim_speed(CPUName_Lable,5);
	lv_label_set_text(CPUName_Lable,"CPUName");//设置文本
	
	lv_style_copy(&Lable_style,&lv_style_plain_color);
	Lable_style.text.color = LV_COLOR_WHITE;
	lv_label_set_style(CPUName_Lable,LV_LABEL_STYLE_MAIN,&Lable_style);
	
	lv_style_copy(&Dashboard_style, &lv_style_pretty_color);
	Dashboard_style.body.main_color = LV_COLOR_MAKE(0x5F,0xB8,0x78);	//关键数值点之前的刻度线的起始颜色,为浅绿色
	Dashboard_style.body.grad_color = LV_COLOR_MAKE(0xFF,0xB8,0x00);	//关键数值点之前的刻度线的终止颜色,为浅黄色
	Dashboard_style.body.padding.left = 4;//每一条刻度线的长度
	Dashboard_style.body.padding.inner = 2;//数值标签与刻度线之间的距离
	Dashboard_style.body.border.color = LV_COLOR_WHITE;//中心圆点的颜色
	Dashboard_style.line.width = 2;//刻度线的宽度
	Dashboard_style.text.color = LV_COLOR_BLACK;//数值标签的文本颜色
	Dashboard_style.line.color = LV_COLOR_RED;//关键数值点之后的刻度线的颜色
	
	CPUFre_Gauge = lv_gauge_create(scr, NULL);//创建仪表盘
	lv_obj_set_size(CPUFre_Gauge,80,80);//设置仪表盘的大小
	lv_gauge_set_style(CPUFre_Gauge,LV_GAUGE_STYLE_MAIN,&Dashboard_style);//设置样式
	lv_gauge_set_range(CPUFre_Gauge,0,500);//设置仪表盘的范围
	CPUFre_Gauge_Colors[0]=LV_COLOR_WHITE;
	lv_gauge_set_needle_count(CPUFre_Gauge,1,CPUFre_Gauge_Colors);	//设置指针的数量和其颜色
	lv_gauge_set_value(CPUFre_Gauge,0,0);//设置指针 1 指向的数值
	lv_gauge_set_critical_value(CPUFre_Gauge,400);//设置关键数值点
	lv_gauge_set_scale(CPUFre_Gauge,240,11,6);//设置角度,刻度线的数量,数值标签的数量
	lv_obj_align(CPUFre_Gauge,NULL,LV_ALIGN_IN_TOP_LEFT,0,25);

	CPUFre_Lable = lv_label_create(scr,CPUName_Lable);//创建标签
	lv_obj_set_width(CPUFre_Lable,80);//设置宽度,一定得放在lv_label_set_long_mode的后面,否则不起作用的
	lv_obj_align(CPUFre_Lable,CPUFre_Gauge,LV_ALIGN_CENTER,0,0);//设置与 CPUFre_Gauge的对齐方式
	lv_obj_set_y(CPUFre_Lable,90);
	lv_label_set_text(CPUFre_Lable,"000GHz");//设置文本
	
	lv_style_copy(&Chart_style,&lv_style_pretty);
	Chart_style.body.main_color = LV_COLOR_WHITE;//主背景为纯白色
	Chart_style.body.grad_color = Chart_style.body.main_color;
	Chart_style.body.border.color = LV_COLOR_GRAY;//边框的颜色
	Chart_style.body.border.width = 1;//边框的宽度
	Chart_style.body.border.opa = LV_OPA_COVER;
	Chart_style.body.radius = 0;
	Chart_style.line.color = LV_COLOR_GRAY;//分割线和刻度线的颜色
	Chart_style.text.color = LV_COLOR_WHITE;//主刻度标题的颜色
	
	CPUUse_Chart = lv_chart_create(scr,NULL);
	lv_obj_set_size(CPUUse_Chart,80,60);//设置图表的大小
	lv_obj_align(CPUUse_Chart,NULL,LV_ALIGN_IN_TOP_MID,20,25);//设置对齐方式
	lv_chart_set_type(CPUUse_Chart,LV_CHART_TYPE_AREA);	//设置为面积图
	lv_chart_set_series_width(CPUUse_Chart,2);//设置数据线的宽度
	lv_chart_set_style(CPUUse_Chart,LV_CHART_STYLE_MAIN,&Chart_style);//设置样式
	lv_chart_set_point_count(CPUUse_Chart,10);//设置每条数据线所具有的数据点个数,如果不设置的话,则默认值是 10
	lv_chart_set_div_line_count(CPUUse_Chart,4,4);//设置水平和垂直分割线
	lv_chart_set_range(CPUUse_Chart,0,100);//设置 y 轴的数值范围,[0,100]也是默认值
	lv_chart_set_y_tick_length(CPUUse_Chart,4,2);//设置 y 轴的主刻度线长度和次刻度线长度
	lv_chart_set_y_tick_texts(CPUUse_Chart,"100\n80\n60\n40\n20\n0",2,LV_CHART_AXIS_SKIP_LAST_TICK);
	lv_chart_set_x_tick_length(CPUUse_Chart,4,2);	//设置 x 轴的主刻度线长度和次刻度线长度
	lv_chart_set_x_tick_texts(CPUUse_Chart,"0\n2\n4\n6\n8\n10",2,LV_CHART_AXIS_SKIP_LAST_TICK);	//设置 x 轴的刻度数和主刻度标题
	lv_chart_set_margin(CPUUse_Chart,4);//设置刻度区域的高度
	lv_chart_set_update_mode(CPUUse_Chart,LV_CHART_UPDATE_MODE_SHIFT);
	//往图表中添加第 1 条数据线
	CPUUse_Series = lv_chart_add_series(CPUUse_Chart,LV_COLOR_NAVY);
	lv_chart_init_points(CPUUse_Chart,CPUUse_Series,0);
	lv_chart_refresh(CPUUse_Chart);//如果是采用直接修改的方式,请最好调用一下刷新操作
	
	CPUUse_Lable = lv_label_create(scr,CPUFre_Lable);//创建标签
	lv_obj_align(CPUUse_Lable,CPUUse_Chart,LV_ALIGN_OUT_BOTTOM_MID,0,0);//设置与 CPUUse_Chart 的对齐方式
	lv_obj_set_y(CPUUse_Lable,90);
	lv_label_set_text(CPUUse_Lable,"000%");//设置文本
	
	//创建进度条背景样式
	lv_style_copy(&BarBg_style,&lv_style_plain_color);
	BarBg_style.body.main_color = LV_COLOR_WHITE;
	BarBg_style.body.grad_color = LV_COLOR_WHITE;
	BarBg_style.body.radius = LV_RADIUS_CIRCLE;//绘制圆角
	//创建进度条指示器样式
	lv_style_copy(&CPUBarIndic_style,&lv_style_plain_color);
	CPUBarIndic_style.body.main_color = LV_COLOR_GREEN;
	CPUBarIndic_style.body.grad_color = LV_COLOR_GREEN;
	CPUBarIndic_style.body.radius = LV_RADIUS_CIRCLE;//绘制圆角
	CPUBarIndic_style.body.padding.left = 2;
	CPUBarIndic_style.body.padding.top = 2;
	CPUBarIndic_style.body.padding.right = 2;
	CPUBarIndic_style.body.padding.bottom = 2;
	
	CPUTemp_bar = lv_bar_create(scr, NULL);//从 bar1 进行拷贝
	lv_obj_set_size(CPUTemp_bar,12,60);//设置大小,宽度比高度小就是垂直的
	//设置与 bar1 的对齐方式
	lv_obj_align(CPUTemp_bar,scr,LV_ALIGN_IN_TOP_RIGHT,-20,25);
	lv_bar_set_anim_time(CPUTemp_bar,500);//设置动画时长
	lv_bar_set_style(CPUTemp_bar,LV_BAR_STYLE_BG,&BarBg_style);//设置进度条背景的样式
	lv_bar_set_style(CPUTemp_bar,LV_BAR_STYLE_INDIC,&CPUBarIndic_style);//设置进度条指示器的样式
	lv_bar_set_value(CPUTemp_bar,0,LV_ANIM_ON);//设置新的进度值
	
	lv_style_copy(&CPUTempLable_style,&Lable_style);
	CPUTemp_Lable = lv_label_create(scr,CPUFre_Lable);//创建标签
	lv_obj_align(CPUTemp_Lable,CPUTemp_bar,LV_ALIGN_OUT_BOTTOM_MID,0,0);//设置与 CPUTemp_bar 的对齐方式
	lv_obj_set_y(CPUTemp_Lable,90);
	lv_label_set_style(CPUTemp_Lable,LV_LABEL_STYLE_MAIN,&CPUTempLable_style);	
	lv_label_set_text(CPUTemp_Lable,"000");//设置文本
	
	GPUName_Lable = lv_label_create(scr,CPUName_Lable);//创建标签
	lv_obj_align(GPUName_Lable,NULL,LV_ALIGN_CENTER,0,0);
	lv_label_set_text(GPUName_Lable,"GPUName");//设置文本
	
	GPUFre_Gauge = lv_gauge_create(scr, CPUFre_Gauge);//创建仪表盘
	lv_gauge_set_range(GPUFre_Gauge,0,500);//设置仪表盘的范围
	lv_gauge_set_critical_value(GPUFre_Gauge,400);//设置关键数值点
	lv_obj_align(GPUFre_Gauge,NULL,LV_ALIGN_IN_LEFT_MID,0,53);

	GPUFre_Lable = lv_label_create(scr,CPUFre_Lable);//创建标签
	lv_obj_align(GPUFre_Lable,GPUFre_Gauge,LV_ALIGN_CENTER,0,0);//设置与 CPUFre_Gauge的对齐方式
	lv_obj_set_y(GPUFre_Lable,198);
	lv_label_set_text(GPUFre_Lable,"0000GHz");//设置文本
	
	GPUUse_Chart = lv_chart_create(scr,CPUUse_Chart);
	lv_obj_align(GPUUse_Chart,CPUUse_Chart,LV_ALIGN_OUT_BOTTOM_MID,0,48);//设置对齐方式
	//往图表中添加第 1 条数据线
	GPUUse_Series = lv_chart_add_series(GPUUse_Chart,LV_COLOR_NAVY);
	lv_chart_init_points(GPUUse_Chart,GPUUse_Series,0);
	lv_chart_refresh(GPUUse_Chart);//如果是采用直接修改的方式,请最好调用一下刷新操作
	
	GPUUse_Lable = lv_label_create(scr,CPUFre_Lable);//创建标签
	lv_obj_align(GPUUse_Lable,GPUUse_Chart,LV_ALIGN_OUT_BOTTOM_MID,0,0);
	lv_obj_set_y(GPUUse_Lable,198);
	lv_label_set_text(GPUUse_Lable,"000%");//设置文本
	
	lv_style_copy(&GPUBarIndic_style,&CPUBarIndic_style);
	GPUTemp_bar = lv_bar_create(scr, CPUTemp_bar);//从 bar1 进行拷贝
	lv_bar_set_style(GPUTemp_bar,LV_BAR_STYLE_INDIC,&GPUBarIndic_style);//设置进度条指示器的样式
	lv_obj_align(GPUTemp_bar,CPUTemp_bar,LV_ALIGN_OUT_BOTTOM_MID,0,48);
	
	lv_style_copy(&GPUTempLable_style,&Lable_style);
	GPUTemp_Lable = lv_label_create(scr,CPUFre_Lable);//创建标签
	lv_obj_align(GPUTemp_Lable,GPUTemp_bar,LV_ALIGN_OUT_BOTTOM_MID,0,0);//设置与 CPUTemp_bar 的对齐方式
	lv_obj_set_y(GPUTemp_Lable,198);
	lv_label_set_style(GPUTemp_Lable,LV_LABEL_STYLE_MAIN,&GPUTempLable_style);	
	lv_label_set_text(GPUTemp_Lable,"000");//设置文本
	
	lv_style_copy(&RAMUse_BarIndic_style,&CPUBarIndic_style);
	RAMUse_bar = lv_bar_create(scr, CPUTemp_bar);//从 bar1 进行拷贝
	lv_obj_set_size(RAMUse_bar,100,12);//设置大小,宽度比高度小就是垂直的
	lv_obj_align(RAMUse_bar,scr,LV_ALIGN_IN_BOTTOM_RIGHT,-2,0);
	lv_bar_set_style(RAMUse_bar,LV_BAR_STYLE_BG,&BarBg_style);//设置进度条背景的样式
	lv_bar_set_style(RAMUse_bar,LV_BAR_STYLE_INDIC,&RAMUse_BarIndic_style);//设置进度条指示器的样式
	lv_bar_set_value(RAMUse_bar,0,LV_ANIM_ON);//设置新的进度值
	
	RAMUse_Lable = lv_label_create(scr,CPUFre_Lable);//创建标签
	lv_obj_set_width(RAMUse_Lable,135);
	lv_obj_align(RAMUse_Lable,RAMUse_bar,LV_ALIGN_OUT_LEFT_MID,0,0);
	lv_label_set_text(RAMUse_Lable,"00GB/00GB(000%)");//设置文本
	
}



/*
								文本  仪表盘	图表		刻度指示器		
	显示CPU				型号、频率、总使用率、温度
	显示GPU				型号、频率、  使用率、温度
	显示运行内存	总大小、已使用大小
*/
void UIInterface_Task(void)		
{
	char CPUFre[10],CPUUse[10],CPUTemp[10];
	char GPUFre[10],GPUUse[10],GPUTemp[10];
	char RAMUse[20];
	UI_Init();
	while(1)
	{
		ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
		sprintf(CPUFre,"%.2fGHz",((float)(monCpuInfo.speed))/100);
		sprintf(CPUUse,"%d%%",monCpuInfo.totalUsage);	
		sprintf(CPUTemp,"%d",monCpuInfo.temperture);
		
		sprintf(GPUFre,"%.3fGHz",((float)(monGpuInfo.coreSpeed))/1000);
		sprintf(GPUUse,"%d%%",monGpuInfo.coreLoad);
		sprintf(GPUTemp,"%d",monGpuInfo.temperture);
		
		sprintf(RAMUse,"%dGB/%dGB(%d%%)",monRamInfo.used/1024,monRamInfo.total/1024,monRamInfo.used*100/monRamInfo.total);
		
		lv_gauge_set_value(CPUFre_Gauge,0,monCpuInfo.speed);
		lv_label_set_text(CPUFre_Lable,CPUFre);
		lv_chart_set_next(CPUUse_Chart,CPUUse_Series,monCpuInfo.totalUsage);
		lv_label_set_text(CPUUse_Lable,CPUUse);
		if(monCpuInfo.temperture<50)
		{
			CPUBarIndic_style.body.main_color = LV_COLOR_GREEN;
			CPUBarIndic_style.body.grad_color = LV_COLOR_GREEN;
			CPUTempLable_style.text.color = LV_COLOR_WHITE;
		}
		else if(monCpuInfo.temperture<75)
		{
			CPUBarIndic_style.body.main_color = LV_COLOR_YELLOW;
			CPUBarIndic_style.body.grad_color = LV_COLOR_YELLOW;
			CPUTempLable_style.text.color = LV_COLOR_YELLOW;
		}
		else
		{
			CPUBarIndic_style.body.main_color = LV_COLOR_RED;
			CPUBarIndic_style.body.grad_color = LV_COLOR_RED;
			CPUTempLable_style.text.color = LV_COLOR_RED;
		}
		lv_label_set_style(CPUTemp_Lable,LV_LABEL_STYLE_MAIN,&CPUTempLable_style);	
		lv_bar_set_style(CPUTemp_bar,LV_BAR_STYLE_INDIC,&CPUBarIndic_style);
		lv_bar_set_value(CPUTemp_bar,monCpuInfo.temperture,LV_ANIM_ON);
		lv_label_set_text(CPUTemp_Lable,CPUTemp);
		
		lv_gauge_set_value(GPUFre_Gauge,0,monGpuInfo.coreSpeed/10);
		lv_label_set_text(GPUFre_Lable,GPUFre);
		lv_chart_set_next(GPUUse_Chart,GPUUse_Series,monGpuInfo.coreLoad);
		lv_label_set_text(GPUUse_Lable,GPUUse);
		if(monGpuInfo.temperture<50)
		{
			GPUBarIndic_style.body.main_color = LV_COLOR_GREEN;
			GPUBarIndic_style.body.grad_color = LV_COLOR_GREEN;
			GPUTempLable_style.text.color = LV_COLOR_WHITE;
		}
		else if(monGpuInfo.temperture<75)
		{
			GPUBarIndic_style.body.main_color = LV_COLOR_YELLOW;
			GPUBarIndic_style.body.grad_color = LV_COLOR_YELLOW;
			GPUTempLable_style.text.color = LV_COLOR_YELLOW;
		}
		else
		{
			GPUBarIndic_style.body.main_color = LV_COLOR_RED;
			GPUBarIndic_style.body.grad_color = LV_COLOR_RED;
			GPUTempLable_style.text.color = LV_COLOR_RED;
		}
		lv_label_set_style(GPUTemp_Lable,LV_LABEL_STYLE_MAIN,&GPUTempLable_style);	
		lv_bar_set_style(GPUTemp_bar,LV_BAR_STYLE_INDIC,&GPUBarIndic_style);
		lv_bar_set_value(GPUTemp_bar,monGpuInfo.temperture,LV_ANIM_ON);
		lv_label_set_text(GPUTemp_Lable,GPUTemp);
		
		lv_bar_set_value(RAMUse_bar,monRamInfo.used*100/monRamInfo.total,LV_ANIM_ON);
		lv_label_set_text(RAMUse_Lable,RAMUse);
		
//		vTaskDelay(10);
	}
}

void LVGL_TASK(void)
{
	while(1)
	{
		lv_task_handler();
		vTaskDelay(2);
	}
}




