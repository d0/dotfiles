/*
 * client.cc
 *
 *  Created on: 14.03.2012
 *      Author: aureliano
 */

#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <string>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include "client.hh"
#include "ssl_conn.hh"


Client::Client() {
	cout << "Client: Starting client" << endl;

}

Client::~Client() {
	// destructor
}

void Client::operator()() {


	try {
		boost::asio::io_service io_service;
		tcp::socket socket(io_service);
		tcp::endpoint _server(boost::asio::ip::address_v4::from_string("127.0.0.1"),50012);

		// Try to connect until server is up and ready to serve
		for(;;) {
			boost::system::error_code ec;
			socket.connect(_server,ec);
			if (!ec) {
				cout << "Client: connected" << endl;
				break;
			}
		}

		/*
		// 1. send the length of the data
		int length_field = 16;
		socket.send(boost::asio::buffer(&length_field, sizeof(int)));

		// 2. send data with length n
		char data[length_field];
		strcpy(data, "Yey, got ya!");
		socket.send(boost::asio::buffer(&data, length_field));
		 */

		SSL_CONN s(&socket, "CLIENT");
		s.start();


		cout << "Client: Closing" << endl;

		socket.close();


	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

}



