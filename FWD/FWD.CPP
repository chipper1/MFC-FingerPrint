#include<fstream>
#include<iostream>
#include<stdio.h>
#include<WinSock2.h>
#include<stdlib.h>
#include <time.h> 

using namespace std ;

#pragma comment (lib,"Ws2_32.lib")
 
int main()
{ 
	while (1)
	{
		WSADATA wsadata ;
		SOCKET  listening ;
		SOCKET  NEW ;
		SOCKADDR_IN  ServerAddr ;
		SOCKADDR_IN  KHD ;
		int KHD_len ;
		int port = 5150 ;
		int ret   ;
		//  ��ʼ���׽���
		WSAStartup(MAKEWORD(2,2),&wsadata) ;
		//  �����׽���
		listening  = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
		
		ServerAddr.sin_family = AF_INET ;
		ServerAddr.sin_port = htons(port);
		ServerAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
		//	���׽���
		bind(listening,(SOCKADDR*)&ServerAddr,sizeof(ServerAddr));
		//	�����׽���
		listen(listening,50);
		//  ����
		KHD_len  = sizeof(SOCKADDR);
		NEW  = accept(listening,(SOCKADDR*)&KHD,&KHD_len);
		//  ���ݽ���
		char ip[256] ;
		recv(NEW,ip,256,0); 
		cout << ip<< ": ���ӳɹ�..." << endl;
		char questionId[256] ;
		ret = recv(NEW,questionId,256,0);
		cout << questionId <<endl ;
		
		// ʱ��
		time_t rawtime; 
		struct tm * timeinfo; 
		time ( &rawtime ); 
		timeinfo = localtime ( &rawtime ); 
		printf ("�ύʱ��: %s", asctime(timeinfo) ); 

		//  �������� 
		closesocket(listening);
		closesocket(NEW);
		WSACleanup();
	}

	return 0 ;
}