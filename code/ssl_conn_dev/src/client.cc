/*
 * client.cc
 *
 *  Created on: 14.03.2012
 *      Author: aureliano
 */
#include "client.hh"
#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <string>
#include <openssl/ssl.h>

using namespace std;
using boost::asio::ip::tcp;

Client::Client() {
	cout << "Client: Starting client" << endl;

}

Client::~Client() {
	// destructor
}

void Client::operator()() {
	// do OpenSSL foo
	SSL_library_init();
	SSL_CTX *ctx = SSL_CTX_new(TLSv1_client_method());
	SSL* conn = SSL_new(ctx);
	BIO* bioIn = BIO_new(BIO_s_mem());
	BIO* bioOut = BIO_new(BIO_s_mem());
	// connect the ssl-object to the bios
	SSL_set_bio(conn,bioIn,bioOut);


	try {
		boost::asio::io_service io_service;
		tcp::socket socket(io_service);
		tcp::endpoint _server(boost::asio::ip::address_v4::from_string("127.0.0.1"),50012);

		// Try to connect until server is up and ready to serve
		for(;;) {
			boost::system::error_code ec;
			socket.connect(_server,ec);
			if (ec)
				break;
		}

		boost::system::error_code ec;

		/*
		// 1. send the length of the data
		int length_field = 16;
		socket.send(boost::asio::buffer(&length_field, sizeof(int)));

		// 2. send data with length n
		char data[length_field];
		strcpy(data, "Yey, got ya!");
		socket.send(boost::asio::buffer(&data, length_field));
		 */

		// do your client-job
		SSL_set_connect_state(conn);

		Client::SendPendingHandshakeData(&socket,bioOut);

		Client::ReceiveHandshakeData(&socket,bioOut);

		cout << "Client: Closing" << endl;

		socket.close();
		/*
		int len = 256;
		unsigned char buf[len];


		cout << "Client: Establishing connection..." << endl;

		Client::SendPendingHandshakeData(&socket,bioOut);

		cout << "Client: Lets start crypting..." << endl;

		string hello = "[crypted]";
		memcpy(buf, hello.data(), hello.size());

		int wres = 0;
		while (!wres)
			wres = SSL_write(conn, buf, len);

		cout << "Client: msg sent" << endl;

		if(!SSL_shutdown(conn)) {
			cout << "Client: bye failed." << endl;
		} else {
			cout << "Client: bye bye. " << endl;
		}
		*/

	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

}

void Client::ReceiveHandshakeData(tcp::socket *socket, BIO *bioIn) {
	unsigned char buf[256];

	cout << "Client: Looking for Handshake data " << endl;

	int len;
	if(socket->available()>0) {
		// blocking socket
		len = socket->receive(boost::asio::buffer(&buf, sizeof(buf)), NULL);
		BIO_write(bioIn,buf,len);

		cout << "Client: rcv " << len << " bytes" << endl;
	} else {
		cout << "Client: got nothing" << endl;
	}
}


void Client::SendPendingHandshakeData(tcp::socket *socket, BIO *bioOut) {

	cout << "Client: send handshake data ... " << endl;

	unsigned char buf[256];
	int cbPending;
	while(BIO_ctrl_pending(bioOut) > 0) {

		int len = BIO_read(bioOut,buf,sizeof(buf));
		socket->send(boost::asio::buffer(buf, len));

		cout << "Client: send " << len << endl;
	}

}

void Client::StoreDataForSendingLater(unsigned char *buf, int len) {
	// todo
}



