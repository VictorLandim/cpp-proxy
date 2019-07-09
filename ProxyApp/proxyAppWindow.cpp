#include "proxyAppWindow.h"
#include <iostream>
#include <QMessageBox>

ProxyAppWindow::ProxyAppWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	// disable both text inputs and buttons
	ui.clientRequestText->setDisabled(true);
	ui.hostResponseText->setDisabled(true);
	ui.requestButton->setDisabled(true);
	ui.responseButton->setDisabled(true);

	serverThread = new ServerThread(this);
	spiderThread = new SpiderThread(this);
	dumpThread = new DumpThread(this);

	connect(ui.spiderButton, SIGNAL(clicked()), this, SLOT(onSpiderClick()));
	connect(ui.dumpButton, SIGNAL(clicked()), this, SLOT(onDumpClick()));


	// old way of connecting
	//connect(serverThread, SIGNAL(statusChanged(QString)), this, SLOT(setStatusText(QString)));

	// status / alert
	connect(serverThread, &ServerThread::statusChanged, this, &ProxyAppWindow::setStatus);
	connect(serverThread, &ServerThread::alert, this, &ProxyAppWindow::setAlert);

	// request/response set text area contents
	connect(serverThread, &ServerThread::requestReceived, this, &ProxyAppWindow::setRequest);
	connect(serverThread, &ServerThread::responseReceived, this, &ProxyAppWindow::setResponse);

	// request/response buttons
	connect(ui.requestButton, SIGNAL(clicked()), this, SLOT(parseRequest()));
	connect(ui.responseButton, SIGNAL(clicked()), this, SLOT(parseResponse()));

	connect(this, SIGNAL(sendRequest(QString)), serverThread, SLOT(setRequest(QString)));
	connect(this, SIGNAL(sendResponse(QString)), serverThread, SLOT(setResponse(QString)));
;
	//connect(ui.requestButton, SIGNAL(clicked()), serverThread, SLOT(setShouldRequestToServer()));
	//connect(ui.responseButton, SIGNAL(clicked()), serverThread, SLOT(setShouldRespondToClient()));
	
	// port button
	connect(ui.portButton, SIGNAL(clicked()), this, SLOT(configureListeningPort()));
	connect(this, SIGNAL(onPortSet(int)), serverThread, SLOT(setListeningPort(int)));

	serverThread->start();
		
	emit onPortSet(8228);
}

// slots
void ProxyAppWindow::exit()
{
	serverThread->quit();
	serverThread->wait();
	//QApplication::exit();
}

void ProxyAppWindow::setStatus(QString status)
{
	ui.statusLabel->clear();
	ui.statusLabel->setText(status);
}

void ProxyAppWindow::setAlert(QString message)
{
	QMessageBox::information(this, tr("Error"), tr(message.toStdString().c_str()));
}

void ProxyAppWindow::configureListeningPort()
{

	ui.hostResponseText->setDisabled(true);
	ui.responseButton->setDisabled(true);
	ui.hostResponseText->setPlainText("");

	ui.clientRequestText->setDisabled(true);
	ui.requestButton->setDisabled(true);
	ui.clientRequestText->setPlainText("");

	QString portText = ui.portText->text();
	int port = portText.toInt();
	emit onPortSet(port);
}

void ProxyAppWindow::setRequest(QString request)
{
	ui.hostResponseText->setDisabled(true);
	ui.responseButton->setDisabled(true);
	ui.hostResponseText->setPlainText("");

	ui.clientRequestText->setDisabled(false);
	ui.requestButton->setDisabled(false);
	ui.clientRequestText->setPlainText(request);

	ui.statusLabel->setText("Browser request received.");
}

void ProxyAppWindow::setResponse(QString response)
{
	ui.clientRequestText->setDisabled(true);
	ui.requestButton->setDisabled(true);
	ui.clientRequestText->setPlainText("");

	ui.hostResponseText->setDisabled(false);
	ui.responseButton->setDisabled(false);
	ui.hostResponseText->setPlainText(response);

	ui.statusLabel->setText("Host response received.");
}

void ProxyAppWindow::parseRequest()
{
	QString request = ui.clientRequestText->toPlainText();
	request.replace("\n", "\r\n");

	//ui.clientRequestText->setPlainText("");
	ui.clientRequestText->setDisabled(true);
	ui.requestButton->setDisabled(true);

	emit sendRequest(request);
}

void ProxyAppWindow::parseResponse()
{
	QString response = ui.hostResponseText->toPlainText();
	response.replace("\n", "\r\n");

	ui.hostResponseText->setPlainText("");
	ui.hostResponseText->setDisabled(true);
	ui.responseButton->setDisabled(true);

	emit sendResponse(response);
}

void ProxyAppWindow::onSpiderClick() 
{
	std::string url = ui.spiderUrlText->text().toStdString();
	spiderThread->url = url;

	spiderThread->start();
}

void ProxyAppWindow::onDumpClick()
{
	std::string url = ui.spiderUrlText->text().toStdString();
	dumpThread->url = url;

	dumpThread->start();
}