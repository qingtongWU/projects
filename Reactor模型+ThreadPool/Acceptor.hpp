#ifndef __WQ_ACCEPTOR_HPP__
#define __WQ_ACCEPTOR_HPP__

#include "InetAddress.hpp"
#include "Socket.hpp"

namespace wq
{

class Acceptor
{
public:
	Acceptor(unsigned short port, const string & ip = "127.0.0.1")
	: _listensock()
	, _addr(port, ip)
	{}

	void ready();
	int accept();

	int fd() const {	return _listensock.fd();	}
private:
	void setReuseAddr();
	void setReusePort();
	void bind();
	void listen();

private:
	Socket _listensock;
	InetAddress _addr;
};

}//end of namespace wq
 
#endif
