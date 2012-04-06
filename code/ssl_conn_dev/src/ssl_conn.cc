/*
 * ssl_conn.cc
 *
 *  Created on: 25.03.2012
 *      Author: aureliano
 */

#include <iostream>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <string>

#include "ssl_conn.hh"


SSL_CONN::SSL_CONN(tcp::socket *_socket, enum role _role) {
	if (_role != SERVER && _role != CLIENT)
		exit(1);

	socket 				= _socket;
	role 				= _role;
	str_role 			= (role==CLIENT) ? "CLIENT":"SERVER";

	SSL_library_init();
	SSL_load_error_strings();

	SSL_METHOD *meth 	= (role==CLIENT)? TLSv1_client_method() : TLSv1_server_method();
	ctx 				= SSL_CTX_new(meth);
	conn 				= SSL_new(ctx);
	bioIn 				= BIO_new(BIO_s_mem());
	bioOut 				= BIO_new(BIO_s_mem());
	bio_err 			= BIO_new_fp(stderr, BIO_NOCLOSE);
	SSL_set_bio(conn,bioIn,bioOut); // connect the ssl-object to the bios

	char password[] = "test";
	SSL_CTX_set_default_passwd_cb(ctx, &pem_passwd_cb); //passphrase for both the same
	SSL_CTX_set_default_passwd_cb_userdata(ctx, password);

	// used following cmd to get list of correct cipher lists
	// $ openssl ciphers -tls1 "aRSA:AES:-kEDH:-ECDH:-SRP:-PSK:-NULL:-EXP:-MD5:-DES"
	if(!SSL_CTX_set_cipher_list(ctx, "RC4-SHA")){
		print_err();
	}

	if(role==CLIENT) {
		SSL_CTX_use_certificate_file(ctx, "certs/client.pem", SSL_FILETYPE_PEM);
		SSL_CTX_use_RSAPrivateKey_file(ctx, "certs/key.pem", SSL_FILETYPE_PEM);

	} else if(role==SERVER) {
		SSL_CTX_use_certificate_file(ctx, "certs/demoCA/cacert.pem", SSL_FILETYPE_PEM);
		SSL_CTX_use_RSAPrivateKey_file(ctx, "certs/demoCA/private/cakey.pem", SSL_FILETYPE_PEM);
	}

	if(!SSL_CTX_check_private_key(ctx)) {
		if (SSL_DEBUG) cout << str_role << ": dooong. wow" << endl;
		print_err();
	}
}

SSL_CONN::~SSL_CONN() {
	ERR_free_strings();
	cout << "deconstructor end" << endl;
}





void SSL_CONN::start() {
	// Start SSL-connection as client
	(role==CLIENT)? SSL_set_connect_state(conn) : SSL_set_accept_state(conn);

	if (SSL_DEBUG) cout << str_role << ": " << SSL_get_cipher_list(conn, 0) << endl;

	int done = 0;
	while (!done) {

		/* Perform the handshake. This in turn will activate the
		 * underlying connect BIO and a socket connection will be made
		 */
		int temp = SSL_do_handshake(conn);

		/* Because memmory BIOs can grow indefenitly, we will never
		 * get the error SSL_ERROR_WANT_WRITE. It's up to us to send
		 * the data every now and then. So I am doing it here.
		 */
		if(role==CLIENT) snd_data();

		/* The SSL_get_error() call categorizes errors into groups */
		switch (SSL_get_error(conn, temp)) {
		case SSL_ERROR_NONE:
			/* Handshake has finished successfully. */
			done = 1;
			break;
		case SSL_ERROR_SSL:
			/* Handshake error - report and exit. */
			if (SSL_DEBUG) cout << str_role <<  " ERROR: Handshake failure\n" << endl;
			print_err();
			break;
		case SSL_ERROR_SYSCALL:
			/* System call error. This error is different from
			 * the SSL_ERROR_SSL in that errno (under unix)
			 * has the numeric error value, and it is not
			 * converted into text. If doing an SSL_read() or
			 * SSL_write() there is no recorded error in the error
			 * logging. This is because the error could be a
			 * 'retry' error of which the library is unaware.
			 */
			if (SSL_DEBUG) cout << str_role << " ERROR: System call error = ...\n" << endl;
			print_err();
			break;
		case SSL_ERROR_WANT_READ:
			rcv_data();
			break;
		case SSL_ERROR_WANT_WRITE:
			// we get this message, if e.g. the send-buf is full
			snd_data();
			break;
		case SSL_ERROR_WANT_CONNECT:
			/* Perform the handshake again. These errors are normally
			 * only reported when doing non-blocking I/O.
			 */
			break;
		case SSL_ERROR_ZERO_RETURN:
			/* A read(2)/write(2) system call returned 0 (usually
			 * because the socket was closed). If the socket is
			 * closed, the protocol has failed.
			 */
			if (SSL_DEBUG) cout << str_role << ": socket closed\n" << endl;
			break;
		}

		boost::this_thread::sleep(boost::posix_time::seconds(1));
	}

}


void SSL_CONN::rcv_data() {

	if (SSL_DEBUG) cout << str_role << ": Looking for Handshake data " << endl;

	unsigned char buf[256];
	while(socket->available()>0) {

		// blocking socket
		int len = socket->receive(boost::asio::buffer(&buf, sizeof(buf)));
		BIO_write(bioIn,buf,len);


		if (SSL_DEBUG) cout << str_role << ": rcv " << len << " bytes" << endl;
	}
}

void SSL_CONN::snd_data() {
	if (SSL_DEBUG) cout << str_role << ": send handshake data ... " << endl;

	unsigned char buf[1024];
	while(BIO_ctrl_pending(bioOut) > 0) {

		int len = BIO_read(bioOut,buf,sizeof(buf));
		socket->send(boost::asio::buffer(buf, len));

		if (SSL_DEBUG) cout << str_role << ": send " << len << endl;
	}

}

int pem_passwd_cb(char *buf, int size, int rwflag, void *password) {
	strncpy(buf, (char *)(password), size);
	buf[size - 1] = '\0';
	return(strlen(buf));
}

void SSL_CONN::print_err() {
	//ERR_print_errors(bio_err);
	cerr << str_role << ": " << ERR_error_string(ERR_get_error(), NULL) << endl;
	exit(-1);
}
