#include "stdafx.h"
#include <QtWidgets/QApplication>
#include "proxyapp.h"
//#include "spider.hpp"

int main(int argc, char *argv[])
{
	int port = 8228;
	if (argc == 3 && argv[1] == "-p")
		port = atoi(argv[2]);
	// open console window
	#ifdef _WIN32
	if (AttachConsole(ATTACH_PARENT_PROCESS) || AllocConsole()) {
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
		freopen("CONIN$", "r", stdin);
	}
	#endif
	
	QApplication a(argc, argv);
	
	ProxyApp window;
	if (port != 8228)
		window.setPort(port);
	window.show();

	
	return a.exec();
	
	/*
	Spider * spider = new Spider("www.pudim.com.br", "../Spider_output.txt");
	spider->get_tree("/", 5);
	while (TRUE);
	return 0;
	*/
}
