#pragma once
#include <qthread.h>
#include "spider.hpp"

class SpiderThread : public QThread
{
	Q_OBJECT
public:
	explicit SpiderThread(QObject* parent = 0);
	void run();
	std::string url;

private:
	
};