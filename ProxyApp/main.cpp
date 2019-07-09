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
}
