


#include "stdio.h"  
#include "windows.h"  
#include "net_server.h"

int  server_recv();
int  server_send();

DWORD WINAPI ThreadFun(LPVOID pM)
{
	printf("���̵߳��߳�ID��Ϊ:%d\n���߳����Hello World\n", GetCurrentThreadId());
	server_recv();
	return 0;
}
//����������ν�������������߳�ִ�еĺ���  
int main11111()
{
	char a;
	printf("  ��򵥵Ĵ������߳�ʵ��\n");
	HANDLE handle = CreateThread(NULL, 0, ThreadFun, NULL, 0, NULL);

	server_send();

	WaitForSingleObject(handle, INFINITE);

	scanf("%c",&a);

	return 0;
}


