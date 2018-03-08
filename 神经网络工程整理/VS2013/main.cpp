/*************************************************************************************************
*@描 述：神经网络识别红色引导线中心
*		 图片分辨率为 640*480
*		 该程序基于OPENCV 需要安装OPENCV库并配置相关环境
*@作 者：DeamonYang
*@Email: deamonyang@foxmail.com
*************************************************************************************************/

#include <iostream>  
#include<opencv2/opencv.hpp> 
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include "annpar.h"

using namespace std;
using namespace cv;

#define BUF_LEN 640*480*3

#define PIC_LEN 1024*15

#define SCAL 0.5


int main()
{
	int pid = 0;
	float tag;

	int i = 1;
	char filename[100] ;
	IplImage *jpg_pic ;


	for (i = 372; i < 372 + 83; i++)
	{
		sprintf(filename, "F:/sc_opencv/seldata/%d.jpg", i);
		/*打开图片*/
		jpg_pic = cvLoadImage(filename, CV_LOAD_IMAGE_ANYCOLOR);
		 
		IplImage pic = *jpg_pic;

		/*裁剪图像*/
		cvSetImageROI(jpg_pic, CvRect(0, 235, 640, 10));

		IplImage *rsz;

		CvSize sz;

		/*设置裁剪尺寸*/
		sz.height = jpg_pic->height*SCAL;
		sz.width = jpg_pic->width*SCAL;

		/*创建新的图像*/
		rsz = cvCreateImage(sz, jpg_pic->depth, jpg_pic->nChannels);

		/*裁剪图像*/
		cvResize(jpg_pic, rsz, CV_INTER_CUBIC);

		/*神经网络计算红线中心*/
		tag = pb_ann((unsigned char*)rsz->imageData);

		/*恢复图像*/
		cvResetImageROI(jpg_pic);

		/*绘制目标垂直线*/
		cvLine(jpg_pic, CvPoint(tag*2, 235), CvPoint(tag*2, 245), Scalar(255, 255, 0));

		/*绘制水平线*/
		cvLine(jpg_pic, CvPoint(0, 240), CvPoint(640, 240), Scalar(255, 255, 0));

		cvShowImage("ann", jpg_pic);

		waitKey(0);

	}

	return 0;
}