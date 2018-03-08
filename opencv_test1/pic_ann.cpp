#include <iostream>  
#include<opencv2/opencv.hpp> 
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include "pic.h"

#include "annpar.h"
#include "stdio.h"


using namespace std;
using namespace cv;

/*��������Ԫ��Ŀ*/
#define HID_LEN 15
/*������Ԫ��Ŀ*/
#define INP_LEN 4800

/*************************************************************************
*���ƣ�ͼ����������
*���������ͼ����������Ϊ320*5*2������
*����ֵ������ĺ�ɫλ��
*���ߣ�deamonyang
************************************************************************/
float pb_ann(unsigned char x[INP_LEN])
{
	int i,j;
	double x1[INP_LEN] = {0};
	double a[HID_LEN] = {0};
	double a2 = 0;
	double temp;

	/*�����*/
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

		/*���亯��*/
		a[i] = 2.0 / (1.0 + exp(-2.0 * a[i])) - 1.0;
	}

	/*�����*/
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


int mainnnnn(void)
{
	FILE *fd;
	int i;
	int len;
	float res[94];
	unsigned char pic_data[4800];
	float pos;

	/*���ļ� ֻ��*/
	fd = fopen(".\\DATA\\test_data.yuv", "rb+");
	if (fd == NULL)
	{
		printf("open test_data.yuv error\n");
		exit(1);
	}
	

	for (i = 0; i < 84; i++)
	{
		len = fread(pic_data, sizeof(char), 4800, fd);


		if (len != 4800)
		{
			printf("file size error\r\n");
			exit(2);
		}

		pos = pb_ann(pic_data);

		printf("pos = %f\r\n", pos);
	
	}




	fclose(fd);
	getchar();

	return 0;

}