#include "dumpThread.hpp"

DumpThread::DumpThread(QObject* parent) : QThread(parent)
{
}

void DumpThread::run()
{
	Dump* dump = new Dump(url, "X:/cpp-proxy/Dump");

	try {
		dump->dump_tree("/", 1);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}