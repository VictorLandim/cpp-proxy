#include "stdafx.h"
#include "proxyapp.h"
#include <iostream>

ProxyApp::ProxyApp(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	// disable both text inputs and buttons
	ui.clientRequestText->setDisabled(true);
	ui.hostResponseText->setDisabled(true);
	ui.requestButton->setDisabled(true);
	ui.responseButton->setDisabled(true);

	serverThread = new ServerThread(this, port);

	// old way of connecting
	//connect(serverThread, SIGNAL(statusChanged(QString)), this, SLOT(setStatusText(QString)));

	connect(serverThread, &ServerThread::statusChanged, this, &ProxyApp::setStatus);
	connect(serverThread, &ServerThread::alert, this, &ProxyApp::setAlert);

	connect(serverThread, &ServerThread::requestReceived, this, &ProxyApp::setRequest);
	connect(serverThread, &ServerThread::responseReceived, this, &ProxyApp::setResponse);

	connect(ui.requestButton, SIGNAL(clicked()), serverThread, SLOT(setShouldRequestToServer()));
	connect(ui.responseButton, SIGNAL(clicked()), serverThread, SLOT(setShouldRespondToClient()));

	serverThread->start();
}

void ProxyApp::setPort(int port) {
	this->port = port;
}

// slots
void ProxyApp::exit()
{
	serverThread->quit();
	serverThread->wait();
	//QApplication::exit();
}

void ProxyApp::setStatus(QString status)
{
	ui.statusLabel->setText(status);
}

void ProxyApp::setAlert(std::string message)
{
	QMessageBox::information(this, tr(message.c_str()), tr("OK"));
}

void ProxyApp::setRequest(QString request)
{
	ui.hostResponseText->setDisabled(true);
	ui.responseButton->setDisabled(true);
	ui.hostResponseText->setPlainText("");

	ui.clientRequestText->setDisabled(false);
	ui.requestButton->setDisabled(false);
	ui.clientRequestText->setPlainText(request);
}

void ProxyApp::setResponse(QString response)
{
	ui.clientRequestText->setDisabled(true);
	ui.requestButton->setDisabled(true);
	ui.clientRequestText->setPlainText("");

	ui.hostResponseText->setDisabled(false);
	ui.responseButton->setDisabled(false);
	ui.hostResponseText->setPlainText(response);
}