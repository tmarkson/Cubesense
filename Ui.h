

#define UI_MOUSE_RB 0
#define UI_MOUSE_MB 1
#define UI_MOUSE_LB 2
#define UI_LEFT_SHIFT 3

#define UI_PRESET_VIEW_NONE 0
#define UI_PRESET_VIEW_DEFAULT 1
#define UI_PRESET_VIEW_XZ 2
#define UI_PRESET_VIEW_YZ 3
#define UI_PRESET_VIEW_XY 4

#define UI_CHECK_SINGLE_KEY(keyCode, keyID)	{\
	r=GetAsyncKeyState(keyCode);\
	if (r!=0)\
	{\
	if (uiMouseHeld[keyID]==0)\
		{\
		uiMousePressed[keyID]=1;\
		uiMouseHeld[keyID]=1;\
		}\
		else\
		{\
		uiMousePressed[keyID]=0;\
		}\
	}\
	else\
	{\
	if (uiMouseHeld[keyID]==1)\
		{\
		uiMouseHeld[keyID]=0;\
		uiMouseReleased[keyID]=1;\
		uiMousePressed[keyID]=0;\
		}\
		else\
		{\
		uiMouseReleased[keyID]=0;\
		uiMousePressed[keyID]=0;\
		}\
	}\
}

extern int uiMousePressed[8];								//indicates whether particulart user interface key has just been pressed but not held
extern int uiMouseHeld[8];									//indicates whether particulart user interface key has just been pressed and held
extern int uiMouseReleased[8];								//indicates whether particulart user interface key has just been released
extern int uiMouseX;										//current cursor X coordinate
extern int uiMouseY;										//current cursor Y coordinate
extern int uiMouseLastX;									//cursor X coordinate last time uiHandler was called
extern int uiMouseLastY;									//cursor Y coordinate last time uiHandler was called
extern int uiMouseWheel;									//mouse wheel action
extern float uiViewerAngleX;
extern float uiViewerAngleY;
extern float uiViewerAngleAutoRotateX;
extern float uiViewerAngleAutoRotateY;
extern int uiLatticeDisplayMode;
extern int uiViewerDistance;
extern int uiLatticeSelectedPlaneX;
extern int uiLatticeSelectedPlaneY;
extern int uiLatticeSelectedPlaneZ;
extern int uiPresetView;
extern int uiCanvasActive;

void uiHandler();
void uiInit();
