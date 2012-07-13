#include "stdafx.h"
#include "includeall.h"
#include "windows.h"
#include "stdio.h"
#include "process.h"
#include "FrmScriptSource.h"
#include "FrmNew.h"
#include "FrmFrames.h"

HANDLE threadMutexCopyContentDefaultOpengl;
HANDLE threadMutexCopyContentOpenglDefault;
HANDLE threadMutexCopyContentDefaultCore;
HANDLE threadMutexCopyContentCoreDefault;
HANDLE threadMutexCopyContentCoreOpengl;
HANDLE threadMutexCopyContentOpenglCore;
HANDLE threadMutexCopyContentDefaultUsb;
HANDLE threadMutexCopyContentCoreUsb;
HANDLE threadMutexScriptStatus;
HANDLE threadMutexCopyContentAudioCore;

unsigned char *threadSourceCode;
unsigned int threadSourceCodeLength;
unsigned int threadReadyToRun;
unsigned int threadReadyToRunRealTime;
unsigned int threadType;
unsigned int threadCanvasHeight;
unsigned int threadCanvasWidth;
unsigned int threadCanvasResize;
unsigned char threadVideoBuffer[3*LATTICE_MAX_SIZE];
unsigned char threadUsbVideoBuffer[3*LATTICE_MAX_SIZE];
int threadLatticeFrames;
int threadLatticeType;
int threadLatticeSizeX;
int threadLatticeSizeY;
int threadLatticeSizeZ;
int threadLatticeCustom;
int threadLatticeCreateNew;
int threadSelectedFrameFirst;
int threadSelectedFrameLast;
int threadSelectedFrameCurrent;
int threadSelectionMade;
float threadViewerAngleX;
float threadViewerAngleY;
int threadViewerDistance;
int threadMouseWheel;
int threadSizeX;
int threadSizeY;
int threadSizeZ;
int threadLedSize;
int threadBlackLeds;
int threadLedSpacing;
int threadRenderQuality;
int threadShowBase;
int threadShowAxis;
int threadShowLattice;
int threadPresetView;
int threadPlaybackCommand;
int threadStopScript;
int threadCanvasActive;
int threadShutDownCoreThread;
int threadUsbControl;
int threadOpenAnimationFile;
char threadOpenAnimationFileName[256+3+1];
int threadOpenAnimationFileNameLength;
int threadSaveAnimationFile;
char threadSaveAnimationFileName[256+3+1];
int threadSaveAnimationFileNameLength;
char threadAnimationTitle[32];
int threadRealTimePlaying;
int threadRealTimeCommand;
int threadSoundFft[1024];


void threadsInit()
{

	threadMutexCopyContentDefaultOpengl=CreateMutex(NULL,FALSE,(LPCWSTR)"threadMutexCopyContentDefaultOpengl");
	threadMutexCopyContentOpenglDefault=CreateMutex(NULL,FALSE,(LPCWSTR)"threadMutexCopyContentOpenglDefault");
	threadMutexCopyContentDefaultCore=CreateMutex(NULL,FALSE,(LPCWSTR)"threadMutexCopyContentDefaultCore");
	threadMutexCopyContentCoreDefault=CreateMutex(NULL,FALSE,(LPCWSTR)"threadMutexCopyContentCoreDefault");
	threadMutexCopyContentCoreOpengl=CreateMutex(NULL,FALSE,(LPCWSTR)"threadMutexCopyContentCoreOpengl");
	threadMutexCopyContentOpenglCore=CreateMutex(NULL,FALSE,(LPCWSTR)"threadMutexCopyContentOpenglCore");
	threadMutexCopyContentDefaultUsb=CreateMutex(NULL,FALSE,(LPCWSTR)"threadMutexCopyContentDefaultUsb");
	threadMutexScriptStatus=CreateMutex(NULL,FALSE,(LPCWSTR)"threadMutexScriptStatus");
	threadMutexCopyContentCoreUsb=CreateMutex(NULL,FALSE,(LPCWSTR)"threadMutexCopyContentCoreUsb");
	threadMutexCopyContentCoreUsb=CreateMutex(NULL,FALSE,(LPCWSTR)"threadMutexCopyContentAudioCore");

	threadOpengEvent = CreateEvent(NULL, TRUE, FALSE, TEXT("threadOpengEvent"));


}

