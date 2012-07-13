// CubeSense.cpp : main project file.

#include "stdafx.h"
#include "FrmMain.h"
#include "Log.h"
/*

#include <direct.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
*/

#include "DelconUsb\DelconUsb.h"

using namespace CubeSense;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	logEvent(LOG_THREAD_DEFAULT, "Main application function entered");

	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	logEvent(LOG_THREAD_DEFAULT, "Visual styles set");


//	DelconUsb* testas1=new DelconUsb();




/*
	system("dir>r.txt");


    _chdir("simulations\\");



	WinExec("C:\\MinGW\\bin\\g++ -c -DBUILDING_EXAMPLE_DLL dll_test1.cpp >>_compile.txt 2>>&1",0);
	
	WinExec("C:\\MinGW\\bin\\g++ -shared -o dll_test1.dll dll_test1.o -Wl,--out-implib,dll_test1.a >>_link.txt 2>>&1",0);

*/






	// Create the main window and run it
	Application::Run(gcnew FrmMain());
	return 0;
}
