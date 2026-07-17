#include <Windows.h>
#include "Match3App.hpp"

using namespace PopLib;
#ifdef _WIN32

int main(int argc, char* argv[])


{
#ifndef POP_CONSOLE_ON
#ifdef _WIN32
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif
#endif

	Match3App* ThisApp = new Match3App;
	ThisApp->Init();
	ThisApp->Start();
	ThisApp->Shutdown();


	return 0;
}
#endif

