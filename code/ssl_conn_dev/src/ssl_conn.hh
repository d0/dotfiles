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





class SSL_CONN{
public:
	SSL_CONN(tcp::socket *socket, string _role);
	~SSL_CONN();

	void start();
private:
	string role;

	SSL_CTX *ctx;
	SSL* conn;
	BIO* bioIn;
	BIO* bioOut;
	BIO* bio_err;

	tcp::socket *socket;

	void snd_data();
	void rcv_data();
};



#endif /* SSL_CONN_HH_ */
