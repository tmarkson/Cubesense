
void handlerFrmMainLoad(int formMainHandle, int canvasHandle, int formNewHandle, int formScriptSourceHandler);
void handlerFrmMainFormClosing();
void handlerPictureBox1Resize(int height, int width);

extern int handlerCanvasHeight;
extern int handlerCanvasWidth;
extern int handlerCanvasResize;

extern int handlerLedSize;
extern int handlerLedSpacing;
extern int handlerBlackLeds;
extern int handlerRenderQuality;
extern int handlerShowBase;
extern int handlerShowAxis;
extern int handlerShowLattice;
extern int handlerPresetView;
extern int handlerPlaybackCommand;
extern int handlerStopScript;
extern int handlerCanvasActive;
extern int handlerShutDownCoreThread;
extern int handlerUsbControl;
extern int handlerOpeningAnimation;
extern int handlerSaveAnimationFile;
extern char* handlerSaveAnimationFileName;
extern int handlerSaveAnimationFileNameLength;
extern char* handlerAnimationTitle;
extern int handlerAnimationTitleLength;
extern int handlerCreatingAnimation;

#define UNICODE_TEXT(x) ((XTYPE::UCHAR *)(L##x))
namespace XTYPE
{
	typedef wchar_t UCHAR ;
	typedef UCHAR * USTRING ;
};

int handlerAskAboutSavingScript();
int c();
void handlerDisableMainForm();
void handlerEnableMainForm();
void handlerFrmScriptOutputListBox1SelectedIndexChanged(int l);
void handlerNoAnimationTitle();
int handlerAskAboutSavingAnimation();

extern int handlerOpenAnimationFile;
extern char* handlerOpenAnimationFileName;
extern int handlerOpenAnimationFileNameLength;
extern int handlerRealTimeCommand;
