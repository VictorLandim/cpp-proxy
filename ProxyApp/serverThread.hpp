#pragma once
#include <qthread.h>
#include "proxyServer.hpp"

class ServerThread : public QThread
{
	Q_OBJECT
public:
	explicit ServerThread(QObject* parent = 0, int port = 8228);
	void run();

private:
	int port;
	void printClientRequest(std::string);
	void printHostResponse(std::string);

	std::string finalRequest;
	std::string finalResponse;

	bool shouldListen = true;
	bool shouldRequestToServer = false;
	bool shouldRespondToClient = false;
	bool shouldInitialize = false;

	ProxyServer* proxyServer;

signals:
	void statusChanged(QString);
	void alert(QString);
	void requestReceived(QString);
	void responseReceived(QString);

public slots:
	void setShouldListen();
	void setListeningPort(int port);

	void setRequest(QString);
	void setResponse(QString);
};