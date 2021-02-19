#include<iostream>
#include<cstdio>
#include<cstring>

#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
	std::cout << "client Start" << std::endl;
	int client = socket(AF_INET, SOCK_STREAM, 0);
	if(client == -1)
	{
		std::cout << "Create socket false!" << std::endl;
		return 0;
	}
	//connet
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8000);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.7");
	if(connect(client, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
	{
		std::cout << "Connet false!" << std::endl;
		return 0;
	}
	std::cout << "" << std::endl;
	char data[1024];
	char buf[1024];
	while(true)
	{
		std::cin >> data;
		send(client, data, strlen(data), 0);
		if(strcmp(data, "exit") == 0)
		{
			std::cout << "Client end !!" << std::endl;
			break;
		}
		memset(buf, 0, sizeof(buf));
		int len = recv(client, buf, sizeof(buf), 0);
		buf[len] = '\0';
		std::cout << "Send " << buf << " success!" << std::endl;
	}
	close(client);
	return 0;
}
