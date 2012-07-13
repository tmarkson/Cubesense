#include "stdafx.h"
#include "includeall.h"
#include "windows.h"
 
HANDLE threadOpengEvent;										//used to signal opengl thread that new frame is ready

void threadOpenglMain(void*)
{

	DWORD64 tcf;
	DWORD64 tccomp;
	DWORD64 tc1;
	DWORD64 tc2;
	DWORD64 tcaverage;
	DWORD64	tccounter;

	logEvent(LOG_THREAD_OPENGL, "Opengl thread launched");

	openglInit();
	//directxInit();
	logEvent(LOG_THREAD_OPENGL, "Opengl initialized");



	QueryPerformanceFrequency((LARGE_INTEGER*)&tcf);
	tccounter=0;
	tcaverage=0;
	
	while(1==1)
	{
		WaitForSingleObject(threadOpengEvent,INFINITE);
		ResetEvent(threadOpengEvent);
	
		threadCopyContentDefaultOpenglOut();
		threadCopyContentCoreOpenglOut();
		
		openglHandler();
		//directxHandle();


		tc1=tc2;
		QueryPerformanceCounter((LARGE_INTEGER*)&tc2);
		tcaverage+=tcf/(tc2-tc1);
		tccounter++;
		if (tccounter==30)
		{
			SendMessageW((HWND)wndprocFrmMainHandle,wndprocMessages[0],WNDPROC_MESSAGE0_SHOW_OPENGL_FPS,tcaverage/tccounter);
			tccounter=0;
			tcaverage=0;
		}
		//thread: resource sharing issue may occur

	}


}