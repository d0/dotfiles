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

using namespace std;
using boost::asio::ip::tcp;

class Server {
public:
	Server();
	~Server();

	void operator()();

private:


};

#endif /* SERVER_HH_ */
