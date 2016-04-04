#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <string>

#include "Connector.h"
#include "third_party/logging/easylogging++.h"

INITIALIZE_EASYLOGGINGPP

using namespace std;

#define SERVER_URL "chat.freenode.net"
#define PORT 6667
#define BUFFSIZE 1024

int send_message(const string& message, int sfd)
{
	cout<<"Sending : " << message << endl;
	if (write(sfd, message.c_str(), message.length()) != message.length())
	{
		return -1;
	}
	else
	{
		return message.length();
	}
}
int main()
{
	int sfd;
	Connector *conn = new Connector(SERVER_URL, PORT);
	sfd = conn->connect();
	if (sfd < 0)
	{
		LOG(ERROR) << "Failed to connect :" << sfd;
	}
	string nick = "NICK sumit4iit1\r\n";
	string user = "USER sumit4iit1 0 * :teardrop\r\n";
//	string join = "JOIN #linux \r\n";
	send_message(nick, sfd);
	send_message(user, sfd);
//	send_message(join, sfd);
	char buff[BUFFSIZE] =
	{ 0 };
	while ((read(sfd, buff, BUFFSIZE)) > 0)
		puts(buff);
}

