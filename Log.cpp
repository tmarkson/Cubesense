#include "stdafx.h"
#include "includeall.h"

#include <iostream>
#include <fstream>

using namespace System::Runtime::InteropServices; // for class Marshal


void logInit()
{

}
void logEvent(int threadId, System::String^ e)
{
	int i,j;
	System::String^ logFileName;
	System::String^ currentTime;
	System::String^ currentDate;

	System::String^ t;

	if (!LOG_TO_FILE)
		return;

	logFileName=System::Reflection::Assembly::GetEntryAssembly()->CodeBase;
	logFileName=logFileName->Substring(7,logFileName->Length-7);

	for(i=logFileName->Length-1;i>=0;i--)
	{
		t=logFileName->Substring(i,1);
		if (t=="/")
		{
			j=i;
			i=-1;
		}
	}
	logFileName=logFileName->Substring(1,j);
	if (threadId==LOG_THREAD_DEFAULT)
		logFileName=logFileName+"threadDefault.log";
	if (threadId==LOG_THREAD_CORE)
		logFileName=logFileName+"threadCore.log";
	if (threadId==LOG_THREAD_OPENGL)
		logFileName=logFileName+"threadOpengl.log";
	if (threadId==LOG_THREAD_USB)
		logFileName=logFileName+"threadUsb.log";
/*	
	logFileNameC = (char*)(void*)Marshal::StringToHGlobalAnsi(logFileName);
	std::ofstream myfile;
	myfile.open(logFileNameC);
	myfile << "e";
	myfile.close();
	Marshal::FreeHGlobal((System::IntPtr)(void*)logFileNameC);
*/

	System::DateTime^ now = System::DateTime::Now;
	
	currentTime=now->Hour.ToString()+":"+now->Minute.ToString()+":"+now->Second.ToString()+"."+now->Millisecond.ToString();
	currentDate=now->Year.ToString()+"/"+now->Month.ToString()+"/"+now->Day.ToString();

	System::IO::StreamWriter^ outfile = gcnew System::IO::StreamWriter(logFileName, true);
	outfile->Write(System::Environment::NewLine);
	outfile->Write(currentDate+" "+currentTime+" - "+e);
	outfile->Close();


/*(System::DateTime::Now.ToString("T"));*/

/*
 ofstream myfile;
  myfile.open ("example.txt");
  myfile << "Writing this to a file.\n";
  myfile.close();
  return 0;*/

}