void threadsRun()
{
	_beginthread(threadOpenglMain,0,NULL);
	_beginthread(threadCoreMain,0,NULL);
	_beginthread(threadUsbMain,0,NULL);
	//_beginthread(threadAudioMain,0,NULL);

}


void threadsClean()
{
	CloseHandle(threadOpengEvent);

	CloseHandle(threadMutexCopyContentDefaultOpengl);
	CloseHandle(threadMutexCopyContentOpenglDefault);
	CloseHandle(threadMutexCopyContentDefaultCore);
	CloseHandle(threadMutexCopyContentCoreDefault);
	CloseHandle(threadMutexCopyContentCoreOpengl);
	CloseHandle(threadMutexCopyContentOpenglCore);
	CloseHandle(threadMutexCopyContentDefaultUsb);
	CloseHandle(threadMutexCopyContentCoreUsb);
	CloseHandle(threadMutexScriptStatus);
	CloseHandle(threadMutexCopyContentAudioCore);


}
void threadCopyContentDefaultUsbIn()
{
	WaitForSingleObject(threadMutexCopyContentDefaultCore, INFINITE);
	if (handlerUsbControl!=0)
	{
		threadUsbControl=handlerUsbControl;
		handlerUsbControl=0;
	}
	ReleaseMutex(threadMutexCopyContentDefaultCore);
}
void threadCopyContentDefaultUsbOut()
{
	WaitForSingleObject(threadMutexCopyContentDefaultCore, INFINITE);
	if (threadUsbControl!=0)
	{
		usbUsbControl=threadUsbControl;
		threadUsbControl=0;
	}
	ReleaseMutex(threadMutexCopyContentDefaultCore);
}

void threadCopyContentAudioCoreIn()
{
	WaitForSingleObject(threadMutexCopyContentAudioCore, INFINITE);
	memcpy(threadSoundFft,audioSoundFft,1024*4);
	ReleaseMutex(threadMutexCopyContentAudioCore);
}
void threadCopyContentAudioCoreOut()
{
	WaitForSingleObject(threadMutexCopyContentAudioCore, INFINITE);
	memcpy(scriptSoundFft,threadSoundFft,1024*4);
	ReleaseMutex(threadMutexCopyContentAudioCore);
}

void threadCopyContentCoreUsbIn()
{
	WaitForSingleObject(threadMutexCopyContentDefaultCore, INFINITE);
//	lattice->copyFrameForUsb(latticeActiveFrame,&threadUsbVideoBuffer[0]);
	ReleaseMutex(threadMutexCopyContentDefaultCore);
}
void threadCopyContentCoreUsbOut()
{
	WaitForSingleObject(threadMutexCopyContentDefaultCore, INFINITE);
	memcpy(&usbVideoBuffer[0],&threadUsbVideoBuffer[0],3*lattice->getSize());
	ReleaseMutex(threadMutexCopyContentDefaultCore);
}

