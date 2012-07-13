#include "stdafx.h"
#include "includeall.h"
#include "windows.h"

int uiMousePressed[8];								//indicates whether particulart user interface key has just been pressed but not held
int uiMouseHeld[8];									//indicates whether particulart user interface key has just been pressed and held
int uiMouseReleased[8];								//indicates whether particulart user interface key has just been released
int uiMouseX;										//current cursor X coordinate
int uiMouseY;										//current cursor Y coordinate
int uiMouseLastX;									//cursor X coordinate last time uiHandler was called
int uiMouseLastY;									//cursor Y coordinate last time uiHandler was called
int uiMouseWheel;									//mouse wheel action
float uiViewerAngleX;
float uiViewerAngleY;
float uiViewerAngleAutoRotateX;
float uiViewerAngleAutoRotateY;
int uiLatticeDisplayMode;
int uiViewerDistance;
int uiLatticeSelectedPlaneX;
int uiLatticeSelectedPlaneY;
int uiLatticeSelectedPlaneZ;
int uiPresetViewStepCount;
float uiPresetStepX;
float uiPresetStepY;
int uiPresetView;
int uiCanvasActive;

void uiInit()
{

	uiViewerAngleAutoRotateX=1;
	uiViewerAngleAutoRotateY=0;
}

void uiAutoRotate()
{
	if (uiPresetViewStepCount>0)
	{
		uiViewerAngleX=(uiViewerAngleX+(uiPresetStepX)+360);
		uiViewerAngleY=(uiViewerAngleY+(uiPresetStepY)+360);
		uiPresetViewStepCount--;
		while (uiViewerAngleX>=360)
			uiViewerAngleX-=360;
		while (uiViewerAngleY>=360)
			uiViewerAngleY-=360;

	}
	else
	{
		uiViewerAngleX=(uiViewerAngleX+(uiViewerAngleAutoRotateX)+360);
		uiViewerAngleY=(uiViewerAngleY+(uiViewerAngleAutoRotateY)+360);
		while (uiViewerAngleX>=360)
			uiViewerAngleX-=360;
		while (uiViewerAngleY>=360)
			uiViewerAngleY-=360;

	}
}

void uiProcessor()
{
	int wheelDelta;								//mouse wheel delta

	if(uiCanvasActive)
	{
		if (!uiMouseHeld[UI_LEFT_SHIFT])			
		{											//if left mouse button is not held down
			if (uiMouseHeld[UI_MOUSE_RB])			
			{										//if right mouse button is held down calculate new viewing angle, disable auto-rotation
				uiViewerAngleX=(int)(uiViewerAngleX+(uiMouseLastX-uiMouseX)+360)%360;
				uiViewerAngleY=(int)(uiViewerAngleY-(uiMouseLastY-uiMouseY)+360)%360;
				uiViewerAngleAutoRotateX=0;
				uiViewerAngleAutoRotateY=0;
			}
			if (uiMouseReleased[UI_MOUSE_RB])
			{										//if right mouse button has just been released calculate auto-rotation step
				uiViewerAngleAutoRotateX=(uiMouseLastX-uiMouseX)/3*5/10.0*2;
				uiViewerAngleAutoRotateY=(uiMouseY-uiMouseLastY)/3*5/10.0*2;
			}
			if (uiMousePressed[UI_MOUSE_MB])
			{										//if middle mouse button has just been pressed change lattice display mode
				uiLatticeDisplayMode=(uiLatticeDisplayMode+1)%4;
			}

			if ((uiMouseWheel!=0)&(uiMouseHeld[UI_MOUSE_RB]!=0))
				//if right mouse button is held down and mouse wheel is turned changes viewer distance
				if (uiMouseWheel==120)
					uiViewerDistance-=125;
				else
					uiViewerDistance+=125;

			if ((uiMouseWheel!=0)&(uiMouseHeld[UI_MOUSE_RB]==0))
			{										//if right mouse button is not held down and mouse wheel is turned change active plane for selected lattice display mode
				if (uiMouseWheel==120)
					wheelDelta=1;
				else
					wheelDelta=-1;
				if (uiLatticeDisplayMode==1)
					uiLatticeSelectedPlaneX=(uiLatticeSelectedPlaneX+wheelDelta+8)%8;
				if (uiLatticeDisplayMode==2)
					uiLatticeSelectedPlaneY=(uiLatticeSelectedPlaneY+wheelDelta+8)%8;
				if (uiLatticeDisplayMode==3)
					uiLatticeSelectedPlaneZ=(uiLatticeSelectedPlaneZ+wheelDelta+8)%8;
			}
		}
	}
}

