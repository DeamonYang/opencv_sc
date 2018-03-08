#include <iostream>  
#include<opencv2/opencv.hpp> 
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include "pic.h"
#include "myNeuralNetworkFunction.h"
#include "myann.h"


using namespace std;
using namespace cv;

/*��������Ԫ��Ŀ*/
#define HID_LEN 10
/*������Ԫ��Ŀ*/
#define INP_LEN 1

static void tansig_apply(const double n[15], double a[15])
{
	int i;

	//  Sigmoid Symmetric Transfer Function
	for (i = 0; i < HID_LEN; i++) 
	{
		a[i] = 2.0 / (1.0 + exp(-2.0 * n[i])) - 1.0;
	}
}



float pb_ann(float x )
{
	int i;
	float x1 = x - fx1_step1_xoffset;
	double a[HID_LEN];
	double a2;


	x1 = x1 * fx1_step1_gain;

	x1 = x1 + fx1_step1_ymin;

	/*������*/
	for (i = 0; i < HID_LEN; i++)
	{
		/*��������*/
		a[i] = x1 * fIW1_1[i] + fb1[i];
		
		/*���亯��*/
		a[i] = 2.0 / (1.0 + exp(-2.0 * a[i])) - 1.0;
	}

	/*�����*/
	for (i = 0; i < HID_LEN; i++)
	{
		/*��������*/
		a2 = a2 + a[i] * fIW2_1[i];
	}

	a2 = a2 + fb2;

	a2 = a2 - fy1_step1_ymin;

	a2 = a2 / fy1_step1_gain;

	a2 = a2 + fy1_step1_xoffset;

	return a2;

}


int mainannann(void)
{
	int i;
	float res[94];
	for (i = 0; i < 94; i++)
	{
		res[i] = pb_ann(fx[i]);
		printf("err = %f\r\n", res[i] - ft[i]);
	}

	getchar();

	return 0;

}








////
/////*************************************************************************************************
////*���������ɼ�����ͷ��Ƶ���洢ΪAVI��Ƶ
////*�ֱ���Ϊ 640*480
////*************************************************************************************************/
////
////#include <iostream>  
////#include<opencv2/opencv.hpp> 
////#include<opencv2/core/core.hpp>
////#include<opencv2/highgui/highgui.hpp>
////#include <opencv2/ml/ml.hpp>
////#include "pic.h"
////#include "myNeuralNetworkFunction.h"
////
////
////using namespace std;
////using namespace cv;
////
////#define BUF_LEN 640*480*3
////
////#define PIC_LEN 1024*15
////
////
////int main()
////{
////	IplImage temp;
////	IplImage * img;
////	
//////	VideoCapture capture(0);
////	Mat src;
////	Mat data;
////	vector<uchar> buf;
////	char rvbuf(PIC_LEN);
////	//vector<int> parm(2);
////	//char filename[20];
////
////	int i = 1;
////	//capture.set(CV_CAP_PROP_FRAME_WIDTH,320);
////	//capture.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
////
////	char filename[100] = "F:/sc_opencv/resheep/train/1.jpg";
////	IplImage *jpg_pic = cvLoadImage(filename, CV_LOAD_IMAGE_ANYCOLOR);
////	cvShowImage("train", jpg_pic);
////
////	FILE *fs;
////
////
////
////
////	char picbuf[3 * 320 * 5];
////	for (int j = 0; j < jpg_pic->imageSize; j++)
////	{
////		picbuf[j] = jpg_pic->imageData[j];
////
////	}
////
////
//// 
////	fs = fopen(".\\DATA\\test_data.yuv","rb+");
////	if (fs == NULL)
////	{
////		printf("open test_data.yuv error\n");
////	}
////	else
////	{
////		fread(picbuf, sizeof(char), 3 * 320 * 5, fs);
////	}
////	
////	fclose(fs);
////
////	fs = fopen(".\\DATA\\test_data_pic1.yuv", "ab+");//׷�ӷ�ʽ���ļ� �洢ѵ�����ݽ��
////	if (fs == NULL)
////	{
////		printf("open test_data.yuv error\n");
////	}
////	else
////	{
////		fwrite(picbuf, sizeof(char), jpg_pic->imageSize, fs);
////	}
////	fclose(fs);
////
////
////	double tag;
////
////	tag = myNeuralNetworkFunction(picbuf);
////
////	printf("%f",tag);
////
////
////
////	waitKey(0);
////
////	
////
////	return 0;
////}