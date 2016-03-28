#ifndef __EXPORTER_H__
#define __EXPORTER_H__

#include<sys/types.h>
#include<sys/socket.h>

#include "localTypes.h"

class Exporter
{
private:
	char hostname[2048];
	int16_t port;

public:
	int32_t send();
};

#endif //__EXPORTER_H__
