#include <stdio.h>  
#include <winsock2.h>  
#include <cv.h>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  

#pragma comment(lib,"ws2_32.lib")  

int main111111(void)
{
	//��ʼ��WSA  
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}
	//�����׽���  
	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (slisten == INVALID_SOCKET)
	{
		printf("socket error !");
		return 0;
	}
	//��IP�Ͷ˿�  
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8888);//�˿�8888  
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf("bind error !");
	}

	//��ʼ����  
	if (listen(slisten, 5) == SOCKET_ERROR)
	{
		printf("listen error !");
		return 0;
	}

	//ѭ����������  
	SOCKET sClient;
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);

	printf("�ȴ�����...\n");
	do
	{
		sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
	} while (sClient == INVALID_SOCKET);
	printf("���ܵ�һ�����ӣ�%s \r\n", inet_ntoa(remoteAddr.sin_addr));

	char revData[1000000] = "";
	IplImage *image_src = cvCreateImage(cvSize(640, 480), 8, 1);//�յ���ͼ����640x480�ģ��粻ͬ�������޸�  
	int i, j;
	int ret;
	cvNamedWindow("server", 1);
	while (true)
	{
		//��������  
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
		cvShowImage("server", image_src);//�յ����ǻҶ�ͼ��  
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
////////	//��ʼ��WSA  
////////	WORD sockVersion = MAKEWORD(2, 2);
////////	WSADATA wsaData;
////////	if (WSAStartup(sockVersion, &wsaData) != 0)
////////	{
////////		return 0;
////////	}
////////	//�����׽���  
////////	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
////////	if (slisten == INVALID_SOCKET)
////////	{
////////		printf("socket error !");
////////		return 0;
////////	}
////////	//��IP�Ͷ˿�  
////////	sockaddr_in sin;
////////	sin.sin_family = AF_INET;
////////	sin.sin_port = htons(8888);//�˿�8888  
////////	sin.sin_addr.S_un.S_addr = INADDR_ANY;
////////	if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
////////	{
////////		printf("bind error !");
////////	}
////////
////////	//��ʼ����  
////////	if (listen(slisten, 5) == SOCKET_ERROR)
////////	{
////////		printf("listen error !");
////////		return 0;
////////	}
////////
////////	//ѭ����������  
////////	SOCKET sClient;
////////	sockaddr_in remoteAddr;
////////	int nAddrlen = sizeof(remoteAddr);
////////
////////	printf("�ȴ�����...\n");
////////	do
////////	{
////////		sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
////////	} while (sClient == INVALID_SOCKET);
////////	printf("���ܵ�һ�����ӣ�%s \r\n", inet_ntoa(remoteAddr.sin_addr));
////////
////////	char revData[1000000] = "";
////////	IplImage *image_src = cvCreateImage(cvSize(640, 480), 8, 1);//���ջҶ�ͼ��  
////////	int i, j;
////////	int ret;
////////	cvNamedWindow("server", 1);
////////	while (true)
////////	{
////////		//��������  
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