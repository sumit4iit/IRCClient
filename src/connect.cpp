#include<iostream>
#include<netinet/ip.h>
#include<unistd.h>
#include<netdb.h>
using namespace std;

#define SERVER_URL "chat.freenode.net"
#define PORT 6667
int main()
{
	int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in addr;
	addr.sin_addr = gethostbyname(SERVER_URL);
	addr.sin_port = PORT;
	addr.sin_family = AF_INET;
	string data = "hello world";
	const char* buff = data.c_str();
	if (write(tcp_socket, buff, 11) != -1)
	{
		cout<<"Success\n";
	}
	else
	{
		cout<<"Failed\n";
	}
}