void threadCopyContentDefaultCoreIn()
{
	int i;

	WaitForSingleObject(threadMutexCopyContentDefaultCore, INFINITE);
	if (frmScriptRealTimeSourceReadyToRun==1)
	{
		//if (threadSourceCode!=NULL)
			//delete /*[]*/threadSourceCode;
		/*threadSourceCodeLength=frmScriptSourceSourceCodeLength;
		threadSourceCode=new unsigned char[frmScriptSourceSourceCodeLength+1];
		i=0;
		while (frmScriptSourceSourceCode[i]!=0)
		{
			threadSourceCode[i]=frmScriptSourceSourceCode[i];
			i=i+1;
		}
		threadSourceCode[i]=frmScriptSourceSourceCode[i];
		threadSourceCode[i+1]=0;*/
		threadReadyToRunRealTime=1;
		frmScriptRealTimeSourceReadyToRun=0;
	}
	if (frmScriptSourceReadyToRun==1)
	{
		//if (threadSourceCode!=NULL)
			//delete /*[]*/threadSourceCode;
		threadType=frmScriptSourceType;
		threadSourceCodeLength=frmScriptSourceSourceCodeLength;
		threadSourceCode=new unsigned char[frmScriptSourceSourceCodeLength+1];
		i=0;
		while (frmScriptSourceSourceCode[i]!=0)
		{
			threadSourceCode[i]=frmScriptSourceSourceCode[i];
			i=i+1;
		}
		threadSourceCode[i]=frmScriptSourceSourceCode[i];
		threadSourceCode[i+1]=0;
		threadReadyToRun=1;
		frmScriptSourceReadyToRun=0;
	}
	if (handlerOpenAnimationFile==1)
	{

		for(i=0;i<handlerOpenAnimationFileNameLength;i++)
			threadOpenAnimationFileName[i]=handlerOpenAnimationFileName[i];
		threadOpenAnimationFileName[handlerOpenAnimationFileNameLength]=0;
		threadOpenAnimationFileNameLength=handlerOpenAnimationFileNameLength;
		handlerOpenAnimationFile=0;
		threadOpenAnimationFile=1;
	}
	if (handlerSaveAnimationFile==1)
	{

		for(i=0;i<handlerSaveAnimationFileNameLength;i++)
			threadSaveAnimationFileName[i]=handlerSaveAnimationFileName[i];
		for(i=0;i<handlerAnimationTitleLength;i++)
			threadAnimationTitle[i]=handlerAnimationTitle[i];
		threadAnimationTitle[handlerAnimationTitleLength]=0;

		threadSaveAnimationFileName[handlerSaveAnimationFileNameLength]=0;
		threadSaveAnimationFileNameLength=handlerSaveAnimationFileNameLength;
		handlerSaveAnimationFile=0;
		threadSaveAnimationFile=1;
	}
	if (frmNewLatticeCreateNew==1)
	{
		threadLatticeFrames=frmNewLatticeFrames;
		threadLatticeType=frmNewLatticeType;
		threadLatticeSizeX=frmNewLatticeSizeX;
		threadLatticeSizeY=frmNewLatticeSizeY;
		threadLatticeSizeZ=frmNewLatticeSizeZ;
		threadLatticeCustom=frmNewLatticeCustom;
		frmNewLatticeCreateNew=0;
		threadLatticeCreateNew=1;
	}
	if (frmFramesSelectionMade==1)
	{
		threadSelectedFrameFirst=frmFramesSelectedFrameFirst;
		threadSelectedFrameLast=frmFramesSelectedFrameLast;
		threadSelectedFrameCurrent=frmFramesSelectedFrameCurrent;
		threadSelectionMade=1;
		frmFramesSelectionMade=0;
	}
	threadMouseWheel=wndprocMouseWheel;
	wndprocMouseWheel=0;
	if (handlerPresetView!=0)
	{
		threadPresetView=handlerPresetView;
		handlerPresetView=0;
	}
	if (handlerPlaybackCommand!=0)
	{
		threadPlaybackCommand=handlerPlaybackCommand;
		handlerPlaybackCommand=0;
	}
	if (handlerStopScript!=0)
	{
		threadStopScript=handlerStopScript;
		handlerStopScript=0;
	}
	threadCanvasActive=handlerCanvasActive;
	threadShutDownCoreThread=handlerShutDownCoreThread;
	if (handlerRealTimeCommand)
	{
		threadRealTimeCommand=handlerRealTimeCommand;
		handlerRealTimeCommand=0;
	}
	ReleaseMutex(threadMutexCopyContentDefaultCore);
}

