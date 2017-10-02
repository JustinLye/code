#ifndef __THREAD_H_INCLUDED__
#define __THREAD_H_INCLUDED__

#define BOOST_THREAD_VERSION 2

#include<boost/thread/thread.hpp>
#include<boost/core/noncopyable.hpp>
#include<boost/core/ref.hpp>

class Thread :
	private boost::noncopyable,
	private boost::thread
{
public:
	explicit Thread();
	virtual ~Thread();
	void operator()();
	virtual void launch();
	using boost::thread::get_id;
	using boost::thread::join;
	using boost::thread::joinable;
	inline boost::thread::id Get_id() const
	{
		return mThread_id;
	}
protected:
	boost::thread::id mThread_id;
	
	virtual void entry_point() = 0;
};

#endif
