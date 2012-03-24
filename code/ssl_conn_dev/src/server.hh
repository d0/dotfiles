/*
 * server.hh
 *
 *  Created on: 14.03.2012
 *      Author: aureliano
 */

#ifndef SERVER_HH_
#define SERVER_HH_

#include <openssl/ssl.h>
#include <boost/asio.hpp>
using boost::asio::ip::tcp;

class Server {
public:
	Server();
	~Server();

	void operator()();
	void listen();

private:
	void SendPendingHandshakeData(tcp::socket *socket, BIO *bioOut);
	void ReceiveHandshakeData(tcp::socket *socket, BIO *bioIn);

};

#endif /* SERVER_HH_ */
