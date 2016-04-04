/*
 * Connector.h
 *
 *  Created on: 03-Apr-2016
 *      Author: sumit
 */

#ifndef _CONNECTOR_H_
#define _CONNECTOR_H_
#include "include/localTypes.h"
#include "third_party/logging/easylogging++.h"

class Connector
{
private:
	tstring m_tstrHost;
	uint16_t m_uiPort;
public:
	Connector(const tstring& host, const uint16_t port);

	// Returns file descriptor after making connection.
	virtual int connect();
	virtual ~Connector();
};

#endif /* SRC_CONNECTOR_H_ */
