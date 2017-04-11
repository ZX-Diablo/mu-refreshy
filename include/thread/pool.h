#pragma once

#include <boost/asio/io_service.hpp>

#include <list>
#include <thread>
#include <memory>

class pool
{
public:
	typedef std::function<void()> callback_t;

public:
	pool (unsigned int size = 4);
	~pool ();

	void add_task (callback_t func);

	void wait ();

private:
	typedef std::shared_ptr<boost::asio::io_service::work> work_ptr_t;
	typedef std::list<std::thread> threads_list_t;

private:
	void init_threads ();
	void stop ();

private:
	boost::asio::io_service io;
	work_ptr_t work;
	threads_list_t threads;
	unsigned int size;
};
