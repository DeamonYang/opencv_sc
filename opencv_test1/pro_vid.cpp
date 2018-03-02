/******************************************************************************
*描	述：将采集的视频数据裁剪为所需尺寸的图片
*输	出：图片保存在PIC_DATA文件夹下
******************************************************************************/

#include <opencv2\opencv.hpp>  
#include "stdio.h"

using namespace cv;
using namespace std;

#define PIC_LEN 640*480

#define PIC1 640*120*1
#define PIC2 640*120*2
#define PIC3 640*120*3

/*取4行数据*/
#define CUT_W	640
#define CUT_H	10
#define BUF_LEN  CUT_W*CUT_H

#define FILE_NAME ".\\PIC_DATA\\CUT_PIC.yuv"

int mainccc()
{
	//读取视频或摄像头  
//	VideoCapture capture("cam.avi");

	int i;

	unsigned int id = 0;

	char * buf;

	char file_name[50];

	FILE* fd ;
	
	CvCapture *cff;

	IplImage *frame;

	IplImage *cpframe;

	IplImage *gryframe;

	IplImage *cutframe;

	cff = cvCreateFileCapture("cam.avi");

	frame = cvQueryFrame(cff);

	gryframe = cvCreateImage(cvGetSize(frame) , 8,1);

	cutframe = cvCreateImage(cvSize(CUT_W, CUT_H), 8, 1);

	char sdata[PIC_LEN * 2];
	unsigned char pdata[PIC_LEN];

	while (true)
	{

		frame = cvQueryFrame(cff);

//		cvCopy(frame,cpframe);

		cvShowImage("frame", frame);

		cvCvtColor(frame, gryframe, CV_BGR2GRAY);

		cvShowImage("gryframe", gryframe);

		/*截取图片*/
		buf = gryframe->imageData;


		sprintf(file_name,".\\PIC_DATA\\CUT_PIC%d.yuv",id++);
		fd = fopen(file_name, "w");
		fwrite(buf + PIC1, sizeof(char), BUF_LEN, fd);
		fclose(fd);

		sprintf(file_name, ".\\PIC_DATA\\CUT_PIC%d.yuv", id++);
		fd = fopen(file_name, "w");
		fwrite(buf + PIC2, sizeof(char), BUF_LEN, fd);
		fclose(fd);

		sprintf(file_name, ".\\PIC_DATA\\CUT_PIC%d.yuv", id++);
		fd = fopen(file_name, "w");
		fwrite(buf + PIC3, sizeof(char), BUF_LEN, fd);
		fclose(fd);


		cutframe->imageData = buf + PIC3;
		cvShowImage("cutframe", cutframe);

		waitKey(30);    //延时30  
	}
	return 0;
}