/*
 * client.hh
 *
 *  Created on: 14.03.2012
 *      Author: aureliano
 */

#ifndef CLIENT_HH_
#define CLIENT_HH_

#include <boost/asio.hpp>
#include <openssl/ssl.h>

using boost::asio::ip::tcp;

class Client {

public:
	Client();
	~Client();

	void connect();

private:


};

#endif /* CLIENT_HH_ */
