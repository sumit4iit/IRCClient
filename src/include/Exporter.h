#ifndef __EXPORTER_H__
#define __EXPORTER_H__

#include<sys/socket.h>
#include<netdb.h>
#include "localTypes.h"

#define URL_LENGTH 1024

class Exporter {
private:
	char hostname[URL_LENGTH];
	uint16_t port;
	addrinfo address;
public:
	Exporter();
	virtual size_t send(tchar* buff, size_t size);
	virtual ~Exporter();
};

#endif //__EXPORTER_H__