void threadCopyContentDefaultCoreOut()
{
	unsigned int i;

	WaitForSingleObject(threadMutexCopyContentDefaultCore, INFINITE);
	if (threadReadyToRunRealTime==1)
	{
		/*scriptSourceCodeLength=threadSourceCodeLength;
		scriptSourceCode=new unsigned char[threadSourceCodeLength];
		i=0;
		for(i=0;i<threadSourceCodeLength+1;i++)
			scriptSourceCode[i]=threadSourceCode[i];*/
		scriptReadyToRunRealTime=1;
		threadReadyToRunRealTime=0;
	}
	if (threadReadyToRun==1)
	{
	//	if (scriptSourceCode!=NULL)
	//		delete /*[]*/scriptSourceCode;

		scriptType=threadType;
		scriptSourceCodeLength=threadSourceCodeLength;
		scriptSourceCode=new unsigned char[threadSourceCodeLength];
		i=0;
		for(i=0;i<threadSourceCodeLength+1;i++)
			scriptSourceCode[i]=threadSourceCode[i];
		scriptReadyToRun=1;
		threadReadyToRun=0;
	}
	if (threadOpenAnimationFile==1)
	{
		for(i=0;i<threadOpenAnimationFileNameLength;i++)
			latticeOpenAnimationFileName[i]=threadOpenAnimationFileName[i];
		latticeOpenAnimationFileName[threadOpenAnimationFileNameLength]=0;
		latticeOpenAnimationFileNameLength=threadOpenAnimationFileNameLength;
		threadOpenAnimationFile=0;
		latticeOpenAnimationFile=1;
	}
	if (threadSaveAnimationFile==1)
	{
		for(i=0;i<threadSaveAnimationFileNameLength;i++)
			latticeSaveAnimationFileName[i]=threadSaveAnimationFileName[i];
		for(i=0;i<32;i++)
			latticeAnimationTitle[i]=threadAnimationTitle[i];
		latticeSaveAnimationFileName[threadSaveAnimationFileNameLength]=0;
		latticeSaveAnimationFileNameLength=threadSaveAnimationFileNameLength;
		threadSaveAnimationFile=0;
		latticeSaveAnimationFile=1;
	}
	if (threadLatticeCreateNew==1)
	{
		latticeNewAnimationFrames=threadLatticeFrames;
		latticeLatticeType=threadLatticeType;
		latticeNewAnimationLatticeX=threadLatticeSizeX;
		latticeNewAnimationLatticeY=threadLatticeSizeY;
		latticeNewAnimationLatticeZ=threadLatticeSizeZ;
		latticeLatticeCustom=threadLatticeCustom;
		threadLatticeCreateNew=0;
		latticeLatticeCreateNew=1;
	}
	if (threadSelectionMade==1)
	{
		latticeSelectedFrameFirst=threadSelectedFrameFirst;
		latticeSelectedFrameLast=threadSelectedFrameLast;
		latticeSelectedFrameCurrent=threadSelectedFrameCurrent;
		latticeSelectionMade=1;
		threadSelectionMade=0;
	}
	uiMouseWheel=threadMouseWheel;
	threadMouseWheel=0;
	if (threadPresetView!=0)
	{
		uiPresetView=threadPresetView;
		threadPresetView=0;
	}
	if (threadPlaybackCommand!=0)
	{
		playbackPlaybackCommand=threadPlaybackCommand;
		threadPlaybackCommand=0;
	}
	if (threadStopScript!=0)
	{
		scriptStopScript=threadStopScript;
		threadStopScript=0;
	}
	uiCanvasActive=threadCanvasActive;
	threadCoreShutDownCoreThread=threadShutDownCoreThread;
	if (threadRealTimeCommand)
	{
		scriptRealTimeCommand=threadRealTimeCommand;
		threadRealTimeCommand=0;
	}
	ReleaseMutex(threadMutexCopyContentDefaultCore);
}

