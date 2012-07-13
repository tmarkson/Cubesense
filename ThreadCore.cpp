#include "stdafx.h"
#include "includeall.h"

int threadCoreFrmFramesHandler;
int threadCoreShutDownCoreThread;



void threadCoreMainStatusUpdate()
{

	if (playbackPlaying==1)
	{
		SendMessageW((HWND)wndprocFrmMainHandle,wndprocMessages[0],WNDPROC_MESSAGE0_SHOW_MAIN_STATUS,1);
	}
	else
	{
		SendMessageW((HWND)wndprocFrmMainHandle,wndprocMessages[0],WNDPROC_MESSAGE0_SHOW_MAIN_STATUS,0);
	}

}
extern HANDLE threadMutexCopyContentDefaultCore;
void threadCoreMain(void*)
{
	DWORD64 tcf;
	DWORD64 tccomp;
	DWORD64 tc1;
	DWORD64 tc2;
	DWORD64 tct1;
	DWORD64 tct2;
	DWORD64 tcaverage;
	DWORD64	tccounter;

	logEvent(LOG_THREAD_CORE, "Core thread launched");

	QueryPerformanceFrequency((LARGE_INTEGER*)&tcf);
	tccomp=(1*1666*tcf/100000);
	tc1=0;
	tccounter=0;
	tcaverage=0;

	while (1==1)
	{
		threadCopyContentDefaultCoreOut();
		if (threadCoreShutDownCoreThread)
			return;

		scriptHandler();

		if (scriptRunning==0)
		{
			uiHandler();
			playbackHandler();
			latticeHandler();

			
 			threadCoreMainStatusUpdate();

			threadCopyContentCoreOpenglIn();
			threadCopyContentCoreUsbIn();
			SetEvent(threadOpengEvent);

			scriptRealTimeHandler();
		
			WaitForSingleObject(threadMutexCopyContentCoreOpengl, INFINITE);
			lattice->copyFrame(latticeActiveFrame,&threadVideoBuffer[0]);
			if (scriptGlBuffer!=0)
			{
	
				/*
				memcpy(&threadVideoBuffer[0],&scriptGlBuffer[0],512);
				memcpy(&threadVideoBuffer[0+LATTICE_MAX_SIZE],&scriptGlBuffer[512],512);
				memcpy(&threadVideoBuffer[0+LATTICE_MAX_SIZE*2],&scriptGlBuffer[1024],512);
				*/
			//	memcpy(&threadVideoBuffer[0],&scriptGlBuffer[0],3*LATTICE_MAX_SIZE);
				
			}
			ReleaseMutex(threadMutexCopyContentCoreOpengl);
			WaitForSingleObject(threadMutexCopyContentDefaultCore, INFINITE);
	//			memcpy(&threadUsbVideoBuffer[0],&scriptGlBuffer[0],512);
	//			memcpy(&threadUsbVideoBuffer[0+512],&scriptGlBuffer[512],512);
	//			memcpy(&threadUsbVideoBuffer[0+512*2],&scriptGlBuffer[1024],512);
			ReleaseMutex(threadMutexCopyContentDefaultCore);

		}
		else
		{
		//	openglClearCanvas();
		}
		
		QueryPerformanceCounter((LARGE_INTEGER*)&tc2);
		while (tc2<tc1)
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&tc2);
			Sleep(0);
		}
		QueryPerformanceCounter((LARGE_INTEGER*)&tc2);
		tc1=tc2+tccomp;

		tct1=tct2;
		QueryPerformanceCounter((LARGE_INTEGER*)&tct2);
		tcaverage+=tcf/(tct2-tct1);
		tccounter++;
		if (tccounter==30)
		{
			SendMessageW((HWND)wndprocFrmMainHandle,wndprocMessages[0],WNDPROC_MESSAGE0_SHOW_CORE_FPS,tcaverage/tccounter);
			tccounter=0;
			tcaverage=0;
		}
		SendMessageW((HWND)wndprocFrmMainHandle,wndprocMessages[0],WNDPROC_MESSAGE0_SHOW_ACTIVE_FRAME,latticeActiveFrame);

		
	}


}