//calculate X and Y angle steps for preset view mode
void uiCalculatePresetViewStep()
{
	int targetAngleX;
	int targetAngleY;

	if (uiPresetView==UI_PRESET_VIEW_DEFAULT)
	{
		targetAngleX=45;
		targetAngleY=45;
	}
	if (uiPresetView==UI_PRESET_VIEW_XZ)
	{
		targetAngleX=0;
		targetAngleY=0;
	}
	if (uiPresetView==UI_PRESET_VIEW_XY)
	{
		targetAngleX=0;
		targetAngleY=90;
	}
	if (uiPresetView==UI_PRESET_VIEW_YZ)
	{
		targetAngleX=90;
		targetAngleY=0;
	}
	uiPresetView=0;
	uiViewerAngleAutoRotateX=0;
	uiViewerAngleAutoRotateY=0;
	uiPresetViewStepCount=20;
	
	if (targetAngleX>uiViewerAngleX)
		if ((targetAngleX-uiViewerAngleX)<180)
			uiPresetStepX=(targetAngleX-(uiViewerAngleX))/uiPresetViewStepCount;
		else
			uiPresetStepX=(360-targetAngleX+(uiViewerAngleX))/uiPresetViewStepCount;
	else
		if ((uiViewerAngleX-targetAngleX)<180)
			uiPresetStepX=(targetAngleX-(uiViewerAngleX))/uiPresetViewStepCount;
		else
			uiPresetStepX=(360+targetAngleX-(uiViewerAngleX))/uiPresetViewStepCount;

	if (targetAngleY>uiViewerAngleY)
		if ((targetAngleY-uiViewerAngleY)<180)
			uiPresetStepY=(targetAngleY-(uiViewerAngleY))/uiPresetViewStepCount;
		else
			uiPresetStepY=(360-targetAngleY+(uiViewerAngleY))/uiPresetViewStepCount;
	else
		if ((uiViewerAngleY-targetAngleY)<180)
			uiPresetStepY=(targetAngleY-(uiViewerAngleY))/uiPresetViewStepCount;
		else
			uiPresetStepY=(360+targetAngleY-(uiViewerAngleY))/uiPresetViewStepCount;
}

void uiHandler()
{
	int r;
	LPPOINT lpPoint=new POINT;

	//check user interface key's status
	UI_CHECK_SINGLE_KEY(VK_RBUTTON,UI_MOUSE_RB);
	UI_CHECK_SINGLE_KEY(VK_MBUTTON,UI_MOUSE_MB);
	UI_CHECK_SINGLE_KEY(VK_LBUTTON,UI_MOUSE_LB);
	UI_CHECK_SINGLE_KEY(VK_LSHIFT,UI_LEFT_SHIFT);
	//store last cursor position
	uiMouseLastX=uiMouseX;
	uiMouseLastY=uiMouseY;
	//get current cursor position
	GetCursorPos(lpPoint);
	uiMouseX=(int)lpPoint->x/2;
	uiMouseY=(int)lpPoint->y/2;
	//find new viewing angle and center point coordinates
	uiProcessor();
	if (uiPresetView)
		uiCalculatePresetViewStep();
	
	//perform lattice auto-rotation if necessary 
	uiAutoRotate();
	delete lpPoint;
}