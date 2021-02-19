#include<iostream>
#include<cstdio>
#include<cstring>

#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
int main(int argc, char **argv)
{
	std::cout << "Server Start" << std::endl;
	// socket
	int listendfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listendfd == -1)
	{
		std::cout << "Creat Skcket false" << std::endl;
		return 0;
	}
	// bind
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8000);
	addr.sin_addr.s_addr = INADDR_ANY;
	if(bind(listendfd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
	{
		std::cout << "Bind false" << std::endl;
		return 0;
	}
	// listeb
	if(listen(listendfd, 5) == -1)
	{
		std::cout << "Listen false" << std::endl;
		return 0;
	}
	// accept
	int conn;
	char clientIP[INET_ADDRSTRLEN] = "";
	struct sockaddr_in clientAddr;
	socklen_t clientAddrLen = sizeof(clientAddr);
	while(true)
	{
		std::cout << "Listening ..." << std::endl;
		conn = accept(listendfd, (struct sockaddr*)&clientAddr, &clientAddrLen);
		if(conn < 0)
		{
			std::cout << "Accrpt false, conn < 0" << std::endl;
			continue;
		}
		inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN);
		std::cout << "connect" << clientIP << ":" << ntohs(clientAddr.sin_port) << std::endl;

		char buf[1024];
		while(true)
		{
			memset(buf, 0, sizeof(buf));
			int len = recv(conn, buf, sizeof(buf), 0);
			buf[len] = '\0';
			if(strcmp(buf, "exit") == 0)
			{
				std::cout << "End Connect" << clientIP << std::endl;
				break;
			}
			std::cout << buf << std::endl;
			send(conn, buf, len, 0);
		}
		close(conn);
	}
	close(listendfd);
	return 0;
}
