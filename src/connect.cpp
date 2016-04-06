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
#define TIMEOUT_SEC 5

int send_message(const string& message, int sfd)
{
	LOG(DEBUG)<<"Sending : " << message << endl;
	if (write(sfd, message.c_str(), message.length()) != message.length())
	{
		return -1;
	}
	else
	{
		return message.length();
	}
}

void parse_message(const TCHAR* inBuff, uint32_t uiInSize, TCHAR* outBuff, uint32_t uiOutSize)
{

}

int main()
{
	int sfd;
	Connector *conn = new Connector(SERVER_URL, PORT);
	sfd = conn->connect();
	if (sfd < 0)
	{
		LOG(ERROR)<< "Failed to connect :" << sfd;
	}
	string nick = "NICK sumit4iit_bot\r\n";
	string user = "USER sumit4iit_bot 0 * :teardrop_bot\r\n";
	string join = "JOIN #linux \r\n";
	send_message(nick, sfd);
	send_message(user, sfd);
	send_message(join, sfd);

// wait for data
	fd_set set;
	char buff[BUFFSIZE] =
	{ 0 };
	int count = 0;
	while (true)
	{
		// `select` updates timeout to represent the time that was
		// left before timeout would kick in.
		// This eventually resets value of timeout to zero and causes
		// select to return immediately.
		struct timeval timeout;
		timeout.tv_sec = TIMEOUT_SEC;
		timeout.tv_usec = 0;

		FD_ZERO(&set);
		FD_SET(sfd, &set);
		int retval = select(FD_SETSIZE, &set, NULL, NULL, &timeout);
		if (retval == -1)
		{
			LOG(ERROR)<< "Select call failed";
			break;
		}
		else if(retval)
		{
			LOG(DEBUG) << "Data is available after: " <<count + TIMEOUT_SEC - timeout.tv_sec << " sec";
			count = 0;
			int size = read(sfd, buff, BUFFSIZE);
			if (size>0)
			{
				LOG(DEBUG) << "Read : "<< size << " bytes";
				LOG(INFO) << buff;
			}
			else
			{
				LOG(ERROR) << "Read failed";
				break;
			}
		}
		else
		{
			LOG(WARNING) << "No data for last " << count+TIMEOUT_SEC<< " seconds";
		}
	}

	// cleanup
	delete conn;
}
