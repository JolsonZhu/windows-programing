// Client.cpp : 定义控制台应用程序的入口点。

#include "winsock2.h"
#include "windows.h"
#include "stdio.h"
#define    BUF_SZIE    64
#pragma comment(lib, "ws2_32.lib")

int main(int argc, char* argv[])
{

	WSADATA            wsad;            //WSADATA变量
	SOCKET            sHost;            //服务器套接字
	SOCKADDR_IN        servAddr;        //服务器地址
	char            buf[BUF_SZIE];    //接收数据缓冲区
	int                retVal;            //返回值

										  //初始化套接字动态库
	if (WSAStartup(MAKEWORD(2, 2), &wsad) != 0)
	{
		printf("初始化套接字失败!\n");
		return -1;
	}

	//创建套接字
	sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sHost)
	{
		printf("创建套接字失败!\n");
		WSACleanup();//释放套接字资源
		return  -1;
	}

	//设置服务器地址
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons((short)2012);
	int    nServAddlen = sizeof(servAddr);

	printf("网络1311第二组-客户端\n");

	//连接服务器
	retVal = connect(sHost, (LPSOCKADDR)&servAddr, sizeof(servAddr));
	if (SOCKET_ERROR == retVal)
	{
		printf("连接服务器失败!\n");
		closesocket(sHost);    //关闭套接字
		WSACleanup();        //释放套接字资源
		return -1;
	}

	//向服务器发送数据
	ZeroMemory(buf, BUF_SZIE);
	strcpy(buf, "我也是集美大学网络工程专业学生\n");
	retVal = send(sHost, buf, strlen(buf), 0);
	if (SOCKET_ERROR == retVal)
	{
		printf("发送数据失败!\n");
		closesocket(sHost);    //关闭套接字
		WSACleanup();        //释放套接字资源
		return -1;
	}

	printf("我是集美大学网络工程专业学生\n");

	//退出
	closesocket(sHost);    //关闭套接字
	WSACleanup();        //释放套接字资源
	return 0;
}
