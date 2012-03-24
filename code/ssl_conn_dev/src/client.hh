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

	void operator()();
	void connect();

private:
	void SendPendingHandshakeData(tcp::socket *socket, BIO *bioOut);
	void StoreDataForSendingLater(unsigned char *buf, int len);
	void ReceiveHandshakeData(tcp::socket *socket, BIO *bioIn);


};

#endif /* CLIENT_HH_ */
