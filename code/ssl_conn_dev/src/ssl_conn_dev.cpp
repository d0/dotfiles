//============================================================================
// Name        : ssl_conn_dev.cpp
// Author      : crx
// Version     :
// Copyright   :
// Description : Create developing area for openssl
//============================================================================

#include <iostream>
#include <boost/thread.hpp>
using namespace std;

#include "client.hh"
#include "server.hh"

void test();

int main() {

	cout << "Starting test." << endl;
	/*
	 * Arbeitsziele
	 * 1. Threads aufbauen. ok
	 * 2. TCP-Verbindung aufbauen. ok
	 * 3. SSL-Verbindung aufbauen. Dieser Teil soll später portiert werden.
	 */

	Client client = Client();
	Server server = Server();

	boost::thread server_t(server);
	boost::this_thread::sleep(boost::posix_time::seconds(1));
	boost::thread client_t(client);

	server_t.join();
	client_t.join();
	return 0;
}


