
extern int openglCanvasHandle;
extern int openglCanvasHdc;
extern int openglCanvasHeight;
extern int openglCanvasWidth;
extern int openglCanvasResize;
extern int openglSizeX;
extern int openglSizeY;
extern int openglSizeZ;
extern int openglLedSpacing;
extern int openglLedSize;
extern int openglBlackLeds;
extern int openglViewerCenterX;
extern int openglViewerCenterY;
extern int openglViewerDistance;
extern float openglViewerAngleY;
extern float openglViewerAngleX;
extern unsigned char openglVideoBuffer[];
extern int openglRenderQuality;
extern int openglShowBase;
extern int openglShowAxis;
extern int openglShowLattice;

void openglResizeCanvas();
void openglInit();
void openglHandler();
void openglDrawLattice();
void openglDrawAxis();
void openglClearCanvas();




