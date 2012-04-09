/*
 * ssl_conn.hh
 *
 *  Created on: 25.03.2012
 *      Author: aureliano
 */

#ifndef SSL_CONN_HH_
#define SSL_CONN_HH_


using namespace std;
using boost::asio::ip::tcp;

const bool SSL_DEBUG = true;

enum role {SERVER, CLIENT};
const size_t BUFSIZE = 256;


class SSL_CONN{
public:
	SSL_CONN(tcp::socket *socket, enum role _role);
	~SSL_CONN();

	void start();
private:
	enum role role;
	string str_role;

	SSL_CTX *ctx;
	SSL* conn;
	BIO* bioIn;
	BIO* bioOut;
	BIO* bio_err;

	tcp::socket *socket;

	void snd_data();
	void rcv_data();
	void print_err();

};

int pem_passwd_cb(char *buf, int size, int rwflag, void *userdata);

#endif /* SSL_CONN_HH_ */
