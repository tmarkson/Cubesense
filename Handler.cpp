#include "stdafx.h"
#include "includeall.h"
#include "windows.h"

int handlerCanvasHeight;
int handlerCanvasWidth;
int handlerCanvasResize;

int handlerLatticeSizeX;
int handlerLatticeSizeY;
int handlerLatticeSizeZ;

int handlerLedSize;
int handlerLedSpacing;
int handlerBlackLeds;
int handlerRenderQuality;
int handlerShowBase;
int handlerShowAxis;
int handlerShowLattice;
int handlerPresetView;
int handlerPlaybackCommand;
int handlerStopScript;
int handlerCanvasActive;
int handlerShutDownCoreThread;
int handlerUsbControl;
int handlerOpenAnimationFile;
char* handlerOpenAnimationFileName;
int handlerOpenAnimationFileNameLength;
int handlerOpeningAnimation;
int handlerSaveAnimationFile;
char* handlerSaveAnimationFileName;
int handlerSaveAnimationFileNameLength;
char* handlerAnimationTitle;
int handlerAnimationTitleLength;
int handlerCreatingAnimation;
int handlerRealTimeCommand;

void handlerFrmMainLoad(int formMainHandle, int canvasHandle, int formFramesHandle, int formScriptSourceHandler)
{
	logEvent(LOG_THREAD_DEFAULT, "Entered custom handler for main form load event");

	wndprocFrmMainHandle=formMainHandle;
	wndprocFrmScriptSourceHandle=formScriptSourceHandler;
	openglCanvasHandle=canvasHandle;
	threadCoreFrmFramesHandler=formFramesHandle;
	wndprocMessages[0]=RegisterWindowMessage(UNICODE_TEXT("Message1"));

	logEvent(LOG_THREAD_DEFAULT, "Windows message registered");

	threadsInit();
	threadCopyContentDefaultOpenglInit();
	threadCopyContentCoreOpenglInit();

	logEvent(LOG_THREAD_DEFAULT, "Default values used by other threads copied");

	scriptInit();
	logEvent(LOG_THREAD_DEFAULT, "Script module initialized");
	uiInit();
	logEvent(LOG_THREAD_DEFAULT, "Ui module initialized");
	latticeInit();
	logEvent(LOG_THREAD_DEFAULT, "Lattice module initialized");
	playbackInit();
	logEvent(LOG_THREAD_DEFAULT, "Playback module initialized");

	SendMessageW((HWND)threadCoreFrmFramesHandler,wndprocMessages[0],WNDPROC_MESSAGE0_SHOW_FRAME_LIST,latticeNewAnimationFrames);
	logEvent(LOG_THREAD_DEFAULT, "Message sent to show frames list");
	SendMessageW((HWND)formMainHandle,wndprocMessages[0],WNDPROC_MESSAGE0_SHOW_LATTICE_SIZE,((lattice->getSizeX()*LATTICE_MAX_Y)+lattice->getSizeY())*LATTICE_MAX_Z+lattice->getSizeZ());
	logEvent(LOG_THREAD_DEFAULT, "Message sent to show current lattice size");

	threadsRun();
	logEvent(LOG_THREAD_DEFAULT, "All extra threads launched");


}


void handlerFrmMainFormClosing()
{
	handlerShutDownCoreThread=1;
	threadCopyContentDefaultCoreIn();
	Sleep(500);
	threadsClean();


}

void handlerPictureBox1Resize(int height, int width)
{
	handlerCanvasHeight=height;
	handlerCanvasWidth=width;
	handlerCanvasResize=1;
	threadCopyContentDefaultOpenglIn();
}

int handlerAskAboutSavingScript()
{
	int r;
	SendMessageW((HWND)wndprocFrmMainHandle,wndprocMessages[0],WNDPROC_MESSAGE0_ENABLE_MAIN_FORM,0);
	r=MessageBoxA(0,"Do you want to save changes to current script file?","Cubesense", MB_YESNOCANCEL);
	SendMessageW((HWND)wndprocFrmMainHandle,wndprocMessages[0],WNDPROC_MESSAGE0_ENABLE_MAIN_FORM,1);
	return r;
 }

int handlerAskAboutSavingAnimation()
{
	int r;
	SendMessageW((HWND)wndprocFrmMainHandle,wndprocMessages[0],WNDPROC_MESSAGE0_ENABLE_MAIN_FORM,0);
	r=MessageBoxA(0,"Do you want to save changes to your animation file?","Cubesense", MB_YESNOCANCEL);
	SendMessageW((HWND)wndprocFrmMainHandle,wndprocMessages[0],WNDPROC_MESSAGE0_ENABLE_MAIN_FORM,1);
	return r;
 }

void handlerDisableMainForm()
{
	SendMessageW((HWND)wndprocFrmMainHandle,wndprocMessages[0],WNDPROC_MESSAGE0_ENABLE_MAIN_FORM,0);
}

void handlerEnableMainForm()
{
	SendMessageW((HWND)wndprocFrmMainHandle,wndprocMessages[0],WNDPROC_MESSAGE0_ENABLE_MAIN_FORM,1);
}

void handlerFrmScriptOutputListBox1SelectedIndexChanged(int l)
{
	SendMessageW((HWND)wndprocFrmScriptSourceHandle,wndprocMessages[0],WNDPROC_MESSAGE0_HIGHLIGHT_ERROR,scriptErrorRow[l]);
}	

void handlerNoAnimationTitle()
{
	SendMessageW((HWND)wndprocFrmMainHandle,wndprocMessages[0],WNDPROC_MESSAGE0_NO_ANIMATION_FILE_NAME,0);
}