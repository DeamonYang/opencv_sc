/******************************************************************************
*��	�������ɼ�����Ƶ���ݲü�Ϊ����ߴ��ͼƬ
*��	����ͼƬ������PIC_DATA�ļ�����
******************************************************************************/

#include <opencv2\opencv.hpp>  
#include "stdio.h"

using namespace cv;
using namespace std;

#define PIC_LEN 640*480

#define PIC1 640*120*1
#define PIC2 640*120*2
#define PIC3 640*120*3

/*ȡ4������*/
#define CUT_W	640
#define CUT_H	10
#define BUF_LEN  CUT_W*CUT_H

#define FILE_NAME ".\\PIC_DATA\\CUT_PIC.yuv"

int mainccc()
{
	//��ȡ��Ƶ������ͷ  
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

		/*��ȡͼƬ*/
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

		waitKey(30);    //��ʱ30  
	}
	return 0;
}