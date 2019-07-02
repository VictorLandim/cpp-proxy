#include "stdafx.h"
#include <QtWidgets/QApplication>
#include "proxyapp.h"
//#include "spider.hpp"

int main(int argc, char *argv[])
{

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
	window.show();
	
	return a.exec();
	
	/*
	Spider * spider = new Spider("www.cplusplus.com");
	spider->get_tree("/", 1);
	while (TRUE);
	return 0;
	*/
}
