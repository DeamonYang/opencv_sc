#include "annpar.h"
#include "stdio.h"

/*隐含层神经元数目*/
#define HID_LEN 15
/*输入神经元数目*/
#define INP_LEN 4800

/*************************************************************************
*名称：图像处理神经网络
*输入参数：图像数据输入为320*5*2个数据
*返回值：计算的红色位置
*作者：deamonyang
************************************************************************/
float pb_ann(unsigned char x[INP_LEN])
{
	int i,j;
	double x1[INP_LEN] = {0};
	double a[HID_LEN] = {0};
	double a2 = 0;
	double temp;

	/*输入层*/
	for (i = 0; i < INP_LEN; i++)
	{
		x1[i] = x[i] - x1_step1_xoffset[i];
	}

	for (i = 0; i < INP_LEN; i++)
	{
		x1[i] = x1[i] * x1_step1_gain[i] + x1_step1_ymin;
	}

	/*layer 1*/
	for (i = 0; i < HID_LEN; i++)
	{
		temp = 0;

		for (j = 0; j < INP_LEN; j++)
		{
			temp = temp + x1[j] * IW1_1[i][j] ;
		}

		a[i] = temp + b1[i];

		/*传输函数*/
		a[i] = 2.0 / (1.0 + exp(-2.0 * a[i])) - 1.0;
	}

	/*输出层*/
	for (i = 0; i < HID_LEN; i++)
	{
		a2 = a[i] * LW2_1[i] + a2;
	}
	
	a2 = a2 + b2;

	a2 = a2 - y1_step1_ymin;

	a2 = a2 / y1_step1_gain;

	a2 = a2 + y1_step1_xoffset;

	return a2;

}
