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

#pragma comment(lib,"ws2_32.lib")  
#define  PORT 8088  

#define PIC_LEN 1024*40


int mainrrrr(int argc, char* argv[])
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

