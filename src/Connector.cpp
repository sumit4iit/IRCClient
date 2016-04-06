/*
 * Connector.cpp
 *
 *  Created on: 03-Apr-2016
 *      Author: sumit
 */

#include "Connector.h"

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <errno.h>

using namespace std;
Connector::Connector(const tstring& tstrHost, const uint16_t uiPort)
{
	this->m_tstrHost = tstrHost;
	this->m_uiPort = uiPort;
	this->sfd = -1;
}

Connector::~Connector()
{
	// Close this connection
	close(this->sfd);
}

int Connector::connect()
{
	struct addrinfo hints =
	{ 0 }, *res;
	int status = 0;
	int sfd = -1;

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_NUMERICSERV;
	hints.ai_protocol = 0;
	std::stringstream ssPort;
	ssPort << this->m_uiPort;
	status = getaddrinfo(this->m_tstrHost.c_str(), ssPort.str().c_str(), &hints,
			&res);

	addrinfo *iter;
	for (iter = res; iter != NULL; iter = iter->ai_next)
	{
		sfd = socket(iter->ai_family, iter->ai_socktype, iter->ai_protocol);

		if (sfd == -1)
		{
			continue;
		}

		if (::connect(sfd, iter->ai_addr, iter->ai_addrlen) != -1)
		{

			// we just got a connection
			LOG(INFO)<< "Connected";

			char address[INET6_ADDRSTRLEN] =
			{	0};
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

			LOG(INFO)<< "Server: "<<address<<":"<<ntohs(sin->sin_port);
			break;
		}

		close(sfd);
	}

	if (iter == NULL)
	{
		cout << "Could not connect: " << errno << endl;
	}

	freeaddrinfo(res);
	this->sfd = sfd;
	return this->sfd;
}
