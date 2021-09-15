#ifndef __WQ_NONCOPYABLE_HPP__
#define __WQ_NONCOPYABLE_HPP__

namespace wq
{
class Noncopyable
{
protected:
	Noncopyable() {}
	~Noncopyable() {}

	Noncopyable(const Noncopyable&) = delete;
	Noncopyable & operator=(const Noncopyable&) = delete;

};

}//end of namespace wq
 
#endif
