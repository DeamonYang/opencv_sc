/*************************************************************************************************
*描述：接受网络图片 并解码显示 保存为jpg图像
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
	//初始化网络环境  
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("WSAStartup failed\n");
		return -1;
	}

	//建立一个UDP的socket  
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == SOCKET_ERROR)
	{
		printf("create socket failed\n");
		return -1;
	}

	//绑定地址信息  
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	bind(sock, (sockaddr*)&serverAddr, sizeof(sockaddr));

	unsigned char buf[PIC_LEN];
	while (TRUE)
	{
		memset(buf, 0, PIC_LEN);
		// 网络节点的信息，用来保存客户端的网络信息  
		sockaddr_in clientAddr;
		memset(&clientAddr, 0, sizeof(sockaddr_in));
		int clientAddrLen = sizeof(sockaddr);
		//接收客户端发来的数据  

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


			/*将视频存储为文件*/
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
		




		
		// 发一个数据包返回给客户  
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
			CvScalar s_hsv = cvGet2D(hsv, i, j);//获取像素点为（j, i）点的HSV的值   
			/*
			opencv 的H范围是0~180，红色的H范围大概是(0~8)∪(160,180)
			S是饱和度，一般是大于一个值,S过低就是灰色（参考值S>80)，
			V是亮度，过低就是黑色，过高就是白色(参考值220>V>50)。
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

