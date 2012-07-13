#include "stdafx.h"
#include "includeall.h"
#include "windows.h"
#include "mpusbapi.h"



char usbVidPid[]="vid_04d8&pid_f101";
char usbPipeAddressGenIn[]="\\MCHP_EP1";
char usbPipeAddressGenOut[]="\\MCHP_EP1";
char usbPipeAddressStrmIn[]="\\MCHP_EP2";
char usbPipeAddressStrmOut[]="\\MCHP_EP2";

HANDLE usbPipeGenIn;
HANDLE usbPipeGenOut;
HANDLE usbPipeStrmIn;
HANDLE usbPipeStrmOut;

char usbUseUsbStream;

unsigned char usbVideoBuffer[LATTICE_MAX_SIZE*3];
unsigned char usbFeedbackBuffer[64];

int usbUsbControl;
int usbStreamVideo;
int usbConnected;

void usbInit()
{
	HINSTANCE libHandle;
	libHandle = NULL; 
	libHandle = LoadLibrary(UNICODE_TEXT("mpusbapi")); 
	if(libHandle!=NULL) 
	{ 
		MPUSBGetDLLVersion=(DWORD(*)(void))GetProcAddress(libHandle,"_MPUSBGetDLLVersion"); 
		MPUSBGetDeviceCount=(DWORD(*)(PCHAR))GetProcAddress(libHandle,"_MPUSBGetDeviceCount"); 
		MPUSBOpen=(HANDLE(*)(DWORD,PCHAR,PCHAR,DWORD,DWORD))GetProcAddress(libHandle,"_MPUSBOpen"); 
		MPUSBWrite=(DWORD(*)(HANDLE,PVOID,DWORD,PDWORD,DWORD))GetProcAddress(libHandle,"_MPUSBWrite"); 
		MPUSBRead=(DWORD(*)(HANDLE,PVOID,DWORD,PDWORD,DWORD))GetProcAddress(libHandle,"_MPUSBRead");
		MPUSBReadInt=(DWORD(*)(HANDLE,PVOID,DWORD,PDWORD,DWORD))GetProcAddress(libHandle,"_MPUSBReadInt"); 
		MPUSBClose=(BOOL(*)(HANDLE))GetProcAddress(libHandle,"_MPUSBClose"); 
	}

	usbPipeGenIn=INVALID_HANDLE_VALUE;
	usbPipeGenOut=INVALID_HANDLE_VALUE;
	usbPipeStrmIn=INVALID_HANDLE_VALUE;
	usbPipeStrmOut=INVALID_HANDLE_VALUE;
	
	usbStreamVideo=0;
}

bool usbConnect()
{
	bool r;

	usbPipeGenIn=MPUSBOpen(0,usbVidPid,usbPipeAddressGenIn,MP_READ,0);
	usbPipeGenOut=MPUSBOpen(0,usbVidPid,usbPipeAddressGenOut,MP_WRITE,0);
	usbPipeStrmIn=MPUSBOpen(0,usbVidPid,usbPipeAddressStrmIn,MP_READ,0);
	usbPipeStrmOut=MPUSBOpen(0,usbVidPid,usbPipeAddressStrmOut,MP_WRITE,0);
	if ((usbPipeGenIn!=INVALID_HANDLE_VALUE)&(usbPipeGenOut!=INVALID_HANDLE_VALUE)&
		(usbPipeStrmIn!=INVALID_HANDLE_VALUE)&(usbPipeStrmOut!=INVALID_HANDLE_VALUE))
		r=true;
	else
		r=false;

	return r;
}

void usbDisconnect()
{

	if (usbPipeGenIn!=INVALID_HANDLE_VALUE)
		MPUSBClose(usbPipeGenIn); 
	if (usbPipeGenOut!=INVALID_HANDLE_VALUE)
		MPUSBClose(usbPipeGenOut); 
	if (usbPipeStrmIn!=INVALID_HANDLE_VALUE)
		MPUSBClose(usbPipeStrmIn); 
	if (usbPipeStrmOut!=INVALID_HANDLE_VALUE)
		MPUSBClose(usbPipeStrmOut);
	usbPipeGenIn=INVALID_HANDLE_VALUE;
	usbPipeGenOut=INVALID_HANDLE_VALUE;
	usbPipeStrmIn=INVALID_HANDLE_VALUE;
	usbPipeStrmOut=INVALID_HANDLE_VALUE;
}
/*



*/

/*
void usbCopyToUsbBuffer()
{
	int i;
	for(i=0;i<LATTICE_MAX_SIZE;i++)
		usbUsbBuffer[i]=threadUsbBuffer[i];
	for(i=0;i<LATTICE_MAX_SIZE;i++)
		usbUsbBuffer[i+512]=threadUsbBuffer[i+LATTICE_MAX_SIZE];
	for(i=0;i<LATTICE_MAX_SIZE;i++)
		usbUsbBuffer[i+512*2]=threadUsbBuffer[i+LATTICE_MAX_SIZE*2];
}
*/

char usbService()
{

	int sizeSent;
	sizeSent=1536;

	if ((usbPipeStrmIn!=INVALID_HANDLE_VALUE)&(usbPipeStrmOut!=INVALID_HANDLE_VALUE))
	{
		MPUSBRead(usbPipeStrmIn,usbFeedbackBuffer,64,(PDWORD)&sizeSent,200);
		MPUSBWrite(usbPipeStrmOut,usbVideoBuffer,1536,(PDWORD)&sizeSent,200);
		return 1;
	}
	else
		return 0;
}

int usbServiceStatus(int s)
{
	unsigned char bufout[64];
	int i;
	int sizeSent;
	sizeSent=64;

	for(i=0;i<64;i++)
		bufout[i]=0;

	bufout[1]=s+1;

	if (usbPipeGenOut!=INVALID_HANDLE_VALUE)
	{
		MPUSBWrite(usbPipeGenOut,bufout,64,(PDWORD)&sizeSent,200);
		return 1;
	}
	else
		return 0;
}

void usbHandler()
{
	if (usbUsbControl!=0)
	{
		if (usbUsbControl==1)
		{
			if (usbConnected)
			{
				if (MPUSBGetDeviceCount(usbVidPid)==0)
				{
					SendMessageW((HWND)wndprocFrmMainHandle,wndprocMessages[0],WNDPROC_MESSAGE0_SHOW_USB_STATUS,3);
					usbConnected=0;
				}
			}
			if (!usbConnected)
			{
				if (usbConnect())
				{
					SendMessageW((HWND)wndprocFrmMainHandle,wndprocMessages[0],WNDPROC_MESSAGE0_SHOW_USB_STATUS,1);
					usbConnected=1;
					usbServiceStatus(usbStreamVideo);
				}
				else
				{
					SendMessageW((HWND)wndprocFrmMainHandle,wndprocMessages[0],WNDPROC_MESSAGE0_SHOW_USB_STATUS,2);
					usbConnected=0;
				}
			}
		}
		if (usbUsbControl==2)
		{
			usbServiceStatus(0);
			usbDisconnect();
			usbConnected=0;
			SendMessageW((HWND)wndprocFrmMainHandle,wndprocMessages[0],WNDPROC_MESSAGE0_SHOW_USB_STATUS,3);
		}
		if (usbUsbControl==3)
		{
			usbStreamVideo=0;
			usbServiceStatus(usbStreamVideo);
		}
		if (usbUsbControl==4)
		{
			usbStreamVideo=1;
			usbServiceStatus(usbStreamVideo);
		}
		usbUsbControl=0;
	}
}