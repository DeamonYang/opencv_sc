/*************************************************************************************************
*��������������ͼƬ ��������ʾ ����Ϊjpgͼ��
*
************************************************************************************************/

#include <stdio.h>  
#include <winsock2.h>  
#include <Windows.h>  
#include <iostream>  
#include<opencv2/opencv.hpp>  

#include "pic.h"


using namespace std;
using namespace cv;

void proc_dis(Mat pic);

#pragma comment(lib,"ws2_32.lib")  
#define  PORT 8088  

#define PIC_LEN 1024*40


int mainrrrrrr (int argc, char* argv[])
{
	int i;
	
	Mat dispic;
	Mat data;
	//��ʼ�����绷��  
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("WSAStartup failed\n");
		return -1;
	}

	//����һ��UDP��socket  
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == SOCKET_ERROR)
	{
		printf("create socket failed\n");
		return -1;
	}

	//�󶨵�ַ��Ϣ  
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	bind(sock, (sockaddr*)&serverAddr, sizeof(sockaddr));

	unsigned char buf[PIC_LEN];
	while (TRUE)
	{
		memset(buf, 0, PIC_LEN);
		// ����ڵ����Ϣ����������ͻ��˵�������Ϣ  
		sockaddr_in clientAddr;
		memset(&clientAddr, 0, sizeof(sockaddr_in));
		int clientAddrLen = sizeof(sockaddr);
		//���տͻ��˷���������  

		int ret = recvfrom(sock, (char *)buf, PIC_LEN, 0, (sockaddr*)&clientAddr, &clientAddrLen);

		if (ret > 0)
		{
			vector <uchar> picbuf(ret);

			for (i = 0; i < ret; i++)
			{
				picbuf[i] = buf[i];
			}

			data = imdecode(picbuf, CV_LOAD_IMAGE_COLOR);

			imshow("data", data);
			proc_dis(data);


			/*����Ƶ�洢Ϊ�ļ�*/
			vector<int> parm(2);
			parm[0] = CV_IMWRITE_JPEG_QUALITY;
			parm[1] = 90;
			char filename[100];
			static int num = 0;
			sprintf(filename, "./pic/%d.jpg", num++);
			imwrite(filename, data, parm);



			printf("rv len %d\n", ret);

			waitKey(1);
		}
		




		
		// ��һ�����ݰ����ظ��ͻ�  
//		sendto(sock, "Hello World!", strlen("Hello World!"), 0, (sockaddr*)&clientAddr, clientAddrLen);
	 
	}
	return 0;
}



void proc_dis(Mat pic)
{
	Mat gry;
	Mat bina;
//	cvtColor(pic, gry, CV_BGR2GRAY);  
//	imshow("gry", gry);
////	adaptiveThreshold(gry, bina, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY,5,0);
//	threshold(gry, bina, 100, 255, THRESH_BINARY_INV);
//	imshow("th", bina);
	IplImage* jpg_pic = &IplImage(pic);
	IplImage *hsv = cvCreateImage(cvGetSize(jpg_pic), jpg_pic->depth, jpg_pic->nChannels);
 
	CvMat *outputImage;
	int i, j;

	cvCvtColor(jpg_pic, hsv, CV_BGR2HSV);

	int width = hsv->width;
	int height = hsv->height;
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
		{
			CvScalar s_hsv = cvGet2D(hsv, i, j);//��ȡ���ص�Ϊ��j, i�����HSV��ֵ   
			/*
			opencv ��H��Χ��0~180����ɫ��H��Χ�����(0~8)��(160,180)
			S�Ǳ��Ͷȣ�һ���Ǵ���һ��ֵ,S���;��ǻ�ɫ���ο�ֵS>80)��
			V�����ȣ����;��Ǻ�ɫ�����߾��ǰ�ɫ(�ο�ֵ220>V>50)��
			*/
			CvScalar s;
			if (!(((s_hsv.val[0]>0) && (s_hsv.val[0]<8)) || (s_hsv.val[0]>120) && (s_hsv.val[0]<180)))
			{
				s.val[0] = 0;
				s.val[1] = 0;
				s.val[2] = 0;
				cvSet2D(hsv, i, j, s);
			}


		}
	outputImage = cvCreateMat(hsv->height, hsv->width, CV_8UC3);
	Mat imghsv = cvarrToMat(hsv);
	Mat mypic;
	cvtColor(imghsv, mypic, CV_HSV2BGR);
	imshow("mypic",mypic);

	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(mypic, mypic, MORPH_OPEN, element);
	morphologyEx(mypic, mypic, MORPH_CLOSE, element);

	imshow("cut", mypic);



}

