#pragma once
#include <qthread.h>
#include "dump.hpp"

class DumpThread : public QThread
{
	Q_OBJECT
public:
	explicit DumpThread(QObject* parent = 0);
	void run();
	std::string url;

private:

};