void threadCopyContentDefaultOpenglInit()
{
	handlerLedSize=10;
	handlerBlackLeds=3;
	handlerLedSpacing=36;
	handlerRenderQuality=1;
	handlerShowBase=0;
	handlerShowAxis=1;
	handlerShowLattice=1;
}

void threadCopyContentDefaultOpenglIn()
{


	WaitForSingleObject(threadMutexCopyContentDefaultOpengl, INFINITE);
	if (handlerCanvasResize==1)
	{
		threadCanvasHeight=handlerCanvasHeight;
		threadCanvasWidth=handlerCanvasWidth;
		threadCanvasResize=1;
		handlerCanvasResize=0;
	}
	threadLedSize=handlerLedSize;
	threadBlackLeds=handlerBlackLeds;
	threadLedSpacing=handlerLedSpacing;
	threadRenderQuality=handlerRenderQuality;
	threadShowBase=handlerShowBase;
	threadShowAxis=handlerShowAxis;
	threadShowLattice=handlerShowLattice;
	ReleaseMutex(threadMutexCopyContentDefaultOpengl);
}


void threadCopyContentDefaultOpenglOut()
{

	WaitForSingleObject(threadMutexCopyContentDefaultOpengl, INFINITE);
	if (threadCanvasResize==1)
	{
		openglCanvasHeight=threadCanvasHeight;
		openglCanvasWidth=threadCanvasWidth;
	//	SendMessageW((HWND)wndprocFrmMainHandle,wndprocMessages[0],WNDPROC_MESSAGE0_SHOW_DEBUG_PARAM_1,handlerCanvasHeight);
	//	SendMessageW((HWND)wndprocFrmMainHandle,wndprocMessages[0],WNDPROC_MESSAGE0_SHOW_DEBUG_PARAM_2,openglCanvasWidth);
		openglCanvasResize=1;
		threadCanvasResize=0;
	}
	openglLedSize=threadLedSize;
	openglBlackLeds=threadBlackLeds;
	openglLedSpacing=threadLedSpacing;
	openglRenderQuality=threadRenderQuality;
	openglShowBase=threadShowBase;
	openglShowAxis=threadShowAxis;
	openglShowLattice=threadShowLattice;
	ReleaseMutex(threadMutexCopyContentDefaultOpengl);
}
void threadCopyContentCoreOpenglInit()
{
	uiViewerAngleX=30;
	uiViewerAngleY=25;
	uiViewerDistance=600;

}

void threadCopyContentCoreOpenglIn()
{
	WaitForSingleObject(threadMutexCopyContentCoreOpengl, INFINITE);
	//lattice->copyFrame(latticeActiveFrame,&threadVideoBuffer[0]);  //-disabled to test real time scripts
	threadViewerAngleX=uiViewerAngleX;
	threadViewerAngleY=uiViewerAngleY;
	threadViewerDistance=uiViewerDistance;
	threadSizeX=lattice->getSizeX();
	threadSizeY=lattice->getSizeY();
	threadSizeZ=lattice->getSizeZ();

	ReleaseMutex(threadMutexCopyContentCoreOpengl);
}

void threadCopyContentCoreOpenglOut()
{
	WaitForSingleObject(threadMutexCopyContentCoreOpengl, INFINITE);

	memcpy(&openglVideoBuffer[0],&threadVideoBuffer[0],3*LATTICE_MAX_SIZE);
	openglViewerAngleX=threadViewerAngleX;
	openglViewerAngleY=threadViewerAngleY;
	openglViewerDistance=threadViewerDistance;
	openglSizeX=threadSizeX;
	openglSizeY=threadSizeY;
	openglSizeZ=threadSizeZ;

	ReleaseMutex(threadMutexCopyContentCoreOpengl);

}