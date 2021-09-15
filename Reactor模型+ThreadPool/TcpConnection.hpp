#ifndef __WQ_TCPCONNECTION_HPP__
#define __WQ_TCPCONNECTION_HPP__

#include "Noncopyable.hpp"

#include "Socket.hpp"
#include "SocketIO.hpp"
#include "InetAddress.hpp"

namespace wq
{

class TcpConnection : Noncopyable
{
public:
	TcpConnection(int fd);
	~TcpConnection();

	string receive();
	void send(const string & msg);

	string toString() const;

private:
	InetAddress getLocalAddr();
	InetAddress getPeerAddr();

private:
	Socket _sock;
	SocketIO _sockIO;
	InetAddress _localAddr;
	InetAddress _peerAddr;
	bool _shutdownWrite;
};

}//end of namespace wq
  
#endif
