/*
 * server.cc
 *
 *  Created on: 14.03.2012
 *      Author: aureliano
 */
#include <openssl/ssl.h>
#include <boost/asio.hpp>
#include <iostream>
#include <string>
using namespace std;
using boost::asio::ip::tcp;

#include "server.hh"


Server::Server() {
	cout << "Server: Starting server" << endl;
}

Server::~Server() {

}

void Server::operator()() {
	Server::listen();
}

void Server::listen() {

	// do OpenSSL foo
	SSL_library_init();
	SSL_CTX *ctx = SSL_CTX_new(TLSv1_client_method());
	SSL* conn = SSL_new(ctx);
	BIO* bioIn = BIO_new(BIO_s_mem());
	BIO* bioOut = BIO_new(BIO_s_mem());
	SSL_set_bio(conn,bioIn,bioOut);

	try {
		boost::asio::io_service io_service;
		// listen on port 50012
		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 50012));

		//
		tcp::socket socket(io_service);
		acceptor.accept(socket);

		// todo
		// längen feld aufbauen und analysieren und buffer größe zu bestimen
		// unsigned char buffer bauen
		boost::system::error_code ec;

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

		// This tells the server to start the negotiation
		SSL_set_accept_state(conn);
		Server::SendPendingHandshakeData(&socket,bioOut);
		Server::ReceiveHandshakeData(&socket,bioIn);

		//Server::SendPendingHandshakeData(&socket,bioOut);

		// somehow i have to use SSL_get_error

		socket.close();
		/*
		 * Handshake mit socket receive und send muss noch einmal
		 * komplett überdacht werden.. siehe SSL_do_handshake
		 * Die Frage, die sich mir gestellt hat ist, wie viele Nachrichten
		 * hin und her gesendet werden, wie aus der socket ausgelesen
		 * werden muss. Reichen zwei hin oder her? oder wie?
		 */

		/*
		Server::ReceiveHandshakeData(&socket,bioIn);
		Server::SendPendingHandshakeData(&socket,bioOut);
		Server::ReceiveHandshakeData(&socket,bioIn);

		cout << "Give me your crypto stuff.. " << endl;

		unsigned char plaintext[256];
		while(SSL_read(conn,&plaintext,sizeof(plaintext)) > 0) {

			cout << "Server: rcved " << (char *)plaintext << endl;
		}

		cout << "Server: Closing" << endl;

		*/


	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

}

void Server::ReceiveHandshakeData(tcp::socket *socket, BIO *bioIn) {
	unsigned char buf[256];

	cout << "Server: Looking for Handshake data " << endl;

	int len;
	if(socket->available()>0) {
		// blocking socket
		len = socket->receive(boost::asio::buffer(&buf, sizeof(buf)), NULL);
		BIO_write(bioIn,buf,len);

		cout << "Server: rcv " << len << " bytes" << endl;
	} else {
		cout << "Server: got nothing" << endl;
	}


}


void Server::SendPendingHandshakeData(tcp::socket *socket, BIO *bioOut) {

	cout << "Server: send handshake data ... " << endl;

	unsigned char buf[256];
	int cbPending;
	while(BIO_ctrl_pending(bioOut) > 0) {

		int len = BIO_read(bioOut,buf,sizeof(buf));
		socket->send(boost::asio::buffer(buf, len));

		cout << "Server: send " << len << endl;
	}
}
