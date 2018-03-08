/*************************************************************************************************
*功能描述采集摄像头视频并存储为AVI视频
*分辨率为 640*480
*************************************************************************************************/

#include <iostream>  
#include<opencv2/opencv.hpp> 
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include "pic.h"
#include "myNeuralNetworkFunction.h"
#include "annpar.h"


using namespace std;
using namespace cv;

#define BUF_LEN 640*480*3

#define PIC_LEN 1024*15

#define SCAL 0.5


int main()
{
	IplImage temp;
	IplImage * img;
	
//	VideoCapture capture(0);
	Mat src;
	Mat data;
	vector<uchar> buf;
	char rvbuf(PIC_LEN);
	//vector<int> parm(2);
	//char filename[20];
	int pid = 0;
	float tag;

	int i = 1;
	//capture.set(CV_CAP_PROP_FRAME_WIDTH,320);
	//capture.set(CV_CAP_PROP_FRAME_HEIGHT, 240);

	char filename[100] = "F:/sc_opencv/resheep/train/1.jpg";
	IplImage *jpg_pic = cvLoadImage(filename, CV_LOAD_IMAGE_ANYCOLOR);


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



	//for (i = 372; i < 372 + 83; i++)
	//{
	//	sprintf(filename, "F:/sc_opencv/resheep/train/%d.jpg",pid++);

	//	IplImage *jpg_pic = cvLoadImage(filename, CV_LOAD_IMAGE_ANYCOLOR);


	//	tag = pb_ann((unsigned char*)jpg_pic->imageData);

	//	cvLine(jpg_pic, CvPoint(tag,0),CvPoint(tag,5),Scalar(255,255,0));
	//	
	//	cvShowImage("train", jpg_pic);

	//	printf("%f", tag);
	//	
	//	waitKey(0);
	//
	//}





	

	return 0;
}