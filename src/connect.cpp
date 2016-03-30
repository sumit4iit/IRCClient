#include<iostream>
#include<netinet/ip.h>
#include<unistd.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<cstdio>
#include<cstdlib>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
using namespace std;

#define SERVER_URL "chat.freenode.net"
#define PORT "6667"

int main()
{
	string s = SERVER_URL;
	struct addrinfo hints={0}, *res;
	int errorCode, status, sfd;

	string url = SERVER_URL;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_NUMERICSERV;
	hints.ai_protocol = 0;
	string port = PORT;
	status = getaddrinfo(url.c_str(), port.c_str(), &hints, &res);

	addrinfo *iter;
	for (iter = res; iter!= NULL; iter = iter->ai_next)
	{
		sfd = socket(iter->ai_family, iter->ai_socktype, iter->ai_protocol);
		if (sfd == -1)
		{
			continue;
		}

		if (connect(sfd, iter->ai_addr, iter->ai_addrlen) != -1)
		{
			// we just got a connection
			cout<<"connected\n"<<"";
			char address[INET6_ADDRSTRLEN] = {0};
			sockaddr_in *sin = reinterpret_cast<sockaddr_in*>(iter->ai_addr);
			switch (iter->ai_addr->sa_family)
			{
			case AF_INET:
				inet_ntop(AF_INET, &sin->sin_addr, address, INET6_ADDRSTRLEN);
				break;
			case AF_INET6:
				inet_ntop(AF_INET6, &sin->sin_addr, address, INET6_ADDRSTRLEN);
				break;
			}
			cout<<address<<endl;
			cout<<ntohs(sin->sin_port)<<endl;
			break;
		}
		close(sfd);
	}

	if (iter == NULL)
	{
		cout<<"Could not connect: "<<errno<<endl;
	}

	freeaddrinfo(res);
}



