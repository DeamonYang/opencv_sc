


#include "stdio.h"  
#include "windows.h"  
#include "net_server.h"

int  server_recv();
int  server_send();

DWORD WINAPI ThreadFun(LPVOID pM)
{
	printf("子线程的线程ID号为:%d\n子线程输出Hello World\n", GetCurrentThreadId());
	server_recv();
	return 0;
}
//主函数，所谓主函数就是主线程执行的函数  
int main()
{
	char a;
	printf("  最简单的创建多线程实例\n");
	HANDLE handle = CreateThread(NULL, 0, ThreadFun, NULL, 0, NULL);

	server_send();




	WaitForSingleObject(handle, INFINITE);
	scanf("%c",&a);
	return 0;
}


