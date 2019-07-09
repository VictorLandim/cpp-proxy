#include "spiderThread.hpp"

SpiderThread::SpiderThread(QObject* parent) : QThread(parent)
{
}

void SpiderThread::run()
{
	Spider* spider = new Spider(url, "../Spider_output.txt");
	
	try {
		spider->get_tree("/", 2);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}