#include "stdafx.h"
#include "includeall.h"




void threadUsbMain(void*)
{
	int t;

	logEvent(LOG_THREAD_USB, "USB thread launched");

	usbInit();
	
	logEvent(LOG_THREAD_USB, "USB module initialized");

	while(1==1)
	{
		threadCopyContentDefaultUsbOut();
		threadCopyContentCoreUsbOut();
		usbHandler();
		usbService();

		if ((usbStreamVideo)&(usbConnected))
		{
			Sleep(0);
			SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
		}
		else
		{
			Sleep(100);
			SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_NORMAL);
		}

	}

/*
	int a;
	unsigned char buf2[64];
	int lastPreviewUsbStreamVideo;
	lastPreviewUsbStreamVideo=2;
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
	int i;
	for(i=0;i<64;i++)
		buf2[i]=0;
	while (1==1)
	{

		threadCopyContentPreviewSetupOut2();

		if (previewUsbConnect)
		{
			usbConnect();
			previewUsbConnect=0;
			usbStatusService();
		}
		if (previewUsbDisconnect)
		{
			usbDisconnect();
			previewUsbDisconnect=0;
		}
		if (lastPreviewUsbStreamVideo!=previewUsbStreamVideo)
		{
			lastPreviewUsbStreamVideo=previewUsbStreamVideo;
			usbStatusService();
		}

		if (usbPipeStrmIn!=INVALID_HANDLE_VALUE)
			Sleep(0);
		else
			Sleep(500);

		WaitForSingleObject(threadMutexUsbBufferAccess, INFINITE);
		usbCopyToUsbBuffer();
	//	j=threadOpenglFrameRate;
		ReleaseMutex(threadMutexUsbBufferAccess);
		usbService(&usbUsbBuffer[0], &buf2[0]);
	}	*/


}