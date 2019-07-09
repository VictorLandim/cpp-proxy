#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_proxyAppWindow.h"
#include "serverThread.hpp"
#include "spiderThread.hpp"
#include "dumpThread.hpp"

class ProxyAppWindow : public QMainWindow
{
	Q_OBJECT

public:
	ProxyAppWindow(QWidget *parent = Q_NULLPTR);
	ServerThread* serverThread;
	SpiderThread* spiderThread;
	DumpThread* dumpThread;

private:
	Ui::ProxyAppWindowClass ui;

private slots:
	void exit();
	void setAlert(QString);
	void setStatus(QString);
	void setRequest(QString);
	void setResponse(QString);
	void configureListeningPort();

	void parseRequest();
	void parseResponse();

	void onSpiderClick();
	void onDumpClick();
		
signals:
	void sendRequest(QString);
	void sendResponse(QString);

	void onSpiderButtonClick();
	void onDumpButtonClick();

	void onPortSet(int port);
};
