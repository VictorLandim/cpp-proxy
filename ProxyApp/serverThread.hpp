#pragma once
#include <qthread.h>

class ServerThread : public QThread
{
	Q_OBJECT
public:
	explicit ServerThread(QObject* parent = 0);
	void run();
	bool shouldListen			= true;
	bool shouldRequestToServer	= false;
	bool shouldRespondToClient	= false;

private:
	void printClientRequest(std::string);
	void printHostResponse(std::string);

signals:
	void statusChanged(QString);
	void alert(std::string);
	void requestReceived(QString);
	void responseReceived(QString);

public slots:
	void setShouldListen();
	void setShouldRequestToServer();
	void setShouldRespondToClient();
};