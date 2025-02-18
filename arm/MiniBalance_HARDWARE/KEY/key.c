#include "key.h"
/**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
/**************************************************************************
函数功能：按键初始化
入口参数：无
返回  值：无
**************************************************************************/
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); // 使能GPIOB时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;			  // KEY对应引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;		  // 普通输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	  // 100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		  // 上拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);				  // 初始化GPIOB14

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);				  // 使能GPIOA时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_11 | GPIO_Pin_12; // KEY对应引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;						  // 普通输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;					  // 100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;						  // 上拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);								  // 初始化GPIOB14

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); // 使能GPIOC时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;			  // KEY对应引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;		  // 普通输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	  // 100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		  // 上拉
	GPIO_Init(GPIOC, &GPIO_InitStructure);				  // 初始化GPIOB14
}
/**************************************************************************
函数功能：按键扫描
入口参数：双击等待时间
返回  值：按键状态 0：无动作 1：单击 2：双击
**************************************************************************/
u8 click_N_Double(u8 time)
{
	static u8 flag_key, count_key, double_key;
	static u16 count_single, Forever_count;
	if (KEY == 0)
		Forever_count++; // 长按标志位未置1
	else
		Forever_count = 0;
	if (0 == KEY && 0 == flag_key)
		flag_key = 1;
	if (0 == count_key)
	{
		if (flag_key == 1)
		{
			double_key++;
			count_key = 1;
		}
		if (double_key == 2)
		{
			double_key = 0;
			count_single = 0;
			return 2; // 双击执行的指令
		}
	}
	if (1 == KEY)
		flag_key = 0, count_key = 0;

	if (1 == double_key)
	{
		count_single++;
		if (count_single > time && Forever_count < time)
		{
			double_key = 0;
			count_single = 0;
			return 1; // 单击执行的指令
		}
		if (Forever_count > time)
		{
			double_key = 0;
			count_single = 0;
		}
	}
	return 0;
}
/**************************************************************************
函数功能：按键扫描
入口参数：无
返回  值：按键状态 0：无动作
**************************************************************************/
u8 click(void)
{
	int temp;
	static u8 flag_key = 1; // 按键按松开标志
	if (flag_key && (KEY == 0 || KEY_P == 0 || KEY_J == 0 || KEY_M == 0 || KEY_X == 0))
	{
		flag_key = 0;
		if (KEY == 0)
			temp = 1;
		else if (KEY_P == 0)
			temp = 2;
		else if (KEY_X == 0)
			temp = 3;
		else if (KEY_J == 0)
			temp = 4;
		else if (KEY_M == 0)
			temp = 5;
		return temp; // 按键按下
	}
	else if (1 == KEY && 1 == KEY_P && 1 == KEY_J && 1 == KEY_M && 1 == KEY_X)
		flag_key = 1;
	return 0; // 无按键按下
}
/**************************************************************************
函数功能：长按检测
入口参数：无
返回  值：按键状态 0：无动作 1：长按2s
**************************************************************************/
u8 Long_Press(void)
{
	static u16 Long_Press_count, Long_Press;
	if (Long_Press == 0 && KEY == 0)
		Long_Press_count++; // 长按标志位未置1
	else
		Long_Press_count = 0;
	if (Long_Press_count > 200)
	{
		Long_Press = 1;
		Long_Press_count = 0;
		return 1;
	}
	if (Long_Press == 1) // 长按标志位置1
	{
		Long_Press = 0;
	}
	return 0;
}
