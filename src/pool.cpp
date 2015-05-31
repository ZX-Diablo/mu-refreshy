#include "../include/pool.h"

pool::pool (unsigned int size)
	: io()
	, work(std::make_shared<boost::asio::io_service::work>(io))
	, threads()
	, size(size)
{
	this->init_threads();
}

pool::~pool ()
{
	this->stop();
}

void pool::add_task (callback_t func)
{
	this->io.dispatch(std::move(func));
}

void pool::wait ()
{
	this->stop();
	
	this->io.reset();
	this->work = std::make_shared<boost::asio::io_service::work>(this->io);
	
	this->threads.clear();
	this->init_threads();
}

void pool::init_threads ()
{
	for (unsigned int i = 0; i < this->size; i++)
	{
		this->threads.push_back(std::thread(
			std::bind<std::size_t (boost::asio::io_service::*)()>(&boost::asio::io_service::run, &this->io)
		));
	}
}

void pool::stop ()
{
	this->work = nullptr;
	
	for (auto& it : this->threads)
	{
		it.join();
	}
}
