#ifndef __WQ_SOCKET_HPP__
#define __WQ_SOCKET_HPP__

#include "Noncopyable.hpp"

namespace wq
{

class Socket : Noncopyable
{
public:
	Socket();
	explicit Socket(int fd);
	~Socket();

	int fd() const {	return _fd;	}
	void shutdownWrite();
	void setNonblock();

private:
	int _fd;
};

}//end of namespace wq
 
#endif
