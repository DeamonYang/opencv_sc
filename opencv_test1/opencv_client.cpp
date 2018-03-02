////#include <WINSOCK2.H>  
////#include <iostream>  
////#include <stdio.h>  
////#include <cv.h>  
////#include <opencv2/core/core.hpp>  
////#include <opencv2/highgui/highgui.hpp>  
////#include <opencv2/imgproc/imgproc.hpp>  
////
////#pragma  comment(lib,"ws2_32.lib")  
////
////int main(int argc, char* argv[])
////{
////
////	//��ȡͼ�񲢷���  
////	IplImage *image_src =  cvLoadImage("lena.jpg");//����ͼƬ //NULL;
////	IplImage *image_dst = cvCreateImage(cvSize(640, 480), 8, 1);//�ҵ�����ͷ��640x480�ģ��粻ͬ�������޸�  
////
////	CvCapture *capture = cvCreateCameraCapture(0);//������ͷ  
////	if (!capture)
////	{
////		printf("����ͷ��ʧ�ܣ������豸��\n");
////	}
////	int i, j;
////	char sendData[1000000] = "";
////	cvNamedWindow("client", 1);
////	while (1)
////	{
//////		image_src = cvQueryFrame(capture);
////		cvCvtColor(image_src, image_dst, CV_RGB2GRAY);
////		for (i = 0; i < image_dst->height; i++)
////		{
////			for (j = 0; j < image_dst->width; j++)
////			{
////				sendData[image_dst->width * i + j] = ((char *)(image_dst->imageData + i * image_dst->widthStep))[j];
////			}
////		}
////		cvShowImage("client", image_src);//��ʾԭͼ  
////		cvWaitKey(30);//���������յ�����Ƶ�ȽϿ����˴���ʱ�ʵ��Ĵ�һ��  
//////		send(sclient, sendData, 1000000, 0);
////	}
////	cvReleaseCapture(&capture);
////	cvDestroyWindow("client");
//////	closesocket(sclient);
////	WSACleanup();
////	return 0;
////}


#include <WINSOCK2.H>  
#include <iostream>  
#include <stdio.h>  
#include <cv.h>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  

#pragma  comment(lib,"ws2_32.lib")  

int maincc  (int argc, char* argv[]) 
{
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0)
	{
		return 0;
	}

	SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sclient == INVALID_SOCKET)
	{
		printf("invalid socket !\n");
		return 0;
	}

	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(8888);
	serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); //��������IP��ַ�������ǣ����������������Ģ��ֶ����õ�  
	if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
	{
		printf("connect error !\n");
		closesocket(sclient);
		return 0;
	}
	//��ȡͼ�񲢷���  
	IplImage *image_src =  cvLoadImage("lena.jpg");//����ͼƬ //NULL;
	IplImage *image_dst = cvCreateImage(cvSize(640, 480), 8, 1);//�ҵ�����ͷ��640x480�ģ��粻ͬ�������޸�  

	CvCapture *capture = cvCreateCameraCapture(0);//������ͷ  
	if (!capture)
	{
		printf("����ͷ��ʧ�ܣ������豸��\n");
	}
	int i, j;
	char sendData[1000000] = "";
	cvNamedWindow("client", 1);
	while (1)
	{
//		image_src = cvQueryFrame(capture);
		cvCvtColor(image_src, image_dst, CV_RGB2GRAY);
		for (i = 0; i < image_dst->height; i++)
		{
			for (j = 0; j < image_dst->width; j++)
			{
				sendData[image_dst->width * i + j] = ((char *)(image_dst->imageData + i * image_dst->widthStep))[j];
			}
		}
		cvShowImage("client", image_src);//��ʾԭͼ  
		cvWaitKey(30);//���������յ�����Ƶ�ȽϿ����˴���ʱ�ʵ��Ĵ�һ��  
		send(sclient, sendData, 1000000, 0);
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("client");
	closesocket(sclient);
	WSACleanup();
	return 0;
}









//////#include <WINSOCK2.H>  
//////#include <iostream>  
//////#include <stdio.h>  
//////#include <cv.h>  
//////#include <opencv2/core/core.hpp>  
//////#include <opencv2/highgui/highgui.hpp>  
//////#include <opencv2/imgproc/imgproc.hpp>  
//////
//////#pragma  comment(lib,"ws2_32.lib")  
//////
//////int main(int argc, char* argv[])
//////{
//////
//////	//��ȡͼ�񲢷���  
//////	IplImage *image_src = cvLoadImage("lena.jpg");//����ͼƬ  
//////	IplImage *image_dst = cvCreateImage(cvSize(640, 480), image_src->depth, 1);//,cvSize(640, 480), IPL_DEPTH_8U , 1);//���ûҶ�ͼ��  
//////
//////	cvShowImage("client_src", image_src);
//////	cvShowImage("client_dst", image_dst);
//////
////////	cvWaitKey(0);//���������  
////// 
////// 
//////	cvNamedWindow("client", 1);
//////	cvCvtColor(image_src, image_dst, CV_RGB2GRAY);
//////
//////
//////	cvShowImage("client", image_dst);
//////	cvWaitKey(0);//���������  
//////
//////	cvDestroyWindow("client");
//////
//////	return 0;
//////}
////
////
////
////
////
////
////
////
////
////
////
////
////
////#include <WINSOCK2.H>  
////#include <iostream>  
////#include <stdio.h>  
////#include <cv.h>  
////#include <opencv2/core/core.hpp>  
////#include <opencv2/highgui/highgui.hpp>  
////#include <opencv2/imgproc/imgproc.hpp>  
////
////#pragma  comment(lib,"ws2_32.lib")  
////
////int main (int argc, char* argv[])
////{
////	WORD sockVersion = MAKEWORD(2, 2);
////	WSADATA data;
////	if (WSAStartup(sockVersion, &data) != 0)
////	{
////		return 0;
////	}
////
////	SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
////	if (sclient == INVALID_SOCKET)
////	{
////		printf("invalid socket !\n");
////		return 0;
////	}
////
////	sockaddr_in serAddr;
////	serAddr.sin_family = AF_INET;
////	serAddr.sin_port = htons(8888);
////	serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
////	if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
////	{
////		printf("connect error !\n");
////		closesocket(sclient);
////		return 0;
////	}
////	//��ȡͼ�񲢷���  
////	IplImage *image_src = cvLoadImage("lena.jpg");//����ͼƬ  
////	IplImage *image_dst = cvCreateImage(cvSize(640, 480), 8, 1);//���ûҶ�ͼ��  
////
////	//cvShowImage("client_src", image_src);
////	//cvShowImage("client_dst", image_dst);
////  
////
////	int i, j;
////	char sendData[1000000] = "";
////	cvNamedWindow("client", 1);
////	cvCvtColor(image_src, image_dst, CV_RGB2GRAY);
////
////	for (i = 0; i < image_dst->height; i++)
////	{
////		for (j = 0; j < image_dst->width; j++)
////		{
////			sendData[image_dst->width * i + j] = ((char *)(image_dst->imageData + i * image_dst->widthStep))[j];
////		}
////	}
////	cvShowImage("client", image_dst);
//// 
////	send(sclient, sendData, 1000000, 0);//����  
////	cvWaitKey(0);//��������� 
////	cvDestroyWindow("client");
////	closesocket(sclient);
////	WSACleanup();
////	return 0;
////}