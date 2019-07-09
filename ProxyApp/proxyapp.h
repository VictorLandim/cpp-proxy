#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_proxyapp.h"
#include "serverThread.hpp"

class ProxyApp : public QMainWindow
{
	Q_OBJECT

public:
	ProxyApp(QWidget *parent = Q_NULLPTR);
	ServerThread* serverThread;
	void setPort(int);
	int port = 8228;

private:
	Ui::ProxyAppClass ui;

private slots:
	void exit();
	void setAlert(QString);
	void setStatus(QString);
	void setRequest(QString);
	void setResponse(QString);

signals:
	void onRequestButtonClick();
	void onResponseButtonClick();

	void onSpiderButtonClick();
	void onDumpButtonClick();
};
