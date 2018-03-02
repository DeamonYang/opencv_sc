
#include <stdio.h>  
#include <Winsock2.h> //windows socket��ͷ�ļ�  

#pragma comment( lib, "ws2_32.lib" )// ����Winsock2.h�ľ�̬���ļ�  


#define DATA_LEN 1024
char gpsdatabuf[DATA_LEN];

#define INF_LEN 100


/*������λ�忨 ������ض�λ����*/
int  server_recv()
{
	//��ʼ��winsocket  
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	int indx = 0;

	wVersionRequested = MAKEWORD(1, 1);//��һ������Ϊ��λ�ֽڣ��ڶ�������Ϊ��λ�ֽ�  

	err = WSAStartup(wVersionRequested, &wsaData);//��winsock DLL����̬���ӿ��ļ������г�ʼ����Э��Winsock�İ汾֧�֣��������Ҫ����Դ��  
	if (err != 0)
	{
		return 0;
	}

	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)//LOBYTE����ȡ��16���������λ��HIBYTE����ȡ��16��������ߣ�����ߣ��Ǹ��ֽڵ�����        
	{
		WSACleanup();
		return 0;
	}

	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);//����socket��AF_INET��ʾ��Internet��ͨ�ţ�SOCK_STREAM��ʾsocket�����׽��֣���Ӧtcp��0ָ������Э��ΪTCP/IP  

	SOCKADDR_IN addrSrv;

	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY); //htonl�����������ֽ�˳��ת��Ϊ�����ֽ�˳��(to network long)  
	//INADDR_ANY����ָ����ַΪ0.0.0.0�ĵ�ַ,  
	//��ʾ��ȷ����ַ,�������ַ������  
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(8089);//htons�����������ֽ�˳��ת��Ϊ�����ֽ�˳��(to network short)  

	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));//�����ص�ַ�󶨵���������socket�ϣ���ʹ�������ϱ�ʶ��socket  

	listen(sockSrv, 5);//socket������׼��������������  

	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);

	while (1)
	{
		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);//Ϊһ�����������ṩ����addrClient�����˷�����������Ŀͻ���IP��ַ��Ϣ�����ص���socket������������ÿͻ���������  


		char recvBuf[1024];
		recv(sockConn, (char*)&gpsdatabuf, sizeof(gpsdatabuf), 0);

		printf("%s", gpsdatabuf);

		closesocket(sockConn);
		//		Sleep(2000);//2000����  
	}
	WSACleanup();

	return 0;
}


/*�����ͻ��� �������� �������������*/
int  server_send()
{
	//��ʼ��winsocket  
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	int indx = 0;

	wVersionRequested = MAKEWORD(1, 1);//��һ������Ϊ��λ�ֽڣ��ڶ�������Ϊ��λ�ֽ�  

	err = WSAStartup(wVersionRequested, &wsaData);//��winsock DLL����̬���ӿ��ļ������г�ʼ����Э��Winsock�İ汾֧�֣��������Ҫ����Դ��  
	if (err != 0)
	{
		return 0;
	}

	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)//LOBYTE����ȡ��16���������λ��HIBYTE����ȡ��16��������ߣ�����ߣ��Ǹ��ֽڵ�����        
	{
		WSACleanup();
		return 0;
	}

	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);//����socket��AF_INET��ʾ��Internet��ͨ�ţ�SOCK_STREAM��ʾsocket�����׽��֣���Ӧtcp��0ָ������Э��ΪTCP/IP  

	SOCKADDR_IN addrSrv;

	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY); //htonl�����������ֽ�˳��ת��Ϊ�����ֽ�˳��(to network long)  
	//INADDR_ANY����ָ����ַΪ0.0.0.0�ĵ�ַ,  
	//��ʾ��ȷ����ַ,�������ַ������  
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(8088);//htons�����������ֽ�˳��ת��Ϊ�����ֽ�˳��(to network short)  

	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));//�����ص�ַ�󶨵���������socket�ϣ���ʹ�������ϱ�ʶ��socket  

	listen(sockSrv, 5);//socket������׼��������������  

	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);

	while (1)
	{
		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);//Ϊһ�����������ṩ����addrClient�����˷�����������Ŀͻ���IP��ַ��Ϣ�����ص���socket������������ÿͻ���������  


		char recvBuf[1024];
		recv(sockConn, (char*)&recvBuf, 1024, 0);
		printf("%s", recvBuf);

		char sendBuf[50];
		send(sockConn, gpsdatabuf, strlen(gpsdatabuf) + 1, 0);


		closesocket(sockConn);
		//		Sleep(2000);//2000����  
	}
	WSACleanup();

	return 0;
}