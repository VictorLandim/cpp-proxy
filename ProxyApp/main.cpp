#include "proxyAppWindow.h"
#include <QtWidgets/QApplication>
#include <windows.h>

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

	ProxyAppWindow window;
	window.show();

	
	return a.exec();
	
	/*
	Spider * spider = new Spider("www.pudim.com.br", "../Spider_output.txt");
	spider->get_tree("/", 5);
	while (TRUE);
	return 0;
	
	Dump * dump = new Dump("www.cplusplus.com", "D:/TR2/cpp-proxy/Dump");
	dump->dump_tree("/", 1);
	while (TRUE);
	return 0;
	*/
}
