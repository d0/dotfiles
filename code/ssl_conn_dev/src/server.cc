/*
 * server.cc
 *
 *  Created on: 14.03.2012
 *      Author: aureliano
 */
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <string>

#include "server.hh"
#include "ssl_conn.hh"


Server::Server() {
	cout << "Server: Starting server" << endl;
}

Server::~Server() {

}

void Server::operator()() {

	try {
		boost::asio::io_service io_service;
		// listen on port 50012
		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 50012));

		tcp::socket socket(io_service);
		boost::system::error_code ec;
		acceptor.accept(socket, ec);
		if(!ec)
			cout << "Server: connected" << endl;

		/*
		// 1. Längenfeld empfangen
		int length_field;
		socket.receive(boost::asio::buffer(&length_field, sizeof(int)), NULL, ec);
		cout << "Server: rcved " << length_field << endl;

		// 2. Daten empfangen
		char data[length_field];
		socket.receive(boost::asio::buffer(&data, length_field), NULL, ec);
		cout << "Server: rcved " << data << endl;
		*/
		SSL_CONN s(&socket, SERVER);
		s.start();

		cout << "Server: Closing" << endl;
		socket.close();


	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

}
