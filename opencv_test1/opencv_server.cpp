#include <stdio.h>  
#include <winsock2.h>  
#include <cv.h>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  

#pragma comment(lib,"ws2_32.lib")  

int main111111(void)
{
	//初始化WSA  
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}
	//创建套接字  
	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (slisten == INVALID_SOCKET)
	{
		printf("socket error !");
		return 0;
	}
	//绑定IP和端口  
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8888);//端口8888  
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf("bind error !");
	}

	//开始监听  
	if (listen(slisten, 5) == SOCKET_ERROR)
	{
		printf("listen error !");
		return 0;
	}

	//循环接收数据  
	SOCKET sClient;
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);

	printf("等待连接...\n");
	do
	{
		sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
	} while (sClient == INVALID_SOCKET);
	printf("接受到一个连接：%s \r\n", inet_ntoa(remoteAddr.sin_addr));

	char revData[1000000] = "";
	IplImage *image_src = cvCreateImage(cvSize(640, 480), 8, 1);//收到的图像是640x480的，如不同请自行修改  
	int i, j;
	int ret;
	cvNamedWindow("server", 1);
	while (true)
	{
		//接收数据  
		ret = recv(sClient, revData, 1000000, 0);
		if (ret > 0)
		{
			revData[ret] = 0x00;
			for (i = 0; i < image_src->height; i++)
			{
				for (j = 0; j < image_src->width; j++)
				{
					((char *)(image_src->imageData + i * image_src->widthStep))[j] = revData[image_src->width * i + j];
				}
			}
			ret = 0;
		}
		cvShowImage("server", image_src);//收到的是灰度图像  
		cvWaitKey(1);
	}
	cvDestroyWindow("server");
	closesocket(slisten);
	WSACleanup();
	return 0;
}


////////#include <stdio.h>  
////////#include <winsock2.h>  
////////#include <cv.h>  
////////#include <opencv2/core/core.hpp>  
////////#include <opencv2/highgui/highgui.hpp>  
////////#include <opencv2/imgproc/imgproc.hpp>  
////////
////////#pragma comment(lib,"ws2_32.lib")  
////////
////////int maindd(int argc, char* argv[])
////////{
////////	//初始化WSA  
////////	WORD sockVersion = MAKEWORD(2, 2);
////////	WSADATA wsaData;
////////	if (WSAStartup(sockVersion, &wsaData) != 0)
////////	{
////////		return 0;
////////	}
////////	//创建套接字  
////////	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
////////	if (slisten == INVALID_SOCKET)
////////	{
////////		printf("socket error !");
////////		return 0;
////////	}
////////	//绑定IP和端口  
////////	sockaddr_in sin;
////////	sin.sin_family = AF_INET;
////////	sin.sin_port = htons(8888);//端口8888  
////////	sin.sin_addr.S_un.S_addr = INADDR_ANY;
////////	if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
////////	{
////////		printf("bind error !");
////////	}
////////
////////	//开始监听  
////////	if (listen(slisten, 5) == SOCKET_ERROR)
////////	{
////////		printf("listen error !");
////////		return 0;
////////	}
////////
////////	//循环接收数据  
////////	SOCKET sClient;
////////	sockaddr_in remoteAddr;
////////	int nAddrlen = sizeof(remoteAddr);
////////
////////	printf("等待连接...\n");
////////	do
////////	{
////////		sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
////////	} while (sClient == INVALID_SOCKET);
////////	printf("接受到一个连接：%s \r\n", inet_ntoa(remoteAddr.sin_addr));
////////
////////	char revData[1000000] = "";
////////	IplImage *image_src = cvCreateImage(cvSize(640, 480), 8, 1);//接收灰度图像  
////////	int i, j;
////////	int ret;
////////	cvNamedWindow("server", 1);
////////	while (true)
////////	{
////////		//接收数据  
////////		ret = recv(sClient, revData, 1000000, 0);
////////		if (ret > 0)
////////		{
////////			revData[ret] = 0x00;
////////			for (i = 0; i < image_src->height; i++)
////////			{
////////				for (j = 0; j < image_src->width; j++)
////////				{
////////					((char *)(image_src->imageData + i * image_src->widthStep))[j] = revData[image_src->width * i + j];
////////				}
////////			}
////////			ret = 0;
////////		}
////////		printf("create ok");
////////		cvShowImage("server", image_src);
////////		cvWaitKey(1);
////////	}
////////	cvDestroyWindow("server");
////////	closesocket(slisten);
////////	WSACleanup();
////////	return 0;
////////}